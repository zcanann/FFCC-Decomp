#!/usr/bin/env python3
"""Check .sdata2 symbols in gaps between claimed ranges."""
import re

syms = []
with open("config/GCCP01/symbols.txt") as f:
    for line in f:
        line = line.strip()
        if not line or line.startswith('#') or line.startswith('//'):
            continue
        m = re.match(r'(\S+)\s*=\s*\.sdata2:(0x[\da-fA-F]+)\s*;.*?size:(0x[\da-fA-F]+)', line)
        if m:
            syms.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))

syms.sort(key=lambda x: x[1])

# Print all .sdata2 symbols with running totals
print(f"Total .sdata2 symbols: {len(syms)}")
print(f"Range: 0x{syms[0][1]:08X} - 0x{syms[-1][1]+syms[-1][2]:08X}")

running = 0
for name, addr, size in syms:
    running += size
    if addr < 0x8032F710 or (0x8032F868 <= addr < 0x8032FEF8):
        print(f"  0x{addr:08X} [{size:>4}] running={running:>5} {name}")

print(f"\nSymbols in gap 0x8032F710-0x8032F850:")
gap_total = 0
for name, addr, size in syms:
    if 0x8032F710 <= addr < 0x8032F850:
        gap_total += size
        print(f"  0x{addr:08X} [{size:>4}] cum={gap_total:>4} {name}")
print(f"Gap total: {gap_total} bytes, gap size: {0x8032F850-0x8032F710} = {0x8032F850-0x8032F710}")

print(f"\nSymbols in gap 0x8032F868-0x8032FEF8:")
gap_total = 0
for name, addr, size in syms:
    if 0x8032F868 <= addr < 0x8032FEF8:
        gap_total += size
        print(f"  0x{addr:08X} [{size:>4}] cum={gap_total:>4} {name}")
print(f"Gap total: {gap_total} bytes")
