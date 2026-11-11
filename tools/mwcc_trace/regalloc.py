#!/usr/bin/env python3
"""Show how GC/2.5 colored one function's registers (macOS, LLDB + Wibo).

Compiles the unit twice from its ninja command: once normally and once under a
private LLDB session that reads the allocator's interference graph, simplified
stack and final colors. The two objects must be byte-identical.

    python3 tools/mwcc_trace/regalloc.py -u main/menu_letter -f LetterListDraw__8CMenuPcsFv
    python3 tools/mwcc_trace/regalloc.py -u main/menu_letter -f LetterListDraw__8CMenuPcsFv --class fpr --json out.json
    python3 tools/mwcc_trace/regalloc.py -u main/menu_letter -f LetterMessDraw__8CMenuPcsFv --compare --search

Rows are listed in coloring order (first row is colored first). "pass" is the
simplification scan that removed the node, replayed from the captured graph
("sN" marks a node pushed by spill-cost selection after scan N); nodes removed
later had higher degree and are colored earlier.
Callee-saved registers are claimed from the top (r31, r30, ...), and each node
takes the lowest-numbered claimed register its neighbors leave free.

--compare (needs a link name) aligns the captured pre-rewrite PCode with
our emitted instructions and reads the retail register at the same operand, so
each virtual register that differs from retail is named. Instruction streams
must already agree apart from registers.

--search replays simplify/select offline and hill-climbs the order of named
locals (vreg numbering follows reverse declaration order), aiming for the
retail registers from --compare. It explores numbering only: edges, temps and
split ranges are fixed, so treat a result as a candidate to compile and diff.
"""

import argparse
import difflib
import hashlib
import random
import re
import json
import os
from pathlib import Path
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
import gc25

CLASS_IDS = {"gpr": 4, "fpr": 3}


def unit_command(unit):
    project = json.loads((ROOT / "objdiff.json").read_text())
    entry = next((u for u in project["units"] if u["name"] == unit), None)
    if entry is None or not entry.get("base_path"):
        raise SystemExit(f"unit {unit!r} has no compiled source object in objdiff.json")
    obj = entry["base_path"]
    lines = subprocess.run(["ninja", "-t", "commands", obj], cwd=ROOT, capture_output=True,
                           text=True, check=True).stdout.strip().splitlines()
    command = shlex.split(lines[-1].split(" && ")[0])
    compiler = next(i for i, arg in enumerate(command) if arg.endswith("mwcceppc.exe"))
    args = command[compiler + 1:]
    if "GC/2.5/" not in command[compiler]:
        raise SystemExit(f"{unit} is not built with GC/2.5 ({command[compiler]})")
    output = args.index("-o")
    del args[output:output + 2]
    args = [a for a in args if a != "-MMD"]
    return command[compiler], args


def ordinary(compiler, args, out_dir):
    subprocess.run([str(ROOT / "build/tools/wibo"), compiler, *args, "-o", str(out_dir)],
                   cwd=ROOT, check=True, capture_output=True)


