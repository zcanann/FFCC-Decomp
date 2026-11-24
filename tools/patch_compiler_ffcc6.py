#!/usr/bin/env python3
"""Derive GC/2.0p1l, the Japanese game compiler, from GC/2.0p1k.

GC/2.0p1k is BFBB's GC/2.0p1g binary-patch chain plus FFCC's own corrections
(tools/patch_compiler_ffcc{,2,3,4}.py). The chain emulates BFBB's GC 2.0p2
clause by clause, but 2.0p2's scheduler asks may_alias_scheduling(a, b) where
2.0p1 asks may_alias(a, b), and its gather_instruction_alias starts with two
rules the chain lacks. This patch adds those, plus two FFCC rules of our own
that Japan needs. It has two hooks:

  gather  gather_instruction_alias (0x5123B0) first applies 2.0p2's two rules
          to pcode->alias: a write that is a direct small-data access (alias
          an object or object part that is not a local and not '@'-named, with
          an Addr16 memory operand) to a global that is not a safe const gets
          the worst_case alias, so value numbering forgets other globals after
          it (LetterClose reloads m_letterMenuState after the store to
          s_BackUpCur[0]); and a load of a floating-point '@' literal in inline
          data gets worst_case. The stock function then runs unchanged.
  sched   the scheduler's three dependency-graph queries (serialize_store
          twice, findsuccessors once; VA 0x5081F2, 0x50836B and 0x5083A0,
          formerly calls of may_alias) call a new routine that answers as
          2.0p2's may_alias_scheduling, extended:
          1. is_small_data_load(a) with is_direct_small_data_store(b), in
             either order, may alias.
          2. is_pointer_like_load: a load that is a direct small-data access
             (also of a const global, FFCC's first rule) or a load of
             any part (not only the whole, FFCC's second rule) of a non-float
             '@' object through an Addr16 operand is queried as a worst_case
             access.
          3. The stock may_alias (0x511FC0, with the chain's clauses, including
             pwcp) answers the remaining question, with the substituted aliases
             written into the two PCodes for the duration of the call and
             restored afterwards.

Both only add worst_case aliases or may-alias answers, so the chain's other
clauses (e3ns, c3a, dsl and BFBB's) keep working, and a query that none of the
above touches takes the old path. Offsets: PCode flags +0x14 (fIsWrite 4),
alias +0x18, argCount +0x22, args +0x24 (12 bytes: kind, arg); Alias object
+0x10, type +0x2C (2 = set); Object datatype +2 (1 = DLOCAL), name +0xA
(HashNameNode, characters from +0xA), type +0xE, qual +0x12 (Q_INLINE_DATA
0x10000); Type kind +0 (2 = float), size +2. is_safe_const is stock 0x5133E0,
worst_case_ptr the global at 0x5E9CB4 and copts.sdata_threshold the word at
0x5E4838; both are read PC-relatively.

The code lives in a new executable section, .ffcc6, appended after .sbpatch at
the old SizeOfImage (the section table has a free slot), so no existing VA
moves. It uses rel32 calls and PC-relative data reads only, so it needs no base
relocations. It was assembled once from the x86 kept below, so the build needs
no assembler. Every edit checks the expected old bytes, and the input and
output are checked by SHA-1.

    python tools/patch_compiler_ffcc6.py <compilers>/GC/2.0p1l/mwcceppc.exe
"""
import hashlib
import shutil
import struct
import sys
from pathlib import Path

BASE_VERSION = "GC/2.0p1k"
BASE_SHA1 = "abeb8e6e85568dd4e904e26ae3ca55b5b2cc5bcd"
PATCHED_VERSION = "GC/2.0p1l"
PATCHED_SHA1 = "bfccb4b31e5d12fa7fac79ffa2f5ffa1e8a99588"

