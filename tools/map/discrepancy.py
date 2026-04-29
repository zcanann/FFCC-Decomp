#!/usr/bin/env python3
"""MAP discrepancy tool.

Compares the locally emitted MAP (``build/GCCP01/main.elf.MAP``) against the
shipped PAL (``orig/GCCP01/game.MAP``) and EN (``orig/GCCE01/game.MAP``) MAPs,
scoped to a single object file (``pppRandUpFV.o``) or stem (``pppRandUpFV``).

Highlights:

* missing ``UNUSED`` helpers (helpers our source forgot to inline-and-discard)
* extra symbols we emit that orig does not (over-exposed globals, named lbls)
* per-section size deltas
* layout ordering differences

Usage::

    python3 tools/map/discrepancy.py pppRandUpFV
    python3 tools/map/discrepancy.py pppRandUpFV.o --no-en
    python3 tools/map/discrepancy.py src/pppRandUpFV.cpp
"""
from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Optional

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
DEFAULT_OURS = REPO_ROOT / "build" / "GCCP01" / "main.elf.MAP"
DEFAULT_PAL = REPO_ROOT / "orig" / "GCCP01" / "game.MAP"
DEFAULT_EN = REPO_ROOT / "orig" / "GCCE01" / "game.MAP"

try:
    from .map_index import (  # type: ignore
        LayoutRecord,
        MapIndex,
        load_map_index,
        normalize_object_file,
    )
except ImportError:  # script invocation (no package context)
    sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
    from map.map_index import (  # type: ignore
        LayoutRecord,
        MapIndex,
        load_map_index,
        normalize_object_file,
    )


# Sections we report on, in display order.
SECTION_ORDER = (
    ".text",
    ".ctors",
    ".dtors",
    "extab",
    "extabindex",
    ".rodata",
    ".data",
    ".bss",
    ".sdata",
    ".sdata2",
    ".sbss",
    ".sbss2",
)


# Anonymous symbols look like ``@715`` (orig) or ``@etb_80007148`` /
# ``@eti_8000D09C`` (ours); they're inherently address-derived and will never
# match between builds, so we collapse them for comparison.
ANON_RE = re.compile(r"^@[A-Za-z]*_?[0-9A-Fa-f]+$")
# Our build emits ``lbl_<HEX>`` for unnamed sdata2/sdata constants.
LBL_RE = re.compile(r"^lbl_[0-9A-Fa-f]+$")


def _normalize_symbol(name: str) -> str:
    """Collapse address-derived names so order/membership is comparable."""
    if ANON_RE.match(name) or LBL_RE.match(name):
        return "<anon>"
    return name


@dataclass
class SectionEntry:
    section: str
    symbol: str
    normalized: str
    size: int
    is_unused: bool
    virtual_address: Optional[int]


def _records_for_object(index: MapIndex, object_file: str) -> list[LayoutRecord]:
    target = normalize_object_file(object_file)
    out: list[LayoutRecord] = []
    for records in index.layout_by_symbol.values():
        for rec in records:
            if rec.object_file == target:
                out.append(rec)
    return out


def _sort_key(rec: LayoutRecord) -> tuple[int, int, str]:
    # Place UNUSED rows after live rows; otherwise sort by virtual address.
    return (
        1 if rec.is_unused else 0,
        rec.virtual_address if rec.virtual_address is not None else 1 << 31,
        rec.symbol_name,
    )


def _entries(index: Optional[MapIndex], object_file: str) -> dict[str, list[SectionEntry]]:
    by_section: dict[str, list[SectionEntry]] = {}
    if index is None:
        return by_section
    for rec in _records_for_object(index, object_file):
        # Skip section-level records (e.g. the row whose symbol equals the section name).
        if rec.symbol_name == rec.section:
            continue
        # Skip kind-only marker rows that re-state the section size.
        by_section.setdefault(rec.section, []).append(
            SectionEntry(
                section=rec.section,
                symbol=rec.symbol_name,
                normalized=_normalize_symbol(rec.symbol_name),
                size=rec.size,
                is_unused=rec.is_unused,
                virtual_address=rec.virtual_address,
            )
        )
    for sec in by_section:
        by_section[sec].sort(key=lambda e: (
            1 if e.is_unused else 0,
            e.virtual_address if e.virtual_address is not None else 1 << 31,
            e.symbol,
        ))
    return by_section


