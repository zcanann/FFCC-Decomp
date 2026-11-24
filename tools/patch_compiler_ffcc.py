#!/usr/bin/env python3
"""Derive GC/2.0p1h for the Japanese game library from GC/2.0p1g.

GC/2.0p1g is BFBB's model of the 2003 retail CodeWarrior (tools/patch_compiler.py
and tools/patch_compiler_rw.py). FFCC Japan exercises two further retail
behaviours that 2.0p1g lacks. Both are narrow emulation corrections of the
scheduler's may-alias answers, measured on all Japanese game units and on a
frozen BFBB checkout (see docs/compiler_baseline.md):

  e3ns  BFBB's clause E3n, corrected: a store with a subrange alias into a frame
        object whose address escapes (declared, inlined or compiler '@' local,
        including struct-copy stores flagged 0x40) is ordered before a later
        whole literal-pool load of at most 8 bytes. E3n's predicate was too
        narrow for these stores. FFCC JP +13 / -0 exact; BFBB game 0 / -1
        (xBoxFromCircle, BFBB's documented E3n counter-witness), RW 0 / 0.
  dsl   a direct-operand store to a named static is ordered before a later
        non-store access, through a register, to an '@'-named static (the
        __sinit_* vtable store before the PTMF constant loads). FFCC JP +2 / -0
        exact and 12 exception-table sections exact; BFBB 0 / 0.

The patch redirects four scheduler may_alias dispatch entries (0, 1, 3, 4) to a
predicate stub and adds the predicate code in free space of the .sbpatch
section. It was assembled once from the x86 source kept in ASM_REFERENCE below;
the bytes are applied here so the build needs no assembler. Every edit checks
the expected old bytes, and the input and output are checked by SHA-1.

    python tools/patch_compiler_ffcc.py <compilers>/GC/2.0p1h/mwcceppc.exe
"""
import hashlib
import shutil
import sys
from pathlib import Path

BASE_VERSION = "GC/2.0p1g"
BASE_SHA1 = "99bd18455ff674337d7a6186164df8a1b1ba13a7"
PATCHED_VERSION = "GC/2.0p1h"
PATCHED_SHA1 = "6114c0c66bc9b4ded51a1a278402a753ab12792c"

