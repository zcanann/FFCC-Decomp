#!/usr/bin/env python3
"""Derive GC/2.5ffcc, the PAL/USA game compiler, from the stock GC/2.5.

FFCC's retail compiler keeps an object's alias on a store through a pointer
that has an unanalysable reaching definition. GC/2.5's operand_alias (the
alias of a register operand, the union over its reaching address defs) counts a
reaching def whose address_def_alias is NULL as "unknown" and widens the whole
result to the worst-case pointer alias. FFCC's compiler does this differently
for stores, as in PrimeDecomp/mwcc-tools' PATCH_FFCC build of
gc2/src/optimizer/Alias.c:

  in the loop over reaching defs, if address_def_alias(def) is NULL and the
  instruction is a write (pcode->flags & fIsWrite), the def is skipped: it is
  not counted and does not widen the result. After the loop, if something was
  skipped and a result exists, and the result is not a single non-local object
  (an Object/ObjectPart alias whose object->datatype != DLOCAL), the result is
  widened to the worst-case pointer alias (add_alias_member(worst_case_ptr,
  result)).

Three hooks into operand_alias (VA 0x512700), all other bytes stock:

  A  0x512709  `mov [esp+4],0` (count = 0) also clears the free stack slot
               [esp], the "skipped" flag.
  B  0x512778  after `defalias = address_def_alias(def)`: the NULL-and-write
               test, a jump to the loop's advance (0x5128cb) setting skipped, or
               else the stock `count++; if (!alias)` code.
  C  0x5128d5  the function exit: the post-loop clause, then stock return.

The stubs live in a new executable section, .ffcc5, appended after .reloc at the
old SizeOfImage (the section table has a free slot); no existing VA moves. They
are position independent (rel32 jumps; the worst_case_ptr global is read
PC-relatively), so they need no base relocations. They were assembled once from
the x86 in the comments below so the build needs no assembler. Every edit checks
the expected old bytes, and input and output are checked by SHA-1.

    python tools/patch_compiler_ffcc5.py <compilers>/GC/2.5ffcc/mwcceppc.exe
"""
import hashlib
import shutil
import struct
import sys
from pathlib import Path

BASE_VERSION = "GC/2.5"
BASE_SHA1 = "539c0b31d51510cd076755bc64c0c39c3d0f364e"
PATCHED_VERSION = "GC/2.5ffcc"
PATCHED_SHA1 = "fc8966c312fe2dc4fef7800937dd00725520cf4e"

IMAGE_BASE = 0x400000
TEXT_VA, TEXT_OFF = 0x401000, 0x400
SECTION_NAME = b".ffcc5"
SECTION_RVA = 0x20F000        # the old SizeOfImage
SECTION_FILE = 0x1F8A00       # the old end of file
SECTION_SIZE = 0x200
SECTION_FLAGS = 0x60000020    # code, executable, readable
STUB_B = SECTION_RVA + IMAGE_BASE          # 0x60F000
STUB_C = STUB_B + 0x40

# x86 of the stubs. [esp+0x1c] is operand_alias's pcode argument, [esi+0x2c]
# the alias type (0 Object, 1 ObjectPart, 2 Set), [esi+0x10] its object,
# [obj+2] the object's datatype (1 = DLOCAL), [pcode+0x14] pcode->flags
# (fIsWrite = 4), 0x5ea964 worst_case_ptr, 0x513080 add_alias_member(parent,
# child), esi the running result and ebp (dead after the loop) scratch.
#
#   stub B (0x60f000), entered at 0x512778 with eax = address_def_alias(def)
#       mov ebp, eax
#       test eax, eax
#       jne  keep
#       mov  ecx, [esp+0x1c]
#       test byte [ecx+0x14], 4
#       je   keep
#       mov  [esp], esp                 ; skipped = TRUE
#       jmp  0x5128cb                   ; continue
#   keep:
#       inc  dword [esp+4]              ; stock: count++
#       test ebp, ebp
#       je   0x512864                   ; stock: no alias
#       jmp  0x512786                   ; stock: cmp count, 1
#
#   stub C (0x60f040), entered at 0x5128d5 in place of `mov eax,esi; add esp,8`
#       cmp  dword [esp], 0
#       je   done
#       test esi, esi
#       je   done
#       mov  al, [esi+0x2c]
#       cmp  al, 1
#       ja   widen                      ; a Set
#       mov  eax, [esi+0x10]
#       cmp  byte [eax+2], 1
#       jne  done                       ; single non-local object: keep
#   widen:
#       push esi
#       call $+5 / pop eax / mov eax, [eax + (0x5ea964 - pop address)]
#       mov  ebp, eax
#       push ebp
#       call 0x513080                   ; add_alias_member(worst_case_ptr, result)
#       add  esp, 8
#       mov  esi, ebp                   ; result = worst_case_ptr
#   done:
#       mov  eax, esi
#       add  esp, 8
#       jmp  0x5128da                   ; stock: pop ebp / edi / esi / ebx; ret
STUB_B_BYTES = ("89c585c075128b4c241cf64114047408892424e9b338f0ff"
                "ff44240485ed0f844038f0ffe95d37f0ff")
