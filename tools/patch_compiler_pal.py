#!/usr/bin/env python3
"""Derive GC/2.5a for the PAL and USA game library from the stock GC/2.5.

One alias-analysis correction (kss), found by rebuilding every PAL and USA
game unit with source-built variants of GC 2.5 (the mweppc decompilation) and
then ported to the stock binary:

  kss   Alias.c operand_alias: a STORE whose base register has several reaching
        definitions, some with an alias and some without, keeps the alias of
        the definitions that have one when that alias is a single static
        object (whole or part; Object datatype != DLOCAL). Stock GC 2.5 makes
        every such access worst_case. Loads, and stores into locals, are
        unchanged. Typical case: `target = cond ? (T*)gPppDefaultValueBuffer :
        (T*)(work + off)` followed by stores through `target`; retail keeps
        `*valuePtr` in a register across those stores.

The patch adds a section .ffpatch after .reloc (no existing section, VA or RVA
moves; the section table has room for an eleventh header) holding three
position-independent stubs, and redirects three spots of operand_alias
(0x512700) to them. Every redirect is a REL32 call/jump over bytes that carry
no base relocation, and the only global the stubs read (worst_case_ptr) is
loaded PC-relatively, so the result survives a rebase.

Input and output are checked by SHA-1 and every edit by its expected old bytes.

    python tools/patch_compiler_pal.py <compilers>/GC/2.5a/mwcceppc.exe
"""
import hashlib
import os
import shutil
import struct
import sys
from pathlib import Path

BASE_VERSION = "GC/2.5"
BASE_SHA1 = "539c0b31d51510cd076755bc64c0c39c3d0f364e"
PATCHED_VERSION = "GC/2.5a"
PATCHED_SHA1 = "9cf46cd73d0aa756865fd0b29182802759b1aceb"

IMAGE_BASE = 0x00400000
TEXT_VA, TEXT_FILE = 0x00401000, 0x400
SECTION_NAME = b".ffpatch"
SECTION_RVA = 0x0020F000      # stock SizeOfImage
SECTION_FILE = 0x001F8A00     # stock file size
SECTION_RAW = 0x200
SECTION_VIRT = 0x1000
SECTION_FLAGS = 0x60000020    # code | execute | read
S = IMAGE_BASE + SECTION_RVA  # VA of the stubs

INIT, ITER, EXIT = S + 0x00, S + 0x20, S + 0x60

# Addresses inside stock operand_alias (0x512700) and its callees.
LOOP_NEXT = 0x005128CB        # mov ebx,[ebx]: next reaching definition
NOALIAS = 0x00512864          # stock path for a definition without an alias
HASALIAS = 0x00512786         # stock path for a definition with an alias
ADD_ALIAS_MEMBER = 0x00513080
WORST_CASE_PTR = 0x005EA964   # Alias* worst_case_ptr


def rel32(src_next, dst):
    return struct.pack("<i", dst - src_next)