def _fmt_entry(entry: Optional[SectionEntry]) -> str:
    if entry is None:
        return ""
    label = entry.symbol
    if entry.is_unused:
        label = f"UNUSED {label}"
    return f"{label}  0x{entry.size:x}"


def _section_diff(
    section: str,
    ours: list[SectionEntry],
    pal: list[SectionEntry],
    en: Optional[list[SectionEntry]],
) -> list[str]:
    """Return human-readable lines for one section."""
    lines: list[str] = []

    def _key_set(entries: Iterable[SectionEntry]) -> set[tuple[str, bool]]:
        return {(e.normalized, e.is_unused) for e in entries}

    ours_keys = _key_set(ours)
    pal_keys = _key_set(pal)
    en_keys = _key_set(en) if en is not None else set()

    if not ours and not pal and not en:
        return lines

    ours_size = sum(e.size for e in ours)
    pal_size = sum(e.size for e in pal)
    en_size = sum(e.size for e in en) if en is not None else 0

    header = f"[{section}] ours=0x{ours_size:x}  PAL=0x{pal_size:x}"
    if en is not None:
        header += f"  EN=0x{en_size:x}"
    if ours_size != pal_size:
        header += f"  delta_PAL={ours_size - pal_size:+d}b"
    lines.append(header)

    # Side-by-side rows aligned by index. They aren't always positionally
    # comparable but for a single .o this is usually clear enough.
    max_rows = max(len(ours), len(pal), len(en) if en is not None else 0)
    col_w = 44
    for i in range(max_rows):
        o = ours[i] if i < len(ours) else None
        p = pal[i] if i < len(pal) else None
        e = en[i] if en is not None and i < len(en) else None

        flag = ""
        if o is not None and (o.normalized, o.is_unused) not in pal_keys:
            flag = "  *** EXTRA vs PAL"
        elif p is not None and (p.normalized, p.is_unused) not in ours_keys:
            flag = "  *** MISSING vs PAL"
        elif o is not None and p is not None and o.normalized != p.normalized:
            # Same membership counts but ordering differs at this row.
            flag = "  ~ order"
        elif o is not None and p is not None and o.size != p.size:
            flag = f"  ~ size ({o.size - p.size:+d}b)"

        pieces = [f"  {_fmt_entry(o):<{col_w}}", f"{_fmt_entry(p):<{col_w}}"]
        if en is not None:
            pieces.append(f"{_fmt_entry(e):<{col_w}}")
        lines.append("".join(pieces).rstrip() + flag)

    # Also surface set-level membership deltas (in case the row alignment
    # masked them).
    missing = sorted(pal_keys - ours_keys)
    extra = sorted(ours_keys - pal_keys)
    if missing:
        lines.append(
            "  -> missing vs PAL: "
            + ", ".join(f"{n}{' (UNUSED)' if u else ''}" for n, u in missing)
        )
    if extra:
        lines.append(
            "  -> extra vs PAL:   "
            + ", ".join(f"{n}{' (UNUSED)' if u else ''}" for n, u in extra)
        )
    if en is not None:
        en_missing = sorted(en_keys - ours_keys)
        en_extra = sorted(ours_keys - en_keys)
        if en_missing:
            lines.append(
                "  -> missing vs EN:  "
                + ", ".join(f"{n}{' (UNUSED)' if u else ''}" for n, u in en_missing)
            )
        if en_extra:
            lines.append(
                "  -> extra vs EN:    "
                + ", ".join(f"{n}{' (UNUSED)' if u else ''}" for n, u in en_extra)
            )

    return lines


def _summary_counts(
    ours_by_sec: dict[str, list[SectionEntry]],
    pal_by_sec: dict[str, list[SectionEntry]],
    en_by_sec: dict[str, list[SectionEntry]],
) -> dict[str, int]:
    missing_unused = 0
    missing_live = 0
    extra_live = 0
    size_delta_total = 0
    for sec in set(ours_by_sec) | set(pal_by_sec):
        ours = ours_by_sec.get(sec, [])
        pal = pal_by_sec.get(sec, [])
        ours_keys = {(e.normalized, e.is_unused) for e in ours}
        pal_keys = {(e.normalized, e.is_unused) for e in pal}
        for n, unused in pal_keys - ours_keys:
            if unused:
                missing_unused += 1
            else:
                missing_live += 1
        for n, unused in ours_keys - pal_keys:
            if not unused:
                extra_live += 1
        size_delta_total += sum(e.size for e in ours) - sum(e.size for e in pal)
    return {
        "missing_unused_helpers": missing_unused,
        "missing_live_symbols": missing_live,
        "extra_live_symbols": extra_live,
        "size_delta_total_bytes": size_delta_total,
    }


