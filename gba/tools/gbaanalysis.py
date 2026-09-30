"""Code discovery for GBA multiboot images.

Recursive descent over ARM and Thumb code starting at the image entry point,
following calls, tail branches, literal-loaded `bx` targets, jump tables, and
Thumb function pointers found in literal pools and data.
"""

import re
import struct
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Set, Tuple

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

EWRAM_BASE = 0x02000000
EWRAM_END = 0x02040000
IWRAM_BASE = 0x03000000
IWRAM_END = 0x03008000

_ARM = Cs(CS_ARCH_ARM, CS_MODE_ARM)
_THUMB = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

_REG = r"(r\d+|sb|sl|fp|ip|sp|lr|pc)"
_LDR_PC = re.compile(rf"^{_REG}, \[pc(?:, #(-?0x[0-9a-f]+|-?\d+))?\]$")
_ADD_PC = re.compile(rf"^{_REG}, pc, #(0x[0-9a-f]+|\d+)$")
_ADR = re.compile(rf"^{_REG}, #(0x[0-9a-f]+|\d+)$")
_IMM = re.compile(r"^#(-?0x[0-9a-f]+|-?\d+)$")


def _int(text: str) -> int:
    return int(text, 0)


@dataclass
class Function:
    address: int
    thumb: bool
    # Byte addresses of decoded instructions, and literal pool word addresses.
    instructions: Set[int] = field(default_factory=set)
    end: int = 0


@dataclass
class Analysis:
    base: int
    data: bytes
    functions: Dict[int, Function] = field(default_factory=dict)
    # Instruction start -> size, for every decoded instruction in the image.
    code: Dict[int, int] = field(default_factory=dict)
    # Thumb BL pairs and ARM BL instructions: address -> (target, thumb_source).
    calls: Dict[int, Tuple[int, bool]] = field(default_factory=dict)
    # Word-aligned addresses read as data by pc-relative loads.
    literals: Set[int] = field(default_factory=set)
    # Jump table word addresses.
    jump_tables: Set[int] = field(default_factory=set)
    code_end: int = 0

    @property
    def end(self) -> int:
        return self.base + len(self.data)

    def contains(self, address: int) -> bool:
        return self.base <= address < self.end

    def word(self, address: int) -> int:
        return struct.unpack_from("<I", self.data, address - self.base)[0]

    def half(self, address: int) -> int:
        return struct.unpack_from("<H", self.data, address - self.base)[0]


