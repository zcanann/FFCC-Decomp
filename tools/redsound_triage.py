#!/usr/bin/env python3
"""Summarize remaining RedSound objdiff mismatches by likely cause."""

from __future__ import annotations

import argparse
import json
import re
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
    mnemonic,
    normalize_unit,
    run_ninja,
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

SIZE_BUCKETS = [
    ("tiny", 0, 64),
    ("small", 65, 256),
    ("medium", 257, 768),
    ("large", 769, 1536),
    ("huge", 1537, None),
]

ATTEMPT_RESULT_RANK = {
    "": 0,
    "improved": 1,
    "no_change": 2,
    "regressed": 3,
}

CONTEXT_ATTEMPT_NOTE_PREFIXES = (
    "baseline context",
)


def short_unit(unit: str) -> str:
    return unit.rsplit("/", 1)[-1]


def truncate(text: str, width: int) -> str:
    if len(text) <= width:
        return text
    return text[: max(0, width - 3)] + "..."


def size_bucket(size: int) -> str:
    for name, start, end in SIZE_BUCKETS:
        if size >= start and (end is None or size <= end):
            return name
    return "unknown"


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


def diff_instruction_pairs(left: dict[str, Any], right: dict[str, Any]) -> list[tuple[int, dict[str, Any], dict[str, Any]]]:
    pairs: list[tuple[int, dict[str, Any], dict[str, Any]]] = []
    left_instructions = left.get("instructions") or []
    right_instructions = right.get("instructions") or []
    max_len = max(len(left_instructions), len(right_instructions))
    for i in range(max_len):
        left_item = left_instructions[i] if i < len(left_instructions) else {}
        right_item = right_instructions[i] if i < len(right_instructions) else {}
        if "diff_kind" in left_item or "diff_kind" in right_item:
            pairs.append((i, left_item, right_item))
    return pairs


def is_save_restore_only(left: dict[str, Any], right: dict[str, Any]) -> bool:
    pairs = diff_instruction_pairs(left, right)
    if len(pairs) != 2:
        return False
    return all(
        mnemonic(left_item) == mnemonic(right_item) and mnemonic(left_item) in {"stmw", "lmw"}
        for _, left_item, right_item in pairs
    )


def has_param_spill_mismatch(left: dict[str, Any], right: dict[str, Any]) -> bool:
    pairs = diff_instruction_pairs(left, right)
    for index, left_item, right_item in pairs:
        if index > 16:
            break
        left_text = instruction_text(left_item)
        right_text = instruction_text(right_item)
        if right_text.startswith("stw r4, ") and left_text != right_text:
            return True
        if left_text.startswith("stw r4, ") and left_text != right_text:
            return True
    return False


def has_target_only_counter(left: dict[str, Any], right: dict[str, Any]) -> bool:
    """Detect target-side locals that look like a simple dead/diagnostic counter."""
    pairs = diff_instruction_pairs(left, right)
    target_only = [
        (index, instruction_text(left_item))
        for index, left_item, right_item in pairs
        if instruction_text(right_item) == "<gap>"
    ]
    regs = set()
    for _, text in target_only:
        match = re.fullmatch(r"li (r(?:2[0-9]|3[0-1])), 0x0", text)
        if match:
            regs.add(match.group(1))
    for reg in regs:
        if any(text == f"addi {reg}, {reg}, 0x1" for _, text in target_only):
            return True
    return False


def operands(item: dict[str, Any]) -> list[str]:
    text = instruction_text(item)
    if text == "<gap>" or " " not in text:
        return []
    return [part.strip() for part in text.split(None, 1)[1].split(",")]