def normalize_target(target: str) -> str:
    """Accept ``foo``, ``foo.o``, ``foo.cpp``, or a path; return ``foo.o``."""
    name = Path(target).name
    if name.endswith(".o"):
        return name
    stem = Path(name).stem
    return f"{stem}.o"


def report(
    target: str,
    ours_path: Path = DEFAULT_OURS,
    pal_path: Path = DEFAULT_PAL,
    en_path: Optional[Path] = DEFAULT_EN,
    sections: Iterable[str] = SECTION_ORDER,
) -> int:
    object_file = normalize_target(target)

    if not ours_path.exists():
        print(f"ERROR: {ours_path} not found. Run 'ninja' first.", file=sys.stderr)
        return 2
    if not pal_path.exists():
        print(f"ERROR: {pal_path} not found.", file=sys.stderr)
        return 2

    ours_index = load_map_index(ours_path, label="ours")
    pal_index = load_map_index(pal_path, label="PAL")
    en_index = load_map_index(en_path, label="EN") if en_path and en_path.exists() else None

    ours_by_sec = _entries(ours_index, object_file)
    pal_by_sec = _entries(pal_index, object_file)
    en_by_sec = _entries(en_index, object_file) if en_index else {}

    if not ours_by_sec and not pal_by_sec and not en_by_sec:
        print(f"No layout records for {object_file} in any MAP. Did you spell it right?")
        return 1

    print(f"=== MAP DISCREPANCY: {object_file} ===")
    print(f"  ours: {ours_path}")
    print(f"  PAL:  {pal_path}")
    if en_index is not None:
        print(f"  EN:   {en_path}")
    else:
        print("  EN:   (skipped)")
    print()

    for section in sections:
        lines = _section_diff(
            section,
            ours_by_sec.get(section, []),
            pal_by_sec.get(section, []),
            en_by_sec.get(section, []) if en_index is not None else None,
        )
        if lines:
            for line in lines:
                print(line)
            print()

    counts = _summary_counts(ours_by_sec, pal_by_sec, en_by_sec)
    print("SUMMARY (vs PAL):")
    print(f"  missing UNUSED helpers : {counts['missing_unused_helpers']}")
    print(f"  missing live symbols   : {counts['missing_live_symbols']}")
    print(f"  extra live symbols     : {counts['extra_live_symbols']}")
    print(f"  total size delta       : {counts['size_delta_total_bytes']:+d} bytes")

    has_diff = any(counts.values())
    return 0 if not has_diff else 1


def _build_argparser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__.split("\n", 1)[0])
    parser.add_argument(
        "target",
        help="object file (foo.o), stem (foo), or source path (src/foo.cpp).",
    )
    parser.add_argument(
        "--ours",
        type=Path,
        default=DEFAULT_OURS,
        help=f"path to our emitted MAP (default: {DEFAULT_OURS})",
    )
    parser.add_argument(
        "--pal",
        type=Path,
        default=DEFAULT_PAL,
        help=f"path to PAL MAP (default: {DEFAULT_PAL})",
    )
    parser.add_argument(
        "--en",
        type=Path,
        default=DEFAULT_EN,
        help=f"path to EN MAP (default: {DEFAULT_EN})",
    )
    parser.add_argument(
        "--no-en",
        action="store_true",
        help="skip EN comparison",
    )
    parser.add_argument(
        "--section",
        action="append",
        help="only show this section (can be repeated)",
    )
    return parser


def main(argv: Optional[list[str]] = None) -> int:
    args = _build_argparser().parse_args(argv)
    sections = tuple(args.section) if args.section else SECTION_ORDER
    return report(
        args.target,
        ours_path=args.ours,
        pal_path=args.pal,
        en_path=None if args.no_en else args.en,
        sections=sections,
    )


if __name__ == "__main__":
    raise SystemExit(main())
