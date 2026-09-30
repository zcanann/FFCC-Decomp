#!/usr/bin/env python3
"""Split a GBA multiboot image into per-unit assembly using symbols.txt and splits.txt.

Instructions are emitted with `.inst` so disassemblers still see code, while
calls, literal pool pointers, jump tables and data pointers are emitted as
symbol references so the resulting objects carry relocations.

With --bootstrap, analyzes the image and writes initial symbols.txt/splits.txt.
"""

import argparse
import bisect
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).parent))
from gbaanalysis import (  # noqa: E402
    EWRAM_BASE, EWRAM_END, IWRAM_BASE, Analysis, Analyzer,
)

ENTRY = EWRAM_BASE
# The top of IWRAM holds the BIOS interrupt vector and stacks, not program data.
IWRAM_DATA_END = 0x03007E00

LOAD_SECTIONS = (".text", ".rodata")
BSS_SECTIONS = {".ewram_bss": (EWRAM_BASE, EWRAM_END), ".bss": (IWRAM_BASE, IWRAM_DATA_END)}

_SYMBOL = re.compile(r"^(\S+)\s*=\s*(\.\w+):0x([0-9A-Fa-f]+);\s*//(.*)$")
_UNIT = re.compile(r"^(\S+):\s*$")
_RANGE = re.compile(r"^\s+(\.\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)\s*$")


@dataclass
class Symbol:
    name: str
    section: str
    address: int
    kind: str  # function / object
    size: int
    thumb: bool = False


@dataclass
class Split:
    unit: str
    section: str
    start: int
    end: int


def parse_symbols(path: Path) -> List[Symbol]:
    symbols = []
    for line in path.read_text().splitlines():
        m = _SYMBOL.match(line.strip())
        if not m:
            continue
        attrs = dict(a.split(":", 1) if ":" in a else (a, "") for a in m.group(4).split())
        symbols.append(Symbol(m.group(1), m.group(2), int(m.group(3), 16), attrs.get("type", "object"),
                              int(attrs.get("size", "0"), 0), "thumb" in attrs))
    return sorted(symbols, key=lambda s: s.address)


