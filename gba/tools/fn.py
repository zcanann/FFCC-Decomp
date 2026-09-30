#!/usr/bin/env python3
"""Show a GBA function's target assembly and, if it has source, its objdiff result.

    python gba/tools/fn.py mgr AgbMain          # target disassembly + diff
    python gba/tools/fn.py mgr fn_02000234 -a   # target disassembly only
    python gba/tools/fn.py mgr --list 0x02001000 0x02002000   # functions in a range

Run from the repository root after `ninja`. Rebuilds the unit's object first.
"""

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BUILD = ROOT / "build" / "GCCP01" / "gba"
EXE = ".exe" if sys.platform == "win32" else ""


def tool(name):
    local = ROOT / "build" / "tools" / "gba-binutils" / "bin" / f"arm-none-eabi-{name}{EXE}"
    return str(local) if local.exists() else f"arm-none-eabi-{name}"


def symbols(program):
    out = []
    for line in (ROOT / "gba" / "config" / program / "symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) = (\.\w+):0x([0-9A-Fa-f]+); // type:(\w+) size:(0x[0-9A-Fa-f]+)", line)
        if m:
            out.append((int(m.group(3), 16), m.group(1), m.group(2), m.group(4), int(m.group(5), 16)))
    return sorted(out)


def unit_of(program, address):
    unit = None
    for line in (ROOT / "gba" / "config" / program / "splits.txt").read_text().splitlines():
        m = re.match(r"^(\S+):\s*$", line)
        if m:
            unit = m.group(1)
            continue
        m = re.match(r"^\s+\.\w+\s+start:0x([0-9A-F]+)\s+end:0x([0-9A-F]+)", line)
        if m and int(m.group(1), 16) <= address < int(m.group(2), 16):
            return unit
    return None


def disassemble(obj, name):
    text = subprocess.run([tool("objdump"), "-dr", "--no-show-raw-insn", obj], capture_output=True, text=True).stdout
    lines = text.splitlines()
    out = []
    capture = False
    for line in lines:
        if re.match(r"^[0-9a-f]+ <(.+)>:$", line):
            capture = line.endswith(f"<{name}>:")
            if capture:
                out.append(line)
            continue
        if capture:
            out.append(line)
    return "\n".join(out).rstrip()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("program", choices=["cli", "mgr"])
    parser.add_argument("function", nargs="?")
    parser.add_argument("-a", "--asm", action="store_true", help="target assembly only")
    parser.add_argument("--list", nargs=2, metavar=("START", "END"), help="list functions in an address range")
    args = parser.parse_args()

    syms = symbols(args.program)
    if args.list:
        lo, hi = (int(x, 0) for x in args.list)
        for address, name, section, kind, size in syms:
            if kind == "function" and lo <= address < hi:
                print(f"0x{address:08X} {name} size:0x{size:X}")
        return

    match = [s for s in syms if s[1] == args.function]
    if not match:
        sys.exit(f"{args.function} not found in {args.program} symbols")
    address = match[0][0]
    unit = unit_of(args.program, address)
    target = BUILD / args.program / "obj" / f"{unit}.o"
    subprocess.run(["ninja", str(target.relative_to(ROOT)).replace("\\", "/")], cwd=ROOT, capture_output=True)
    print(f"; {args.function} 0x{address:08X} unit {args.program}/{unit}")
    print(disassemble(str(target), args.function))
    if args.asm:
        return

    base = BUILD / args.program / "src" / f"{unit}.o"
    result = subprocess.run(["ninja", str(base.relative_to(ROOT)).replace("\\", "/")], cwd=ROOT,
                            capture_output=True, text=True)
    if result.returncode:
        print(result.stdout[-3000:])
        sys.exit(1)
    objdiff = ROOT / "build" / "tools" / f"objdiff-cli{EXE}"
    diff = subprocess.run([str(objdiff), "diff", "-p", ".", "-u", f"gba/{args.program}/{unit}", "-o", "-",
                           args.function], cwd=ROOT, capture_output=True, text=True)
    data = json.loads(diff.stdout)
    left = [s for s in data["left"]["symbols"] if s.get("name") == args.function]
    right = [s for s in data["right"]["symbols"] if s.get("name") == args.function]
    if not right:
        print("\n; not in compiled source")
        return
    percent = left[0].get("match_percent", 0)
    print(f"\n; match {percent:.2f}%")
    if percent >= 100:
        return
    for a, b in zip(left[0].get("instructions", []), right[0].get("instructions", [])):
        kind = a.get("diff_kind") or b.get("diff_kind") or ""
        la = a.get("instruction", {}).get("formatted", "")
        lb = b.get("instruction", {}).get("formatted", "")
        mark = " " if not kind else "|" if "ARG" in kind else ">" if "INSERT" in kind else "<" if "DELETE" in kind else "!"
        print(f"{la:<44} {mark} {lb}")


if __name__ == "__main__":
    main()