IMAGE_BASE = 0x400000
TEXT_VA, TEXT_OFF = 0x401000, 0x400
SECTION_NAME = b".ffcc6"
SECTION_RVA = 0x20F000        # the old SizeOfImage
SECTION_FILE = 0x1F9200       # the old end of file
SECTION_SIZE = 0x400
SECTION_FLAGS = 0x60000020    # code, executable, readable
STUB = SECTION_RVA + IMAGE_BASE            # 0x60F000
SCHED_ALIAS = STUB + 0x1B0                # sched_alias
MAY_ALIAS = 0x511FC0
CALL_SITES = (0x5081F2, 0x50836B, 0x5083A0)
GATHER_ENTRY = 0x5123B0                    # gather_instruction_alias
GATHER_HOOK = STUB + 0x29C                # gather_hook

STUB_BYTES = (
    "e8000000005881e805f0600005b49c5e008b00c38b4c240885c9743580792c02"
    "742f8b49108079020174268b510a807a0a40741d8b54240466837a22027e1280"
    "7a3c03750c807a3d027506b801000000c331c0c3538b5c24088b431885c07458"
    "f643140474275053e8a7ffffff83c40885c074198b4318ff7010e83d00000083"
    "c40484c07507e875ffffffeb2b8b431880782c0274228b48108b510e803a0275"
    "17f7411200000100740e8b510a807a0a407505e848ffffff5bc36690e91f43f0"
    "ff0f1f008b442404f64014047556ff74240850e83cffffff83c40885c0753f8b"
    "4c240885c9743d80792c0274378b491080790201742e8b510a807a0a4075258b"
    "510e803a02741d8b54240466837a22027e12807a3c03750c807a3d027506b801"
    "000000c331c0c3908b442404f640140475418b4c240885c9743980792c027433"
    "8b491080790201742a8b510a807a0a4074218b490e8b4902e8000000005881e8"
    "5df160000538485e003b087f06b801000000c331c0c366908b442404f6401404"
    "7428e879feffff3b442408751d8b54240466837a22027e12807a3c03750c807a"
    "3d027506b801000000c331c0c30f1f005356575583ec108b7424248b7c2428e8"
    "3cfeffff89c58b46188904248b47188944240456e87bfeffff83c40489442408"
    "57e86efeffff83c4048944240cff74240856e831ffffff83c40885c07411ff74"
    "240c57e870ffffff83c40885c07578ff74240c57e80fffffff83c40885c07411"
    "ff74240856e84effffff83c40885c07556ff74240856e889feffff83c40885c0"
    "7404896c2408ff74240c57e874feffff83c40885c07404896c240c8b44240889"
    "46188b44240c8947185756e82400000083c4080fb6d88b04248946188b442404"
    "89471889d8eb05b80100000083c4105d5f5e5bc3e9272df0ff0f1f008b442404"
    "50e8aefdffff83c4048b4c24048941185356575583ec18e9fb30f0ff"
)


def _rel(frm: int, to: int) -> str:
    return struct.pack("<i", to - (frm + 5)).hex()


