#!/usr/bin/env python3
"""Derive the patched CodeWarrior used to build the SB library.

GC/2.0p1a
---------
mwcceppc.exe GC/2.0p1 answers memory-disambiguation questions more
aggressively than the compiler that built the retail DOL: a float constant
loaded from the .sdata2 literal pool gets hoisted above a store it is assumed
not to touch (the long-standing "float meme"), a store to a small static does
not kill a cached literal load, a whole static read is hoisted out of a loop,
and the two halves of a static of at most 8 bytes are disambiguated as if
they were separate objects. This patch narrows those answers back toward
retail's.

The narrowing is expressed as C, not as hand-assembled bytes. It lives in the
CodeWarrior decompilation repo:

    src/compiler_and_linker/BackEnd/PowerPC/GlobalOptimizer/AliasPatch.c

That file holds ONLY the clause predicates -- the part that is the patch. The
compiler's own stock answers (the 3x3 may_alias_alias switch, and the
whole-object kill walks in update_alias_value) are left as its own bytes and
reached by fall-through. Nothing stock is reimplemented, so nothing stock can
diverge: a query the patch does not claim is answered by the identical original
code. This is what the older eight-clause byte cave (A, B, C, C+, E3n, V, F, H)
could not do -- it carried four hand-derived copies of the same switch, one per
inlined call site, because a byte patch cannot call a shared function.

HOW IT IS INJECTED
------------------
Two operand-kind tables in Alias.c are hooked, and one call site in
CodeMotion.c:

    0x5bd068  update_alias_value (0x511a30)  entry 0 -> clauses V and F
                                             entry 1 -> clause S
    0x5bd0bc  may_alias          (0x511fc0)  entries 0,1,3 -> A/B/C/C+/E3n
                                             entry 4 -> clause S
    0x56f472  call isloopinvariant (0x570f60) from moveinvariantsfromloop
              -> sb_licm_invariant (a whole static read is never invariant)

The third is a REL32 call retargeted to a stub: isloopinvariant decides a
read by the defs of its own object, so for a loop with no store and no call
no alias table is ever consulted, and the only place to say
"not invariant" is the call itself. Only moveinvariantsfromloop's call is
redirected; simpleunswitchloop and srawi_addze_isloopinvariant keep the stock
routine.

`may_alias` keeps the original PCode arguments in esi/ebp at the dispatch
point, so the predicates read opcode and flags directly; eax and
edx hold the two memrefs.

The injected image is a new executable section, .sbpatch, appended after
.reloc at the old SizeOfImage. No existing section, VA or RVA moves; the
section table had room for an eleventh header below SizeOfHeaders. It holds:

  * seven register-marshalling stubs (tools/aliaspatch_asm.py) that hand each
    query to the right C predicate in cdecl form and act on the answer -- jump
    to the compiler's own "may alias" answer tail on a hit, fall into the
    compiler's own stock test on a miss;
  * the C blob. Its linked bytes are checked in as tools/aliaspatch_blob.py,
    so a bare bfbb checkout derives the compiler with no external repo. When
    the mwcc-gc repo is present (MWCC_GC env var, or its default location),
    tools/aliaspatch_link.py recompiles AliasPatch.c with that repo's own
    Metrowerks mwcc.exe and refuses to build if the fresh link differs from
    the artefact -- the C stays the source of truth, and a stale artefact is
    a loud failure, not a silent divergence. `aliaspatch_link.py --refresh`
    regenerates the artefact after an intended C change.

The blob is position-independent: every relocation is a REL32 (inter-function
calls and the one call to killmemory), which survives the sjiswrap rebase
because caller and callee move together. The alias-list head is loaded PC-
relatively by the VN stub and passed in, so the blob carries no absolute word
and needs no base relocations of its own. The six redirected dispatch entries
are the only absolute edits, and they already carry HIGHLOW relocations that
rebase their new in-image targets. The LICM call-site retarget is a rel32 with no relocation
entry of its own (verified against .reloc), so it needs none.

All writes are guarded by the SHA-1 of the input and by the expected bytes at
each offset, so an unexpected build fails loudly instead of being corrupted.
The whole clause set now reads as C; changing AliasPatch.c changes the derived
compiler's SHA-1, so re-measure with tools/patchcost.py after any change.
"""

import hashlib
import os
import shutil
import struct
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import aliaspatch_link
import aliaspatch_asm

BASE_VERSION = "GC/2.0p1"
PATCHED_VERSION = "GC/2.0p1a"

