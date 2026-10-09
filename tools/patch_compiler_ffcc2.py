#!/usr/bin/env python3
"""Derive GC/2.0p1i for the Japanese game library from GC/2.0p1h.

GC/2.0p1h is BFBB's GC/2.0p1g plus FFCC's e3ns and dsl corrections
(tools/patch_compiler_ffcc.py). Three more retail behaviours of the 2003
compiler were identified from FFCC Japan with BFBB's in-process may-alias probe.
None exists in any stock compiler (1.3.2 to 3.0a5.2), so all are emulation
corrections. Measured over every Japanese game unit and on a frozen BFBB
checkout (SB game and RW sets), with no function and no partial score lower
in either game (see docs/compiler_baseline.md):

  ksa   Alias.c's per-access pass downgrades an access to worst_case when
        another reaching definition of its base register has no alias. Retail
        keeps the access's own alias. Three bytes at 0x5124D7/0x5124E2/
        0x5124EE skip the reaching-definition check. FFCC JP +19 / -0
        (gpmCol, pppMemAlloc, pppCreatePObject, pppLight, the pppRand family);
        BFBB RW +1 / -0.
  pwcp  the prologue's worst_case stores (stw/stwu/stmw) may alias a later load
        of a stack-passed PARAMETER (variable-info byte +0x24 bit 0), so those
        loads stay below the register saves. FFCC JP +5 / -0; BFBB game +2 / -0.
  c3a   a subrange store to a named static orders a later whole '@' literal
        load of at most 8 bytes, whatever its flags (may_alias entry 3).
        FFCC JP +4 / -0; BFBB game +1 / -0.

Together: FFCC JP +28 / -0 exact functions (+37 / -0 with the source fix that
gives gPppDefaultValueBuffer its real size), BFBB +4 / -0.

Every edit checks the expected old bytes; input and output are checked by SHA-1.

    python tools/patch_compiler_ffcc2.py <compilers>/GC/2.0p1i/mwcceppc.exe
"""
import hashlib
import shutil
import sys
from pathlib import Path

BASE_VERSION = "GC/2.0p1h"
BASE_SHA1 = "6114c0c66bc9b4ded51a1a278402a753ab12792c"
PATCHED_VERSION = "GC/2.0p1i"
PATCHED_SHA1 = "58c5e3ccd07f5ce533695ecedd1a2a7f1eca1d13"

