#!/usr/bin/env python3
"""Summarize remaining RedSound objdiff mismatches by likely cause."""

from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path
from typing import Any

from objdiff_experiment import (
    DEFAULT_ATTEMPT_LOG,
    ROOT,
    as_float,
    classify_diff,
    extract_save_range,
    extract_stack_frame,
    instruction_text,
    is_real_symbol_name,
    load_objdiff_json,
    normalize_unit,
    source_path_for_unit,
    symbol_by_name,
)


REDSOUND_UNITS = [
    "RedSound",
    "RedCommand",
    "RedDriver",
    "RedEntry",
    "RedExecute",
    "RedMemory",
    "RedMidiCtrl",
    "RedStream",
]


def short_unit(unit: str) -> str:
    return unit.rsplit("/", 1)[-1]


def truncate(text: str, width: int) -> str:
    if len(text) <= width:
        return text
    return text[: max(0, width - 3)] + "..."


def diff_summary(left: dict[str, Any], right: dict[str, Any]) -> tuple[Counter[str], str]:
    counts: Counter[str] = Counter()
    first_hint = "no diffs"
    left_instructions = left.get("instructions") or []
    right_instructions = right.get("instructions") or []
    max_len = max(len(left_instructions), len(right_instructions))
    for i in range(max_len):
        left_item = left_instructions[i] if i < len(left_instructions) else {}
        right_item = right_instructions[i] if i < len(right_instructions) else {}
        if "diff_kind" not in left_item and "diff_kind" not in right_item:
            continue
        diff_kind = str(left_item.get("diff_kind") or right_item.get("diff_kind") or "DIFF")
        counts[diff_kind] += 1
        if first_hint == "no diffs":
            first_hint = classify_diff(left_item, right_item)
    return counts, first_hint


def category(
    left_frame: str | None,
    right_frame: str | None,
    left_save: str | None,
    right_save: str | None,
    counts: Counter[str],
) -> str:
    structural_count = counts.get("DIFF_INSERT", 0) + counts.get("DIFF_DELETE", 0) + counts.get("DIFF_REPLACE", 0)
    if structural_count:
        return "structural"
    if left_frame != right_frame or left_save != right_save:
        return "stack"
    if counts and set(counts) <= {"DIFF_ARG_MISMATCH"}:
        return "regs"
    if counts:
        return "other"
    return "data"


def summarize_symbol(unit: str, left: dict[str, Any], right: dict[str, Any]) -> dict[str, Any]:
    left_instructions = left.get("instructions") or []
    right_instructions = right.get("instructions") or []
    left_frame = extract_stack_frame(left_instructions)
    right_frame = extract_stack_frame(right_instructions)
    left_save = extract_save_range(left_instructions)
    right_save = extract_save_range(right_instructions)
    counts, first_hint = diff_summary(left, right)
    return {
        "unit": unit,
        "symbol": left.get("name", ""),
        "pct": as_float(left.get("match_percent")),
        "size": int(left.get("size", 0) or 0),
        "diff_count": sum(counts.values()),
        "category": category(left_frame, right_frame, left_save, right_save, counts),
        "frame": f"{left_frame or '?'}->{right_frame or '?'}",
        "save": f"{left_save or '?'}->{right_save or '?'}",
        "counts": ",".join(f"{k.removeprefix('DIFF_')}={v}" for k, v in sorted(counts.items())) or "-",
        "hint": first_hint,
    }


def collect_unit(unit: str, timeout: int) -> list[dict[str, Any]]:
    normalized = normalize_unit(unit)
    raw = load_objdiff_json(normalized, [], timeout)
    left_symbols = symbol_by_name(raw, "left")
    right_symbols = symbol_by_name(raw, "right")
    rows = []
    for name, left in left_symbols.items():
        if not is_real_symbol_name(name):
            continue
        if left.get("match_percent") is None or as_float(left.get("match_percent")) >= 100.0:
            continue
        right = right_symbols.get(name)
        if not right:
            continue
        rows.append(summarize_symbol(normalized, left, right))
    return rows


def print_rows(rows: list[dict[str, Any]], limit: int) -> None:
    if not rows:
        print("No mismatched RedSound symbols found.")
        return

    show_attempts = any(row.get("attempt_count", 0) for row in rows[:limit])
    attempt_header = " attempts" if show_attempts else ""
    print(f"{'cat':<10} {'pct':>8} {'diffs':>5} {'size':>5} {'unit':<11} {'symbol':<55} hint{attempt_header}")
    print("-" * (130 if show_attempts else 120))
    for row in rows[:limit]:
        attempt = ""
        if show_attempts:
            count = row.get("attempt_count", 0)
            if count:
                attempt = f" {count}:{row.get('last_attempt_result', '')}"
        print(
            f"{row['category']:<10} {row['pct']:8.3f} {row['diff_count']:5d} {row['size']:5d} "
            f"{short_unit(row['unit']):<11} {truncate(row['symbol'], 55):<55} {row['hint']}{attempt}"
        )
    if len(rows) > limit:
        print(f"... {len(rows) - limit} more")


def print_detail(rows: list[dict[str, Any]], limit: int) -> None:
    for row in rows[:limit]:
        print(f"\n{row['unit']} :: {row['symbol']}")
        print(f"  {row['category']} {row['pct']:.4f}% size={row['size']}")
        print(f"  total diffs {row['diff_count']}")
        print(f"  frame {row['frame']}")
        print(f"  save  {row['save']}")
        print(f"  diffs {row['counts']}")
        print(f"  hint  {row['hint']}")


