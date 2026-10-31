#!/usr/bin/env python3
"""Place a compiled unit's COMMON symbols in their recovered order.

The original linker allocated each object's COMMON symbols in the order of its
symbol hash table, which depends on the original (unknown) names, so ld cannot
reproduce the layout from recovered names. This writes a linker script fragment
that defines the object's COMMON symbols in the configured address order, using
the size and alignment the compiler gave each one. The object must define
exactly the configured symbols of its .common range, and each placement is
asserted against the configured address.
"""

import argparse
import struct
import sys
from pathlib import Path
from typing import Dict, Tuple

sys.path.insert(0, str(Path(__file__).parent))
from split import parse_splits, parse_symbols  # noqa: E402

SHN_COMMON = 0xFFF2


def common_symbols(path: Path) -> Dict[str, Tuple[int, int]]:
    """An ELF32 little-endian object's COMMON symbols: name -> (alignment, size)."""
    data = path.read_bytes()
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        raise ValueError(f"{path}: not a little-endian ELF32 object")
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
    sections = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
    result = {}
    for _, sh_type, _, _, offset, size, link, _, _, entsize in sections:
        if sh_type != 2:  # SHT_SYMTAB
            continue
        strtab = sections[link][4]
        for pos in range(offset, offset + size, entsize):
            name, value, sym_size, _, _, shndx = struct.unpack_from("<IIIBBH", data, pos)
            if shndx == SHN_COMMON:
                end = data.index(b"\0", strtab + name)
                result[data[strtab + name:end].decode()] = (value, sym_size)
    return result


def fragment(split, configured, compiled: Dict[str, Tuple[int, int]]) -> str:
    """Linker script text placing configured COMMON symbols at their addresses."""
    out = []
    for s in configured:
        align, size = compiled[s.name]
        out += [f". = ALIGN({align});",
                f"ASSERT(ABSOLUTE(.) == 0x{s.address:08X}, \"{s.name}: COMMON layout differs from config\");",
                f"{s.name} = .;",
                f". += 0x{size:X};"]
    out.append(f"ASSERT(ABSOLUTE(.) == 0x{split.end:08X}, \"{split.unit}: COMMON range end differs from config\");")
    return "\n".join(out) + "\n"


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("object", type=Path)
    parser.add_argument("config", type=Path, help="config directory with symbols.txt and splits.txt")
    parser.add_argument("unit")
    parser.add_argument("-o", "--output", type=Path, required=True)
    args = parser.parse_args()

    ranges = [s for s in parse_splits(args.config / "splits.txt")
              if s.unit == args.unit and s.section == ".common"]
    if len(ranges) != 1:
        sys.exit(f"{args.unit}: expected one .common range, found {len(ranges)}")
    split = ranges[0]
    configured = [s for s in parse_symbols(args.config / "symbols.txt")
                  if s.section == ".common" and split.start <= s.address < split.end]
    compiled = common_symbols(args.object)
    names = {s.name for s in configured}
    if names != compiled.keys():
        missing = sorted(names - compiled.keys())
        extra = sorted(compiled.keys() - names)
        sys.exit(f"{args.unit}: COMMON symbols differ from config; missing {missing}, unexpected {extra}")

    text = fragment(split, configured, compiled)
    if not args.output.exists() or args.output.read_text() != text:
        args.output.write_text(text)


if __name__ == "__main__":
    main()