# (file offset, expected old bytes, new bytes)
EDITS = [
    (0x1118D8, "17", "27"),
    (0x1118E3, "0c", "1c"),
    (0x1118EE, "75", "eb"),
    (0x1BA6C4, "8b20510044ee60005cee60008b205100a8205100a82051", "b4ee6000d8ee60005cee6000fce7600020e8600044e860"),
    (0x1F8858, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "8b4424048b400a85c074050fb6400ac331c0c356578b74240c8b7c2410f7461400000000756556e8f40700005985c0745a57e8e90700005985c0754f8b461880782c0274468b401085c0743f833805753a50e8a9ffffff5983f840742e8b471880782c00752583781808771f8b401085c07418833805751350e882ffffff5983f8407507b801000000eb0231c05f5ec3"),
    (0x1F89FC, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "50525556e87e07000083c40885c075075a58e97838f0ff5a58e96738f0ff00000000000050525556e85a07000083c40885c075075a58e97138f0ff5a58e94338f0ff00000000000050525556e83607000083c40885c075075a58e94d38f0ff5a58e91f38f0ff"),
    (0x1F9078, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "8b4424040fb740208d48d883f90e760e8d886affffff83f907760331c0c3b801000000c3e8000000005881e8a1ee600005b49c5e008b00c30000000050525556e8c600000083c40885c075075a58e9c031f0ff5a58e9af31f0ff00000000000050525556e88af7ffff83c40885c075075a58e955ffffff5a58e98b31f0ff"),
    (0x1F9124, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "56578b74240c8b7c2410e869ffffff394618754656e83affffff5985c0743b57e82fffffff5985c075308b471885c0742980782c0274238b401085c0741c81380500010075148b402a85c0740df64024017407b801000000eb0231c05f5ec3ff742408ff742408e894ffffff83c40885c07510ff742404ff74240ce880ffffff83c408c3"),
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


# Research source of the pwcp/c3a predicates and the ksa edit (keystone-assembled
# at the .sbpatch free areas 0x60e658, 0x60e7fc, 0x60ee78 and 0x60ef24). Kept for
# review only; the build applies EDITS above.
#
#   #!/usr/bin/env python3
#   """cave.py <name> <part>[,<part>...] [--src DIR] : build a scratch compiler = SRC (default 2.0p1h) + cave parts.
#
#   Writes only to _scratch/jpcc2/cc/<name>. Code goes into free zero runs of .sbpatch; every absolute
#   reference is PC-relative (survives the sjiswrap rebase); dispatch-table words keep their HIGHLOW relocs.
#   """
#   import os, shutil, struct, sys
#   import keystone, pefile
#
#   KS = keystone.Ks(keystone.KS_ARCH_X86, keystone.KS_MODE_32)
#   WCP = 0x5E9CB4           # global holding the worst_case alias pointer
#   YES = 0x512081           # may_alias: mov ebx,1 ; jmp epilogue
#   SCHED_TABLE = 0x5BD0BC   # may_alias 3x3 dispatch (a.kind*3 + b.kind)
#   FREE = [(0x60E658, 0x60E700), (0x60E7FC, 0x60E900), (0x60EE78, 0x60EF00), (0x60EF24, 0x60EFC0)]
#
#   # ---- shared helpers (cdecl, PIC) ----
#   HELP = r"""
#   h_isstore:
#       mov eax, dword ptr [esp+4]
#       movzx eax, word ptr [eax+0x20]
#       lea ecx, [eax-0x28]
#       cmp ecx, 0xe
#       jbe hst_y
#       lea ecx, [eax-0x96]
#       cmp ecx, 0x7
#       jbe hst_y
#       xor eax, eax
#       ret
#   hst_y:
#       mov eax, 1
#       ret
#   h_wc:
#       call hwc_pc
#   hwc_pc:
#       pop eax
#       sub eax, hwc_pc
#       add eax, WCP
#       mov eax, dword ptr [eax]
#       ret
#   """
#
#   # pwc: one side a store whose alias IS the worst_case set, the other a non-store whose alias is a
#   # whole/subrange of a frame object (0x10005) -> may alias.  Hooked on entries 2,5 (b=set) and 6,7 (a=set).
#   PWC = r"""
#   p_pwc_one:
#       push esi
#       push edi
#       mov esi, dword ptr [esp+0xc]
#       mov edi, dword ptr [esp+0x10]
#       call h_wc
#       cmp dword ptr [esi+0x18], eax
#       jne pw_no
#       push esi
#       call h_isstore
#       pop ecx
#       test eax, eax
#       jz pw_no
#       push edi
#       call h_isstore
#       pop ecx
#       test eax, eax
#       jnz pw_no
#       mov eax, dword ptr [edi+0x18]
#       test eax, eax
#       jz pw_no
#       cmp byte ptr [eax+0x2c], 2
#       je pw_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz pw_no
#       cmp dword ptr [eax], 0x10005
#       jne pw_no
#       PWC_EXTRA
#       mov eax, 1
#       jmp pw_out
#   pw_no:
#       xor eax, eax
#   pw_out:
#       pop edi
#       pop esi
#       ret
#   p_pwc:
#       push dword ptr [esp+8]
#       push dword ptr [esp+8]
#       call p_pwc_one
#       add esp, 8
#       test eax, eax
#       jnz pwc_out
#       push dword ptr [esp+4]
#       push dword ptr [esp+0xc]
#       call p_pwc_one
#       add esp, 8
#   pwc_out:
#       ret
#   """
#
#   C40 = r"""
#   h_objname0:
#       mov eax, dword ptr [esp+4]
#       mov eax, dword ptr [eax+0xa]
#       test eax, eax
#       jz hn0_no
#       movzx eax, byte ptr [eax+0xa]
#       ret
#   hn0_no:
#       xor eax, eax
#       ret
#   p_pwc:
#       push esi
#       push edi
#       mov esi, dword ptr [esp+0xc]
#       mov edi, dword ptr [esp+0x10]
#       test dword ptr [esi+0x14], C40_FLAG
#       C40JMP c4_no
#       push esi
#       call h_isstore
#       pop ecx
#       test eax, eax
#       jz c4_no
#       push edi
#       call h_isstore
#       pop ecx
#       test eax, eax
#       jnz c4_no
#       mov eax, dword ptr [esi+0x18]
#       cmp byte ptr [eax+0x2c], 2
#       je c4_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz c4_no
#       cmp dword ptr [eax], 5
#       jne c4_no
#       push eax
#       call h_objname0
#       pop ecx
#       cmp eax, 0x40
#       je c4_no
#       mov eax, dword ptr [edi+0x18]
#       cmp byte ptr [eax+0x2c], 0
#       jne c4_no
#       cmp dword ptr [eax+0x18], 8
#       ja c4_no
#       mov eax, dword ptr [eax+0x10]
#       test eax, eax
#       jz c4_no
#       cmp dword ptr [eax], 5
#       jne c4_no
#       push eax
#       call h_objname0
#       pop ecx
#       cmp eax, 0x40
#       jne c4_no
#       mov eax, 1
#       jmp c4_out
#   c4_no:
#       xor eax, eax
#   c4_out:
#       pop edi
#       pop esi
#       ret
#   """
#
#   PARTS = {
#       # c40: a store carrying pcode flag 0x40 whose alias is on a named static (subrange: entry 3) orders a
#       # later whole literal-pool load of <= 8 bytes (clause C/C+ reject the 0x40 flag)
#       'c40': (C40, 'p_pwc', (3,), {'C40_FLAG': '0x40', 'C40JMP': 'jz'}),
#       'c40w': (C40, 'p_pwc', (0, 3), {'C40_FLAG': '0x40', 'C40JMP': 'jz'}),
#       # any flags (not only 0x40)
#       'c3a': (C40, 'p_pwc', (3,), {'C40_FLAG': '0', 'C40JMP': 'jnz'}),
#       'c3aw': (C40, 'p_pwc', (0, 3), {'C40_FLAG': '0', 'C40JMP': 'jnz'}),
#       # name: (asm, predicate symbol, entries, extra-substitutions)
#       'pwc': (PWC, 'p_pwc', (2, 5, 6, 7), {'PWC_EXTRA': ''}),
#       # only declared/named objects (VarInfo word != 0): excludes compiler temporaries
#       'pwcd': (PWC, 'p_pwc', (2, 5, 6, 7), {'PWC_EXTRA': 'cmp dword ptr [eax+0x18], 0\n    je pw_no'}),
#       # only the earlier-store order seen at 0x508370 is unknown; the a=set entries only
#       'pwcp': (PWC, 'p_pwc', (2, 5, 6, 7), {'PWC_EXTRA': 'mov eax, dword ptr [eax+0x2a]; test eax, eax; jz pw_no; test byte ptr [eax+0x24], 1; jz pw_no'}),
#       'pwcp67': (PWC, 'p_pwc', (6, 7), {'PWC_EXTRA': 'mov eax, dword ptr [eax+0x2a]; test eax, eax; jz pw_no; test byte ptr [eax+0x24], 1; jz pw_no'}),
#       'pwc67': (PWC, 'p_pwc', (6, 7), {'PWC_EXTRA': ''}),
#       'pwc25': (PWC, 'p_pwc', (2, 5), {'PWC_EXTRA': ''}),
#   }
#
#
#   def asm(text, at, syms):
#       def res(name, value):
#           n = name.decode() if isinstance(name, bytes) else name
#           if n in syms:
#               value[0] = syms[n]
#               return True
#           return False
#       KS.sym_resolver = res
#       enc, _ = KS.asm(text, at)
#       return bytes(enc)
#
#
#   def main():
#       name, parts = sys.argv[1], sys.argv[2].split(',')
#       src = 'C:/Projects/ffcc-wt/jpclauses2/build/compilers/GC/2.0p1h'
#       if '--src' in sys.argv:
#           src = sys.argv[sys.argv.index('--src') + 1]
#       dst = 'C:/Projects/ffcc-wt/_scratch/jpcc2/cc/' + name
#       if os.path.exists(dst):
#           shutil.rmtree(dst)
#       shutil.copytree(src, dst)
#       exe = dst + '/mwcceppc.exe'
#       pe = pefile.PE(exe, fast_load=True)
#       base = pe.OPTIONAL_HEADER.ImageBase
#       data = bytearray(open(exe, 'rb').read())
#
#       def foff(va):
#           return pe.get_offset_from_rva(va - base)
#
#       regs = [list(r) for r in FREE]
#       syms = {}
#
#       def put(txt, labels):
#           t = txt
#           for k in sorted(syms, key=len, reverse=True):
#               t = t.replace('call ' + k + '\n', 'call %#x\n' % syms[k])
#           for r in sorted(regs, key=lambda r: r[1] - r[0]):
#               at = (r[0] + 3) & ~3
#               try:
#                   c = asm(t, at, {})
#               except Exception:
#                   raise
#               if at + len(c) <= r[1]:
#                   o = foff(at)
#                   assert not any(data[o:o + len(c)]), hex(at)
#                   data[o:o + len(c)] = c
#                   for l in labels:
#                       syms[l] = at + len(asm(t[:t.index(l + ':')], at, {})) if t.index(l + ':') else at
#                   r[0] = at + len(c) + 4
#                   return at, len(c)
#           sys.exit('no room (%d)' % len(c))
#
#       put(HELP.replace('WCP', hex(WCP)), ['h_isstore', 'h_wc'])
#       preds = []
#       total = 0
#       for p in parts:
#           a, sym, ents, sub = PARTS[p]
#           for k, v in sub.items():
#               a = a.replace(k, v)
#           a = a.replace('p_pwc', 'p_pwc_' + p).replace('h_objname0', 'h_objname0_' + p)
#           sym = sym.replace('p_pwc', 'p_pwc_' + p)
#           at, n = put(a + '\n', [sym])
#           total += n
#           preds.append((sym, ents))
#       entries = {}
#       for sym, ents in preds:
#           for e in ents:
#               entries.setdefault(e, []).append(sym)
#       for e, ss in sorted(entries.items()):
#           stock = struct.unpack_from('<I', data, foff(SCHED_TABLE + 4 * e))[0]
#           t = 'push eax; push edx;'
#           for sym in ss:
#               t += 'push ebp; push esi; call %#x; add esp, 8; test eax, eax; jnz yy;' % syms[sym]
#           t += 'pop edx; pop eax; jmp %#x; yy: pop edx; pop eax; jmp %#x' % (stock, YES)
#           at, n = put(t, [])
#           struct.pack_into('<I', data, foff(SCHED_TABLE + 4 * e), at)
#       code = b'x' * total
#       at = 0
#       pe.close()
#       open(exe, 'wb').write(data)
#       print('built', name, len(code), 'bytes at', hex(at), 'entries', sorted(entries))
#
#
#   if __name__ == '__main__':
#       main()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_ffcc2.py <compilers dir | <compilers>/GC/2.0p1i/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    derive(root)