# (file offset, expected old bytes, new bytes) inside the stock image: the
# three scheduler call sites, each call of may_alias retargeted to sched_alias
EDITS = [
    (va - TEXT_VA + TEXT_OFF, "e8" + _rel(va, MAY_ALIAS), "e8" + _rel(va, SCHED_ALIAS))
    for va in CALL_SITES
] + [
    # gather_instruction_alias' `push ebx/esi/edi/ebp; sub esp,0x18` (the hook
    # runs them itself) becomes a jump to gather_hook
    (GATHER_ENTRY - TEXT_VA + TEXT_OFF, "53565755" "83ec18",
     "e9" + _rel(GATHER_ENTRY, GATHER_HOOK) + "9090"),
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
    code = bytes.fromhex(STUB_BYTES)
    section[:len(code)] = code
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


# x86 source of the routine (Intel syntax), assembled once at 0x60F000 with
# every external reference resolved to rel32 or PC-relative; kept for review
# only. Arguments are cdecl on the stack. dsa, eff, plike, sdload and dsstore
# are the 2.0p2 helpers is_direct_small_data_access, the gather rules,
# is_pointer_like_load, is_small_data_load and is_direct_small_data_store;
# sched_alias is may_alias_scheduling.
#
#   .set BASE, 0x60f000
#   .set WCP, 0x5e9cb4
#   .set SDT, 0x5e4838
#   .set STOCK, 0x511fc0
#   .set GATHER, 0x5123b7
#   .set GWC1, BASE + (gwc1 - start)
#   .set SDL1, BASE + (sdl1 - start)
#   .set SAFECONST, 0x5133e0
#   start:
#
#   # get_wc: eax = worst_case_ptr (PIC)
#   get_wc:
#       call gwc1
#   gwc1:
#       pop eax
#       sub eax, offset GWC1
#       add eax, WCP
#       mov eax, [eax]
#       ret
#   # dsa(p, al): direct small-data access
#   dsa:
#       mov ecx, [esp+8]
#       test ecx, ecx
#       jz dsa_no
#       cmp byte ptr [ecx+0x2c], 2
#       je dsa_no
#       mov ecx, [ecx+0x10]
#       cmp byte ptr [ecx+2], 1
#       je dsa_no
#       mov edx, [ecx+0xa]
#       cmp byte ptr [edx+0xa], 0x40
#       je dsa_no
#       mov edx, [esp+4]
#       cmp word ptr [edx+0x22], 2
#       jle dsa_no
#       cmp byte ptr [edx+0x3c], 3
#       jne dsa_no
#       cmp byte ptr [edx+0x3d], 2
#       jne dsa_no
#       mov eax, 1
#       ret
#   dsa_no:
#       xor eax, eax
#       ret
#   # eff(p): alias after gather_instruction_alias' p2 rules
#   eff:
#       push ebx
#       mov ebx, [esp+8]
#       mov eax, [ebx+0x18]
#       test eax, eax
#       jz eff_out
#       test byte ptr [ebx+0x14], 4
#       jz eff_lit
#       push eax
#       push ebx
#       call dsa
#       add esp, 8
#       test eax, eax
#       jz eff_lit
#       mov eax, [ebx+0x18]
#       push dword ptr [eax+0x10]
#       call fix_safeconst
#       add esp, 4
#       test al, al
#       jnz eff_lit
#       call get_wc
#       jmp eff_out
#   eff_lit:
#       mov eax, [ebx+0x18]
#       cmp byte ptr [eax+0x2c], 2
#       je eff_out
#       mov ecx, [eax+0x10]
#       mov edx, [ecx+0xe]
#       cmp byte ptr [edx], 2
#       jne eff_out
#       test dword ptr [ecx+0x12], 0x10000
#       jz eff_out
#       mov edx, [ecx+0xa]
#       cmp byte ptr [edx+0xa], 0x40
#       jne eff_out
#       call get_wc
#   eff_out:
#       pop ebx
#       ret
#   fix_safeconst:
#       .byte 0xe9
#       .long SAFECONST - (BASE + (. - start) + 4)
#   # plike(p, al): is_pointer_like_load
#   plike:
#       mov eax, [esp+4]
#       test byte ptr [eax+0x14], 4
#       jnz pl_no
#       push dword ptr [esp+8]
#       push eax
#       call dsa
#       add esp, 8
#       test eax, eax
#       jnz pl_yes
#       mov ecx, [esp+8]
#       test ecx, ecx
#       jz pl_no
#       cmp byte ptr [ecx+0x2c], 2
#       je pl_no
#       mov ecx, [ecx+0x10]
#       cmp byte ptr [ecx+2], 1
#       je pl_no
#       mov edx, [ecx+0xa]
#       cmp byte ptr [edx+0xa], 0x40
#       jne pl_no
#       mov edx, [ecx+0xe]
#       cmp byte ptr [edx], 2
#       je pl_no
#       mov edx, [esp+4]
#       cmp word ptr [edx+0x22], 2
#       jle pl_no
#       cmp byte ptr [edx+0x3c], 3
#       jne pl_no
#       cmp byte ptr [edx+0x3d], 2
#       jne pl_no
#   pl_yes:
#       mov eax, 1
#       ret
#   pl_no:
#       xor eax, eax
#       ret
#   # sdload(p, al): is_small_data_load
#   sdload:
#       mov eax, [esp+4]
#       test byte ptr [eax+0x14], 4
#       jnz sl_no
#       mov ecx, [esp+8]
#       test ecx, ecx
#       jz sl_no
#       cmp byte ptr [ecx+0x2c], 2
#       je sl_no
#       mov ecx, [ecx+0x10]
#       cmp byte ptr [ecx+2], 1
#       je sl_no
#       mov edx, [ecx+0xa]
#       cmp byte ptr [edx+0xa], 0x40
#       je sl_no
#       mov ecx, [ecx+0xe]
#       mov ecx, [ecx+2]
#       call sdl1
#   sdl1:
#       pop eax
#       sub eax, offset SDL1
#       add eax, SDT
#       cmp ecx, [eax]
#       jg sl_no
#       mov eax, 1
#       ret
#   sl_no:
#       xor eax, eax
#       ret
#   # dsstore(p, al): is_direct_small_data_store
#   dsstore:
#       mov eax, [esp+4]
#       test byte ptr [eax+0x14], 4
#       jz ds_no
#       call get_wc
#       cmp eax, [esp+8]
#       jne ds_no
#       mov edx, [esp+4]
#       cmp word ptr [edx+0x22], 2
#       jle ds_no
#       cmp byte ptr [edx+0x3c], 3
#       jne ds_no
#       cmp byte ptr [edx+0x3d], 2
#       jne ds_no
#       mov eax, 1
#       ret
#   ds_no:
#       xor eax, eax
#       ret
#   # sched_alias(a, b): may_alias_scheduling
#   sched_alias:
#       push ebx
#       push esi
#       push edi
#       push ebp
#       sub esp, 16
#       mov esi, [esp+0x24]
#       mov edi, [esp+0x28]
#       call get_wc
#       mov ebp, eax
#       mov eax, [esi+0x18]
#       mov [esp], eax
#       mov eax, [edi+0x18]
#       mov [esp+4], eax
#       push esi
#       call eff
#       add esp, 4
#       mov [esp+8], eax
#       push edi
#       call eff
#       add esp, 4
#       mov [esp+12], eax
#       push dword ptr [esp+8]
#       push esi
#       call sdload
#       add esp, 8
#       test eax, eax
#       jz sa_r1b
#       push dword ptr [esp+12]
#       push edi
#       call dsstore
#       add esp, 8
#       test eax, eax
#       jnz sa_yes
#   sa_r1b:
#       push dword ptr [esp+12]
#       push edi
#       call sdload
#       add esp, 8
#       test eax, eax
#       jz sa_pl
#       push dword ptr [esp+8]
#       push esi
#       call dsstore
#       add esp, 8
#       test eax, eax
#       jnz sa_yes
#   sa_pl:
#       push dword ptr [esp+8]
#       push esi
#       call plike
#       add esp, 8
#       test eax, eax
#       jz sa_pl2
#       mov [esp+8], ebp
#   sa_pl2:
#       push dword ptr [esp+12]
#       push edi
#       call plike
#       add esp, 8
#       test eax, eax
#       jz sa_call
#       mov [esp+12], ebp
#   sa_call:
#       mov eax, [esp+8]
#       mov [esi+0x18], eax
#       mov eax, [esp+12]
#       mov [edi+0x18], eax
#       push edi
#       push esi
#       call stock
#       add esp, 8
#       movzx ebx, al
#       mov eax, [esp]
#       mov [esi+0x18], eax
#       mov eax, [esp+4]
#       mov [edi+0x18], eax
#       mov eax, ebx
#       jmp sa_out
#   sa_yes:
#       mov eax, 1
#   sa_out:
#       add esp, 16
#       pop ebp
#       pop edi
#       pop esi
#       pop ebx
#       ret
#   stock:
#       .byte 0xe9
#       .long STOCK - (BASE + (. - start) + 4)
#   # gather_hook: entered by a jump replacing the first instructions of
#   # gather_instruction_alias (0x5123B0); applies the 2.0p2 pre-rules to pcode->alias
#   gather_hook:
#       mov eax, [esp+4]
#       push eax
#       call eff
#       add esp, 4
#       mov ecx, [esp+4]
#       mov [ecx+0x18], eax
#       push ebx
#       push esi
#       push edi
#       push ebp
#       sub esp, 0x18
#       .byte 0xe9
#       .long GATHER - (BASE + (. - start) + 4)
#   end:


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc6.py <compilers dir | <compilers>/GC/2.0p1l/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
