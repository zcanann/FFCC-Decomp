#!/usr/bin/env python3
"""Rename GBA symbols in symbols.txt and every source file of a program.

    python gba/tools/rename.py mgr fn_020001A0 AssertFailed
    python gba/tools/rename.py cli --file renames.txt     # lines: "old new"

Names are replaced as whole identifiers. Refuses to rename to a name that
already exists in the program's symbols.txt.
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("program")
    parser.add_argument("old", nargs="?")
    parser.add_argument("new", nargs="?")
    parser.add_argument("--file", type=Path)
    args = parser.parse_args()

    pairs = []
    if args.file:
        for line in args.file.read_text().splitlines():
            fields = line.split("#")[0].split()
            if len(fields) == 2:
                pairs.append((fields[0], fields[1]))
    if args.old and args.new:
        pairs.append((args.old, args.new))
    if not pairs:
        sys.exit("nothing to rename")

    symbols_path = ROOT / "gba" / "config" / args.program / "symbols.txt"
    symbols = symbols_path.read_text()
    existing = set(re.findall(r"^(\S+) =", symbols, re.M))
    for old, new in pairs:
        if old not in existing:
            sys.exit(f"{old} is not a symbol of {args.program}")
        if new in existing:
            sys.exit(f"{new} already exists in {args.program}")
        existing.discard(old)
        existing.add(new)

    for old, new in pairs:
        symbols = re.sub(rf"^{re.escape(old)} =", f"{new} =", symbols, flags=re.M)
    symbols_path.write_text(symbols)

    sources = [p for p in (ROOT / "gba" / "src" / args.program).rglob("*") if p.suffix in (".c", ".h", ".s")]
    sources += [p for p in (ROOT / "gba" / "include" / args.program).rglob("*.h")] \
        if (ROOT / "gba" / "include" / args.program).is_dir() else []
    for path in sources:
        raw = path.read_bytes().decode("utf-8")
        text = raw
        for old, new in pairs:
            text = re.sub(rf"\b{re.escape(old)}\b", new, text)
        if text != raw:
            path.write_bytes(text.encode("utf-8"))
            print(f"updated {path.relative_to(ROOT)}")
    for old, new in pairs:
        print(f"{old} -> {new}")


if __name__ == "__main__":
    main()