def experiment_command(row: dict[str, Any]) -> str:
    unit = short_unit(row["unit"])
    source_path = source_path_for_unit(row["unit"])
    try:
        source_arg = source_path.relative_to(ROOT)
    except ValueError:
        source_arg = source_path
    return (
        f"python3 tools/objdiff_experiment.py -u {unit} {row['symbol']} "
        f"--build --explain --context --limit 8 --window 2 --record-attempt --revert-path {source_arg}"
    )


def print_commands(rows: list[dict[str, Any]], limit: int) -> None:
    if not rows:
        return
    print("\nExperiment commands:")
    for row in rows[:limit]:
        print(f"  {experiment_command(row)}")


def attempt_key(unit: str, symbol: str) -> tuple[str, str]:
    return normalize_unit(unit), symbol


def load_attempts(path: Path) -> dict[tuple[str, str], dict[str, Any]]:
    attempts: dict[tuple[str, str], dict[str, Any]] = {}
    if not path.exists():
        return attempts
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            try:
                entry = json.loads(line)
            except json.JSONDecodeError:
                continue
            unit = normalize_unit(str(entry.get("unit", "")))
            symbols = entry.get("symbols") or [""]
            for symbol in symbols:
                key = (unit, str(symbol))
                current = attempts.setdefault(key, {"count": 0, "last_result": "", "last_note": "", "last_time": ""})
                current["count"] += 1
                current["last_result"] = entry.get("result", "")
                current["last_note"] = entry.get("note", "")
                current["last_time"] = entry.get("timestamp", "")
    return attempts


def annotate_attempts(rows: list[dict[str, Any]], attempts: dict[tuple[str, str], dict[str, Any]]) -> None:
    for row in rows:
        row_attempts = attempts.get(attempt_key(row["unit"], row["symbol"]), {})
        row["attempt_count"] = int(row_attempts.get("count", 0) or 0)
        row["last_attempt_result"] = row_attempts.get("last_result", "")
        row["last_attempt_note"] = row_attempts.get("last_note", "")


def print_attempts(rows: list[dict[str, Any]], limit: int) -> None:
    attempted = [row for row in rows if row.get("attempt_count", 0)]
    if not attempted:
        print("\nAttempts: none recorded for shown rows")
        return
    print("\nAttempts:")
    for row in attempted[:limit]:
        note = f" ({row['last_attempt_note']})" if row.get("last_attempt_note") else ""
        print(
            f"  {short_unit(row['unit'])} {row['symbol']}: "
            f"{row['attempt_count']} attempt(s), last={row['last_attempt_result']}{note}"
        )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-u", "--unit", action="append", help="Limit to one unit. May be repeated.")
    parser.add_argument("--category", choices=["regs", "stack", "structural", "other", "data"], help="Filter category.")
    parser.add_argument("--min-pct", type=float, default=0.0, help="Only show symbols at or above this match percent.")
    parser.add_argument("--max-pct", type=float, default=99.9999, help="Only show symbols below or equal to this percent.")
    parser.add_argument("--limit", type=int, default=80, help="Maximum table rows to print.")
    parser.add_argument(
        "--sort",
        choices=["category", "easy", "pct"],
        default="category",
        help="Sort order. easy ranks fewest diffs first.",
    )
    parser.add_argument("--detail", action="store_true", help="Print frame/save/diff details for shown rows.")
    parser.add_argument("--commands", action="store_true", help="Print ready-to-run objdiff_experiment commands.")
    parser.add_argument("--attempts", action="store_true", help="Show attempt counts from the attempt log.")
    parser.add_argument("--attempt-log", type=Path, default=DEFAULT_ATTEMPT_LOG, help="Attempt log path.")
    parser.add_argument(
        "--fresh",
        action="store_true",
        help="Hide symbols whose latest recorded attempt regressed or made no change.",
    )
    parser.add_argument(
        "--skip-attempt-result",
        action="append",
        choices=["improved", "regressed", "no_change"],
        default=[],
        help="Hide symbols whose latest recorded attempt has this result. May be repeated.",
    )
    parser.add_argument("--objdiff-timeout", type=int, default=60)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    units = args.unit or REDSOUND_UNITS
    rows: list[dict[str, Any]] = []
    for unit in units:
        rows.extend(collect_unit(unit, args.objdiff_timeout))

    rows = [
        row
        for row in rows
        if row["pct"] >= args.min_pct
        and row["pct"] <= args.max_pct
        and (args.category is None or row["category"] == args.category)
    ]
    if args.attempts or args.fresh or args.skip_attempt_result:
        annotate_attempts(rows, load_attempts(args.attempt_log))
    skipped_results = set(args.skip_attempt_result)
    if args.fresh:
        skipped_results.update({"regressed", "no_change"})
    if skipped_results:
        rows = [row for row in rows if row.get("last_attempt_result") not in skipped_results]
    if args.sort == "easy":
        rows.sort(key=lambda row: (row["diff_count"], -row["pct"], row["category"], row["unit"], row["symbol"]))
    elif args.sort == "pct":
        rows.sort(key=lambda row: (-row["pct"], row["diff_count"], row["unit"], row["symbol"]))
    else:
        rows.sort(key=lambda row: (row["category"], -row["pct"], row["diff_count"], row["unit"], row["symbol"]))

    counts = Counter(row["category"] for row in rows)
    if counts:
        print("Category counts: " + ", ".join(f"{key}={counts[key]}" for key in sorted(counts)))
    print_rows(rows, args.limit)
    if args.detail:
        print_detail(rows, args.limit)
    if args.commands:
        print_commands(rows, args.limit)
    if args.attempts:
        print_attempts(rows[: args.limit], args.limit)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