def stubs() -> bytes:
    out = bytearray(SECTION_RAW)

    # kss_init: called from operand_alias's prologue in place of
    # `mov dword ptr [esp+4], 0` (count = 0). Also clears [esp], the unused
    # second local, which holds the "skipped a no-alias store definition" flag.
    #   mov dword ptr [esp+8], 0
    #   mov dword ptr [esp+4], 0
    #   ret
    init = bytes.fromhex("c744240800000000" "c744240400000000" "c3")
    out[0x00:0x00 + len(init)] = init

    # kss_iter: replaces `inc [esp+4] / test ebp,ebp / je NOALIAS` after
    # address_def_alias (ebp = its result, [esp+0x1c] = the pcode).
    #       test ebp, ebp
    #       jne  has_alias
    #       mov  eax, [esp+0x1c]
    #       test byte ptr [eax+0x14], 4      ; fIsWrite
    #       je   stock_noalias
    #       mov  dword ptr [esp], 1          ; skipped = TRUE
    #       jmp  LOOP_NEXT                   ; neither counted nor merged
    #   stock_noalias:
    #       inc  dword ptr [esp+4]
    #       jmp  NOALIAS
    #   has_alias:
    #       inc  dword ptr [esp+4]
    #       jmp  HASALIAS
    a = ITER
    it = bytearray()
    it += bytes.fromhex("85ed" "751f" "8b44241c" "f6401404" "740c" "c7042401000000")
    it += b"\xe9" + rel32(a + len(it) + 5, LOOP_NEXT)
    it += bytes.fromhex("ff442404")
    it += b"\xe9" + rel32(a + len(it) + 5, NOALIAS)
    it += bytes.fromhex("ff442404")
    it += b"\xe9" + rel32(a + len(it) + 5, HASALIAS)
    assert len(it) == 44
    out[0x20:0x20 + len(it)] = it

    # kss_exit: replaces `mov eax, esi / add esp, 8` at the epilogue.
    #       mov  eax, esi                    ; result
    #       cmp  dword ptr [esp], 0
    #       je   done                        ; nothing skipped: stock result
    #       test eax, eax
    #       je   done                        ; no definition had an alias
    #       cmp  byte ptr [eax+0x2c], 1      ; Object (0) or ObjectPart (1)?
    #       ja   fallback
    #       mov  ecx, [eax+0x10]             ; alias->object
    #       cmp  byte ptr [ecx+2], 1         ; datatype == DLOCAL?
    #       jne  done                        ; a static: keep its alias
    #   fallback:                            ; stock answer, as create_alias_union
    #       call getpc
    #   getpc:
    #       pop  edx
    #       mov  edx, [edx + (WORST_CASE_PTR - getpc)]
    #       push edx
    #       push eax
    #       push edx
    #       call add_alias_member            ; (worst_case_ptr, result)
    #       pop  ecx
    #       pop  ecx
    #       pop  eax                         ; worst_case_ptr
    #   done:
    #       add  esp, 8
    #       pop  ebp / pop edi / pop esi / pop ebx
    #       ret
    b = EXIT
    ex = bytearray()
    ex += bytes.fromhex("89f0" "833c2400" "742a" "85c0" "7426" "80782c01" "7709" "8b4810" "80790201" "7517")
    assert len(ex) == 27
    ex += bytes.fromhex("e800000000")          # call getpc
    getpc = b + len(ex)
    ex += bytes.fromhex("5a")                  # pop edx
    ex += bytes.fromhex("8b92") + struct.pack("<i", WORST_CASE_PTR - getpc)
    ex += bytes.fromhex("525052")
    ex += b"\xe8" + rel32(b + len(ex) + 5, ADD_ALIAS_MEMBER)
    ex += bytes.fromhex("595958")
    assert len(ex) == 50
    ex += bytes.fromhex("83c408" "5d5f5e5b" "c3")
    out[0x60:0x60 + len(ex)] = ex
    return bytes(out)


def hooks():
    """(va, old bytes, new bytes) inside operand_alias."""
    return [
        (0x00512709, bytes.fromhex("c744240400000000"),
         b"\xe8" + rel32(0x00512709 + 5, INIT) + b"\x90\x90\x90"),
        (0x0051277A, bytes.fromhex("ff44240485ed0f84de000000"),
         b"\xe9" + rel32(0x0051277A + 5, ITER) + b"\x90" * 7),
        (0x005128D5, bytes.fromhex("89f083c408"),
         b"\xe9" + rel32(0x005128D5 + 5, EXIT)),
    ]


def apply(data: bytearray) -> bytes:
    for va, old, new in hooks():
        off = va - TEXT_VA + TEXT_FILE
        if bytes(data[off:off + len(old)]) != old:
            sys.exit(f"unexpected bytes at {va:#x}: {data[off:off + len(old)].hex()}")
        data[off:off + len(new)] = new

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
    struct.pack_into("<8sIIIIIIHHI", data, hdr, SECTION_NAME, SECTION_VIRT, SECTION_RVA,
                     SECTION_RAW, SECTION_FILE, 0, 0, 0, 0, SECTION_FLAGS)
    struct.pack_into("<H", data, pe + 6, nsec + 1)
    struct.pack_into("<I", data, opt + 56, size_of_image + SECTION_VIRT)
    data += stubs()
    return bytes(data)


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
    if PATCHED_SHA1 and dst.exists() and hashlib.sha1(dst.read_bytes()).hexdigest() == PATCHED_SHA1:
        return
    out = apply(data)
    result = hashlib.sha1(out).hexdigest()
    if PATCHED_SHA1 is None:
        print(f"NOTE: PATCHED_SHA1 unset; this build is {result}")
    elif result != PATCHED_SHA1:
        sys.exit(f"derived compiler has SHA-1 {result}, expected {PATCHED_SHA1}")
    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file() and f.name != "mwcceppc.exe":
            shutil.copy2(f, dst_dir / f.name)
    tmp = dst.with_suffix(".tmp")
    tmp.write_bytes(out)
    os.chmod(tmp, 0o755)
    tmp.replace(dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_pal.py <compilers dir | <compilers>/GC/2.5a/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
