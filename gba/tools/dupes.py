#!/usr/bin/env python3
"""Find functions whose code is identical between the two GBA programs.

Compares each function's bytes with relocated words masked out, using the target
objects in build/GCCP01/gba. Prints pairs as "cli_name mgr_name size"; with
--matched, only mgr functions whose unit has compiled source are listed.

    python gba/tools/dupes.py
"""

import argparse
import re
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[2]
BUILD = ROOT / "build" / "GCCP01" / "gba"


def functions(program):
    """name -> (masked bytes) for every function in the program's target objects."""
    out = {}
    for obj in (BUILD / program / "obj").rglob("*.o"):
        if obj.name.endswith(".v5.o"):
            continue
        with open(obj, "rb") as f:
            elf = ELFFile(f)
            symtab = elf.get_section_by_name(".symtab")
            for index, section in enumerate(elf.iter_sections()):
                if not section.name.startswith(".text"):
                    continue
                data = bytearray(section.data())
                rel = elf.get_section_by_name(".rel" + section.name)
                if isinstance(rel, RelocationSection):
                    for r in rel.iter_relocations():
                        for k in range(4):
                            if r["r_offset"] + k < len(data):
                                data[r["r_offset"] + k] = 0
                for s in symtab.iter_symbols():
                    if s["st_shndx"] == index and s["st_info"]["type"] == "STT_FUNC" and s["st_size"]:
                        start = s["st_value"] & ~1
                        out[s.name] = bytes(data[start:start + s["st_size"]])
    return out


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--min-size", type=int, default=8)
    args = parser.parse_args()
    cli = functions("cli")
    mgr = functions("mgr")
    by_code = {}
    for name, code in mgr.items():
        by_code.setdefault(code, []).append(name)
    total = 0
    for name, code in sorted(cli.items()):
        if len(code) < args.min_size or name in mgr:
            continue
        if code in by_code:
            print(f"{name} {' '.join(by_code[code])} 0x{len(code):X}")
            total += len(code)
    print(f"-- 0x{total:X} bytes of client code identical to minigame code")


if __name__ == "__main__":
    main()