STUB_C_BYTES = ("833c2400742e85f6742a8a462c3c0177098b461080780201751a56e800000000"
                "588b8004b9fdff89c555e81140f0ff83c40889ee89f083c408e95c38f0ff")


def _jmp(frm: int, to: int) -> str:
    return "e9" + struct.pack("<i", to - (frm + 5)).hex()


# (file offset, expected old bytes, new bytes) inside the stock image
EDITS = [
    # A: count = 0 and skipped = 0 (esi is 0 here)
    (0x512709 - TEXT_VA + TEXT_OFF, "c744240400000000", "89742404" "89342490"),
    # B: count++ / test alias, to stub B
    (0x512778 - TEXT_VA + TEXT_OFF, "89c5ff44240485ed0f84de000000",
     _jmp(0x512778, STUB_B) + "90" * 9),
    # C: function exit, to stub C
    (0x5128D5 - TEXT_VA + TEXT_OFF, "89f083c408", _jmp(0x5128D5, STUB_C)),
]


def _apply(data: bytearray) -> bytes:
    for off, old, new in EDITS:
        old_b, new_b = bytes.fromhex(old), bytes.fromhex(new)
        if bytes(data[off:off + len(old_b)]) != old_b or len(old_b) != len(new_b):
            sys.exit(f"unexpected bytes at {off:#x}")
        data[off:off + len(new_b)] = new_b

    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    optsz = struct.unpack_from("<H", data, pe + 20)[0]
    opt = pe + 24
    size_of_image = struct.unpack_from("<I", data, opt + 56)[0]
    size_of_headers = struct.unpack_from("<I", data, opt + 60)[0]
    hdr = opt + optsz + 40 * nsec
    if size_of_image != SECTION_RVA or len(data) != SECTION_FILE:
        sys.exit(f"SizeOfImage {size_of_image:#x} / file size {len(data):#x}, "
                 f"expected {SECTION_RVA:#x} / {SECTION_FILE:#x}")
    if hdr + 40 > size_of_headers or any(data[hdr:hdr + 40]):
        sys.exit(f"no free section header slot at {hdr:#x}")
    struct.pack_into("<8sIIIIIIHHI", data, hdr, SECTION_NAME, SECTION_SIZE,
                     SECTION_RVA, SECTION_SIZE, SECTION_FILE, 0, 0, 0, 0,
                     SECTION_FLAGS)
    struct.pack_into("<H", data, pe + 6, nsec + 1)
    struct.pack_into("<I", data, opt + 56, size_of_image + 0x1000)
    section = bytearray(SECTION_SIZE)
    b, c = bytes.fromhex(STUB_B_BYTES), bytes.fromhex(STUB_C_BYTES)
    section[:len(b)] = b
    section[STUB_C - STUB_B:STUB_C - STUB_B + len(c)] = c
    return bytes(data + section)


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
    out = _apply(data)
    result = hashlib.sha1(out).hexdigest()
    if result != PATCHED_SHA1:
        sys.exit(f"derived compiler has SHA-1 {result}, expected {PATCHED_SHA1}")
    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file() and f.name != "mwcceppc.exe":
            shutil.copy2(f, dst_dir / f.name)
    tmp = dst.with_suffix(".tmp")
    tmp.write_bytes(out)
    tmp.replace(dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc5.py <compilers dir | <compilers>/GC/2.5ffcc/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