def mismatch_patterns(
    left: dict[str, Any],
    right: dict[str, Any],
    left_frame: str | None,
    right_frame: str | None,
    left_save: str | None,
    right_save: str | None,
) -> list[str]:
    patterns: list[str] = []
    if is_save_restore_only(left, right):
        patterns.append("save-only")
    if has_param_spill_mismatch(left, right):
        patterns.append("param-spill")
    if has_target_only_counter(left, right):
        patterns.append("target-counter")
    if left_frame != right_frame or left_save != right_save:
        patterns.append("stack")

    left_instructions = left.get("instructions") or []
    right_instructions = right.get("instructions") or []
    max_len = max(len(left_instructions), len(right_instructions))
    has_shape = False
    has_regs = False
    for i in range(max_len):
        left_item = left_instructions[i] if i < len(left_instructions) else {}
        right_item = right_instructions[i] if i < len(right_instructions) else {}
        if "diff_kind" not in left_item and "diff_kind" not in right_item:
            continue
        left_text = instruction_text(left_item)
        right_text = instruction_text(right_item)
        if left_text == "<gap>" or right_text == "<gap>":
            has_shape = True
            continue

        left_mnemonic = mnemonic(left_item)
        right_mnemonic = mnemonic(right_item)
        if {left_mnemonic, right_mnemonic} == {"srawi", "srwi"}:
            patterns.append("signed-shift")
        elif {left_mnemonic, right_mnemonic} & {"cmpwi", "cmplwi", "cmpw", "cmplw"} and left_mnemonic != right_mnemonic:
            patterns.append("signed-compare")
        elif left_mnemonic != right_mnemonic:
            has_shape = True
        else:
            left_ops = operands(left_item)
            right_ops = operands(right_item)
            if (
                left_mnemonic in {"add", "addi", "mullw", "slwi", "srawi", "srwi"}
                and len(left_ops) >= 2
                and len(right_ops) >= 2
                and left_ops[0] in left_ops[1:]
                and right_ops[0] not in right_ops[1:]
            ):
                patterns.append("temp-result")
            elif left_ops != right_ops:
                has_regs = True

    if has_shape:
        patterns.append("shape")
    if has_regs:
        patterns.append("regs")
    return sorted(set(patterns))


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
    patterns = mismatch_patterns(left, right, left_frame, right_frame, left_save, right_save)
    row = {
        "unit": unit,
        "symbol": left.get("name", ""),
        "pct": as_float(left.get("match_percent")),
        "size": int(left.get("size", 0) or 0),
        "current_size": int(right.get("size", 0) or 0),
        "diff_count": sum(counts.values()),
        "category": category(left_frame, right_frame, left_save, right_save, counts),
        "frame": f"{left_frame or '?'}->{right_frame or '?'}",
        "save": f"{left_save or '?'}->{right_save or '?'}",
        "counts": ",".join(f"{k.removeprefix('DIFF_')}={v}" for k, v in sorted(counts.items())) or "-",
        "hint": first_hint,
        "patterns": ",".join(patterns) or "-",
    }
    row["bucket"] = size_bucket(row["size"])
    return row


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


def object_path_for_unit(unit: str) -> Path:
    normalized = normalize_unit(unit)
    parts = normalized.split("/")
    if parts[:2] == ["main", "RedSound"] and len(parts) == 3:
        return ROOT / "build" / "GCCP01" / "src" / "RedSound" / f"{parts[2]}.o"
    if parts[:1] == ["main"] and len(parts) == 2:
        return ROOT / "build" / "GCCP01" / "src" / f"{parts[1]}.o"
    return ROOT / "build" / "GCCP01" / "src" / f"{short_unit(normalized)}.o"


def stale_build_warnings(units: list[str]) -> list[str]:
    warnings: list[str] = []
    for unit in units:
        normalized = normalize_unit(unit)
        source_path = source_path_for_unit(normalized)
        object_path = object_path_for_unit(normalized)
        if not source_path.exists():
            continue
        if not object_path.exists():
            warnings.append(f"{short_unit(normalized)} has no object artifact yet; run with --build for fresh scores")
            continue
        if source_path.stat().st_mtime > object_path.stat().st_mtime + 0.001:
            warnings.append(
                f"{short_unit(normalized)} source is newer than {object_path.relative_to(ROOT)}; "
                "scores may be stale, run with --build"
            )
    return warnings