BASE_SHA1 = "74bc177b10d1bbe8a60a21a6c0aa86d2dd9c0668"
# The C-sourced GC/2.0p1a. This is a NEW hash: the old byte-cave p1a was
# 5c6862b641adb8845f0fc09a6569902df068a83f. The derived-compiler bytes differ;
# the OBJECTS it produces do not (verified byte-identical on 450 SB units).
PATCHED_SHA1 = "a78a5fdb6c1d5677e987636b2e0743dbaefe9542"

# ---- where the injected code goes ---------------------------------------
# A new section after the last one. Stock SizeOfImage is 0x20e000 and the file
# ends exactly at .reloc's raw data (0x1f8200, FileAlignment-aligned), so the
# section's RVA and raw offset are both the old ends. The C blob goes first, at
# BLOB_VA, and the stubs follow it.
SECTION_NAME = b".sbpatch"
SECTION_RVA = 0x0020E000           # stock SizeOfImage
SECTION_FILE = 0x001F8200          # stock file size
SECTION_SIZE = 0x1000              # virtual and raw
SECTION_FLAGS = 0x60000020         # code | execute | read
IMAGE_BASE = 0x00400000
BLOB_VA = IMAGE_BASE + SECTION_RVA
ALIAS_LIST_HEAD_VA = 0x005E1FD8    # global holding the Alias list head

# ---- scheduler may-alias dispatch table (0x5bd0bc) ----------------------
# Entries 0/1/3/4 are redirected to the four sched stubs; 2 and 5-8 stay
# stock. Entry 4 carries only clause S (clause B's form there measures -199).
SCHED_DISPATCH_OFFSET = 0x1BA6BC
SCHED_STOCK = {0: 0x00511FF2, 1: 0x00511FFF, 3: 0x00511FFF, 4: 0x00512012}

# ---- value-numbering store-kill table (0x5bd068) ------------------------
# Entry 0 (whole object) carries V and F; entry 1 (subrange) carries only
# clause S (clause V's walk there measures +1/-30); entry 2 is inert.
VN_DISPATCH_OFFSET = 0x1BA668
VN_STOCK_E0 = 0x00511A53
VN_STOCK_E1 = 0x00511B0E

# ---- CodeMotion LICM call site (0x56f472) --------------------------------
# `call isloopinvariant` inside moveinvariantsfromloop, retargeted to the
# licm-invariant stub. A REL32 call carries no base relocation.
LICM_CALL_OFFSET = 0x16E872         # VA 0x56f472
LICM_CALL_OLD = bytes.fromhex("e8e91a0000")   # call 0x570f60


def sha1_bytes(b: bytes) -> str:
    return hashlib.sha1(b).hexdigest()


def sha1(path: Path) -> str:
    return hashlib.sha1(path.read_bytes()).hexdigest()


def build_injection():
    """Lay out the C blob and the seven stubs in the new section.

    The blob comes from aliaspatch_link.blob_for: the checked-in artefact,
    verified against a fresh compile of AliasPatch.c whenever the mwcc-gc repo
    is present. It is placed at BLOB_VA and the stubs, which call into it,
    directly after it. Returns (section_bytes, stub_vas)."""
    A = aliaspatch_asm

    blob, exp = aliaspatch_link.blob_for(BLOB_VA)
    sched = exp["_sb_sched_clause"]
    vn = exp["_sb_vn_store_kill"]
    vn1 = exp["_sb_vn_subrange_store"]
    inv = exp["_sb_licm_invariant"]

    at = BLOB_VA + len(blob)
    at += -at % 4
    parts = []
    vas = {}

    def emit(name, bts):
        nonlocal at
        vas[name] = at
        parts.append(bts)
        at += len(bts)

    emit("s0", A.sched_stub(at, sched, 0, A.STOCK_E0))
    emit("s1", A.sched_stub(at, sched, 1, A.STOCK_E1_E3))
    emit("s3", A.sched_stub(at, sched, 3, A.STOCK_E1_E3))
    emit("s4", A.sched_stub(at, sched, 4, A.STOCK_E4))
    emit("vn", A.vn_stub(at, vn, ALIAS_LIST_HEAD_VA))
    emit("vn1", A.vn_subrange_stub(at, vn1, ALIAS_LIST_HEAD_VA))
    emit("inv", A.licm_invariant_stub(at, inv))

    if at > BLOB_VA + SECTION_SIZE:
        sys.exit(f"injected code ends at {at:#x}, past the end of the "
                 f"{SECTION_SIZE:#x}-byte section; grow SECTION_SIZE")

    region = bytearray(SECTION_SIZE)
    region[0:len(blob)] = blob
    o = len(blob) + (-(BLOB_VA + len(blob)) % 4)
    stubs = b"".join(parts)
    region[o:o + len(stubs)] = stubs
    return bytes(region), vas