def parse_splits(path: Path) -> List[Split]:
    splits = []
    unit = None
    for line in path.read_text().splitlines():
        m = _UNIT.match(line)
        if m:
            unit = m.group(1)
            continue
        m = _RANGE.match(line)
        if m and unit:
            splits.append(Split(unit, m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    return splits


def write_symbols(path: Path, symbols: List[Symbol]) -> None:
    lines = []
    for s in sorted(symbols, key=lambda s: s.address):
        flags = " thumb" if s.thumb else ""
        lines.append(f"{s.name} = {s.section}:0x{s.address:08X}; // type:{s.kind} size:0x{s.size:X}{flags}")
    path.write_text("\n".join(lines) + "\n")


def write_splits(path: Path, splits: List[Split]) -> None:
    out = []
    unit = None
    for s in splits:
        if s.unit != unit:
            if unit is not None:
                out.append("")
            out.append(f"{s.unit}:")
            unit = s.unit
        out.append(f"\t{s.section:<12}start:0x{s.start:08X} end:0x{s.end:08X}")
    path.write_text("\n".join(out) + "\n")


def analyze(data: bytes, symbols: List[Symbol]) -> Analysis:
    analyzer = Analyzer(data)
    for s in symbols:
        if s.kind == "function" and s.section == ".text":
            analyzer.add_function(s.address, s.thumb)
    return analyzer.run(ENTRY)


def bootstrap(data: bytes) -> Tuple[List[Symbol], List[Split]]:
    a = Analyzer(data).run(ENTRY)
    code_end = (a.code_end + 3) & ~3
    starts = sorted(a.functions)
    symbols = []
    for start in starts:
        f = a.functions[start]
        symbols.append(Symbol(f"fn_{start:08X}", ".text", start, "function", f.end - start, f.thumb))

    # Data labels: start of data plus every pointer target inside data and bss.
    data_labels = {code_end}
    bss_labels: Dict[str, set] = {name: set() for name in BSS_SECTIONS}
    words = set(a.literals) | {x for x in range(code_end, a.end - 3, 4)}
    for address in words:
        value = a.word(address)
        if code_end <= value < a.end:
            data_labels.add(value & ~3 if value % 4 else value)
        for name, (lo, hi) in BSS_SECTIONS.items():
            if lo <= value < hi and not (name == ".ewram_bss" and value < a.end):
                bss_labels[name].add(value)
    labels = sorted(data_labels)
    for index, address in enumerate(labels):
        end = labels[index + 1] if index + 1 < len(labels) else a.end
        symbols.append(Symbol(f"lbl_{address:08X}", ".rodata", address, "object", end - address))

    splits = []
    first_thumb = min(s for s in starts if a.functions[s].thumb)
    splits.append(Split("crt0", ".text", a.base, first_thumb))
    splits.append(Split("main", ".text", first_thumb, code_end))
    splits.append(Split("main", ".rodata", code_end, a.end))
    for name, found in bss_labels.items():
        if not found:
            continue
        addresses = sorted(found)
        lo = a.end if name == ".ewram_bss" else BSS_SECTIONS[name][0]
        addresses = sorted(set([lo] + addresses))
        for index, address in enumerate(addresses):
            end = addresses[index + 1] if index + 1 < len(addresses) else address + 4
            symbols.append(Symbol(f"lbl_{address:08X}", name, address, "object", end - address))
        splits.append(Split("bss", name, lo, addresses[-1] + 4))
    return symbols, splits


class Emitter:
    def __init__(self, a: Analysis, symbols: List[Symbol], splits: List[Split]):
        self.a = a
        self.symbols = symbols
        self.splits = splits
        self.addresses = [s.address for s in symbols]
        self.by_address: Dict[int, List[Symbol]] = {}
        for s in symbols:
            self.by_address.setdefault(s.address, []).append(s)
        self.unit_of: List[Tuple[int, int, str]] = sorted((s.start, s.end, s.unit) for s in splits)
        self.code_ranges = [(s.start, s.end) for s in splits if s.section == ".text"]
        self.local_labels: Dict[str, set] = {}

    def unit_at(self, address: int) -> Optional[str]:
        for start, end, unit in self.unit_of:
            if start <= address < end:
                return unit
        return None

    def containing(self, value: int) -> Optional[Symbol]:
        index = bisect.bisect_right(self.addresses, value) - 1
        while index >= 0:
            s = self.symbols[index]
            if s.address <= value < s.address + max(s.size, 1):
                return s
            if s.address < value - 0x100000:
                break
            index -= 1
        return None

    def expression(self, value: int, unit: str) -> Optional[str]:
        """Symbolic expression for an absolute pointer value, or None to emit it raw."""
        target = value & ~1
        # Pointer to a Thumb function entry: the linker sets the Thumb bit.
        for s in self.by_address.get(target, []):
            if s.kind == "function" and s.thumb and value & 1:
                return s.name
            if not (s.kind == "function" and s.thumb):
                return s.name if value == s.address else None
        s = self.containing(value)
        if s is None:
            return None
        if not (s.kind == "function" and s.thumb):
            return f"{s.name}+0x{value - s.address:X}"
        # Inside a Thumb function (e.g. a jump table case). A function symbol
        # would add the Thumb bit, so use a local label in the same unit.
        if self.unit_at(value) != unit or not self.is_boundary(value & ~1):
            return None
        self.local_labels.setdefault(unit, set()).add(value & ~1)
        suffix = "+1" if value & 1 else ""
        return f".L_{value & ~1:08X}{suffix}"

    def emit_unit(self, unit: str) -> str:
        a = self.a
        out = [
            "\t.syntax unified",
            "\t.cpu arm7tdmi",
            "",
        ]
        ranges = [s for s in self.splits if s.unit == unit]
        # First pass computes needed local labels, second pass emits.
        self.local_labels[unit] = set()
        for _ in range(2):
            body = []
            for split in ranges:
                if split.section in BSS_SECTIONS:
                    body.extend(self.emit_bss(split))
                else:
                    body.extend(self.emit_range(split, unit))
        return "\n".join(out + body) + "\n"

    def emit_bss(self, split: Split) -> List[str]:
        out = ["", f"\t.section {split.section},\"aw\",%nobits", "\t.balign 4"]
        address = split.start
        for s in self.symbols:
            if s.section != split.section or not (split.start <= s.address < split.end):
                continue
            if s.address > address:
                out.append(f"\t.space 0x{s.address - address:X}")
            out += [f"\t.global {s.name}", f"\t.type {s.name}, %object", f"{s.name}:"]
            size = min(s.size, split.end - s.address)
            out += [f"\t.space 0x{size:X}", f"\t.size {s.name}, 0x{size:X}"]
            address = s.address + size
        if split.end > address:
            out.append(f"\t.space 0x{split.end - address:X}")
        return out

    def emit_range(self, split: Split, unit: str) -> List[str]:
        a = self.a
        flags = "\"ax\",%progbits" if split.section == ".text" else "\"a\",%progbits"
        out = ["", f"\t.section {split.section},{flags}"]
        is_code = split.section == ".text"
        mode = None
        open_symbol: Optional[Tuple[Symbol, int]] = None
        address = split.start
        labels = self.local_labels.get(unit, set())

        def close(at: int) -> None:
            nonlocal open_symbol
            if open_symbol is not None:
                out.append(f"\t.size {open_symbol[0].name}, . - {open_symbol[0].name}")
                open_symbol = None

        while address < split.end:
            for s in self.by_address.get(address, []):
                if s.section != split.section:
                    continue
                close(address)
                out.append("")
                if s.kind == "function":
                    want = "thumb" if s.thumb else "arm"
                    if mode != want:
                        out.append(f"\t.{want}")
                        mode = want
                    out.append(f"\t.global {s.name}")
                    out.append(f"\t.type {s.name}, %function")
                    if s.thumb:
                        out.append("\t.thumb_func")
                else:
                    out.append(f"\t.global {s.name}")
                    out.append(f"\t.type {s.name}, %object")
                out.append(f"{s.name}:")
                open_symbol = (s, address)
            if address in labels:
                out.append(f".L_{address:08X}:")

            remaining = split.end - address
            thumb_code = mode == "thumb"
            if is_code and address in a.calls and remaining >= 4:
                target, _ = a.calls[address]
                names = [s for s in self.by_address.get(target, []) if s.kind == "function"]
                if names and names[0].thumb == thumb_code:
                    out.append(f"\tbl {names[0].name}")
                else:
                    raw = a.word(address)
                    if thumb_code:
                        out.append(f"\t.inst.n 0x{raw & 0xFFFF:04X}, 0x{raw >> 16:04X}")
                    else:
                        out.append(f"\t.inst 0x{raw:08X}")
                address += 4
                continue
            if is_code and address in a.code and not (address in a.literals or address in a.jump_tables):
                size = a.code[address]
                if thumb_code and size == 2:
                    out.append(f"\t.inst.n 0x{a.half(address):04X}")
                    address += 2
                    continue
                if not thumb_code and size == 4 and remaining >= 4:
                    out.append(f"\t.inst 0x{a.word(address):08X}")
                    address += 4
                    continue
            if address % 4 == 0 and remaining >= 4 and not self.overlaps_code(address):
                value = a.word(address)
                expr = self.pointer(value, unit, address)
                out.append(f"\t.4byte {expr}" if expr else f"\t.4byte 0x{value:08X}")
                address += 4
                continue
            if address % 2 == 0 and remaining >= 2:
                out.append(f"\t.2byte 0x{a.half(address):04X}")
                address += 2
                continue
            out.append(f"\t.byte 0x{a.data[address - a.base]:02X}")
            address += 1
        close(address)
        return out

    def is_boundary(self, address: int) -> bool:
        a = self.a
        if address in a.literals or address in a.jump_tables:
            return True
        if address in a.code:
            # The second half of a BL pair is not an emitted boundary.
            return (address - 2) not in a.calls
        return address % 4 == 0 and not self.overlaps_code(address)

    def overlaps_code(self, address: int) -> bool:
        a = self.a
        if address in a.literals or address in a.jump_tables:
            return False
        return any((address + i) in a.code for i in range(4))

    def pointer(self, value: int, unit: str, address: int) -> Optional[str]:
        a = self.a
        if a.contains(value & ~1):
            return self.expression(value, unit)
        for name, (lo, hi) in BSS_SECTIONS.items():
            if lo <= value < hi:
                s = self.containing(value)
                if s is not None and s.section == name:
                    off = value - s.address
                    return s.name if off == 0 else f"{s.name}+0x{off:X}"
        return None

    def linker_script(self, objects: Dict[str, str]) -> str:
        out = ["SECTIONS", "{"]
        sections: Dict[str, List[Split]] = {}
        for split in self.splits:
            sections.setdefault(split.section, []).append(split)
        for section in list(LOAD_SECTIONS) + list(BSS_SECTIONS):
            if section not in sections:
                continue
            ordered = sorted(sections[section], key=lambda s: s.start)
            kind = " (NOLOAD)" if section in BSS_SECTIONS else ""
            out.append(f"\t{section} 0x{ordered[0].start:08X}{kind} :")
            out.append("\t{")
            for split in ordered:
                out.append(f"\t\t{objects[split.unit]}({section})")
            out.append("\t}")
        out.append("\t/DISCARD/ : { *(.ARM.attributes) *(.comment) }")
        out.append("}")
        return "\n".join(out) + "\n"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("binary", type=Path)
    parser.add_argument("config", type=Path, help="config directory with symbols.txt and splits.txt")
    parser.add_argument("--bootstrap", action="store_true", help="write initial symbols.txt/splits.txt")
    parser.add_argument("--asm-dir", type=Path)
    parser.add_argument("--ldscript", type=Path)
    parser.add_argument("--object-dir", default="obj", help="object path prefix used in the linker script")
    parser.add_argument("--object", action="append", default=[], metavar="UNIT=PATH",
                        help="override the linked object for a unit (compiled source)")
    args = parser.parse_args()

    data = args.binary.read_bytes()
    symbols_path = args.config / "symbols.txt"
    splits_path = args.config / "splits.txt"

    if args.bootstrap:
        symbols, splits = bootstrap(data)
        args.config.mkdir(parents=True, exist_ok=True)
        write_symbols(symbols_path, symbols)
        write_splits(splits_path, splits)
        return

    symbols = parse_symbols(symbols_path)
    splits = parse_splits(splits_path)
    a = analyze(data, symbols)
    emitter = Emitter(a, symbols, splits)
    units = list(dict.fromkeys(s.unit for s in splits))

    if args.asm_dir:
        args.asm_dir.mkdir(parents=True, exist_ok=True)
        for unit in units:
            text = emitter.emit_unit(unit)
            path = args.asm_dir / f"{unit}.s"
            if not path.exists() or path.read_text() != text:
                path.write_text(text)

    if args.ldscript:
        objects = {unit: f"{args.object_dir}/{unit}.o" for unit in units}
        for override in args.object:
            unit, path = override.split("=", 1)
            objects[unit] = path
        text = emitter.linker_script(objects)
        if not args.ldscript.exists() or args.ldscript.read_text() != text:
            args.ldscript.parent.mkdir(parents=True, exist_ok=True)
            args.ldscript.write_text(text)


if __name__ == "__main__":
    main()
