#!/usr/bin/env python3
"""Extract assets from a GBA multiboot image into the build directory.

Symbols in symbols.txt marked `asset` are written to <outdir>/<name>.bin (their
bytes in the retail image) for source files to pull in with .incbin. Symbols
marked `asset:asm` hold pointers, such as m4a song data; they are written to
<outdir>/<name>.inc as assembly with symbolic pointers, for .include.
"""

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from split import Split, load_emitter  # noqa: E402

BASE = 0x02000000


def write(path: Path, data) -> None:
    mode = "wb" if isinstance(data, bytes) else "w"
    if path.is_file() and (path.read_bytes() if mode == "wb" else path.read_text()) == data:
        return
    with open(path, mode) as f:
        f.write(data)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("binary", type=Path)
    parser.add_argument("config", type=Path, help="config directory with symbols.txt and splits.txt")
    parser.add_argument("outdir", type=Path)
    args = parser.parse_args()

    data = args.binary.read_bytes()
    kinds = {}
    for line in (args.config / "symbols.txt").read_text().splitlines():
        if "//" not in line:
            continue
        for attr in line.split("//", 1)[1].split():
            if attr in ("asset", "asset:asm"):
                kinds[line.split()[0]] = attr
    if not kinds:
        return
    emitter = load_emitter(data, args.config) if "asset:asm" in kinds.values() else None
    args.outdir.mkdir(parents=True, exist_ok=True)
    symbols = emitter.symbols if emitter else None
    if symbols is None:
        from split import parse_symbols
        symbols = parse_symbols(args.config / "symbols.txt")
    for s in symbols:
        kind = kinds.get(s.name)
        if kind is None:
            continue
        offset = s.address - BASE
        if s.size <= 0 or offset < 0 or offset + s.size > len(data):
            sys.exit(f"asset {s.name}: 0x{s.address:08X} size 0x{s.size:X} is outside the image")
        if kind == "asset":
            write(args.outdir / f"{s.name}.bin", data[offset:offset + s.size])
            continue
        unit = emitter.unit_at(s.address)
        lines = emitter.emit_range(Split(unit, s.section, s.address, s.address + s.size), unit)
        # The including file chooses the section.
        lines = [line for line in lines if not line.startswith(("\t.section", "\t.balign"))]
        write(args.outdir / f"{s.name}.inc", "\n".join(lines).lstrip("\n") + "\n")


if __name__ == "__main__":
    main()
