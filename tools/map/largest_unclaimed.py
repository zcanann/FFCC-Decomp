#!/usr/bin/env python3
from __future__ import annotations

import argparse
import sys
from pathlib import Path

if __package__ in {None, ""}:
    sys.path.append(str(Path(__file__).resolve().parents[2]))
    from tools.map.claim_doctor import SectionDiagnosis, collect_diagnoses
else:
    from .claim_doctor import SectionDiagnosis, collect_diagnoses


DEFAULT_SECTIONS = (".bss", ".data", ".rodata", ".sdata", ".sbss", ".sdata2", ".sbss2")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Rank current unclaimed sections by live compiled size, with PAL/EN MAP hints."
    )
    parser.add_argument(
        "targets",
        nargs="*",
        help="Optional source files to restrict the report to, for example joybus.cpp or goout.cpp.",
    )
    parser.add_argument(
        "--version",
        default="GCCP01",
        help="Project version to analyze. Defaults to GCCP01.",
    )
    parser.add_argument(
        "--top",
        type=int,
        default=25,
        help="How many sections to print. Defaults to 25.",
    )
    parser.add_argument(
        "--sections",
        nargs="+",
        default=list(DEFAULT_SECTIONS),
        help="Sections to include. Defaults to all allocatable data sections.",
    )
    parser.add_argument(
        "--min-size",
        type=int,
        default=1,
        help="Minimum unclaimed compiled size to include. Defaults to 1 byte.",
    )
    return parser.parse_args()


def rank_key(diagnosis: SectionDiagnosis) -> tuple[int, int, int, float, str, str]:
    best_attributed = max(diagnosis.pal_attributed_bytes, diagnosis.en_attributed_bytes)
    map_match_bias = 0
    if diagnosis.pal_map_total == diagnosis.compiled_size or diagnosis.en_map_total == diagnosis.compiled_size:
        map_match_bias = 1
    return (
        diagnosis.unclaimed_compiled_size,
        best_attributed,
        map_match_bias,
        diagnosis.score,
        diagnosis.source_file,
        diagnosis.section,
    )


def format_total(value: int | None) -> str:
    return "n/a" if value is None else str(value)


def print_report(diagnoses: list[SectionDiagnosis], top: int) -> None:
    print("largest_unclaimed")
    print("=================")
    print("Sorted by current live unclaimed size. MAP totals stay heuristic only.")
    print()
    for diagnosis in diagnoses[:top]:
        best_attributed = max(diagnosis.pal_attributed_bytes, diagnosis.en_attributed_bytes)
        print(
            f"{diagnosis.unclaimed_compiled_size:6d} {diagnosis.source_file:24s} {diagnosis.section:8s} "
            f"compiled={diagnosis.compiled_size:6d} claimed={diagnosis.claimed_size:6d} "
            f"attr={best_attributed:6d} score={diagnosis.score:5.1f}"
        )
        print(
            f"  PAL total={format_total(diagnosis.pal_map_total)} "
            f"EN total={format_total(diagnosis.en_map_total)} "
            f"{diagnosis.confidence}: {diagnosis.summary}"
        )
        examples: list[str] = []
        if diagnosis.pal_symbols:
            examples.append(f"PAL: {', '.join(diagnosis.pal_symbols)}")
        if diagnosis.en_symbols:
            examples.append(f"EN: {', '.join(diagnosis.en_symbols)}")
        if examples:
            print(f"  {' | '.join(examples)}")


def main() -> int:
    args = parse_args()
    repo_root = Path(__file__).resolve().parents[2]
    target_sources = {Path(target).name for target in args.targets} if args.targets else None
    diagnoses = collect_diagnoses(repo_root, args.version, target_sources=target_sources)
    wanted_sections = set(args.sections)
    diagnoses = [
        diagnosis
        for diagnosis in diagnoses
        if diagnosis.section in wanted_sections and diagnosis.unclaimed_compiled_size >= args.min_size
    ]
    if not diagnoses:
        print("No unclaimed sections found.")
        return 1

    diagnoses.sort(key=rank_key, reverse=True)
    print_report(diagnoses, args.top)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
