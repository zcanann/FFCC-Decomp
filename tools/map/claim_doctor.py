#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Optional

if __package__ in {None, ""}:
    sys.path.append(str(Path(__file__).resolve().parents[2]))
    from tools.map.map_index import MapIndex, load_map_index, normalize_object_file
else:
    from .map_index import MapIndex, load_map_index, normalize_object_file


SECTION_ORDER = (".bss", ".data", ".rodata", ".sdata", ".sbss", ".sdata2", ".sbss2")
SYMBOL_RE = re.compile(r"(\S+)\s*=\s*(\.\w+):(0x[\da-fA-F]+)\s*;(.*)")
SIZE_RE = re.compile(r"size:(0x[\da-fA-F]+)")
SPLIT_RE = re.compile(r"\s+(\.\w+|extab|extabindex)\s+start:(0x[\da-fA-F]+)\s+end:(0x[\da-fA-F]+)")
OBJDUMP_SECTION_RE = re.compile(r"\s*\d+\s+(\.\S+)\s+([0-9A-Fa-f]+)\s+")


@dataclass(frozen=True)
class ProjectSymbol:
    name: str
    section: str
    address: int
    size: int


@dataclass
class AttributionSummary:
    bytes: int = 0
    symbols: list[str] = None

    def __post_init__(self) -> None:
        if self.symbols is None:
            self.symbols = []

    def add_symbol(self, name: str, size: int) -> None:
        self.bytes += size
        if name not in self.symbols and len(self.symbols) < 5:
            self.symbols.append(name)


@dataclass(frozen=True)
class SectionDiagnosis:
    source_file: str
    object_file: str
    section: str
    compiled_size: int
    claimed_size: int
    unclaimed_compiled_size: int
    pal_map_total: Optional[int]
    en_map_total: Optional[int]
    pal_attributed_bytes: int
    en_attributed_bytes: int
    pal_symbols: tuple[str, ...]
    en_symbols: tuple[str, ...]
    score: float
    confidence: str
    summary: str


def parse_symbols_txt(symbols_path: Path) -> list[ProjectSymbol]:
    results: list[ProjectSymbol] = []
    with symbols_path.open("r", encoding="utf-8") as handle:
        for line in handle:
            stripped = line.strip()
            if not stripped or stripped.startswith("#") or stripped.startswith("//"):
                continue
            match = SYMBOL_RE.match(stripped)
            if not match:
                continue
            size_match = SIZE_RE.search(match.group(4))
            size = int(size_match.group(1), 16) if size_match else 0
            results.append(
                ProjectSymbol(
                    name=match.group(1),
                    section=match.group(2),
                    address=int(match.group(3), 16),
                    size=size,
                )
            )
    return results


def parse_splits(splits_path: Path) -> dict[str, dict[str, list[tuple[int, int]]]]:
    results: dict[str, dict[str, list[tuple[int, int]]]] = {}
    current_file: Optional[str] = None
    with splits_path.open("r", encoding="utf-8") as handle:
        for line in handle:
            stripped = line.rstrip("\n")
            if stripped and not stripped[0].isspace() and stripped.endswith(":") and not stripped.startswith("Sections"):
                current_file = stripped[:-1]
                results.setdefault(current_file, {})
                continue
            if current_file is None:
                continue
            match = SPLIT_RE.match(stripped)
            if not match:
                continue
            results[current_file].setdefault(match.group(1), []).append(
                (int(match.group(2), 16), int(match.group(3), 16))
            )
    return results


def derive_object_file(source_file: str) -> str:
    name = Path(source_file).name
    suffix = Path(name).suffix
    if suffix.lower() == ".o":
        return name
    stem = Path(name).stem if suffix else name
    return f"{stem}.o"


def build_object_path_index(build_src_dir: Path) -> dict[str, Path]:
    index: dict[str, Path] = {}
    if not build_src_dir.exists():
        return index
    for path in build_src_dir.rglob("*.o"):
        index.setdefault(path.name, path)
    return index


