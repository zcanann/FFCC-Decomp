#!/usr/bin/env python3
"""Derive GC/2.0p1j for the Japanese game library from GC/2.0p1i.

GC/2.0p1h added FFCC's dsl correction (tools/patch_compiler_ffcc.py): a
direct-operand store to a named static is ordered before a later non-store
access, through a register, to an '@'-named static. That recovers the retail
__sinit_* shape where a Pcs singleton's vtable store precedes the PTMF constant
loads (p_system, p_mc, p_gba), but it also fires for singletons that are not
small data. Retail __sinit_p_map_cpp stores CMapPcs's vtables through a base
register into the large .bss object MapPcs and does not order them before the
PTMF loads; stock GC/2.0p1, GC/2.0p1g and GC/2.5 all produce that shape, and
only the dsl step breaks it.

  dsls  dsl applies only when the stored static is small data: the size of the
        store alias's object type (Object +0xE -> Type +0x2) is at most 8
        bytes, the -sdata threshold. A wrapper f_dsl2 placed in free .sbpatch
        space calls f_dsl and adds the size test; the combined predicate's call
        to f_dsl is redirected to it. FFCC JP +1 / -0 exact functions
        (__sinit_p_map_cpp 89.08 -> 100.00); no other function or section moves.

Every edit checks the expected old bytes; input and output are checked by SHA-1.

    python tools/patch_compiler_ffcc3.py <compilers>/GC/2.0p1j/mwcceppc.exe
"""
import hashlib
import shutil
import sys
from pathlib import Path

BASE_VERSION = "GC/2.0p1i"
BASE_SHA1 = "58c5e3ccd07f5ce533695ecedd1a2a7f1eca1d13"
PATCHED_VERSION = "GC/2.0p1j"
PATCHED_SHA1 = "c900a720e9981e7e470b0a0c5558b81ac6f1bb43"

# (file offset, expected old bytes, new bytes)
EDITS = [
    (0x1F8A64, "00" * 52,
     "ff742408ff742408e86302000083c40885c0741d8b4424048b40188b40108b400e85c0740c837802087706b801000000c331c0c3"),
    (0x1F8D7C, "e853ffffff", "e8e3fcffff"),
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


# x86 source of f_dsl2, assembled at 0x1F8A64 (free space after the 2.0p1i
# predicates). f_dsl is at 0x1F8CD4; the combined dispatch predicate's call to
# f_dsl at 0x1F8D7C is redirected here. Kept for review only.
#
#   f_dsl2:
#       push dword ptr [esp+8]
#       push dword ptr [esp+8]
#       call f_dsl
#       add esp, 8
#       test eax, eax
#       jz d2_no
#       mov eax, dword ptr [esp+4]      ; store pcode
#       mov eax, dword ptr [eax+0x18]   ; its alias
#       mov eax, dword ptr [eax+0x10]   ; the static Object (f_dsl checked it)
#       mov eax, dword ptr [eax+0xe]    ; Object.type
#       test eax, eax
#       jz d2_no
#       cmp dword ptr [eax+2], 8        ; Type.size
#       ja d2_no
#       mov eax, 1
#       ret
#   d2_no:
#       xor eax, eax
#       ret


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc3.py <compilers dir | <compilers>/GC/2.0p1j/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
