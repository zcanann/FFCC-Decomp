#!/usr/bin/env python3
"""Capture, build, and compare objdiff scores for quick matching experiments."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_TIMEOUT_SECONDS = 30
EPSILON = 0.0001


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
            "  python3 tools/objdiff_experiment.py -u RedStream StreamControl__Fv --build\n"
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
    parser.add_argument(
        "--revert-path",
        action="append",
        type=Path,
        default=[],
        help="Explicit path to git-restore if a regression is detected. May be repeated.",
    )
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

    regressed = has_regression(section_changes) or has_regression(symbol_changes)
    if regressed and args.revert_path:
        restore_paths(args.revert_path)
    return 2 if regressed else 0


if __name__ == "__main__":
    raise SystemExit(main())