# (file offset, expected old bytes, new bytes)
EDITS = [
    (0x1BA6BC, "7ce560009be560008b205100bae56000d9e5", "e8eb60002cee60008b20510044ee60005cee"),
    (0x1F8C70, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "56578b74240c8b7c241056e8340300005985c0744157e8290300005985c075368b4e1885c9742f80792c0175298b571885d27422807a2c00751c837a1808771652e8ce0200005985c0740bff7618e81d03000059eb0231c05f5ec3"),
    (0x1F8CD4, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "56578b74240c8b7c2410807e3c03753d56e8ca0200005985c07432ff7618e85d0200005985c07425807f3c03741f57e8ac0200005985c07514ff7718e86f0200005985c07407b801000000eb0231c05f5ec3"),
    (0x1F8D30, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "8b44240485c0742f80782c0274298b401085c07422833805751de8000000005981e94feb600081c108d05b0039480e7406b801000000c331c0c3"),
    (0x1F8D74, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "ff742408ff742408e853ffffff83c40885c07517ff742408ff742408e8dbfeffff83c40885c0750331c0c3b801000000c3"),
    (0x1F8DB0, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "8b44240485c0742380782c02741d8b401085c07416813805000100750e83781800740850e827fbffff59c331c0c3"),
    (0x1F8DE8, "0000000000000000000000000000000000000000000000", "5556e885ffffff83c40885c00f858734f0ffe97df9ffff"),
    (0x1F8F54, "0000000000000000000000000000000000000000000000000000000000000000000000000000", "ff742404e8d3fdffff5985c07415ff742404e8a10000005983f8407406b801000000c331c0c3"),
    (0x1F8F84, "0000000000000000000000000000000000000000000000000000000000000000000000000000", "ff742404e8a3fdffff5985c07415ff742404e8710000005983f8407506b801000000c331c0c3"),
    (0x1F8FB4, "000000000000000000000000000000000000000000000000000000000000000000000000", "8b4424040fb740208d48d883f90e760e8d886affffff83f907760331c0c3b801000000c3"),
    (0x1F8FE0, "00000000000000000000000000000000000000000000000000000000000000000000", "8b44240485c074178b401085c07410813805000100750850e803f9ffff59c331c0c3"),
    (0x1F900C, "00000000000000000000000000000000000000000000", "8b4424048b40108b400a85c074050fb6400ac331c0c3"),
    (0x1F902C, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "5556e841fdffff83c40885c00f854332f0ffe958f7ffff005556e829fdffff83c40885c00f852b32f0ffe95ff7ffff005556e811fdffff83c40885c00f851332f0ffe966f7ffff"),
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


# x86 source of the added predicates, assembled at the addresses the research
# tool chose (symbolic names resolved at assembly time). Kept for review only.
#
# ---- shared helpers ----
#   f_isstatic:
#       mov eax, dword ptr [esp+4]
#       test eax, eax
#       jz hs_no
#       cmp byte ptr [eax+0x2c], 2
#       je hs_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz hs_no
#       cmp dword ptr [eax], 5
#       jne hs_no
#       call hs_pc
#   hs_pc:
#       pop ecx
#       sub ecx, hs_pc
#       add ecx, PSEUDO
#       cmp dword ptr [eax+0xe], ecx
#       je hs_no
#       mov eax, 1
#       ret
#   hs_no:
#       xor eax, eax
#       ret
#   f_namech:
#       mov eax, dword ptr [esp+4]
#       mov eax, dword ptr [eax+0x10]
#       mov eax, dword ptr [eax+0xa]
#       test eax, eax
#       jz hn_none
#       movzx eax, byte ptr [eax+0xa]
#       ret
#   hn_none:
#       xor eax, eax
#       ret
#   f_nstatic:
#       push dword ptr [esp+4]
#       call f_isstatic
#       pop ecx
#       test eax, eax
#       jz hns_no
#       push dword ptr [esp+4]
#       call f_namech
#       pop ecx
#       cmp eax, 0x40
#       je hns_no
#       mov eax, 1
#       ret
#   hns_no:
#       xor eax, eax
#       ret
#   f_islit:
#       push dword ptr [esp+4]
#       call f_isstatic
#       pop ecx
#       test eax, eax
#       jz hl_no
#       push dword ptr [esp+4]
#       call f_namech
#       pop ecx
#       cmp eax, 0x40
#       jne hl_no
#       mov eax, 1
#       ret
#   hl_no:
#       xor eax, eax
#       ret
#   f_framedecl_esc:
#       mov eax, dword ptr [esp+4]
#       test eax, eax
#       jz hf_no
#       cmp byte ptr [eax+0x2c], 2
#       je hf_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz hf_no
#       cmp dword ptr [eax], 0x10005
#       jne hf_no
#       cmp dword ptr [eax+0x18], 0
#       je hf_no
#       push eax
#       call IN_WC
#       pop ecx
#       ret
#   hf_no:
#       xor eax, eax
#       ret
#   f_isstore:
#       mov eax, dword ptr [esp+4]
#       movzx eax, word ptr [eax+0x20]
#       lea ecx, [eax-0x28]
#       cmp ecx, 0xe
#       jbe hst_yes
#       lea ecx, [eax-0x96]
#       cmp ecx, 0x7
#       jbe hst_yes
#       xor eax, eax
#       ret
#   hst_yes:
#       mov eax, 1
#       ret
# ---- dsl ----
#   f_dsl:
#       push esi
#       push edi
#       mov esi, dword ptr [esp+0xc]
#       mov edi, dword ptr [esp+0x10]
#       cmp byte ptr [esi+0x3c], 3
#       jne dl_no
#       push esi
#       call f_isstore
#       pop ecx
#       test eax, eax
#       jz dl_no
#       push dword ptr [esi+0x18]
#       call f_nstatic
#       pop ecx
#       test eax, eax
#       jz dl_no
#       cmp byte ptr [edi+0x3c], 3
#       je dl_no
#       push edi
#       call f_isstore
#       pop ecx
#       test eax, eax
#       jnz dl_no
#       push dword ptr [edi+0x18]
#       call f_islit
#       pop ecx
#       test eax, eax
#       jz dl_no
#       mov eax, 1
#       jmp dl_out
#   dl_no:
#       xor eax, eax
#   dl_out:
#       pop edi
#       pop esi
#       ret
# ---- e3ns ----
#   f_frame_esc:
#       mov eax, dword ptr [esp+4]
#       test eax, eax
#       jz fe_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz fe_no
#       cmp dword ptr [eax], 0x10005
#       jne fe_no
#       push eax
#       call IN_WC
#       pop ecx
#       ret
#   fe_no:
#       xor eax, eax
#       ret
#   f_e3ns:
#       push esi
#       push edi
#       mov esi, dword ptr [esp+0xc]
#       mov edi, dword ptr [esp+0x10]
#       push esi
#       call f_isstore
#       pop ecx
#       test eax, eax
#       jz es_no
#       push edi
#       call f_isstore
#       pop ecx
#       test eax, eax
#       jnz es_no
#       mov ecx, dword ptr [esi+0x18]
#       test ecx, ecx
#       jz es_no
#       cmp byte ptr [ecx+0x2c], 1
#       jne es_no
#       mov edx, dword ptr [edi+0x18]
#       test edx, edx
#       jz es_no
#       cmp byte ptr [edx+0x2c], 0
#       jne es_no
#       cmp dword ptr [edx+0x18], 8
#       ja es_no
#       push edx
#       call f_islit
#       pop ecx
#       test eax, eax
#       jz es_no
#       push dword ptr [esi+0x18]
#       call f_frame_esc
#       pop ecx
#       jmp es_out
#   es_no:
#       xor eax, eax
#   es_out:
#       pop edi
#       pop esi
#       ret
# ---- generator of the dispatch predicate combining the parts ----
#   def pred_x(parts):
#       calls = "".join("""
#       push dword ptr [esp+8]
#       push dword ptr [esp+8]
#       call f_%s
#       add esp, 8
#       test eax, eax
#       jnz px_yes
#   """ % p for p in ("psd", "dsf", "ds", "e3nc", "we", "l8s", "wg4", "dsa", "dsl", "e3ns", "e3nw") if p in parts)
#       return "f_pred_x:" + calls + """
#       xor eax, eax
#       ret
#   px_yes:
#       mov eax, 1
#       ret
#   """


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc.py <compilers dir | <compilers>/GC/2.0p1h/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
