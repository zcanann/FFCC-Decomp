#!/usr/bin/env python3
"""Extract GBA multiboot images from a GameCube disc image."""

import argparse
import struct
import sys
from pathlib import Path


def read_fst(disc):
    disc.seek(0x424)
    fst_offset, fst_size = struct.unpack(">II", disc.read(8))
    disc.seek(fst_offset)
    fst = disc.read(fst_size)
    count = struct.unpack(">I", fst[8:12])[0]
    strings = fst[count * 12:]

    def name_at(offset):
        return strings[offset:strings.index(b"\0", offset)].decode("latin-1")

    # Walk the flat FST, tracking directory ends to rebuild full paths.
    stack = [("", count)]
    for i in range(1, count):
        while i >= stack[-1][1]:
            stack.pop()
        entry = fst[i * 12:i * 12 + 12]
        name = name_at(int.from_bytes(entry[1:4], "big"))
        path = f"{stack[-1][0]}{name}"
        a, b = struct.unpack(">II", entry[4:])
        if entry[0]:
            stack.append((path + "/", b))
        else:
            yield path, a, b


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("disc", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("files", nargs="+", help="disc paths, e.g. gba/ffcc_cli.bin")
    args = parser.parse_args()

    with args.disc.open("rb") as disc:
        entries = {path: (offset, size) for path, offset, size in read_fst(disc)}
        for path in args.files:
            if path not in entries:
                sys.exit(f"{path} not found in {args.disc}")
            offset, size = entries[path]
            disc.seek(offset)
            dest = args.output / Path(path).name
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(disc.read(size))


if __name__ == "__main__":
    main()