class Analyzer:
    def __init__(self, data: bytes, base: int = EWRAM_BASE):
        self.a = Analysis(base, data)
        self.queue: List[Tuple[int, bool]] = []

    def add_function(self, address: int, thumb: bool) -> None:
        if not self.a.contains(address) or address in self.a.functions:
            return
        existing = self.a.code.get(address)
        if existing is not None:
            # Already decoded as part of another function body; still record it
            # as an entry point so it gets a symbol.
            pass
        self.a.functions[address] = Function(address, thumb)
        self.queue.append((address, thumb))

    def run(self, entry: int, entry_thumb: bool = False) -> Analysis:
        self.add_function(entry, entry_thumb)
        while True:
            self._drain()
            if self._scan_pointers() or self._scan_prologues():
                continue
            self._finish()
            if not self._fill_gaps():
                break
        return self.a

    def _fill_gaps(self) -> bool:
        """Start a Thumb function at the first undecoded halfword of each gap in the code region."""
        a = self.a
        found = False
        starts = sorted(a.functions)
        for start, next_start in zip(starts, starts[1:]):
            gap = a.functions[start].end
            while gap < next_start and a.half(gap) == 0:
                gap += 2
            if gap >= next_start or gap % 2 or self._covered(gap):
                continue
            if self._decode(gap, a.functions[start].thumb) is None:
                continue
            self.add_function(gap, a.functions[start].thumb)
            found = True
        if found:
            self._drain()
        return found

    def _drain(self) -> None:
        while self.queue:
            address, thumb = self.queue.pop()
            self._decode_function(self.a.functions[address])

    def _decode_function(self, func: Function) -> None:
        a = self.a
        pending = [func.address]
        seen: Set[int] = set()
        while pending:
            pc = pending.pop()
            regs: Dict[str, int] = {}
            while a.contains(pc) and pc not in seen:
                if pc in a.literals or pc in a.jump_tables:
                    break
                insn = self._decode(pc, func.thumb)
                if insn is None:
                    break
                seen.add(pc)
                func.instructions.add(pc)
                a.code[pc] = insn.size
                flow = self._step(func, insn, regs, pending)
                if not flow:
                    break
                pc += insn.size

    def _decode(self, pc: int, thumb: bool):
        offset = pc - self.a.base
        if thumb:
            chunk = self.a.data[offset:offset + 4]
            half = struct.unpack_from("<H", chunk)[0] if len(chunk) >= 2 else None
            if half is None:
                return None
            # ARMv4T only has 16-bit Thumb plus the BL prefix/suffix pair.
            if (half & 0xF800) in (0xE800, 0xF800):
                return None
            if (half & 0xF800) == 0xF000:
                if len(chunk) < 4 or (struct.unpack_from("<H", chunk, 2)[0] & 0xF800) != 0xF800:
                    return None
            elif (half & 0xE000) == 0xE000 and (half & 0xF800) != 0xE000:
                return None
            insns = list(_THUMB.disasm(chunk, pc, 1))
        else:
            insns = list(_ARM.disasm(self.a.data[offset:offset + 4], pc, 1))
        return insns[0] if insns else None

    def _step(self, func: Function, insn, regs: Dict[str, int], pending: List[int]) -> bool:
        a = self.a
        mnem = insn.mnemonic
        ops = insn.op_str
        thumb = func.thumb
        cond = not thumb and mnem[-2:] in (
            "eq", "ne", "hs", "lo", "mi", "pl", "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "cs", "cc")
        base_mnem = mnem[:-2] if cond else mnem
        if thumb and base_mnem.startswith("b") and len(base_mnem) == 3 and base_mnem not in ("bic", "bkpt"):
            # Thumb conditional branch, e.g. "beq".
            if base_mnem[1:] in ("eq", "ne", "hs", "lo", "mi", "pl", "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "cs", "cc"):
                pending.append(_int(ops.lstrip("#")))
                return True

        m = _LDR_PC.match(ops) if base_mnem == "ldr" else None
        if m:
            pc_value = (insn.address + 4) & ~3 if thumb else insn.address + 8
            literal = pc_value + (_int(m.group(2)) if m.group(2) else 0)
            if a.contains(literal) and literal % 4 == 0:
                a.literals.add(literal)
                value = a.word(literal)
                if m.group(1) == "pc":
                    self._add_code_pointer(value)
                    return cond
                regs[m.group(1)] = value
            return True

        m = _ADD_PC.match(ops) if base_mnem in ("add", "adr") else None
        if m is None and base_mnem == "adr":
            m = _ADR.match(ops)
        if m:
            pc_value = (insn.address + 4) & ~3 if thumb else insn.address + 8
            target = pc_value + _int(m.group(2))
            regs[m.group(1)] = target
            # crt0 installs its ARM interrupt handler by address.
            if not thumb and a.contains(target) and target % 4 == 0 and (a.word(target) >> 28) == 0xE:
                self.add_function(target, False)
            return True

        if base_mnem == "bl":
            target = _int(ops.lstrip("#"))
            a.calls[insn.address] = (target, thumb)
            self.add_function(target, thumb)
            return True

        if base_mnem == "b":
            pending.append(_int(ops.lstrip("#")))
            return cond

        if base_mnem == "bx":
            reg = ops.strip()
            if reg in regs:
                self._add_code_pointer(regs[reg])
            return cond

        if base_mnem in ("mov", "add") and ops.startswith("pc,"):
            src = ops.split(",")[-1].strip()
            if thumb and base_mnem == "mov" and src in regs:
                self._add_jump_table(func, regs[src], pending)
            elif thumb and base_mnem == "mov":
                self._jump_table_from_context(func, insn.address, pending)
            return cond

        if base_mnem == "pop" and "pc" in ops:
            return cond
        if base_mnem.startswith("ldm") and "pc" in ops:
            return cond
        if base_mnem == "ldr" and ops.startswith("pc,"):
            return cond
        if base_mnem == "svc" or base_mnem == "swi":
            return True

        # Invalidate registers written by anything else.
        if ops:
            dest = ops.split(",")[0].strip()
            regs.pop(dest, None)
        return True

    def _add_code_pointer(self, value: int) -> None:
        if not self.a.contains(value & ~1):
            return
        self.add_function(value & ~1, bool(value & 1))

    def _jump_table_from_context(self, func: Function, address: int, pending: List[int]) -> None:
        # agbcc switch: lsls rX, #2; ldr rY, =table; adds rX, rY; ldr rX, [rX]; mov pc, rX
        for back in range(2, 16, 2):
            lit_insn = address - back
            if lit_insn not in func.instructions:
                continue
            insn = self._decode(lit_insn, True)
            if insn is None or insn.mnemonic != "ldr":
                continue
            m = _LDR_PC.match(insn.op_str)
            if not m:
                continue
            literal = ((lit_insn + 4) & ~3) + (_int(m.group(2)) if m.group(2) else 0)
            if self.a.contains(literal):
                self._add_jump_table(func, self.a.word(literal), pending)
                return

    def _add_jump_table(self, func: Function, table: int, pending: List[int]) -> None:
        a = self.a
        address = table
        while a.contains(address) and address % 4 == 0:
            value = a.word(address)
            if not (func.address <= value < func.address + 0x4000) or address in a.literals:
                break
            if value >= table and value < address + 4:
                break
            a.jump_tables.add(address)
            pending.append(value & ~1)
            address += 4

    def _scan_pointers(self) -> bool:
        """Treat odd words pointing at plausible Thumb code as function pointers."""
        a = self.a
        found = False
        for address in range(a.base, a.end - 3, 4):
            if address in a.code or address in a.jump_tables:
                continue
            value = a.word(address)
            if not (value & 1) or not a.contains(value & ~1):
                continue
            target = value & ~1
            if target in a.functions or target in a.code:
                continue
            if not self._looks_like_thumb_entry(target):
                continue
            self.add_function(target, True)
            found = True
        if found:
            self._drain()
        return found

    def _covered(self, address: int) -> bool:
        return address in self.a.code or address in self.a.literals or address in self.a.jump_tables

    def _scan_prologues(self) -> bool:
        """Find Thumb `push {..., lr}` entries in undecoded gaps inside the code region."""
        a = self.a
        limit = max(a.code) if a.code else a.base
        found = False
        address = a.base + 0xC0
        while address < limit:
            if self._covered(address) or self._covered(address & ~3):
                address += 2
                continue
            if (a.half(address) & 0xFF00) == 0xB500 and self._looks_like_thumb_entry(address):
                self.add_function(address, True)
                found = True
            address += 2
        if found:
            self._drain()
        return found

    def _looks_like_thumb_entry(self, address: int) -> bool:
        half = self.a.half(address)
        # push {..., lr}, or common first instructions of leaf functions.
        return (half & 0xFF00) == 0xB500 or (half & 0xFE00) == 0xB400

    def _finish(self) -> None:
        a = self.a
        starts = sorted(a.functions)
        covered = sorted(set(a.code) | a.literals | a.jump_tables)
        a.code_end = 0
        for index, start in enumerate(starts):
            func = a.functions[start]
            limit = starts[index + 1] if index + 1 < len(starts) else a.end
            last = start
            for address in func.instructions:
                if address < limit:
                    last = max(last, address + a.code[address])
            # Extend over literal pools and jump tables that follow the body.
            address = (last + 3) & ~3
            while address < limit and (address in a.literals or address in a.jump_tables):
                address += 4
                last = address
            # Absorb alignment padding.
            while last < limit and last % 4 and a.half(last) == 0:
                last += 2
            func.end = last
            a.code_end = max(a.code_end, last)