def get_compiled_sections(objdump_path: Path, object_path: Path) -> dict[str, int]:
    sections: dict[str, int] = {}
    result = subprocess.run(
        [str(objdump_path), "-h", str(object_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    for line in result.stdout.splitlines():
        match = OBJDUMP_SECTION_RE.match(line)
        if not match:
            continue
        section = match.group(1)
        if section in SECTION_ORDER:
            sections[section] = int(match.group(2), 16)
    return sections


def is_claimed(section_ranges: list[tuple[int, int]], symbol: ProjectSymbol) -> bool:
    return any(start <= symbol.address < end for start, end in section_ranges)


def collect_unclaimed_symbols(
    symbols: list[ProjectSymbol],
    splits: dict[str, dict[str, list[tuple[int, int]]]],
) -> list[ProjectSymbol]:
    claimed_by_section: dict[str, list[tuple[int, int]]] = defaultdict(list)
    for sections in splits.values():
        for section, ranges in sections.items():
            claimed_by_section[section].extend(ranges)

    results: list[ProjectSymbol] = []
    for symbol in symbols:
        if not is_claimed(claimed_by_section.get(symbol.section, []), symbol):
            results.append(symbol)
    return results


def build_attribution_table(
    map_index: MapIndex,
    unclaimed_symbols: list[ProjectSymbol],
) -> dict[str, dict[str, AttributionSummary]]:
    table: dict[str, dict[str, AttributionSummary]] = defaultdict(lambda: defaultdict(AttributionSummary))
    for symbol in unclaimed_symbols:
        layout_records = map_index.layout_records_for_symbol(symbol.name, symbol.section)
        object_files = {record.object_file for record in layout_records}
        if len(object_files) == 1:
            object_file = next(iter(object_files))
        else:
            found_in_records = map_index.found_in_records_for_symbol(symbol.name)
            object_files = {
                normalize_object_file(record.container)
                for record in found_in_records
                if record.container.lower().endswith(".o")
            }
            if len(object_files) == 1:
                object_file = next(iter(object_files))
            else:
                source_objects = {
                    derive_object_file(record.source_file)
                    for record in found_in_records
                    if record.source_file
                }
                if len(source_objects) != 1:
                    continue
                object_file = next(iter(source_objects))
        summary = table[object_file][symbol.section]
        summary.add_symbol(symbol.name, symbol.size)
    return table


def diagnose_section(
    source_file: str,
    object_file: str,
    section: str,
    compiled_size: int,
    claimed_size: int,
    pal_map_total: Optional[int],
    en_map_total: Optional[int],
    pal_attr: AttributionSummary,
    en_attr: AttributionSummary,
) -> SectionDiagnosis:
    unclaimed_compiled_size = max(compiled_size - claimed_size, 0)
    pal_attributed_bytes = pal_attr.bytes if pal_attr else 0
    en_attributed_bytes = en_attr.bytes if en_attr else 0

    best_attributed = max(pal_attributed_bytes, en_attributed_bytes)
    best_total: Optional[int] = None
    total_diffs = [abs(compiled_size - total) for total in (pal_map_total, en_map_total) if total is not None]
    if pal_map_total is not None and (
        best_total is None or abs(compiled_size - pal_map_total) <= abs(compiled_size - best_total)
    ):
        best_total = pal_map_total
    if en_map_total is not None and (
        best_total is None or abs(compiled_size - en_map_total) < abs(compiled_size - best_total)
    ):
        best_total = en_map_total

    confidence = "low"
    summary = "weak hint only"
    score = 0.0

    if unclaimed_compiled_size > 0:
        coverage = min(best_attributed / unclaimed_compiled_size, 1.0) if best_attributed else 0.0
        score += coverage * 100.0

    if total_diffs:
        score += max(0.0, 20.0 - min(total_diffs))

    if (
        pal_map_total is not None
        and en_map_total is not None
        and pal_map_total == en_map_total
        and pal_map_total > 0
    ):
        score += 10.0

    if unclaimed_compiled_size > 0 and best_attributed == unclaimed_compiled_size:
        confidence = "high" if pal_attributed_bytes == en_attributed_bytes == unclaimed_compiled_size else "medium"
        summary = "direct claim candidate: attributed current symbols match the unclaimed compiled size exactly"
        score += 30.0
    elif unclaimed_compiled_size > 0 and best_attributed > 0 and abs(unclaimed_compiled_size - best_attributed) <= 16:
        delta = best_attributed - unclaimed_compiled_size
        confidence = "medium"
        summary = f"near claim candidate: attributed current symbols are off by {delta:+d} bytes"
        score += 20.0
    elif compiled_size > 0 and best_total is not None and abs(compiled_size - best_total) <= 16:
        delta = compiled_size - best_total
        confidence = "medium"
        summary = f"near old-map total: current build is off the MAP by {delta:+d} bytes"
        score += 15.0
    elif claimed_size > compiled_size and compiled_size > 0:
        delta = claimed_size - compiled_size
        confidence = "medium"
        summary = f"claimed range is larger than the current build by {delta:+d} bytes"
        score += 15.0
    elif unclaimed_compiled_size > 0 and best_attributed > 0:
        confidence = "low"
        summary = "partial attribution: some current unclaimed symbols map back to this object"
        score += 10.0
    elif compiled_size > 0 and best_total is not None:
        delta = compiled_size - best_total
        confidence = "low"
        summary = f"old MAP suggests a section total within {delta:+d} bytes of the current build"
        score += 5.0

    return SectionDiagnosis(
        source_file=source_file,
        object_file=object_file,
        section=section,
        compiled_size=compiled_size,
        claimed_size=claimed_size,
        unclaimed_compiled_size=unclaimed_compiled_size,
        pal_map_total=pal_map_total,
        en_map_total=en_map_total,
        pal_attributed_bytes=pal_attributed_bytes,
        en_attributed_bytes=en_attributed_bytes,
        pal_symbols=tuple(pal_attr.symbols if pal_attr else ()),
        en_symbols=tuple(en_attr.symbols if en_attr else ()),
        score=score,
        confidence=confidence,
        summary=summary,
    )


def collect_diagnoses(
    repo_root: Path,
    version: str,
    target_sources: Optional[set[str]] = None,
) -> list[SectionDiagnosis]:
    config_root = repo_root / "config" / version
    build_root = repo_root / "build" / version
    symbols = parse_symbols_txt(config_root / "symbols.txt")
    splits = parse_splits(config_root / "splits.txt")
    unclaimed_symbols = collect_unclaimed_symbols(symbols, splits)

    pal_path = repo_root / "orig" / "GCCP01" / "game.MAP"
    en_path = repo_root / "orig" / "GCCE01" / "game.MAP"
    pal_index = load_map_index(pal_path, label="PAL") if pal_path.exists() else None
    en_index = load_map_index(en_path, label="EN") if en_path.exists() else None

    pal_attribution = build_attribution_table(pal_index, unclaimed_symbols) if pal_index else {}
    en_attribution = build_attribution_table(en_index, unclaimed_symbols) if en_index else {}

    object_paths = build_object_path_index(build_root / "src")
    objdump_path = repo_root / "build" / "binutils" / "powerpc-eabi-objdump.exe"

    diagnoses: list[SectionDiagnosis] = []
    for source_file, sections in splits.items():
        source_basename = Path(source_file).name
        if target_sources is not None and source_basename not in target_sources:
            continue

        object_file = derive_object_file(source_basename)
        object_path = object_paths.get(object_file)
        if object_path is None or not objdump_path.exists():
            continue

        compiled_sections = get_compiled_sections(objdump_path, object_path)
        for section in SECTION_ORDER:
            compiled_size = compiled_sections.get(section, 0)
            claimed_size = sum(end - start for start, end in sections.get(section, []))
            pal_total = pal_index.object_section_size(object_file, section) if pal_index else None
            en_total = en_index.object_section_size(object_file, section) if en_index else None
            pal_attr = pal_attribution.get(object_file, {}).get(section, AttributionSummary())
            en_attr = en_attribution.get(object_file, {}).get(section, AttributionSummary())

            if compiled_size == 0 and claimed_size == 0 and pal_total is None and en_total is None:
                continue

            diagnosis = diagnose_section(
                source_basename,
                object_file,
                section,
                compiled_size,
                claimed_size,
                pal_total,
                en_total,
                pal_attr,
                en_attr,
            )
            if (
                target_sources is not None
                and diagnosis.compiled_size == 0
                and diagnosis.claimed_size == 0
                and diagnosis.pal_attributed_bytes == 0
                and diagnosis.en_attributed_bytes == 0
            ):
                continue
            if target_sources is None and diagnosis.score <= 0.0:
                continue
            diagnoses.append(diagnosis)

    diagnoses.sort(key=lambda entry: (-entry.score, entry.source_file, entry.section))
    return diagnoses


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Conservative MAP-backed diagnostics for section claim and linkage work."
    )
    parser.add_argument(
        "targets",
        nargs="*",
        help="Source files to inspect, for example map.cpp or p_menu.cpp.",
    )
    parser.add_argument(
        "--version",
        default="GCCP01",
        help="Project version to analyze. Defaults to GCCP01.",
    )
    parser.add_argument(
        "--top",
        type=int,
        default=15,
        help="How many ranked opportunities to print when no targets are given.",
    )
    return parser.parse_args()


def print_target_report(diagnoses: list[SectionDiagnosis]) -> None:
    grouped: dict[str, list[SectionDiagnosis]] = defaultdict(list)
    for diagnosis in diagnoses:
        grouped[diagnosis.source_file].append(diagnosis)

    print("claim_doctor")
    print("============")
    print("MAP totals are heuristic only. Objdiff and the current build stay authoritative.")
    print()

    for source_file in sorted(grouped):
        entries = grouped[source_file]
        print(f"{source_file} ({entries[0].object_file})")
        for diagnosis in sorted(entries, key=lambda item: SECTION_ORDER.index(item.section)):
            print(
                f"  {diagnosis.section}: compiled={diagnosis.compiled_size} claimed={diagnosis.claimed_size} "
                f"unclaimed_build={diagnosis.unclaimed_compiled_size}"
            )
            pal_total = diagnosis.pal_map_total if diagnosis.pal_map_total is not None else "n/a"
            en_total = diagnosis.en_map_total if diagnosis.en_map_total is not None else "n/a"
            print(
                f"    PAL total={pal_total} PAL attributed={diagnosis.pal_attributed_bytes} "
                f"EN total={en_total} EN attributed={diagnosis.en_attributed_bytes}"
            )
            print(f"    {diagnosis.confidence}: {diagnosis.summary}")
            if diagnosis.pal_symbols:
                print(f"    PAL examples: {', '.join(diagnosis.pal_symbols)}")
            if diagnosis.en_symbols:
                print(f"    EN examples: {', '.join(diagnosis.en_symbols)}")
        print()


def print_ranked_report(diagnoses: list[SectionDiagnosis], top: int) -> None:
    print("claim_doctor")
    print("============")
    print("MAP totals are heuristic only. Objdiff and the current build stay authoritative.")
    print()
    for diagnosis in diagnoses[:top]:
        print(
            f"{diagnosis.source_file:24s} {diagnosis.section:8s} score={diagnosis.score:5.1f} "
            f"{diagnosis.confidence:6s} {diagnosis.summary}"
        )
        print(
            f"  compiled={diagnosis.compiled_size} claimed={diagnosis.claimed_size} "
            f"unclaimed_build={diagnosis.unclaimed_compiled_size} "
            f"pal_total={diagnosis.pal_map_total if diagnosis.pal_map_total is not None else 'n/a'} "
            f"en_total={diagnosis.en_map_total if diagnosis.en_map_total is not None else 'n/a'} "
            f"pal_attr={diagnosis.pal_attributed_bytes} en_attr={diagnosis.en_attributed_bytes}"
        )
        examples = []
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
    if not diagnoses:
        print("No diagnoses found.")
        return 1

    if target_sources is not None:
        print_target_report(diagnoses)
    else:
        print_ranked_report(diagnoses, args.top)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
