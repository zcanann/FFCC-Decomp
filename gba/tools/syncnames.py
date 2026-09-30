#!/usr/bin/env python3
"""Propagate symbol names from compiled source to a program's symbols.txt.

For every function defined in both a unit's target object and its compiled object,
relocations at the same offset are paired. Where the target references a
placeholder (fn_/lbl_) and the source references a real name, the placeholder is
renamed in gba/config/<program>/symbols.txt.

    python gba/tools/syncnames.py mgr m4a/m4a            # show proposed renames
    python gba/tools/syncnames.py mgr m4a/m4a --apply
"""

import argparse
import re
import struct
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[2]
PLACEHOLDER = re.compile(r"^(fn|lbl)_[0-9A-F]{8}$")


def load(path):
    with open(path, "rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        text_index = elf.get_section_index(".text")
        text = elf.get_section_by_name(".text").data()
        funcs = {}
        for s in symtab.iter_symbols():
            if s["st_shndx"] == text_index and s["st_info"]["type"] == "STT_FUNC":
                funcs[s.name] = (s["st_value"] & ~1, s["st_size"])
        relocs = {}
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name == ".rel.text":
                for r in sec.iter_relocations():
                    sym = symtab.get_symbol(r["r_info_sym"])
                    kind = r["r_info_type"]
                    addend = struct.unpack_from("<I", text, r["r_offset"])[0] if kind == 2 else 0
                    name = sym.name if sym["st_info"]["type"] != "STT_SECTION" else None
                    relocs[r["r_offset"]] = (name, kind, addend)
        return funcs, relocs


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("program")
    parser.add_argument("unit")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    build = ROOT / "build" / "GCCP01" / "gba" / args.program
    tfuncs, trel = load(build / "obj" / f"{args.unit}.o")
    bfuncs, brel = load(build / "src" / f"{args.unit}.o")

    renames = {}
    conflicts = set()
    for name, (tstart, tsize) in tfuncs.items():
        if name not in bfuncs:
            continue
        bstart, bsize = bfuncs[name]
        for off in range(0, min(tsize, bsize), 2):
            t = trel.get(tstart + off)
            b = brel.get(bstart + off)
            if not t or not b or not t[0] or not b[0] or t[1] != b[1] or t[2] != b[2]:
                continue
            if PLACEHOLDER.match(t[0]) and not PLACEHOLDER.match(b[0]) and t[0] != b[0]:
                if renames.get(t[0], b[0]) != b[0]:
                    conflicts.add(t[0])
                renames[t[0]] = b[0]
    for c in conflicts:
        renames.pop(c, None)

    symbols = ROOT / "gba" / "config" / args.program / "symbols.txt"
    text = symbols.read_text()
    existing = set(re.findall(r"^(\S+) =", text, re.M))
    for old, new in sorted(renames.items()):
        clash = " (name already used, skipped)" if new in existing else ""
        print(f"{old} -> {new}{clash}")
    if args.apply:
        for old, new in renames.items():
            if new not in existing:
                text = re.sub(rf"^{re.escape(old)} =", f"{new} =", text, flags=re.M)
        symbols.write_text(text)
    if conflicts:
        print("conflicting:", ", ".join(sorted(conflicts)), file=sys.stderr)


if __name__ == "__main__":
    main()