def print_rows(rows: list[dict[str, Any]], limit: int) -> None:
    if not rows:
        print("No mismatched RedSound symbols found.")
        return

    show_attempts = any(row.get("attempt_count", 0) for row in rows[:limit])
    attempt_header = " attempts" if show_attempts else ""
    print(
        f"{'cat':<10} {'pct':>8} {'diffs':>5} {'size':>9} {'unit':<11} "
        f"{'symbol':<55} {'patterns':<28} hint{attempt_header}"
    )
    print("-" * (160 if show_attempts else 150))
    for row in rows[:limit]:
        attempt = ""
        if show_attempts:
            count = row.get("attempt_count", 0)
            if count:
                attempt = f" {count}:{row.get('last_attempt_result', '')}"
        print(
            f"{row['category']:<10} {row['pct']:8.3f} {row['diff_count']:5d} "
            f"{row['size']:4d}/{row['current_size']:<4d} "
            f"{short_unit(row['unit']):<11} {truncate(row['symbol'], 55):<55} "
            f"{truncate(row['patterns'], 28):<28} {row['hint']}{attempt}"
        )
    if len(rows) > limit:
        print(f"... {len(rows) - limit} more")


def select_bucket_rows(rows: list[dict[str, Any]], per_bucket: int) -> list[dict[str, Any]]:
    selected: list[dict[str, Any]] = []
    for name, _, _ in SIZE_BUCKETS:
        bucket_rows = [row for row in rows if row["bucket"] == name]
        bucket_rows.sort(key=lambda row: (row["diff_count"], -row["pct"], row["category"], row["unit"], row["symbol"]))
        selected.extend(bucket_rows[:per_bucket])
    return selected


def print_buckets(rows: list[dict[str, Any]], per_bucket: int) -> list[dict[str, Any]]:
    if not rows:
        print("No mismatched RedSound symbols found.")
        return []

    selected = select_bucket_rows(rows, per_bucket)
    for name, _, _ in SIZE_BUCKETS:
        bucket_rows = [row for row in selected if row["bucket"] == name]
        if not bucket_rows:
            continue
        print(f"\n{name}:")
        print_rows(bucket_rows, len(bucket_rows))
    return selected


def print_detail(rows: list[dict[str, Any]], limit: int) -> None:
    for row in rows[:limit]:
        print(f"\n{row['unit']} :: {row['symbol']}")
        print(f"  {row['category']} {row['pct']:.4f}% size target/current={row['size']}/{row['current_size']}")
        print(f"  total diffs {row['diff_count']}")
        print(f"  frame {row['frame']}")
        print(f"  save  {row['save']}")
        print(f"  diffs {row['counts']}")
        print(f"  patt  {row['patterns']}")
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
        f"--build --explain --context --limit 8 --window 2 --record-attempt "
        f"--revert-path {source_arg} --revert-no-change"
    )


def print_commands(rows: list[dict[str, Any]], limit: int) -> None:
    if not rows:
        return
    print("\nExperiment commands:")
    for row in rows[:limit]:
        print(f"  {experiment_command(row)}")


def attempt_key(unit: str, symbol: str) -> tuple[str, str]:
    return normalize_unit(unit), symbol


def is_context_attempt(entry: dict[str, Any]) -> bool:
    note = str(entry.get("note", "")).strip().lower()
    return any(note.startswith(prefix) for prefix in CONTEXT_ATTEMPT_NOTE_PREFIXES)


def load_attempts(path: Path, include_context: bool = False) -> dict[tuple[str, str], dict[str, Any]]:
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
            if not include_context and is_context_attempt(entry):
                continue
            unit = normalize_unit(str(entry.get("unit", "")))
            symbols = entry.get("symbols") or [""]
            for symbol in symbols:
                key = (unit, str(symbol))
                current = attempts.setdefault(
                    key,
                    {
                        "count": 0,
                        "last_result": "",
                        "last_note": "",
                        "last_time": "",
                        "results": Counter(),
                        "history": [],
                    },
                )
                current["count"] += 1
                result = entry.get("result", "")
                current["last_result"] = result
                current["last_note"] = entry.get("note", "")
                current["last_time"] = entry.get("timestamp", "")
                if result:
                    current["results"][result] += 1
                current["history"].append(
                    {
                        "result": result,
                        "note": entry.get("note", ""),
                        "timestamp": entry.get("timestamp", ""),
                    }
                )
    return attempts