def _apply(data: bytearray) -> bytes:
    section, vas = build_injection()

    # 1. redirect the scheduler dispatch entries (0,1,3,4)
    for index, stock in SCHED_STOCK.items():
        o = SCHED_DISPATCH_OFFSET + 4 * index
        found = struct.unpack_from("<I", data, o)[0]
        if found != stock:
            sys.exit(f"sched dispatch entry {index} at {o:#x} is {found:#x}, "
                     f"expected {stock:#x}")
        struct.pack_into("<I", data, o, vas[{0: "s0", 1: "s1", 3: "s3", 4: "s4"}[index]])

    # 2. redirect the VN store-kill entry 0
    o = VN_DISPATCH_OFFSET
    found = struct.unpack_from("<I", data, o)[0]
    if found != VN_STOCK_E0:
        sys.exit(f"vn dispatch entry 0 at {o:#x} is {found:#x}, "
                 f"expected {VN_STOCK_E0:#x}")
    struct.pack_into("<I", data, o, vas["vn"])

    # 2b. redirect the VN store-kill entry 1
    o = VN_DISPATCH_OFFSET + 4
    found = struct.unpack_from("<I", data, o)[0]
    if found != VN_STOCK_E1:
        sys.exit(f"vn dispatch entry 1 at {o:#x} is {found:#x}, "
                 f"expected {VN_STOCK_E1:#x}")
    struct.pack_into("<I", data, o, vas["vn1"])

    # 3. retarget moveinvariantsfromloop's call isloopinvariant -> licm-invariant stub
    if data[LICM_CALL_OFFSET:LICM_CALL_OFFSET + 5] != LICM_CALL_OLD:
        sys.exit(f"LICM call bytes at {LICM_CALL_OFFSET:#x} are "
                 f"{data[LICM_CALL_OFFSET:LICM_CALL_OFFSET + 5].hex()}, expected "
                 f"{LICM_CALL_OLD.hex()}")
    rel = vas["inv"] - (0x0056F472 + 5)
    data[LICM_CALL_OFFSET:LICM_CALL_OFFSET + 5] = b"\xE8" + struct.pack("<i", rel)

    # 4. append the .sbpatch section: one more header, SizeOfImage grown, the
    #    raw data at the end of the file
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
    struct.pack_into("<I", data, opt + 56, size_of_image + SECTION_SIZE)
    data += section
    return bytes(data)


def patch_compiler(compilers: Path) -> bool:
    """Create the patched compiler directory. Returns True if it is present."""
    src_dir = compilers / BASE_VERSION
    dst_dir = compilers / PATCHED_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"

    if not src.exists():
        return False

    actual = sha1(src)
    if actual != BASE_SHA1:
        sys.exit(
            f"{src} has unexpected SHA-1 {actual}\n"
            f"  expected {BASE_SHA1}; refusing to patch an unknown build"
        )

    if PATCHED_SHA1 and dst.exists() and sha1(dst) == PATCHED_SHA1:
        return True

    dst_dir.mkdir(parents=True, exist_ok=True)
    # The whole directory is needed: mwcceppc.exe will not start without
    # lmgr326b.dll sitting next to it.
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, dst_dir / f.name)

    # That copy just put the STOCK exe at the PATCHED name. Remove it before
    # doing any work: everything below can sys.exit -- a drifted AliasPatch.c,
    # a moved dispatch entry, a blob past EXEC_LIMIT -- and leaving it behind
    # would strand an unpatched compiler wearing the patched version number.
    # solo.py takes the compiler path from build.ninja without checking its
    # sha1, so that file would quietly hand back stock-compiler numbers. The
    # real write below is atomic, so nothing else recreates it on failure.
    if dst.exists():
        dst.unlink()

    data = bytearray(src.read_bytes())
    out = _apply(data)

    result = sha1_bytes(out)
    if PATCHED_SHA1 is None:
        print(f"NOTE: PATCHED_SHA1 unset; this build is {result}")
    elif result != PATCHED_SHA1:
        sys.exit(f"patched compiler has SHA-1 {result}, expected {PATCHED_SHA1}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler.py <compilers dir | patched mwcceppc.exe>")
    arg = Path(sys.argv[1])
    # Invoked from ninja with $out, i.e. <compilers>/GC/2.0p1a/mwcceppc.exe
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    if not patch_compiler(root):
        sys.exit(f"{root / BASE_VERSION} not found")
