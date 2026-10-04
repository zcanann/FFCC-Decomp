#!/usr/bin/env python3
"""Inspect what the command-list "eat" glitch (CLES) can reach in a live PAL game.

See docs/glitches/cles-targets.md for the background.

Usage:
  cles_scan.py dump <out.bin>              read MEM1 from a running Dolphin (Windows, PAL)
  cles_scan.py edible <mem1.bin>           list every value that currently counts as food
  cles_scan.py scan <mem1.bin>             find edible halfwords inside the CLES reach
  cles_scan.py target <mem1.bin> <value>   where a value's item row lands, and what is there

Addresses are PAL (GCCP01). <value> is a halfword, decimal or 0x-prefixed.
"""

import argparse
import struct
import sys

MEM1_BASE = 0x80000000
MEM1_SIZE = 0x1800000
GAME = 0x8021EEC0                 # CGame Game
CARAVANS = GAME + 0x13F0          # Game.m_caravanWorkArr[9], stride 0xC30
CARAVAN_STRIDE = 0xC30
INVENTORY = 0xB6                  # CCaravanWork::m_inventoryItems
ITEM_TABLE_PTR = GAME + 0xC5A8    # Game.unkCFlatData0[2]
ROW_SIZE = 0x48
FOOD_KINDS = (0x17D, 0x186)       # partyobj.cpp: kinds that go through useItem


class Mem1:
    def __init__(self, data):
        self.data = data

    def u16(self, addr):
        off = addr - MEM1_BASE
        if 0 <= off <= len(self.data) - 2:
            return struct.unpack_from(">H", self.data, off)[0]
        return None

    def u32(self, addr):
        off = addr - MEM1_BASE
        return struct.unpack_from(">I", self.data, off)[0]

    @property
    def item_table(self):
        return self.u32(ITEM_TABLE_PTR)


def row_addr(table, value):
    signed = value - 0x10000 if value & 0x8000 else value
    return table + signed * ROW_SIZE


def edible_values(mem):
    table = mem.item_table
    result = {}
    for value in range(0x10000):
        if value == 0xFFFF:  # empty command slot / already deleted
            continue
        kind = mem.u16(row_addr(table, value))
        if kind in FOOD_KINDS:
            result[value] = kind
    return result


def reach():
    lo = CARAVANS + INVENTORY - 0x10000
    hi = CARAVANS + 7 * CARAVAN_STRIDE + INVENTORY + 0xFFFE
    return lo, hi


def describe(addr):
    off = addr - GAME
    if 0x08 <= off < 0x13F0:
        return "Game.m_gameWork+0x%X" % (off - 0x08)
    if 0x13F0 <= off < 0x81A0:
        k, rel = divmod(off - 0x13F0, CARAVAN_STRIDE)
        return "caravan[%d]+0x%X" % (k, rel)
    if 0x81A0 <= off < 0xC5A0:
        i, rel = divmod(off - 0x81A0, 0x110)
        return "monWork[%d]+0x%X" % (i, rel)
    if 0 <= off < 0x11F88:
        return "Game+0x%X" % off
    return "%s0x%X from Game" % ("-" if off < 0 else "+", abs(off))


def slot_for(addr, caravan):
    return (addr - (CARAVANS + caravan * CARAVAN_STRIDE + INVENTORY)) // 2


def read_dolphin_mem1(game_id=b"GCCP01"):
    import ctypes
    import ctypes.wintypes as wt
    import subprocess

    class MBI(ctypes.Structure):
        _fields_ = [("BaseAddress", ctypes.c_void_p), ("AllocationBase", ctypes.c_void_p),
                    ("AllocationProtect", wt.DWORD), ("PartitionId", wt.WORD),
                    ("RegionSize", ctypes.c_size_t), ("State", wt.DWORD),
                    ("Protect", wt.DWORD), ("Type", wt.DWORD)]

    k32 = ctypes.WinDLL("kernel32", use_last_error=True)
    k32.OpenProcess.restype = wt.HANDLE
    k32.VirtualQueryEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.POINTER(MBI), ctypes.c_size_t]
    k32.ReadProcessMemory.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t,
                                      ctypes.POINTER(ctypes.c_size_t)]

    out = subprocess.check_output(["tasklist", "/FI", "IMAGENAME eq Dolphin.exe", "/FO", "CSV", "/NH"], text=True)
    pids = [int(l.strip('"').split('","')[1]) for l in out.splitlines() if l.lower().startswith('"dolphin.exe"')]
    if not pids:
        sys.exit("Dolphin.exe is not running")
    handle = k32.OpenProcess(0x0400 | 0x0010, False, pids[0])  # QUERY_INFORMATION | VM_READ

    def read(addr, size):
        buf = ctypes.create_string_buffer(size)
        got = ctypes.c_size_t()
        if not k32.ReadProcessMemory(handle, ctypes.c_void_p(addr), buf, size, ctypes.byref(got)):
            return None
        return buf.raw[:got.value]

    addr, mbi = 0, MBI()
    while k32.VirtualQueryEx(handle, ctypes.c_void_p(addr), ctypes.byref(mbi), ctypes.sizeof(mbi)):
        base = mbi.BaseAddress or 0
        if mbi.State == 0x1000 and mbi.Type == 0x40000 and mbi.RegionSize >= MEM1_SIZE:
            if read(base, 6) == game_id:
                data = read(base, MEM1_SIZE)
                if data and len(data) == MEM1_SIZE:
                    return data
        addr = base + mbi.RegionSize
    sys.exit("no %s MEM1 mapping found in Dolphin" % game_id.decode())


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("dump").add_argument("out")
    for name in ("edible", "scan"):
        sub.add_parser(name).add_argument("mem1")
    p = sub.add_parser("target")
    p.add_argument("mem1")
    p.add_argument("value")
    a = ap.parse_args()

    if a.cmd == "dump":
        open(a.out, "wb").write(read_dolphin_mem1())
        print("wrote", a.out)
        return

    mem = Mem1(open(a.mem1, "rb").read())
    table = mem.item_table
    script = mem.data[GAME + 0xC7F4 - MEM1_BASE:GAME + 0xC804 - MEM1_BASE].split(b"\0")[0].decode("latin1")
    print("map script %s, item table %08X" % (script, table))

    if a.cmd == "edible":
        for value, kind in sorted(edible_values(mem).items()):
            where = "table row" if value < 1205 else "outside table"
            signed = value - 0x10000 if value & 0x8000 else value
            print("%6d (0x%04X)  kind 0x%03X  row %08X  %s" % (signed, value, kind, row_addr(table, value), where))
    elif a.cmd == "scan":
        edible = edible_values(mem)
        lo, hi = reach()
        print("reach %08X-%08X" % (lo, hi))
        for addr in range(lo, hi, 2):
            value = mem.u16(addr)
            if value in edible:
                print("%08X  value 0x%04X  %-28s caravan-0 slot %d" % (addr, value, describe(addr), slot_for(addr, 0)))
    elif a.cmd == "target":
        value = int(a.value, 0) & 0xFFFF
        row = row_addr(table, value)
        have = mem.u16(row)
        print("value 0x%04X -> row %08X (%s), halfword there now: %s" % (
            value, row, "inside the item table" if value < 1205 else "outside the table",
            "0x%04X" % have if have is not None else "outside MEM1"))
        if value < 1205:
            print("inside the table: fixed disc data, cannot be made edible")
        else:
            print("needs 0x017D or 0x0186 at %08X to be edible" % row)


if __name__ == "__main__":
    main()
