#!/usr/bin/env python3
"""Capture, build, and compare objdiff scores for quick matching experiments."""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_TIMEOUT_SECONDS = 30
EPSILON = 0.0001
DEFAULT_ATTEMPT_LOG = ROOT / "build" / "agent" / "objdiff_experiments.jsonl"


def normalize_unit(unit: str) -> str:
    if "/" in unit or "\\" in unit:
        return unit.replace("\\", "/")
    if unit.startswith("Red"):
        return f"main/RedSound/{unit}"
    return f"main/{unit}"


def find_objdiff() -> Path:
    candidates = [
        ROOT / "build" / "tools" / "objdiff-cli.exe",
        ROOT / "build" / "tools" / "objdiff-cli",
        ROOT / "tools" / "objdiff-cli.exe",
        ROOT / "tools" / "objdiff-cli",
    ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    raise FileNotFoundError("objdiff-cli not found; run tools/download_tool.py or ninja first")


def run_command(cmd: list[str], timeout: int, *, check: bool = True) -> subprocess.CompletedProcess[str]:
    result = subprocess.run(
        cmd,
        cwd=ROOT,
        capture_output=True,
        text=True,
        timeout=timeout,
    )
    if check and result.returncode != 0:
        print(result.stdout, end="")
        print(result.stderr, end="", file=sys.stderr)
        raise SystemExit(result.returncode)
    return result


def run_ninja(timeout: int) -> bool:
    print(f"Running ninja (timeout {timeout}s)...")
    try:
        result = run_command(["ninja"], timeout, check=False)
    except subprocess.TimeoutExpired:
        print(f"ninja timed out after {timeout}s", file=sys.stderr)
        return False

    if result.returncode != 0:
        print(result.stdout, end="")
        print(result.stderr, end="", file=sys.stderr)
        print(f"ninja failed with exit code {result.returncode}", file=sys.stderr)
        return False

    for line in result.stdout.splitlines():
        if line.startswith("Progress:") or "RedSound:" in line or "build/GCCP01/main.dol:" in line:
            print(line)
    return True


def load_objdiff_json(unit: str, symbols: list[str], timeout: int) -> dict[str, Any]:
    objdiff = find_objdiff()
    with tempfile.NamedTemporaryFile(prefix="objdiff_experiment_", suffix=".json", delete=False) as tmp:
        tmp_path = Path(tmp.name)

    cmd = [str(objdiff), "diff", "-p", ".", "-u", unit, "-o", str(tmp_path), "--format", "json"]
    cmd.extend(symbols)
    try:
        run_command(cmd, timeout, check=True)
        with tmp_path.open("r", encoding="utf-8") as f:
            return json.load(f)
    finally:
        try:
            tmp_path.unlink()
        except FileNotFoundError:
            pass


def as_float(value: Any) -> float:
    try:
        return float(value)
    except (TypeError, ValueError):
        return 0.0


def compact_snapshot(unit: str, symbols_filter: list[str], raw: dict[str, Any]) -> dict[str, Any]:
    left = raw.get("left", {})

    def compact_items(items: list[dict[str, Any]]) -> dict[str, dict[str, Any]]:
        out: dict[str, dict[str, Any]] = {}
        for item in items:
            name = item.get("name")
            if not name:
                continue
            out[name] = {
                "size": int(item.get("size", 0) or 0),
                "match_percent": as_float(item.get("match_percent")),
            }
        return out

    return {
        "schema": 1,
        "unit": unit,
        "symbols_filter": symbols_filter,
        "captured_at": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "complete": bool(left.get("complete", False)),
        "match_percent": as_float(left.get("match_percent")),
        "sections": compact_items(left.get("sections", [])),
        "symbols": compact_items(left.get("symbols", [])),
    }


def capture_snapshot(unit: str, symbols: list[str], timeout: int) -> dict[str, Any]:
    raw = load_objdiff_json(unit, symbols, timeout)
    return compact_snapshot(unit, symbols, raw)


def symbol_by_name(raw: dict[str, Any], side: str) -> dict[str, dict[str, Any]]:
    return {symbol.get("name", ""): symbol for symbol in raw.get(side, {}).get("symbols", []) if symbol.get("name")}


def instruction_text(item: dict[str, Any]) -> str:
    instruction = item.get("instruction")
    if not instruction:
        return "<gap>"
    return str(instruction.get("formatted", "<unknown>"))


def mnemonic(item: dict[str, Any]) -> str:
    instruction = item.get("instruction") or {}
    parts = instruction.get("parts") or []
    if parts and isinstance(parts[0], dict):
        opcode = parts[0].get("opcode")
        if isinstance(opcode, dict):
            return str(opcode.get("mnemonic", ""))
    text = instruction_text(item)
    return text.split(maxsplit=1)[0] if text != "<gap>" else ""


def extract_stack_frame(instructions: list[dict[str, Any]]) -> str | None:
    for item in instructions[:8]:
        text = instruction_text(item)
        match = re.match(r"stwu r1, (-?0x[0-9a-f]+|-?\d+)\(r1\)", text)
        if match:
            return match.group(1)
    return None


def extract_save_range(instructions: list[dict[str, Any]]) -> str | None:
    for item in instructions[:16]:
        text = instruction_text(item)
        match = re.match(r"stmw (r\d+), (0x[0-9a-f]+|-?\d+)\(r1\)", text)
        if match:
            return f"{match.group(1)}..r31 at {match.group(2)}"
    saved = []
    for item in instructions[:24]:
        text = instruction_text(item)
        match = re.match(r"stw (r\d+), (0x[0-9a-f]+|-?\d+)\(r1\)", text)
        if match and match.group(1) != "r0":
            saved.append(f"{match.group(1)}@{match.group(2)}")
    return ", ".join(saved) if saved else None


def classify_diff(left_item: dict[str, Any], right_item: dict[str, Any]) -> str:
    left_text = instruction_text(left_item)
    right_text = instruction_text(right_item)
    left_mnemonic = mnemonic(left_item)
    right_mnemonic = mnemonic(right_item)
    if left_text == "<gap>" or right_text == "<gap>":
        return "insert/delete"
    if left_mnemonic != right_mnemonic:
        return "opcode/control-flow shape"
    if left_mnemonic in {"cmpwi", "cmplwi", "cmpw", "cmplw"}:
        return "signedness/compare shape"
    if left_mnemonic in {"lwz", "lhz", "lha", "lbz", "stw", "sth", "stb"}:
        return "load/store register or offset"
    if left_mnemonic.startswith("b"):
        return "branch target/structure"
    if left_mnemonic in {"mr", "addi", "add", "subf", "mullw", "srawi", "srwi", "slwi", "rlwinm"}:
        return "register allocation/expression shape"
    if left_mnemonic in {"stwu", "stmw", "lmw"}:
        return "stack frame/saved register pressure"
    return "argument/register mismatch"


def print_instruction_window(
    left_instructions: list[dict[str, Any]],
    right_instructions: list[dict[str, Any]],
    center: int,
    radius: int,
) -> None:
    start = max(0, center - radius)
    end = min(max(len(left_instructions), len(right_instructions)), center + radius + 1)
    for index in range(start, end):
        left_item = left_instructions[index] if index < len(left_instructions) else {}
        right_item = right_instructions[index] if index < len(right_instructions) else {}
        marker = "!" if "diff_kind" in left_item or "diff_kind" in right_item else " "
        print(f"        {marker}[{index:03d}] ours:   {instruction_text(left_item)}")
        print(f"         [{index:03d}] target: {instruction_text(right_item)}")


def explain_symbol(left: dict[str, Any], right: dict[str, Any], limit: int, window: int) -> None:
    name = left.get("name") or right.get("name") or "<unknown>"
    match = left.get("match_percent")
    size = left.get("size") or right.get("size")
    print(f"\nExplanation: {name} ({as_float(match):.4f}%, {size}b)")

    left_instructions = left.get("instructions") or []
    right_instructions = right.get("instructions") or []
    left_frame = extract_stack_frame(left_instructions)
    right_frame = extract_stack_frame(right_instructions)
    if left_frame or right_frame:
        print(f"  stack frame: ours {left_frame or '?'} / target {right_frame or '?'}")

    left_save = extract_save_range(left_instructions)
    right_save = extract_save_range(right_instructions)
    if left_save or right_save:
        print(f"  saved regs:  ours {left_save or '?'} / target {right_save or '?'}")

    diff_counts: dict[str, int] = {}
    rows: list[tuple[int, str, str, str]] = []
    max_len = max(len(left_instructions), len(right_instructions))
    for i in range(max_len):
        left_item = left_instructions[i] if i < len(left_instructions) else {}
        right_item = right_instructions[i] if i < len(right_instructions) else {}
        if "diff_kind" not in left_item and "diff_kind" not in right_item:
            continue
        diff_kind = str(left_item.get("diff_kind") or right_item.get("diff_kind") or "DIFF")
        diff_counts[diff_kind] = diff_counts.get(diff_kind, 0) + 1
        if len(rows) < limit:
            rows.append((i, classify_diff(left_item, right_item), instruction_text(left_item), instruction_text(right_item)))

    if diff_counts:
        counts = ", ".join(f"{key}={value}" for key, value in sorted(diff_counts.items()))
        print(f"  diff kinds: {counts}")
    else:
        print("  no instruction diffs")
        return

    print("  first diffs:")
    for index, hint, left_text, right_text in rows:
        print(f"    [{index:03d}] {hint}")
        print(f"          ours:   {left_text}")
        print(f"          target: {right_text}")
        if window > 0:
            print_instruction_window(left_instructions, right_instructions, index, window)


def explain_current_diff(unit: str, symbols: list[str], timeout: int, limit: int, window: int) -> None:
    raw = load_objdiff_json(unit, symbols, timeout)
    left_symbols = symbol_by_name(raw, "left")
    right_symbols = symbol_by_name(raw, "right")
    names = symbols or unmatched_symbol_names(left_symbols)
    for name in names:
        left = left_symbols.get(name)
        right = right_symbols.get(name)
        if not left or not right:
            print(f"\nExplanation: {name}: symbol not present on both sides")
            continue
        explain_symbol(left, right, limit, window)


def is_real_symbol_name(name: str) -> bool:
    return not name.startswith("@") and not name.startswith("[")


def unmatched_symbol_names(symbols: dict[str, dict[str, Any]]) -> list[str]:
    return [
        name
        for name, symbol in symbols.items()
        if symbol.get("match_percent") is not None
        and as_float(symbol.get("match_percent")) < 100.0
        and is_real_symbol_name(name)
    ]


def source_path_for_unit(unit: str) -> Path:
    parts = unit.split("/")
    if parts and parts[0] == "main":
        parts = parts[1:]
    return ROOT / "src" / Path(*parts).with_suffix(".cpp")


def map_hits(symbol: str, map_name: str, limit: int) -> list[tuple[int, str]]:
    path = ROOT / "orig" / map_name / "game.MAP"
    if not path.exists():
        return []
    hits: list[tuple[int, str]] = []
    with path.open("r", encoding="utf-8", errors="replace") as f:
        for lineno, line in enumerate(f, start=1):
            if symbol in line:
                hits.append((lineno, line.rstrip()))
                if len(hits) >= limit:
                    break
    return hits


def ghidra_hits(symbol: str, limit: int) -> list[Path]:
    ghidra_dir = ROOT / "resources" / "ghidra-decomp-1-31-2026"
    if not ghidra_dir.exists():
        return []
    hits = [path for path in ghidra_dir.glob("*.c") if symbol in path.name]
    return sorted(hits)[:limit]


def print_context(unit: str, symbols: list[str], limit: int) -> None:
    print("\nContext")
    source_path = source_path_for_unit(unit)
    if source_path.exists():
        print(f"  source: {source_path.relative_to(ROOT)}")
    else:
        print(f"  source: {source_path.relative_to(ROOT)} (missing)")

    for symbol in symbols:
        print(f"\n  {symbol}")
        for map_name, label in (("GCCP01", "PAL"), ("GCCE01", "EN")):
            hits = map_hits(symbol, map_name, limit)
            if hits:
                print(f"    {label} MAP:")
                for lineno, text in hits:
                    print(f"      {map_name}/game.MAP:{lineno}: {text.strip()}")
            else:
                print(f"    {label} MAP: no hit")
        hits = ghidra_hits(symbol, limit)
        if hits:
            print("    Ghidra:")
            for path in hits:
                print(f"      {path.relative_to(ROOT)}")
        else:
            print("    Ghidra: no filename hit")


def save_snapshot(path: Path, snapshot: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        json.dump(snapshot, f, indent=2, sort_keys=True)
        f.write("\n")
    print(f"Saved baseline: {path}")


def load_snapshot(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as f:
        snapshot = json.load(f)
    if snapshot.get("schema") != 1:
        raise SystemExit(f"unsupported snapshot schema in {path}")
    return snapshot


def pct(value: float) -> str:
    return f"{value:8.4f}%"


def compare_group(before: dict[str, Any], after: dict[str, Any], key: str) -> list[tuple[str, int, int, float, float]]:
    out: list[tuple[str, int, int, float, float]] = []
    before_items = before.get(key, {})
    after_items = after.get(key, {})
    for name in sorted(set(before_items) | set(after_items)):
        b = before_items.get(name, {})
        a = after_items.get(name, {})
        before_pct = as_float(b.get("match_percent"))
        after_pct = as_float(a.get("match_percent"))
        before_size = int(b.get("size", 0) or 0)
        after_size = int(a.get("size", 0) or 0)
        if abs(after_pct - before_pct) > EPSILON or before_size != after_size:
            out.append((name, before_size, after_size, before_pct, after_pct))
    return out


def print_changes(title: str, changes: list[tuple[str, int, int, float, float]], limit: int) -> None:
    if not changes:
        print(f"{title}: no changes")
        return

    print(title)
    print("  delta      before      after       size  name")
    sorted_changes = sorted(changes, key=lambda row: (row[4] - row[3], row[0]))
    for name, before_size, after_size, before_pct, after_pct in sorted_changes[:limit]:
        delta = after_pct - before_pct
        size = f"{before_size}" if before_size == after_size else f"{before_size}->{after_size}"
        print(f"  {delta:+8.4f}  {pct(before_pct)}  {pct(after_pct)}  {size:>9}  {name}")
    if len(changes) > limit:
        print(f"  ... {len(changes) - limit} more")


def has_regression(changes: list[tuple[str, int, int, float, float]]) -> bool:
    return any(after_pct + EPSILON < before_pct for _, _, _, before_pct, after_pct in changes)


def has_progress(changes: list[tuple[str, int, int, float, float]]) -> bool:
    return any(after_pct > before_pct + EPSILON for _, _, _, before_pct, after_pct in changes)


def serialize_changes(changes: list[tuple[str, int, int, float, float]]) -> list[dict[str, Any]]:
    return [
        {
            "name": name,
            "before_size": before_size,
            "after_size": after_size,
            "before_pct": before_pct,
            "after_pct": after_pct,
            "delta": after_pct - before_pct,
        }
        for name, before_size, after_size, before_pct, after_pct in changes
    ]


def record_attempt(
    path: Path,
    unit: str,
    symbols: list[str],
    result: str,
    section_changes: list[tuple[str, int, int, float, float]],
    symbol_changes: list[tuple[str, int, int, float, float]],
    note: str | None,
) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    entry = {
        "timestamp": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "unit": unit,
        "symbols": symbols,
        "result": result,
        "note": note or "",
        "sections": serialize_changes(section_changes),
        "symbols_changed": serialize_changes(symbol_changes),
    }
    with path.open("a", encoding="utf-8") as f:
        json.dump(entry, f, sort_keys=True)
        f.write("\n")
    print(f"Recorded attempt: {path}")


def restore_paths(paths: list[Path]) -> None:
    if not paths:
        return
    cmd = ["git", "restore", "--worktree", "--staged", "--"]
    cmd.extend(str(path) for path in paths)
    print("Reverting explicit paths after regression:")
    for path in paths:
        print(f"  {path}")
    run_command(cmd, DEFAULT_TIMEOUT_SECONDS, check=True)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Capture, build, and compare objdiff scores for a unit/symbol experiment.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=(
            "Examples:\n"
            "  python3 tools/objdiff_experiment.py -u RedStream --save .agent/redstream.base.json\n"
            "  python3 tools/objdiff_experiment.py -u RedStream StreamControl__Fv --build --explain --context\n"
            "  python3 tools/objdiff_experiment.py -u main/RedSound/RedExecute SetReverb__FiiPi --baseline .agent/rev.json --build\n"
        ),
    )
    parser.add_argument("symbols", nargs="*", help="Optional symbol filters passed to objdiff-cli.")
    parser.add_argument("-u", "--unit", required=True, help="Objdiff unit, e.g. RedStream or main/RedSound/RedStream.")
    parser.add_argument("--save", type=Path, help="Save the current objdiff snapshot and exit.")
    parser.add_argument("--baseline", type=Path, help="Compare against a snapshot produced by --save.")
    parser.add_argument("--build", action="store_true", help="Run ninja before capturing the after snapshot.")
    parser.add_argument("--ninja-timeout", type=int, default=DEFAULT_TIMEOUT_SECONDS, help="ninja timeout in seconds.")
    parser.add_argument("--objdiff-timeout", type=int, default=60, help="objdiff-cli timeout in seconds.")
    parser.add_argument("--limit", type=int, default=30, help="Maximum changed rows to print per group.")
    parser.add_argument("--explain", action="store_true", help="Print a compact instruction mismatch summary.")
    parser.add_argument("--window", type=int, default=0, help="Instruction context radius for --explain diffs.")
    parser.add_argument("--context", action="store_true", help="Print source, PAL/EN MAP, and Ghidra context.")
    parser.add_argument(
        "--revert-path",
        action="append",
        type=Path,
        default=[],
        help="Explicit path to git-restore if a regression is detected. May be repeated.",
    )
    parser.add_argument(
        "--no-rebuild-after-revert",
        action="store_false",
        dest="rebuild_after_revert",
        help="Do not run ninja again after an automatic regression revert.",
    )
    parser.add_argument(
        "--record-attempt",
        action="store_true",
        help=f"Append experiment result to {DEFAULT_ATTEMPT_LOG.relative_to(ROOT)}.",
    )
    parser.add_argument("--attempt-log", type=Path, default=DEFAULT_ATTEMPT_LOG, help="Attempt log path.")
    parser.add_argument("--note", help="Short note to store with --record-attempt.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    unit = normalize_unit(args.unit)
    symbols = list(args.symbols)

    if args.save and args.baseline:
        raise SystemExit("--save and --baseline are mutually exclusive")

    if args.save:
        snapshot = capture_snapshot(unit, symbols, args.objdiff_timeout)
        save_snapshot(args.save, snapshot)
        return 0

    if args.baseline:
        before = load_snapshot(args.baseline)
        if before.get("unit") != unit:
            print(f"warning: baseline unit {before.get('unit')} differs from requested unit {unit}", file=sys.stderr)
    else:
        print("Capturing before snapshot from current build...")
        before = capture_snapshot(unit, symbols, args.objdiff_timeout)

    if args.build and not run_ninja(args.ninja_timeout):
        return 1

    print("Capturing after snapshot...")
    after = capture_snapshot(unit, symbols, args.objdiff_timeout)

    section_changes = compare_group(before, after, "sections")
    symbol_changes = compare_group(before, after, "symbols")

    print(f"Unit: {unit}")
    if symbols:
        print(f"Symbols: {', '.join(symbols)}")
    print_changes("Sections", section_changes, args.limit)
    print_changes("Symbols", symbol_changes, args.limit)
    if args.explain:
        explain_current_diff(unit, symbols, args.objdiff_timeout, args.limit, args.window)
    if args.context:
        context_symbols = symbols or unmatched_symbol_names(after.get("symbols", {}))
        print_context(unit, context_symbols, args.limit)

    regressed = has_regression(section_changes) or has_regression(symbol_changes)
    progressed = has_progress(section_changes) or has_progress(symbol_changes)
    result = "regressed" if regressed else "improved" if progressed else "no_change"
    if args.record_attempt:
        record_attempt(args.attempt_log, unit, symbols, result, section_changes, symbol_changes, args.note)
    if regressed and args.revert_path:
        restore_paths(args.revert_path)
        if args.rebuild_after_revert and not run_ninja(args.ninja_timeout):
            return 1
    return 2 if regressed else 0


if __name__ == "__main__":
    raise SystemExit(main())