def annotate_attempts(rows: list[dict[str, Any]], attempts: dict[tuple[str, str], dict[str, Any]]) -> None:
    for row in rows:
        row_attempts = attempts.get(attempt_key(row["unit"], row["symbol"]), {})
        row["attempt_count"] = int(row_attempts.get("count", 0) or 0)
        row["last_attempt_result"] = row_attempts.get("last_result", "")
        row["last_attempt_note"] = row_attempts.get("last_note", "")
        row["last_attempt_time"] = row_attempts.get("last_time", "")
        results = row_attempts.get("results", Counter())
        row["attempt_results"] = dict(results)
        row["attempt_history"] = list(row_attempts.get("history", []))


def print_attempts(rows: list[dict[str, Any]], limit: int, history_limit: int = 0) -> None:
    attempted = [row for row in rows if row.get("attempt_count", 0)]
    if not attempted:
        print("\nAttempts: none recorded for shown rows")
        return
    print("\nAttempts:")
    for row in attempted[:limit]:
        note = f" ({row['last_attempt_note']})" if row.get("last_attempt_note") else ""
        results = row.get("attempt_results", {})
        result_summary = ""
        if results:
            result_summary = " [" + ", ".join(f"{key}={results[key]}" for key in sorted(results)) + "]"
        print(
            f"  {short_unit(row['unit'])} {row['symbol']}: "
            f"{row['attempt_count']} attempt(s){result_summary}, last={row['last_attempt_result']}{note}"
        )
        if history_limit > 0:
            history = row.get("attempt_history", [])[-history_limit:]
            for entry in history:
                entry_note = entry.get("note", "")
                entry_result = entry.get("result", "")
                timestamp = entry.get("timestamp", "")
                when = f" {timestamp}" if timestamp else ""
                print(f"    - {entry_result}{when}: {entry_note}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-u", "--unit", action="append", help="Limit to one unit. May be repeated.")
    parser.add_argument("--category", choices=["regs", "stack", "structural", "other", "data"], help="Filter category.")
    parser.add_argument("--pattern", action="append", help="Only show symbols whose pattern list includes this value.")
    parser.add_argument("--min-pct", type=float, default=0.0, help="Only show symbols at or above this match percent.")
    parser.add_argument("--max-pct", type=float, default=99.9999, help="Only show symbols below or equal to this percent.")
    parser.add_argument("--limit", type=int, default=80, help="Maximum table rows to print.")
    parser.add_argument(
        "--sort",
        choices=["attempts", "category", "easy", "pct", "size-delta", "symbol", "symbols", "unit"],
        default="category",
        help=(
            "Sort order. attempts ranks least-tried symbols first; easy ranks fewest diffs first; "
            "size-delta ranks target/current size gaps."
        ),
    )
    parser.add_argument("--detail", action="store_true", help="Print frame/save/diff details for shown rows.")
    parser.add_argument("--commands", action="store_true", help="Print ready-to-run objdiff_experiment commands.")
    parser.add_argument("--attempts", action="store_true", help="Show attempt counts from the attempt log.")
    parser.add_argument(
        "--attempt-history",
        type=int,
        default=0,
        help="With --attempts, show the last N attempt notes for each displayed symbol.",
    )
    parser.add_argument("--attempt-log", type=Path, default=DEFAULT_ATTEMPT_LOG, help="Attempt log path.")
    parser.add_argument(
        "--include-context-attempts",
        action="store_true",
        help="Count baseline/context-only objdiff captures as attempts.",
    )
    parser.add_argument("--min-attempts", type=int, help="Only show symbols with at least this many recorded attempts.")
    parser.add_argument("--max-attempts", type=int, help="Only show symbols with at most this many recorded attempts.")
    parser.add_argument(
        "--buckets",
        action="store_true",
        help="Show the easiest symbols per function-size bucket after applying filters.",
    )
    parser.add_argument("--bucket-limit", type=int, default=3, help="Rows to show per size bucket with --buckets.")
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
    parser.add_argument(
        "--require-attempt-result",
        action="append",
        choices=["improved", "regressed", "no_change"],
        default=[],
        help="Only show symbols with at least one recorded attempt of this result. May be repeated.",
    )
    parser.add_argument("--build", action="store_true", help="Run ninja before collecting objdiff rows.")
    parser.add_argument("--ninja-timeout", type=int, default=30, help="ninja timeout in seconds for --build.")
    parser.add_argument(
        "--no-stale-warning",
        action="store_true",
        help="Do not warn when source files are newer than the compiled object artifacts.",
    )
    parser.add_argument("--objdiff-timeout", type=int, default=60)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.build and not run_ninja(args.ninja_timeout):
        return 1
    units = args.unit or REDSOUND_UNITS
    if not args.build and not args.no_stale_warning:
        warnings = stale_build_warnings(units)
        if warnings:
            print("Stale build warning:")
            for warning in warnings:
                print(f"  {warning}")
    rows: list[dict[str, Any]] = []
    for unit in units:
        rows.extend(collect_unit(unit, args.objdiff_timeout))

    rows = [
        row
        for row in rows
        if row["pct"] >= args.min_pct
        and row["pct"] <= args.max_pct
        and (args.category is None or row["category"] == args.category)
        and (args.pattern is None or all(pattern in row["patterns"].split(",") for pattern in args.pattern))
    ]
    needs_attempts = (
        args.attempts
        or args.sort == "attempts"
        or args.fresh
        or args.skip_attempt_result
        or args.require_attempt_result
        or args.min_attempts is not None
        or args.max_attempts is not None
    )
    if needs_attempts:
        annotate_attempts(rows, load_attempts(args.attempt_log, include_context=args.include_context_attempts))
    if args.min_attempts is not None:
        rows = [row for row in rows if row.get("attempt_count", 0) >= args.min_attempts]
    if args.max_attempts is not None:
        rows = [row for row in rows if row.get("attempt_count", 0) <= args.max_attempts]
    skipped_results = set(args.skip_attempt_result)
    if args.fresh:
        skipped_results.update({"regressed", "no_change"})
    if skipped_results:
        rows = [row for row in rows if row.get("last_attempt_result") not in skipped_results]
    if args.require_attempt_result:
        required_results = set(args.require_attempt_result)
        rows = [
            row
            for row in rows
            if required_results <= {result for result, count in row.get("attempt_results", {}).items() if count}
        ]
    if args.sort == "easy":
        rows.sort(key=lambda row: (row["diff_count"], -row["pct"], row["category"], row["unit"], row["symbol"]))
    elif args.sort == "attempts":
        rows.sort(
            key=lambda row: (
                row.get("attempt_count", 0),
                ATTEMPT_RESULT_RANK.get(row.get("last_attempt_result", ""), 9),
                row["diff_count"],
                -row["pct"],
                row["unit"],
                row["symbol"],
            )
        )
    elif args.sort == "pct":
        rows.sort(key=lambda row: (-row["pct"], row["diff_count"], row["unit"], row["symbol"]))
    elif args.sort == "size-delta":
        rows.sort(
            key=lambda row: (
                -abs(row["size"] - row["current_size"]),
                row["diff_count"],
                -row["pct"],
                row["unit"],
                row["symbol"],
            )
        )
    elif args.sort in {"symbol", "symbols"}:
        rows.sort(key=lambda row: (row["symbol"], row["unit"], row["diff_count"], -row["pct"]))
    elif args.sort == "unit":
        rows.sort(key=lambda row: (row["unit"], row["symbol"], row["diff_count"], -row["pct"]))
    else:
        rows.sort(key=lambda row: (row["category"], -row["pct"], row["diff_count"], row["unit"], row["symbol"]))

    counts = Counter(row["category"] for row in rows)
    if counts:
        print("Category counts: " + ", ".join(f"{key}={counts[key]}" for key in sorted(counts)))
    shown_rows = print_buckets(rows, args.bucket_limit) if args.buckets else rows[: args.limit]
    if not args.buckets:
        print_rows(rows, args.limit)
    if args.detail:
        print_detail(shown_rows, len(shown_rows))
    if args.commands:
        print_commands(shown_rows, len(shown_rows))
    if args.attempts:
        print_attempts(shown_rows, len(shown_rows), args.attempt_history)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
