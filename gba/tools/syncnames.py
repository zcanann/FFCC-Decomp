#!/usr/bin/env python3
"""Propagate symbol names from compiled source to a program's symbols.txt.

Referenced names (default): for every function defined in both a unit's target
object and its compiled object, relocations at the same offset are paired. Where
the target references a placeholder (fn_/lbl_) and the source references a real
name, the placeholder is renamed.

Defined names (--defined): every symbol a unit's compiled object defines is
placed at its address (the unit's section start from splits.txt plus the symbol's
offset), and the symbols.txt entry at that address takes its name. This follows
the compiler's own names, such as C++ mangled names after a change of linkage.
The units' objects are built with ninja first. Without units, every unit with a
compiled object is synced. Only meaningful for matching units.

    python gba/tools/syncnames.py mgr m4a/m4a            # show proposed renames
    python gba/tools/syncnames.py mgr m4a/m4a --apply
    python gba/tools/syncnames.py mgr --defined --apply
"""

import argparse
import re
import struct
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[2]
PLACEHOLDER = re.compile(r"^(fn|lbl)_[0-9A-F]{8}$")
SECTIONS = (".text", ".rodata", ".data", ".bss", ".ctors")
SYMBOL = re.compile(r"^(\S+) = (\.\w+):0x([0-9A-Fa-f]+); // type:(\w+)", re.M)


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


def referenced_renames(build, unit):
    tfuncs, trel = load(build / "obj" / f"{unit}.o")
    bfuncs, brel = load(build / "src" / f"{unit}.o")

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
    if conflicts:
        print("conflicting:", ", ".join(sorted(conflicts)), file=sys.stderr)
    return renames


def split_starts(config_dir):
    """{unit: {section: start address}} from splits.txt."""
    starts = {}
    unit = None
    for line in (config_dir / "splits.txt").read_text(encoding="utf-8").splitlines():
        m = re.match(r"^(\S+):\s*$", line)
        if m:
            unit = m.group(1)
            continue
        m = re.match(r"^\s+(\.\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:", line)
        if m and unit is not None:
            starts.setdefault(unit, {})[m.group(1)] = int(m.group(2), 16)
    return starts


def defined_symbols(path):
    """(section, offset, name, is_function or None) for each named symbol the object defines."""
    out = []
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for s in elf.get_section_by_name(".symtab").iter_symbols():
            kind = s["st_info"]["type"]
            if kind not in ("STT_FUNC", "STT_OBJECT", "STT_NOTYPE") or not s.name:
                continue
            if s.name.startswith((".L", "$")) or s.name == ".gcc2_compiled." or not isinstance(s["st_shndx"], int):
                continue
            if kind == "STT_NOTYPE" and s["st_info"]["bind"] == "STB_LOCAL":
                continue  # assembly labels
            section = elf.get_section(s["st_shndx"]).name
            base = next((sec for sec in SECTIONS if section == sec or section.startswith(sec + ".")), None)
            if base is None:
                continue
            # Assembly labels (no type) may be functions or data.
            is_func = None if kind == "STT_NOTYPE" else kind == "STT_FUNC"
            out.append((base, s["st_value"] & ~1 if is_func else s["st_value"], s.name, is_func))
    return out


def defined_renames(build, config_dir, units, symbols):
    starts = split_starts(config_dir)
    entries = {}
    for name, section, addr, kind in SYMBOL.findall(symbols):
        entries.setdefault((section, int(addr, 16)), []).append((name, kind == "function"))
    renames = {}
    for unit in units:
        for section, offset, name, is_func in defined_symbols(build / "src" / f"{unit}.o"):
            start = starts.get(unit, {}).get(section)
            if start is None:
                continue
            addr = start + offset
            here = [e[0] for e in entries.get((section, addr), []) if is_func is None or e[1] == is_func]
            if len(here) != 1:
                what = "no symbol" if not here else "several symbols"
                print(f"{unit}: {what} at {section}:0x{addr:08X} for {name}", file=sys.stderr)
                continue
            if here[0] != name:
                renames[here[0]] = name
    return renames


def compiled_units(config_dir, build):
    units = re.findall(r"^(\S+):\s*$", (config_dir / "splits.txt").read_text(encoding="utf-8"), re.M)
    return [u for u in dict.fromkeys(units) if (build / "src" / f"{u}.o").is_file()]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("program")
    parser.add_argument("units", nargs="*")
    parser.add_argument("--defined", action="store_true",
                        help="rename symbols.txt entries to the names the compiled objects define")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    build = ROOT / "build" / "GCCP01" / "gba" / args.program
    config_dir = ROOT / "gba" / "config" / args.program
    symbols = config_dir / "symbols.txt"
    text = symbols.read_bytes().decode("utf-8")

    if args.defined:
        units = args.units or compiled_units(config_dir, build)
        objects = [(build / "src" / f"{u}.o").relative_to(ROOT).as_posix() for u in units]
        subprocess.run(["ninja"] + objects, cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
        renames = defined_renames(build, config_dir, units, text)
    else:
        if len(args.units) != 1:
            sys.exit("give one unit")
        renames = referenced_renames(build, args.units[0])

    # Renames apply at once, so names may move between entries; a name that stays
    # on another entry is not taken.
    existing = set(re.findall(r"^(\S+) =", text, re.M))
    kept = existing - set(renames)
    skipped = {old for old, new in renames.items() if new in kept}
    for old, new in sorted(renames.items()):
        print(f"{old} -> {new}{' (name already used, skipped)' if old in skipped else ''}")
    targets = [new for old, new in renames.items() if old not in skipped]
    if len(set(targets)) != len(targets):
        sys.exit("several symbols would take one name")
    if args.apply:
        apply = {old: new for old, new in renames.items() if old not in skipped}
        text = re.sub(r"^(\S+) =", lambda m: f"{apply.get(m.group(1), m.group(1))} =", text, flags=re.M)
        symbols.write_bytes(text.encode("utf-8"))


if __name__ == "__main__":
    main()
