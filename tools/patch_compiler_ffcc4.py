#!/usr/bin/env python3
"""Derive GC/2.0p1k for the Japanese game library from GC/2.0p1j.

FFCC's dsl clause (GC/2.0p1h, tools/patch_compiler_ffcc.py; narrowed to
small-data stores by GC/2.0p1j) orders a direct-operand store to a named static
before a later non-store access, through a register, to an '@'-named static.
Its load test rejected every access whose third operand is symbolic (arg kind
3). Before register allocation the PTMF constant loads use an immediate offset,
but after register allocation the peephole pass merges `addi rB,rB,@N@l` and
`lwz rX,0(rB)` into `lwzu rX,@N@l(rB)`, whose offset operand is symbolic. The
post-allocation scheduler therefore saw no edge from the `__sinit_*` vtable
store of an sda21 singleton to that `lwzu` and moved the load above the store.

  dslu  the dsl load test also accepts a symbolic third operand when the base
        operand is a register other than r0, i.e. an access through a register
        rather than a direct r0-based (sda21) operand. A stub in free .sbpatch
        space replaces the `cmp byte [edi+0x3c],3 / je dl_no` test inside f_dsl.
        FFCC JP +4 / -0 exact functions (__sinit_p_game_cpp,
        __sinit_p_system_cpp, __sinit_p_mc_cpp, __sinit_p_gba_cpp).

Every edit checks the expected old bytes; input and output are checked by SHA-1.

    python tools/patch_compiler_ffcc4.py <compilers>/GC/2.0p1k/mwcceppc.exe
"""
import hashlib
import shutil
import sys
from pathlib import Path

BASE_VERSION = "GC/2.0p1j"
BASE_SHA1 = "c900a720e9981e7e470b0a0c5558b81ac6f1bb43"
PATCHED_VERSION = "GC/2.0p1k"
PATCHED_SHA1 = "abeb8e6e85568dd4e904e26ae3ca55b5b2cc5bcd"

# (file offset, expected old bytes, new bytes)
EDITS = [
    (0x1F8AA0, "00" * 32,
     "807f3c037515807f30000f857102000066837f34000f8466020000e942020000"),
    (0x1F8CFC, "807f3c03741f", "e99ffdffff90"),
]


def derive(compilers: Path) -> None:
    src_dir = compilers / BASE_VERSION
    dst_dir = compilers / PATCHED_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"
    if not src.exists():
        sys.exit(f"{src} not found")
    data = bytearray(src.read_bytes())
    actual = hashlib.sha1(data).hexdigest()
    if actual != BASE_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}; refusing to patch an unknown build")
    if dst.exists() and hashlib.sha1(dst.read_bytes()).hexdigest() == PATCHED_SHA1:
        return
    for off, old, new in EDITS:
        old_b, new_b = bytes.fromhex(old), bytes.fromhex(new)
        if bytes(data[off:off + len(old_b)]) != old_b:
            sys.exit(f"unexpected bytes at {off:#x}")
        data[off:off + len(new_b)] = new_b
    result = hashlib.sha1(data).hexdigest()
    if result != PATCHED_SHA1:
        sys.exit(f"derived compiler has SHA-1 {result}, expected {PATCHED_SHA1}")
    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file() and f.name != "mwcceppc.exe":
            shutil.copy2(f, dst_dir / f.name)
    tmp = dst.with_suffix(".tmp")
    tmp.write_bytes(data)
    tmp.replace(dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")


# x86 source of the dslu stub, assembled at 0x1F8AA0 (VA 0x60E8A0, free space
# after the 2.0p1j wrapper). f_dsl is at 0x1F8CD4 (VA 0x60EAD4); its load test
# `cmp byte ptr [edi+0x3c], 3 / je dl_no` at 0x1F8CFC (VA 0x60EAFC) becomes a
# jump to the stub. edi is the later (load) pcode; its operands are 12-byte
# records at +0x24, +0x30 and +0x3c (kind byte at +0, register number at +4).
# Kept for review only.
#
#   f_dslu:
#       cmp byte ptr [edi+0x3c], 3      ; offset operand symbolic?
#       jne du_ok                       ; no: as before
#       cmp byte ptr [edi+0x30], 0      ; base operand a register...
#       jne dl_no                       ; (VA 0x60EB21)
#       cmp word ptr [edi+0x34], 0      ; ...other than r0
#       je dl_no
#   du_ok:
#       jmp dl_cont                     ; VA 0x60EB02, f_dsl's next test


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc4.py <compilers dir | <compilers>/GC/2.0p1k/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