def stop_debugservers(debugger_pid):
    """Rosetta starts debugserver with --setsid; kill only our descendants."""
    try:
        output = subprocess.run(["ps", "-axo", "pid=,ppid=,comm="], capture_output=True,
                                text=True, timeout=2).stdout
        processes = {}
        for line in output.splitlines():
            fields = line.split(None, 2)
            if len(fields) == 3 and fields[0].isdigit() and fields[1].isdigit():
                processes[int(fields[0])] = (int(fields[1]), fields[2])
        owned = {debugger_pid}
        while True:
            children = {pid for pid, (parent, _) in processes.items() if parent in owned and pid not in owned}
            if not children:
                break
            owned |= children
        for pid in owned - {debugger_pid}:
            if Path(processes[pid][1]).name == "debugserver":
                try:
                    os.kill(pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
    except (OSError, subprocess.TimeoutExpired):
        pass


def traced(compiler, args, out_dir, functions, timeout, wibo):
    if sys.platform != "darwin":
        raise SystemExit("allocator capture needs macOS LLDB and Wibo")
    if hashlib.sha256((ROOT / compiler).read_bytes()).hexdigest() != gc25.COMPILER_SHA256:
        raise SystemExit("compiler does not match the GC/2.5 capture profile")
    lldb = shutil.which("lldb")
    if not lldb:
        raise SystemExit("lldb is not installed")
    with tempfile.TemporaryDirectory(prefix="mwcc-regalloc-") as scratch:
        scratch = Path(scratch)
        result, pid, job = scratch / "capture.json", scratch / "pid", scratch / "job.json"
        job.write_text(json.dumps({"functions": sorted(functions), "result": str(result), "pid": str(pid)}))
        steps = ["settings set target.disable-aslr false",
                 "breakpoint set --func-regex loadPEFromSource", "run", "breakpoint disable 1",
                 "thread step-out", "command script import " + json.dumps(str(HERE / "lldb_provider.py")),
                 f"script lldb_provider._install(lldb.debugger, {str(job)!r})", "continue",
                 "script lldb_provider._finish(lldb.debugger)"]
        argv = [lldb, "--batch", "--one-line-on-crash", "process kill"]
        for step in steps:
            argv += ["-o", step]
        argv += ["--", str(wibo), compiler, *args, "-o", str(out_dir)]
        with tempfile.TemporaryFile(mode="w+") as log:
            process = subprocess.Popen(argv, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT,
                                       start_new_session=True)
            try:
                process.wait(timeout=timeout)
            except subprocess.TimeoutExpired:
                stop_debugservers(process.pid)
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()
                raise SystemExit(f"capture exceeded {timeout}s")
            finally:
                stop_debugservers(process.pid)
            log.seek(0)
            text = log.read()
        if process.returncode or not result.exists():
            raise SystemExit("LLDB capture failed:\n" + text[-4000:])
        return json.loads(result.read_text())


def replay_simplify(graph, available, scan=None, spill=None, cutoff=None):
    """Replay GC/2.5 simplify (0x508D40); returns ({register: pass}, push order, unresolved).

    Each scan visits nodes in vreg order and removes those with degree < K.
    When a scan removes nothing, the remaining node with the lowest
    spill cost / degree is pushed (the list is walked from the highest vreg;
    nodes at or above the spill cutoff never qualify) and scanning resumes.
    Without spill costs that path cannot be replayed and the rest is returned.
    """
    degree = {n["virtual"]: n["degree"] for n in graph}
    done = {n["virtual"] for n in graph if n["flags"] & 6}
    scan = scan if scan is not None else [n["virtual"] for n in graph[32:]]
    passes, pushed, step = {}, [], 0

    def sweep():
        nonlocal step
        while True:
            step += 1
            remaining, removed = [], False
            for register in scan:
                if register in done:
                    continue
                if degree[register] < available:
                    for neighbor in graph[register]["neighbors"]:
                        degree[neighbor] -= 1
                    done.add(register)
                    passes[register] = step
                    pushed.append(register)
                    removed = True
                else:
                    remaining.insert(0, register)
            if not removed:
                return remaining

    remaining = sweep()
    while remaining and spill is not None:
        cost = lambda r: float("inf") if r >= cutoff else spill[r] / degree[r]
        best = min(remaining, key=lambda r: (cost(r), remaining.index(r)))
        for neighbor in graph[best]["neighbors"]:
            degree[neighbor] -= 1
        done.add(best)
        passes[best] = f"s{step}"
        pushed.append(best)
        remaining = sweep()
    return passes, pushed, remaining


def replay_select(graph, order, available):
    """Replay color selection: volatile colors first, callee-saved claimed r31 downward."""
    physical = {n["virtual"]: (n["physical"] if n["virtual"] < 32 else -1) for n in graph}
    colors = {r for r in available if r < 14}           # volatile: r0/r3-r12, f0-f13
    reserve = [r for r in range(31, 13, -1) if r in available]
    for register in order:
        used = {physical[n] for n in graph[register]["neighbors"] if 0 <= physical[n] < 32}
        free = sorted(colors - used)
        if free:
            physical[register] = free[0]
        elif reserve:
            physical[register] = reserve.pop(0)
            colors.add(physical[register])
    return physical


def objdiff_instructions(unit, symbol):
    output = subprocess.run([str(ROOT / "build/tools/objdiff-cli"), "diff", "-p", ".", "-u", unit, "-o", "-", symbol],
                            cwd=ROOT, capture_output=True, text=True, check=True).stdout
    sides = json.loads(output)

    def side(key):
        entry = next((s for s in sides[key]["symbols"] if s["name"] == symbol), None)
        if entry is None:
            raise SystemExit(f"{symbol} not found in objdiff output for {unit}")
        return [i.get("instruction", {}).get("formatted") for i in entry["instructions"]]

    return [(t, o) for t, o in zip(side("left"), side("right")) if t and o]


def opcode_family(mnemonic):
    aliases = {"extrwi": 0x67, "clrlslwi": 0x67, "rotrwi": 0x67, "inslwi": 0x69, "subi": 0x3F, "subis": 0x42,
               "bne": 0x08, "bge": 0x08, "ble": 0x08, "beq": 0x05, "blt": 0x05, "bgt": 0x05}
    if not hasattr(opcode_family, "table"):
        opcode_family.table = {}
        for opcode, spellings in gc25.OPCODES.items():
            for spelling in spellings.split():
                opcode_family.table.setdefault(spelling.rstrip("+-"), opcode)
    name = mnemonic.rstrip("+-")
    if name in aliases:
        return aliases[name]
    return opcode_family.table.get(name, opcode_family.table.get(name.rstrip("."), name))


def compare(rewrite, unit, symbol, register_class=4):
    """{virtual register: set of retail registers} for one class's operands, via PCode alignment."""
    physical = {n["virtual"]: n["physical"] for n in rewrite["graph"]}
    pcode = [i for block in rewrite["pcode"] for i in block]
    pairs = objdiff_instructions(unit, symbol)
    ours = [opcode_family(o.split()[0]) for _, o in pairs]
    matcher = difflib.SequenceMatcher(None, [i["opcode"] for i in pcode], ours, autojunk=False)
    prefix = "r" if register_class == 4 else "f"
    regs = lambda text: [int(r) for r in re.findall(r"\b" + prefix + r"(\d+)\b", text)]
    observed, aligned = {}, 0
    for a, b, size in matcher.get_matching_blocks():
        for k in range(size):
            target, mine = pairs[b + k]
            if len(regs(target)) != len(regs(mine)):
                continue
            aligned += 1
            for operand in pcode[a + k]["operands"]:
                virtual = (operand.get("number", -1)
                           if operand.get("kind") == 0 and operand.get("class") == register_class else -1)
                if virtual >= 32 and physical[virtual] in regs(mine):
                    observed.setdefault(virtual, set()).add(regs(target)[regs(mine).index(physical[virtual])])
    return observed, aligned, len(pcode)


def search(graph, colored, colors, targets, spill=None, cutoff=None, restarts=40):
    """Hill-climb named-local numbering toward targets; returns (score, total, declaration order, misses)."""
    named = [n["virtual"] for n in graph[33:] if n["object_name"] and not n["object_name"].startswith("@")
             and not n["flags"] & 6]
    named = [v for v in named if v < min([n["virtual"] for n in graph[33:]
                                          if (n["object_name"] or "").startswith("@")] or [len(graph)])]
    rest = [v for v in range(33, len(graph)) if v not in named]
    check = [v for v in range(32, len(graph)) if not graph[v]["flags"] & 6]
    goal = {n["virtual"]: n["physical"] for n in colored}
    goal.update(targets)

    def evaluate(scan):
        _, pushed, remaining = replay_simplify(graph, len(colors), [32] + scan + rest, spill, cutoff)
        if remaining:
            return -1, None
        result = replay_select(graph, list(reversed(pushed)), colors)
        return sum(result[v] == goal[v] for v in check), result

    random.seed(1)
    best_scan, best_score = list(named), evaluate(list(named))[0]
    for attempt in range(restarts):
        scan = list(named) if attempt == 0 else random.sample(named, len(named))
        score = evaluate(scan)[0]
        improved = True
        while improved:
            improved = False
            for i in range(len(scan)):
                for j in range(len(scan)):
                    if i != j:
                        candidate = scan[:]
                        candidate.insert(j, candidate.pop(i))
                        value = evaluate(candidate)[0]
                        if value > score:
                            scan, score, improved = candidate, value, True
        if score > best_score:
            best_scan, best_score = scan, score
        if best_score == len(check):
            break
    _, result = evaluate(best_scan)
    if result is None:
        raise SystemExit("search: the no-spill replay does not complete for this graph")
    misses = {v: (result[v], goal[v]) for v in check if result[v] != goal[v]}
    return best_score, len(check), [graph[v]["object_name"] + f" (v{v})" for v in reversed(best_scan)], misses


def describe(node):
    return node["object_name"] or "-"


def report(capture, function, register_class, show_all, unit=None, symbol=None, want_compare=False,
           want_search=False):
    events = [e for e in capture["events"] if e["name"] == function and e["register_class"] == register_class]
    simplify = [e for e in events if e["hook"] == "simplify"]
    color = [e for e in events if e["hook"] == "color"]
    rewrite = [e for e in events if e["hook"] == "rewrite"]
    if not simplify or not color or not rewrite:
        raise SystemExit(f"no {register_class=} allocation captured for {function}")
    if len(simplify) > 1:
        print(f"note: {len(simplify)} allocation attempts (spill retries); showing the last")
    graph, order, colored = simplify[-1]["graph"], color[-1]["order"], rewrite[-1]["graph"]
    available = len(simplify[-1]["available"])
    spill = color[-1].get("spill_costs")
    cutoff = simplify[-1].get("spill_cutoff")
    passes, pushed, remaining = replay_simplify(graph, available, None, spill, cutoff)
    replay_ok = not remaining and list(reversed(pushed)) == order
    prefix = "r" if register_class == 4 else "f"
    print(f"{function}: {len(graph) - 32} virtual registers, K={available}, "
          f"simplify replay {'matches capture' if replay_ok else 'DIFFERS (spill path?)'}")
    print(f"{'#':>3} {'vreg':>5} {'reg':>4} {'deg':>4} {'nbrs':>4} {'pass':>4}  object")
    for rank, register in enumerate(order):
        node, final = graph[register], colored[register]
        physical = final["physical"]
        callee = physical >= (14 if register_class == 4 else 14)
        if not show_all and not callee:
            continue
        print(f"{rank:>3} {register:>5} {prefix}{physical:<3} {node['degree']:>4} "
              f"{len(node['neighbors']):>4} {passes.get(register, '-'):>4}  {describe(node)}")
    if not (want_compare or want_search):
        return
    if not symbol:
        raise SystemExit("--compare/--search need a link name (-f Foo__3BarFv)")
    observed, aligned, total = compare(rewrite[-1], unit, symbol, register_class)
    final = {n["virtual"]: n["physical"] for n in colored}
    differing = {v: regs for v, regs in observed.items() if regs != {final[v]}}
    print(f"\nretail comparison: {aligned} of {total} PCode instructions aligned")
    for virtual in sorted(differing):
        print(f"  vreg {virtual:>4} {describe(graph[virtual]):16} ours {prefix}{final[virtual]}  retail "
              + ", ".join(f"{prefix}{r}" for r in sorted(differing[virtual])))
    if not differing:
        print("  no register differences on aligned instructions")
    if want_search and not replay_ok:
        print("\nsearch skipped: the captured allocation does not follow the replayed no-spill path")
    elif want_search:
        targets = {v: next(iter(r)) for v, r in differing.items() if len(r) == 1}
        score, total, declaration, misses = search(graph, colored, simplify[-1]["available"], targets, spill, cutoff)
        print(f"\nsearch: best {score}/{total} nodes match; named locals in declaration order:")
        print("  " + ", ".join(declaration))
        for virtual, (got, want) in sorted(misses.items()):
            print(f"  still differs: vreg {virtual} {describe(graph[virtual])} {prefix}{got} (retail {prefix}{want})")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-u", "--unit", required=True)
    parser.add_argument("-f", "--function", required=True,
                        help="function name; a link name (Foo__3BarFv) is reduced to Foo")
    parser.add_argument("--class", dest="register_class", choices=CLASS_IDS, default="gpr")
    parser.add_argument("--all", action="store_true", help="include nodes colored to volatile registers")
    parser.add_argument("--json", type=Path, help="write the raw capture here")
    parser.add_argument("--compare", action="store_true", help="name virtual registers that differ from retail")
    parser.add_argument("--search", action="store_true", help="search named-local order toward retail registers")
    parser.add_argument("--timeout", type=int, default=180)
    parser.add_argument("--wibo", type=Path, default=ROOT / "build/tools/wibo",
                        help="Wibo used for the traced compile (default: the project's)")
    args = parser.parse_args()

    name = args.function.split("__")[0] if "__" in args.function[1:] else args.function
    compiler, flags = unit_command(args.unit)
    with tempfile.TemporaryDirectory(prefix="mwcc-regalloc-out-") as out:
        out = Path(out)
        (out / "ordinary").mkdir()
        (out / "traced").mkdir()
        ordinary(compiler, flags, out / "ordinary")
        capture = traced(compiler, flags, out / "traced", [name], args.timeout, args.wibo.resolve())
        objects = [sorted((out / kind).glob("*.o")) for kind in ("ordinary", "traced")]
        if len(objects[0]) != 1 or len(objects[1]) != 1 or objects[0][0].read_bytes() != objects[1][0].read_bytes():
            raise SystemExit("traced compile did not reproduce the ordinary object; capture rejected")
    if args.json:
        args.json.write_text(json.dumps(capture))
    if capture["functions"].count(name) > 1:
        print(f"note: {capture['functions'].count(name)} functions named {name}; showing the last compiled")
    symbol = args.function if "__" in args.function[1:] else None
    report(capture, name, CLASS_IDS[args.register_class], args.all, args.unit, symbol,
           args.compare, args.search)


if __name__ == "__main__":
    main()
