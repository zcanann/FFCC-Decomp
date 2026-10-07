#!/usr/bin/env python3
"""Derive GC/2.0p1b, the RenderWare SDK's compiler, from GC/2.0p1a.

GC/2.0p1b is GC/2.0p1a (tools/patch_compiler.py) plus ONE change:

    Clause V's literal-kill walk does not fire on a store to a compiler
    temporary.

update_alias_value's whole-object entry (VN dispatch table 0x5bd068, entry 0)
is the hook that 2.0p1a points at its VN stub (clauses V and F, 0x60e5f8).
2.0p1b points that entry at one more stub, which looks at the stored alias's
base expression (alias+0x10) first:

    base != NULL && base->word0 == 0x10005      (a frame object)
                 && *(base+0x18) == 0           (no declared Object: a temp)
        -> jmp 0x511a53   the compiler's own stock whole-object kill
                          (no V walk, so no F either)
    otherwise
        -> jmp 0x60e5f8   2.0p1a's VN stub, unchanged

This is exactly what tools/compilerprobe/cablate.py --mode vtmp does under a
debugger; docs/RW_RESIDUE.md ("What would close the rest", item 1) has the
measurement (+4 RW functions, 0 regressions, game code 0/0). Neither branch
target reads eax or the flags on entry (both start by pushing esi/ebx, or by
`call $+5`), so the stub may use eax freely.

The stub goes into unused space at the end of 2.0p1a's .sbpatch section, so no
section, header, size or relocation changes: the only other edit is the one
dispatch word, which already carries a HIGHLOW base relocation, and the stub's
two branches are rel32 to targets inside the same image, which survive the
sjiswrap rebase. Inputs and outputs are SHA-1-checked; GC/2.0p1 and GC/2.0p1a
are only read, never modified.

GC/2.0p1c (EXPERIMENTAL; not used by configure.py yet)
------------------------------------------------------
GC/2.0p1b plus GC/2.5's loop-invariant code motion of loads through a
pointer-to-const ("R3" in docs/RW_RESIDUE.md). Built only when asked for by
path (`patch_compiler_rw.py <compilers>/GC/2.0p1c/mwcceppc.exe`) or with
`patch_compiler_rw.py <compilers dir> --r3`.

What 2.5 does differently (measured under a debugger on both binaries):

  * Both compilers' CodeGen give the `mr vN, var` that reads a register
    variable whose type is pointer-to-const (or restrict) an alias for a fresh
    pseudo-object (2.0p1: 0x513330, 2.5: 0x513620), and both compilers' pointer
    analysis hands that alias on to loads whose base register comes from it.
  * 2.0p1 makes it a one-member alias SET {pseudo-object}, so the load keeps
    fIsPtrOp (0x20) and alias kind 2, and moveinvariantsfromloop rejects it
    twice: its flag filter (`flags & 0x1a8`) and isloopinvariant's
    `alias->kind == 2 -> not invariant`.
  * 2.5 makes it a plain alias (kind 1) on the pseudo-object, clears 0x20,
    and only propagates it through plain register copies (its def-alias helper
    0x512ec0 returns an alias only for `mr` or an object-address operand; 2.0p1
    also lets it flow through `add`). isloopinvariant then walks the
    pseudo-object's defs, and there are none -- calls and stores through other
    pointers never define it. So the load is invariant whatever else the loop
    does (calls, stores, early returns).
  * 2.5 also moved moveinvariantsfromloop's large-loop veto (a loop of more
    than 25 instructions) from LFS..LFDUX (opcodes 0x8e-0x95) to
    VSPLTIS{B,H,W} (0x161-0x163), so FP loads are hoisted out of big loops too.
    Without that, the const-matrix loads of VectorMultPoint/VectorMultVector
    stay in the loop.

What 2.0p1c changes (all of it is new code at .sbpatch+0xC00, plus three
rel32/immediate edits, none of which overlaps a base relocation):

  1. moveinvariantsfromloop's flag filter (`and eax,0x1a8 / jne` at 0x56f461)
     -> R3_FILTER: still skip 0x188 (volatile / side effects / 0x8), but let
     fIsPtrOp through when the load is a "cps" load (below).
  2. Its `call isloopinvariant` (0x56f472, 2.0p1a's LICM stub target) ->
     R3_INV: a cps load has its alias temporarily swapped for the set's one
     member and is handed to the stock isloopinvariant (0x570f60), which then
     walks the pseudo-object's defs exactly as 2.5 does; if the pseudo-object
     has no use-def node at all it enters isloopinvariant after the memory
     checks (0x5710d0). Every other pcode goes to 2.0p1a's stub as before.
  3. The FP-load veto immediates at 0x570985 (`sub eax,5 / cmp eax,7`) ->
     (`sub eax,0xd8 / cmp eax,2`): 2.5's opcode range.

A "cps" load: a read, not a write; alias is a one-member set, not worst_case,
whose member is a whole-object alias of an object typed 0x5bd008 (the
pseudo-object type); and every register it uses is defined only by `mr`
instructions that carry such a set (or not at all -- an incoming register).
The last condition is 2.5's "propagate through mr only" rule.

Measured (scratch derivation, solo.py on every unit; RW baseline 2.0p1b, game
baseline 2.0p1a/2.0p1b, which are identical on the game):
  RW:   +6 / -0 among RW_COMPILER units: _rpMaterialListFindMaterialIndex,
        _rpMaterialListStreamGetSize, _rpMaterialListStreamWrite, RwImageCopy,
        RpGeometryStreamGetSize, and multiTexGcnData's
        GameCubeMTEffectStreamWrite (that unit is 7/7, so its GC/2.5 override
        can go). Up without crossing: RpGeometryStreamWrite 94.41 -> 99.59,
        ImageConvertDepth 92.31 -> 99.82, RwImageApplyMask 96.49 -> 99.09,
        UserDataListCopy 96.51 -> 98.52 (the GC/2.5 numbers). The only
        function that drops is in stdkey, which is built with GC/2.0p1;
        RpHAnimKeyFrameStreamWrite goes 100 -> 94.26, as it does under
        GC/2.5.
  Game: +2 / -0 (xfont::irender, zFX validate_popper);
        xParCmdAnimalMagentism_Update 81.04 -> 85.85.

GC/2.0p1d (EXPERIMENTAL; not used by configure.py yet)
------------------------------------------------------
GC/2.0p1c plus four independent parts. Built only when asked for by path
(`patch_compiler_rw.py <compilers>/GC/2.0p1d/mwcceppc.exe`) or with
`patch_compiler_rw.py <compilers dir> --p1d`. For measurement, any subset can
be built into a directory of its own (never GC/2.0p1d) with
`--p1d-parts r4,at-sched,at-w,at-v --out <dir>`; single-part builds are
hash-checked too (P1D_PART_SHA1). Every part writes at a fixed place, so a
subset is well defined.

  r4  ("R4" in docs/RW_RESIDUE.md). Not really an X-form scheduling rule: it is
      the alias that Alias.c's pointer-load pass (2.0p1 0x5123b0) gives an
      access with two address registers (lwzx/stbx...). For each GPR it uses,
      2.0p1 takes the access's own alias unless a reaching def is unknown, in
      which case worst_case. With two registers, 2.0p1 answers worst_case when
      NEITHER is unknown -- typically `lwzx rD, obj, off` with both incoming
      parameters -- and adds the access's alias into the worst_case set. The
      prologue's callee-save spills carry the worst_case set, so the scheduler
      sees the load alias every spill and keeps it below all of them.
      2.5 rewrote the pass (0x512570): a register whose defs give no alias
      contributes nothing, so the access keeps its alias. For
      `*(T **)((const char *)object + offset)` that alias is R3's
      pointer-to-const pseudo-object, which no spill touches, and the load
      issues right after the spill of its own destination register. (A
      non-const pointer has no alias there and stays pinned under 2.5 too.)
      The patch is one byte: that `jne` (0x51258b, 75 2d -> 75 31) goes to the
      "keep the access's alias" tail (0x5125be) instead of "worst_case".
      It also lets the indexed loads of a static table (`li r4,tbl@sda21;
      lbzx r4,r4,r5`) keep the table's alias, as 2.5 does.

  at-sched, at-w, at-v: the ADDRESS-TAKEN GATE. 2.0p1a's frame-object clauses
      now apply only to frame objects whose address escapes, i.e. that are a
      member of the worst_case alias set (in_wc, at .sbpatch+0x700). Retail
      lets a static or literal load pass a store to a local that no pointer
      can reach (the IEEE pun unions _gf/_sf/gf_u/sf_u, the `shiney` colour of
      MeshRenderEnvMap) but keeps it below a store to one that escapes (a
      GXColor argument temporary in dlrendst, `scale` and `stripList` passed to
      calls) -- the split R2/R6/R7 could not find on opcode, size or
      partialness.
      at-sched  clause E3n (sb_sched_clause entries 0 and 3) and clause A
                (entry 0): a non-escaping frame object answers "no alias".
                E3n's call sites 0x60e2ee/0x60e3f3 and A's 0x60e371 are
                retargeted to wrappers at +0x740 / +0x760.
      at-w      clause W (entries 0 and 1; calls 0x60e304/0x60e3a5 -> +0x7b0).
      at-v      VN entry 0: a store to a non-escaping frame object takes the
                stock whole-object kill (no clause V walk, no F); everything
                else goes on to 2.0p1b's vtmp stub. The dispatch word (already
                HIGHLOW-relocated) points at +0x7d0.
      in_wc reads worst_case PC-relatively and walks the set's members, so
      nothing new needs a base relocation.

Measured (solo.py on every unit, against 2.0p1c; RW_COMPILER units, the five
GC/2.0p1 override units separately, and all 224 SB units; RW data sections are
identical to 2.0p1c's):
  r4        RW +3 / -0: CollisionDataStreamWrite 89.29, MultiTextureStreamGetSize
            85.00, MultiTextureStreamWrite 92.59 -> 100. Game +1 / -0
            (zDiscoFloor set_object_state 70.18 -> 100).
  at-sched  RW +2 / -0: RpLightGetConeAngle 84.50, MeshRenderEnvMap 97.61 -> 100;
            _rwDlNativeTextureWrite 97.73 -> 97.75. Override units:
            RtQuatSetupSlerpCache 91.52 -> 100 (rtslerp), stdkey Blend /
            Interpolate 88.3 -> 96.7, _rpPTankGameCubeCreateCallBack 95.90 ->
            98.21. Game +5 / -0 (xSpline BasisBspline, zEntPlayerOOBState
            render_fade, zNPCGoalJellyBirth::Process, zNPCGoalPatrol::MoveNormal,
            zSceneSetup); xParCmdAnimalMagentism_Update 85.85 -> 98.27, two
            partials down (xFont get_bounds 67.12 -> 61.42, zNPCFodBzzt
            DiscoRender 79.10 -> 76.25).
  at-w      RW 0 / 0; override unit setup: MatFunc1 53.28 -> 100. Game 0 / 0.
  at-v      RW 0 / 0; stdkey Blend / Interpolate 88.3 -> 91.7. Game 0 / 0.
  all four  RW +5 / -0. Override units: ptankgcncallbacks 4/4, ptankgcnrender
            1/1, setup 7/7, rtslerp 1/1 (its .sdata2 residue is the same as
            under GC/2.0p1), stdkey 7/8 (RpHAnimKeyFrameStreamWrite 94.26, the
            R3 cost; 8/8 only under GC/2.0p1). Game +7 / -0 against 2.0p1c,
            +9 / -0 against GC/2.0p1a (adds xfont::irender, validate_popper).

GC/2.0p1e
---------
GC/2.0p1d plus rep + nps (the GC/2.5 const-pointee alias graft). Built by
path (`patch_compiler_rw.py <compilers>/GC/2.0p1e/mwcceppc.exe`) or with
`patch_compiler_rw.py <compilers dir> --p1e`. Three further retail-only parts
(dss, volb, e3n4) have no later-compiler provenance and too little evidence
for generality, so they are experimental only: any subset of the five with
`--p1e-parts rep,nps,dss,volb,e3n4 --out <dir>` (never GC/2.0p1e itself).
Every part writes at fixed places. dss, e3n4 and volb all extend scheduler
entry 4; its handler chain is dss -> e3n4 -> volb -> 2.0p1a's entry-4 stub,
skipping the parts that are off, so every subset is well defined.

  rep   2.5's alias for a const/restrict pointee (GC/2.5 behaviour). Both
        compilers give the `mr` of a pointer-to-const or restrict variable an
        alias on a fresh pseudo-object. 2.0p1's maker (0x513330) wraps it in a
        one-member alias SET. 2.5's maker (0x513620) returns
        make_alias(pseudo, 0x7fffff, 1): a plain subrange at a mid offset, so
        the stock transfer function (0x512740; the same code in both
        compilers) moves the offset through addi, and gives a merge of
        different offsets (a loop's IV increment, or an addi whose source
        has two reaching defs) a whole-object alias. The patch makes
        2.0p1's maker return 2.5's alias (one site, 0x51336c).
        Consequences, all from stock code reading the plain alias:
          * LICM hoists loads through a const pointer (stock 2.0p1 rejects a
            SET alias; a plain one has no defs inside the loop). This is all
            of R3: with rep, 2.0p1c's R3 hooks never see a SET and are inert
            (byte-identical objects on all 342 units with or without them),
            and every R3 gain stays.
          * AddPropagation (2.0p1 0x56bd70; identical code in 2.5) refuses to
            fold an addi whose alias is a whole-object alias of a non-frame
            object. So an unrolled loop over a pointer-to-const keeps one
            `addi rP,rP,stride` per copy (the later peephole sinks each past
            the next copy's loads) instead of folding them all into the
            displacements and one final addi. This is R10: it is not an
            unroller difference (IroUnrollLoop.c and LoopOptimization.c are
            the same code in 2.0p1 and 2.5).
        Repros (written for this, not RW source): of 30 functions, 2.0p1
        differs from 2.5 on 9 and 2.0p1d on 6 (unrolled const-pointer loops, an
        addi off a twice-defined const pointer); 2.0p1e equals 2.5 on 29. The
        30th differs from 2.5 under 2.0p1d too (2.0p1a's whole-static-read LICM
        hook keeps an int->float bias load in the loop).
  nps   needed by rep. 2.0p1a's clause predicates test "static object" as
        word0 == 5, which a pseudo-object also satisfies; under 2.0p1 they
        never saw one (it only appeared inside a SET) and 2.5 has no clauses.
        The eight tests in 2.0p1a's blob (A's and S's static tests, E3n's and
        W's, the LICM static-read hook, clause V's walk and clause F) skip
        objects of the pseudo type. No effect without rep; without it rep
        loses three iCollide functions to clause V killing pseudo values.
  dss   retail-only (a narrow form of 2.0p1a's clause B on entry 4, which
        DUPLOTRON measured at -199 in its general form). On entry 4 (field x
        field), a plain store addressed directly by symbol (`stw rS,
        sym@sda21`) to a field of a static is ordered before a later store
        to a field of a frame object. Stock 2.0p1, 2.5 and 2.0p1d have no such
        edge. Retail has it in StalacTiteAlloc and _rwDlCameraBeginUpdate;
        StalacMiteAlloc, where the same store goes through a base register
        (`stw rS,4(rB)`), has no edge, so the direct-symbol condition is
        needed (without it StalacMiteAlloc is lost). Allowing a static field as
        the second store costs four game functions.
  volb  retail-only: a volatile store is ordered before any later store
        (entries 0, 1, 3 and 4). Stock compilers order volatile accesses only
        among themselves. _rwDlRasterShowRaster needs it once _RwGCXFBCopy is
        declared volatile (which also fixes its six load-order rows); on the
        current source it changes nothing.
  e3n4  retail-only, the weakest: p1d's address-taken-gated clause E3n also on
        entry 4 when the load is a field of a static of at most 8 bytes
        (clause S's alias unit) that is outside the literal pool (section
        byte 0x0b). RpMaterialStreamRead (both RwEngineInstance and
        materialModule.globalsOffset stay below `mat.color = tmp`). E3n on
        entry 4 in general is -200; for small statics only it is -9 (8-byte
        aggregate literals @NNN); the literal-pool exclusion makes it +1 / -0
        but rests on that one RW function.

Measured (solo-equivalent sweep of every unit, paired against GC/2.0p1d; 117
RW_COMPILER units, stdkey, and the 224 SB units):
  rep+nps   RW +0 / -0, RwCameraFrustumTestSphere 90.77 -> 94.13 (100 with
            the in-loop sphere->center/radius source form). Game +3 / -0:
            zNPCSpawner::Owned, xtextbox::layout::yextent,
            zNPCBPlankton::player_left_territory.
  dss       RW +2 / -0: StalacTiteAlloc, _rwDlCameraBeginUpdate
            (RxLockedPipeUnlock 98.06 -> 98.02). Game 0 / 0.
  volb      RW 0 / 0, game 0 / 0 on the current source.
  e3n4      RW +1 / -0: RpMaterialStreamRead. Game 0 / 0
            (zNPCFodBzzt::DiscoRender 77.59 -> 74.14, two partials up).
  all five  RW +3 / -0, game +3 / -0; stdkey unchanged.

GC/2.0p1f
---------
GC/2.0p1e plus nap. Built by path
(`patch_compiler_rw.py <compilers>/GC/2.0p1f/mwcceppc.exe`) or with
`patch_compiler_rw.py <compilers dir> --p1f`.

  nap   no IRO copy propagation into an address-taken local (GC/3.0a3 and
        3.0a5.2 behaviour). IroPropagate.c's IsPropagatable (2.0p1 0x4709f0)
        decides whether a variable-to-variable copy `y = x` may be propagated
        into later reads of y. Stock 2.0p1 refuses only a register-allocatable
        y fed from a non-allocatable x; when y itself is not allocatable
        (VarInfo+0x22 != 0: its address is taken) it propagates, so a later
        read of y becomes the unrounded register x. 3.0a3 and 3.0a5.2 refuse
        that direction too: the read stays a load of y's home, which the
        backend's store->load forwarding then supplies (with `frsp` for an
        F32, since stfs rounds). 1.3.2 .. 2.7 propagate. The patch is one
        byte: that `jne` (0x470aec, 75 05 -> 75 28) goes to the `return 0`
        tail (0x470b16) instead of the "destination not allocatable ->
        propagate" exit.
        Repros: tools/compilerprobe/repros/x_nap.cpp and x_nap.c group 2.0p1f
        with 3.0a3/3.0a5.2 wherever 2.0p1e and 3.0a differ.

Measured (full-tree sweep against GC/2.0p1e): RW 0 / 0; game 0 / 0 on the
source as it was (written around the propagation with one-element arrays),
+3 / -0 with those arrays reverted to honest scalars (the update_turn functions
of zNPCB_SB2, zNPCDutchman and zNPCBPlankton).

GC/2.0p1g
---------
GC/2.0p1f plus ssi. Built by path
(`patch_compiler_rw.py <compilers>/GC/2.0p1g/mwcceppc.exe`) or with
`patch_compiler_rw.py <compilers dir> --p1g`.

  ssi   2.0p1a's AliasPatch.c clause C+ (blob 0x60e06c: differing opcodes,
        both static objects, the non-store side at most 4 bytes) answers
        "may alias" for a pair of STORES too, so the scheduler never reorders
        two stores to different statics with different opcodes. Stock 2.0p1,
        2.5, 2.6 and 2.7 answer "no alias" for two indirect stores to
        different objects, and retail reorders them (zMusicNotify: the
        `stwx` to sMusicQueueData[t] is scheduled above the earlier `stfsx`
        to sMusicTimer[t]). ssi narrows the clause: when BOTH pcodes are
        indirect stores (pcode+0x14 & 0x24 == 0x24: store, and an X-form or
        pointer access whose memref is the whole object) and their memrefs
        name DIFFERENT objects, C/C+ answer 0. Everything else still reaches
        C+. Direct-symbol stores and two stores into one array keep the edge
        (zGameLoop, FindAndInstanceAtomicCallback and zLasso_AddGuide need
        it). The 0x31-byte stub lives at .sbpatch+0xFC0; entry 0's call of
        C+ (0x60e31a) and clause C's call of it (0x60e12d, entries 1 and 3)
        are retargeted to it.
        Repros: tools/compilerprobe/repros/x_ss.c (q_noglob, q_ptr, q_rev
        byte-identical to stock 2.0p1/2.5/2.6/2.7; c_direct and c_same
        unchanged from 2.0p1f).

Measured (full build against GC/2.0p1f): RW 0 / 0; game +1 / -0 on the source
as it was (zEntPlayer_SNDInit 99.92 -> 100), +3 / -0 with zMusicNotify and
zMusicNotifyEvent written honestly (only the DWARF local `s`, timer store
first): both go to 100 and zMusic.cpp links as Matching.
"""

import hashlib
import os
import shutil
import struct
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import patch_compiler

BASE_VERSION = patch_compiler.PATCHED_VERSION      # GC/2.0p1a
RW_VERSION = "GC/2.0p1b"

BASE_SHA1 = patch_compiler.PATCHED_SHA1
RW_SHA1 = "c8e72ea91fd2cf7f992f90de4f2c6a0f5b897d73"

# 2.0p1a layout this patch builds on (all verified before writing).
VN_DISPATCH_OFFSET = patch_compiler.VN_DISPATCH_OFFSET   # table entry 0, file offset
P1A_VN_STUB = 0x0060E5F8           # 2.0p1a's entry-0 target (clauses V, F)
STOCK_KILL = 0x00511A53            # stock AliasType0 whole-object kill

SECTION_VA = patch_compiler.BLOB_VA                # .sbpatch
SECTION_FILE = patch_compiler.SECTION_FILE
SECTION_SIZE = patch_compiler.SECTION_SIZE
VTMP_STUB_VA = SECTION_VA + 0xF00                  # well clear of blob + stubs

FRAME_OBJECT_WORD = 0x00010005


def _rel32(frm_end, to):
    return struct.pack("<i", to - frm_end)


def vtmp_stub(at):
    """ebx = the alias being stored through (update_alias_value's arg 1)."""
    b = bytearray()
    b += b"\x8B\x43\x10"                       # mov eax,[ebx+0x10]   base
    b += b"\x85\xC0"                           # test eax,eax
    b += b"\x74\x12"                          # jz   p1a
    b += b"\x81\x38" + struct.pack("<I", FRAME_OBJECT_WORD)  # cmp dword [eax],0x10005
    b += b"\x75\x0A"                           # jne  p1a
    b += b"\x83\x78\x18\x00"                   # cmp dword [eax+0x18],0
    b += b"\x0F\x84"; b += _rel32(at + len(b) + 4, STOCK_KILL)   # je stock kill
    assert len(b) == 0x19                      # p1a: label
    b += b"\xE9"; b += _rel32(at + len(b) + 4, P1A_VN_STUB)      # p1a: jmp V/F stub
    return bytes(b)


def _apply(data: bytearray) -> bytes:
    stub = vtmp_stub(VTMP_STUB_VA)
    so = SECTION_FILE + (VTMP_STUB_VA - SECTION_VA)
    if so + len(stub) > SECTION_FILE + SECTION_SIZE or len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected 2.0p1a layout (file size {len(data):#x})")
    # The stub region must be unused section padding ...
    if any(data[so:so + len(stub)]):
        sys.exit(f"stub region at {so:#x} is not free in {BASE_VERSION}")
    # ... and nothing in the section may live past it (the region is padding,
    # not a hole between pieces of 2.0p1a's code).
    if any(data[so:SECTION_FILE + SECTION_SIZE]):
        sys.exit(f"{BASE_VERSION} uses .sbpatch bytes past {VTMP_STUB_VA:#x}")
    data[so:so + len(stub)] = stub

    found = struct.unpack_from("<I", data, VN_DISPATCH_OFFSET)[0]
    if found != P1A_VN_STUB:
        sys.exit(f"vn dispatch entry 0 is {found:#x}, expected {P1A_VN_STUB:#x}")
    struct.pack_into("<I", data, VN_DISPATCH_OFFSET, VTMP_STUB_VA)
    return bytes(data)


def patch_compiler_rw(compilers: Path) -> bool:
    """Create GC/2.0p1b next to GC/2.0p1a. Returns True if it is present."""
    src_dir = compilers / BASE_VERSION
    dst_dir = compilers / RW_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"

    if not src.exists():
        return False

    actual = patch_compiler.sha1(src)
    if actual != BASE_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {BASE_SHA1}; refusing to patch an unknown build")

    if dst.exists() and patch_compiler.sha1(dst) == RW_SHA1:
        return True

    dst_dir.mkdir(parents=True, exist_ok=True)
    # mwcceppc.exe needs lmgr326b.dll beside it; copy the whole directory, then
    # drop the copied (wrong-version) exe before anything can fail.
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, dst_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply(bytearray(src.read_bytes()))
    result = hashlib.sha1(out).hexdigest()
    if result != RW_SHA1:
        sys.exit(f"derived {RW_VERSION} has SHA-1 {result}, expected {RW_SHA1}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


# ---- GC/2.0p1c: R3, 2.5-style LICM through pointer-to-const -----------------
# See the module docstring. Everything below is checked against 2.0p1b's bytes
# before it is written.

R3_VERSION = "GC/2.0p1c"
R3_SHA1 = "0a0662b29a66e4e42310ec45b9b9a9a0269f1350"

TEXT_FILE_DELTA = 0x00400C00       # .text: file offset = VA - this
R3_BLOB_VA = SECTION_VA + 0xC00    # free .sbpatch padding (2.0p1a ends ~+0x652, vtmp is +0xF00)

# 2.0p1 addresses the R3 code reaches (CodeMotion.c / Alias.c / UseDefChains.c)
R3_FILTER_SITE = 0x0056F461        # moveinvariantsfromloop: and eax,0x1a8 ; jne skip
R3_FILTER_OLD = bytes.fromhex("25a80100007526")
R3_FILTER_CONT = 0x0056F468        # -> push 0 ... call isloopinvariant
R3_FILTER_SKIP = 0x0056F48E        # -> not a candidate
R3_CALL_SITE = 0x0056F472          # call isloopinvariant (2.0p1a: -> its LICM stub)
P1A_LICM_STUB = 0x0060E63B         # 2.0p1a's sb_licm_invariant stub
ISLOOPINVARIANT = 0x00570F60
ISLOOPINVARIANT_MEMDONE = 0x005710D0   # isloopinvariant past its memory-operand checks
FINDOBJECTUSEDEF = 0x0056F1D0
WORST_CASE_ALIAS = 0x005E9CB4      # Alias.c: worst_case (global holding the Alias*)
PSEUDO_OBJECT_TYPE = 0x005BD008    # type of the const/restrict pointee pseudo-objects
PSEUDO_MAKER_TYPE_IMM = 0x0051334D # `mov dword [ebx+0xe], PSEUDO_OBJECT_TYPE` in 0x513330
REG_DEFLISTS = 0x005E9A60          # per register class: reg -> list of def ids
DEFS = 0x005E966C                  # Defs[] (10-byte entries, PCode* first)
FP_VETO_SITE = 0x00570985          # large-loop veto: op-0x89 ; sub eax,5 ; cmp eax,7 ; jbe ; jmp
FP_VETO_OLD = bytes.fromhex("2d0500000083f8077635eb3f")
FP_VETO_NEW = bytes.fromhex("2dd800000083f8027635eb3f")   # 2.5: 0x161-0x163 instead

# Assembled from this source (Intel syntax). E8/E9 rel32 to compiler code and
# the four PC-relative displacements (0x11111111 worst_case, 0x22222222 pseudo
# type, 0x33333333 REG_DEFLISTS, 0x44444444 DEFS) are filled in by r3_blob().
#
#   is_cps_alias:            ; (Alias *a) -> the member Alias* if `a` is {pseudo}, else 0
#     mov eax,[esp+4] ; test eax,eax ; jz no
#     call $+5 ; pop edx                         ; edx = VA of the pop
#     cmp eax,[edx+worst_case] ; je no
#     cmp byte [eax+0x2c],2 ; jne no             ; a set
#     mov eax,[eax+0xc] ; test eax,eax ; jz no   ; first member node
#     cmp dword [eax],0 ; jne no                 ; exactly one member
#     mov eax,[eax+0xc] ; cmp byte [eax+0x2c],0 ; jne no   ; whole-object alias
#     mov ecx,[eax+0x10] ; lea edx,[edx+PSEUDO_OBJECT_TYPE] ; cmp [ecx+0xe],edx ; jne no
#     ret
#   no: xor eax,eax ; ret
#   is_cps:                  ; (PCode *p) -> member Alias* if p is a cps load, else 0
#     push ebx/esi/edi/ebp ; mov ebx,[esp+0x14]
#     test byte [ebx+0x14],4 ; jnz fail          ; not a write
#     push [ebx+0x18] ; call is_cps_alias ; pop ecx ; test eax,eax ; jz fail
#     mov edi,eax ; call $+5 ; pop ebp
#     movsx esi,word [ebx+0x22] ; add ebx,0x24   ; operands
#   oploop: sub esi,1 ; jb done
#     cmp byte [ebx],0 ; jne next ; test byte [ebx+2],1 ; jz next   ; a used register
#     movzx eax,byte [ebx+1] ; mov eax,[ebp+eax*4+REG_DEFLISTS]
#     movsx ecx,word [ebx+4] ; mov ecx,[eax+ecx*4]
#   dloop: test ecx,ecx ; jz next
#     mov eax,[ecx+4] ; lea eax,[eax+eax*4] ; mov edx,[ebp+DEFS] ; mov eax,[edx+eax*2]
#     cmp word [eax+0x20],0x8b ; jne fail        ; every def is an `mr` ...
#     push ecx ; push [eax+0x18] ; call is_cps_alias ; pop ecx ; pop ecx
#     test eax,eax ; jz fail                     ; ... carrying a pseudo set
#     mov ecx,[ecx] ; jmp dloop
#   next: add ebx,12 ; jmp oploop
#   done: mov eax,edi ; jmp out
#   fail: xor eax,eax
#   out: pop ebp/edi/esi/ebx ; ret
#   filter:                  ; eax = flags, ebx = pcode (replaces and eax,0x1a8 ; jne)
#     test eax,0x188 ; jnz skip ; test al,0x20 ; jz cont
#     push ebx ; call is_cps ; pop ecx ; test eax,eax ; jz skip
#   cont: jmp R3_FILTER_CONT
#   skip: jmp R3_FILTER_SKIP
#   inv:                     ; isloopinvariant(pcode, loop, vec, f1, f2), cdecl
#     push [esp+4] ; call is_cps ; pop ecx ; test eax,eax ; jz p1a
#     push eax ; push [eax+0x10] ; call FINDOBJECTUSEDEF ; pop ecx
#     test eax,eax ; pop eax ; jz nodefs
#     mov ecx,[esp+4] ; push [ecx+0x18] ; mov [ecx+0x18],eax   ; swap in the member
#     push [esp+0x18] x5 ; call ISLOOPINVARIANT ; add esp,0x14
#     pop edx ; mov ecx,[esp+4] ; mov [ecx+0x18],edx ; ret     ; restore
#   nodefs:                  ; no use-def node: re-enter past the memory checks
#     push ebx/esi/edi/ebp ; sub esp,0x10 ; mov ebp,[esp+0x28] ; mov esi,[esp+0x2c]
#     jmp ISLOOPINVARIANT_MEMDONE
#   p1a: jmp P1A_LICM_STUB
R3_BLOB = bytes.fromhex(
    "8b44240485c07438e8000000005a3b8211111111742a80782c0275248b400c85c0741d83380075188b400c80782c00750f"
    "8b48108d922222222239510e7501c331c0c3535657558b5c2414f64314047575ff7318e8a7ffffff5985c0746889c7e8"
    "000000005d0fbf732283c32483ee017250803b007546f643020174400fb643018b8485333333330fbf4b048b0c8885c974"
    "2a8b41048d04808b95444444448b0442668178208b00751c51ff7018e84dffffff595985c0740d8b09ebd283c30cebab89"
    "f8eb0231c05d5f5e5bc3a9880100007514a820740b53e865ffffff5985c07405e900000000e900000000ff742404e84dff"
    "ffff5985c0745250ff7010e8000000005985c058742f8b4c2404ff7118894118ff742418ff742418ff742418ff742418ff"
    "742418e80000000083c4145a8b4c2404895118c35356575583ec108b6c24288b74242ce900000000e900000000")
R3_FILTER_ENTRY = 0xCD
R3_INV_ENTRY = 0xED


def r3_blob(at):
    """The R3 code placed at VA `at`; returns (bytes, filter_va, inv_va)."""
    b = bytearray(R3_BLOB)
    if len(b) != 0x152:
        sys.exit("R3 blob has the wrong length")

    def disp(off, pc, target, placeholder):
        if struct.unpack_from("<I", b, off)[0] != placeholder:
            sys.exit(f"R3 blob: no placeholder at {off:#x}")
        struct.pack_into("<i", b, off, target - (at + pc))

    def branch(off, op, target):
        if b[off] != op or any(b[off + 1:off + 5]):
            sys.exit(f"R3 blob: no rel32 slot at {off:#x}")
        b[off + 1:off + 5] = _rel32(at + off + 5, target)

    disp(0x10, 0x0D, WORST_CASE_ALIAS, 0x11111111)
    disp(0x36, 0x0D, PSEUDO_OBJECT_TYPE, 0x22222222)
    disp(0x84, 0x65, REG_DEFLISTS, 0x33333333)
    disp(0x9B, 0x65, DEFS, 0x44444444)
    branch(0xE3, 0xE9, R3_FILTER_CONT)
    branch(0xE8, 0xE9, R3_FILTER_SKIP)
    branch(0xFF, 0xE8, FINDOBJECTUSEDEF)
    branch(0x128, 0xE8, ISLOOPINVARIANT)
    branch(0x148, 0xE9, ISLOOPINVARIANT_MEMDONE)
    branch(0x14D, 0xE9, P1A_LICM_STUB)
    return bytes(b), at + R3_FILTER_ENTRY, at + R3_INV_ENTRY


def _apply_r3(data: bytearray) -> bytes:
    def text(va):
        return va - TEXT_FILE_DELTA

    def expect(off, want, what):
        if bytes(data[off:off + len(want)]) != want:
            sys.exit(f"{what} at {off:#x} is {bytes(data[off:off + len(want)]).hex()}, "
                     f"expected {want.hex()}")

    if len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected {RW_VERSION} layout (file size {len(data):#x})")
    # Sanity: the addresses this patch assumes are 2.0p1's.
    expect(text(PSEUDO_MAKER_TYPE_IMM), b"\xC7\x43\x0E" + struct.pack("<I", PSEUDO_OBJECT_TYPE),
           "pseudo-object type store")

    blob, filter_va, inv_va = r3_blob(R3_BLOB_VA)
    so = SECTION_FILE + (R3_BLOB_VA - SECTION_VA)
    if any(data[so:so + len(blob)]) or R3_BLOB_VA + len(blob) > SECTION_VA + 0xF00:
        sys.exit(f"R3 region at {so:#x} is not free in {RW_VERSION}")
    data[so:so + len(blob)] = blob

    # 1. the flag filter -> R3 filter (5-byte jmp + 2 nops over and/jne)
    o = text(R3_FILTER_SITE)
    expect(o, R3_FILTER_OLD, "LICM flag filter")
    data[o:o + 7] = b"\xE9" + _rel32(R3_FILTER_SITE + 5, filter_va) + b"\x90\x90"

    # 2. call isloopinvariant (via 2.0p1a's stub) -> R3 inv
    o = text(R3_CALL_SITE)
    expect(o, b"\xE8" + _rel32(R3_CALL_SITE + 5, P1A_LICM_STUB), "LICM call")
    data[o + 1:o + 5] = _rel32(R3_CALL_SITE + 5, inv_va)

    # 3. 2.5's large-loop veto opcode range
    o = text(FP_VETO_SITE)
    expect(o, FP_VETO_OLD, "large-loop veto")
    data[o:o + len(FP_VETO_NEW)] = FP_VETO_NEW
    return bytes(data)


def patch_compiler_r3(compilers: Path) -> bool:
    """Create GC/2.0p1c next to GC/2.0p1b (deriving 2.0p1b first if needed)."""
    if not patch_compiler_rw(compilers):
        return False
    src_dir = compilers / RW_VERSION
    dst_dir = compilers / R3_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"

    actual = patch_compiler.sha1(src)
    if actual != RW_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {RW_SHA1}; refusing to patch an unknown build")
    if dst.exists() and patch_compiler.sha1(dst) == R3_SHA1:
        return True

    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, dst_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply_r3(bytearray(src.read_bytes()))
    result = hashlib.sha1(out).hexdigest()
    if result != R3_SHA1:
        sys.exit(f"derived {R3_VERSION} has SHA-1 {result}, expected {R3_SHA1}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


# ---- GC/2.0p1d: R4 + the address-taken gate ----------------------------------
# See the module docstring. Four independent parts; GC/2.0p1d is all four. Every
# part writes at a fixed place, so any subset is a well-defined build.

P1D_VERSION = "GC/2.0p1d"
P1D_PARTS = ("r4", "at-sched", "at-w", "at-v")
P1D_SHA1 = "0a4878bb49f808bc137f7a8ae2fa08ae99c0c3b5"     # all four parts
# Single-part builds (experimental, --p1d-parts), checked the same way.
P1D_PART_SHA1 = {
    "r4": "7d8428b22c8d99218b188e3a047cd4175d08be74",
    "at-sched": "d2a7e752f9469bc1f5aa1a4e49ccb040b544485d",
    "at-w": "a5597f3b04ff2168602712363c5fe6a633bca497",
    "at-v": "4e468882b8e0656019848028e8d3705c1e4af40f",
}

# R4: Alias.c's pointer-load alias pass (2.0p1 0x5123b0), two-register case.
R4_SITE = 0x0051258B               # jne 0x5125ba (both registers non-worst -> worst_case)
R4_OLD = bytes.fromhex("752d")
R4_NEW = bytes.fromhex("7531")     # jne 0x5125be (the access keeps its own alias)

# The address-taken gate. AliasPatch.c's clause predicates, reached by rel32
# calls from sb_sched_clause (2.0p1a's blob), and the VN entry-0 dispatch word.
E3N_FN = 0x0060E13C                # clause E3n (store to declared frame object -> static load)
W_FN = 0x0060E1C8                  # clause W   (literal load -> store to declared frame object)
A_FN = 0x0060E2A0                  # clause A   (differing opcodes, <= 4 bytes, one side static)
E3N_CALLS = (0x0060E2EE, 0x0060E3F3)   # sb_sched_clause entry 0 and entry 3
W_CALLS = (0x0060E304, 0x0060E3A5)     # entry 0 and entry 1
A_CALLS = (0x0060E371,)                # entry 0
FRAME_WORD = FRAME_OBJECT_WORD

# Fixed places in .sbpatch padding (2.0p1a ends ~+0x652; R3 is +0xC00..+0xD52;
# vtmp is +0xF00..+0xF1E).
IN_WC_VA = SECTION_VA + 0x700
AT_E3N_VA = SECTION_VA + 0x740
AT_A_VA = SECTION_VA + 0x760
AT_W_VA = SECTION_VA + 0x7B0
AT_V_VA = SECTION_VA + 0x7D0
P1D_REGION = (0x700, 0x800)


def in_wc_fn(at):
    """cdecl int in_wc(Object *o): 1 if a member of the worst_case alias set is
    an alias of `o`, i.e. `o` is address-taken (its address escapes)."""
    b = bytearray()
    b += b"\xE8\x00\x00\x00\x00"               # call $+5
    pop_va = at + len(b)
    b += b"\x5A"                               # pop edx
    b += b"\x8B\x92" + struct.pack("<i", WORST_CASE_ALIAS - pop_va)   # mov edx,[worst_case]
    b += b"\x85\xD2\x74\x1D"                   # test edx,edx ; jz no
    b += b"\x80\x7A\x2C\x02\x75\x17"           # cmp byte [edx+0x2c],2 ; jne no (not a set)
    b += b"\x8B\x52\x0C"                       # mov edx,[edx+0xc]   first member node
    assert len(b) == 0x19                      # loop:
    b += b"\x85\xD2\x74\x10"                   # test edx,edx ; jz no
    b += b"\x8B\x4A\x0C"                       # mov ecx,[edx+0xc]   member alias
    b += b"\x8B\x49\x10"                       # mov ecx,[ecx+0x10]  its object
    b += b"\x3B\x4C\x24\x04\x74\x07"           # cmp ecx,[esp+4] ; je yes
    b += b"\x8B\x12\xEB\xEC"                   # mov edx,[edx] ; jmp loop
    assert len(b) == 0x2D                      # no:
    b += b"\x31\xC0\xC3"                       # xor eax,eax ; ret
    b += b"\xB8\x01\x00\x00\x00\xC3"           # yes: mov eax,1 ; ret
    return bytes(b)


def at_arg_wrap(at, arg_off, clause):
    """clause(a, b, ma, mb) wrapper: answer 0 unless the alias at [esp+arg_off]
    (ma for E3n, mb for W -- the frame side) belongs to an address-taken object."""
    b = bytearray()
    b += b"\x8B\x44\x24" + bytes((arg_off,))   # mov eax,[esp+arg_off]
    b += b"\xFF\x70\x10"                       # push [eax+0x10]  (object)
    b += b"\xE8" + _rel32(at + len(b) + 5, IN_WC_VA)   # call in_wc
    b += b"\x59\x85\xC0\x74\x05"               # pop ecx ; test eax,eax ; jz skip
    b += b"\xE9" + _rel32(at + len(b) + 5, clause)     # jmp clause
    b += b"\x31\xC0\xC3"                       # skip: xor eax,eax ; ret
    return bytes(b)


def at_a_wrap(at):
    """A(a, b) wrapper: answer 0 if either pcode's alias is a frame object that
    is not address-taken; otherwise the stock clause A."""
    b = bytearray()
    for side, (arg, nxt) in enumerate(((4, 0x21), (8, 0x42))):
        start = len(b)
        b += b"\x8B\x4C\x24" + bytes((arg,))   # mov ecx,[esp+arg]  pcode
        b += b"\x8B\x49\x18\x8B\x49\x10"       # mov ecx,[ecx+0x18] ; mov ecx,[ecx+0x10]
        b += b"\x85\xC9" + bytes((0x74, nxt - (len(b) + 4)))       # test ecx,ecx ; jz next
        b += b"\x81\x39" + struct.pack("<I", FRAME_WORD)            # cmp dword [ecx],0x10005
        b += bytes((0x75, nxt - (len(b) + 2)))                      # jne next
        b += b"\x51"                                                # push ecx
        b += b"\xE8" + _rel32(at + len(b) + 5, IN_WC_VA)            # call in_wc
        b += b"\x59\x85\xC0" + bytes((0x74, 0x47 - (len(b) + 5)))   # pop ecx ; test ; jz skip
        assert len(b) == nxt, (side, hex(len(b)))
    b += b"\xE9" + _rel32(at + len(b) + 5, A_FN)       # jmp A
    assert len(b) == 0x47
    b += b"\x31\xC0\xC3"                               # skip: xor eax,eax ; ret
    return bytes(b)


def at_v_stub(at):
    """VN entry 0 (ebx = stored alias): a store to a frame object that is not
    address-taken takes the stock whole-object kill (no V walk, no F); everything
    else goes on to 2.0p1b's vtmp stub as before."""
    b = bytearray()
    b += b"\x8B\x43\x10\x85\xC0\x74\x1C"       # mov eax,[ebx+0x10] ; test ; jz p1b
    b += b"\x81\x38" + struct.pack("<I", FRAME_WORD) + b"\x75\x14"   # cmp [eax],0x10005 ; jne p1b
    b += b"\x51\x52\x50"                       # push ecx ; push edx ; push eax
    b += b"\xE8" + _rel32(at + len(b) + 5, IN_WC_VA)   # call in_wc
    b += b"\x59\x5A\x59"                       # pop ecx (arg) ; pop edx ; pop ecx
    b += b"\x85\xC0\x75\x05"                   # test eax,eax ; jnz p1b
    b += b"\xE9" + _rel32(at + len(b) + 5, STOCK_KILL)   # jmp stock kill
    assert len(b) == 0x23                      # p1b:
    b += b"\xE9" + _rel32(at + len(b) + 5, VTMP_STUB_VA)
    return bytes(b)


def _apply_p1d(data: bytearray, parts) -> bytes:
    parts = set(parts)
    if not parts or parts - set(P1D_PARTS):
        sys.exit(f"--p1d-parts must be a non-empty subset of {','.join(P1D_PARTS)}")

    def text(va):
        return va - TEXT_FILE_DELTA

    def expect(off, want, what):
        if bytes(data[off:off + len(want)]) != want:
            sys.exit(f"{what} at {off:#x} is {bytes(data[off:off + len(want)]).hex()}, "
                     f"expected {want.hex()}")

    def put(va, code):
        so = SECTION_FILE + (va - SECTION_VA)
        if any(data[so:so + len(code)]) or not (
                P1D_REGION[0] <= va - SECTION_VA and va - SECTION_VA + len(code) <= P1D_REGION[1]):
            sys.exit(f"{P1D_VERSION} region at {so:#x} is not free in {R3_VERSION}")
        data[so:so + len(code)] = code

    def retarget(site, old, new):
        o = SECTION_FILE + (site - SECTION_VA)       # the calls are in 2.0p1a's blob
        expect(o, b"\xE8" + _rel32(site + 5, old), f"call at {site:#x}")
        data[o + 1:o + 5] = _rel32(site + 5, new)

    if len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected {R3_VERSION} layout (file size {len(data):#x})")
    if any(data[SECTION_FILE + P1D_REGION[0]:SECTION_FILE + P1D_REGION[1]]):
        sys.exit(f"{P1D_VERSION} region is not free in {R3_VERSION}")

    if "r4" in parts:
        o = text(R4_SITE)
        expect(o, R4_OLD, "R4 two-register branch")
        data[o:o + len(R4_NEW)] = R4_NEW

    if parts & {"at-sched", "at-w", "at-v"}:
        put(IN_WC_VA, in_wc_fn(IN_WC_VA))
    if "at-sched" in parts:
        put(AT_E3N_VA, at_arg_wrap(AT_E3N_VA, 0x0C, E3N_FN))     # ma: the store
        for site in E3N_CALLS:
            retarget(site, E3N_FN, AT_E3N_VA)
        put(AT_A_VA, at_a_wrap(AT_A_VA))
        for site in A_CALLS:
            retarget(site, A_FN, AT_A_VA)
    if "at-w" in parts:
        put(AT_W_VA, at_arg_wrap(AT_W_VA, 0x10, W_FN))           # mb: the store
        for site in W_CALLS:
            retarget(site, W_FN, AT_W_VA)
    if "at-v" in parts:
        put(AT_V_VA, at_v_stub(AT_V_VA))
        found = struct.unpack_from("<I", data, VN_DISPATCH_OFFSET)[0]
        if found != VTMP_STUB_VA:
            sys.exit(f"vn dispatch entry 0 is {found:#x}, expected {VTMP_STUB_VA:#x}")
        struct.pack_into("<I", data, VN_DISPATCH_OFFSET, AT_V_VA)
    return bytes(data)


def _p1d_expected_sha1(parts):
    if set(parts) == set(P1D_PARTS):
        return P1D_SHA1
    if len(parts) == 1:
        return P1D_PART_SHA1[next(iter(parts))]
    return None


def patch_compiler_p1d(compilers: Path, parts=P1D_PARTS, out_dir: Path = None) -> bool:
    """Create GC/2.0p1d (all parts) next to GC/2.0p1c, deriving 2.0p1b/c first if
    needed. With a subset of parts, out_dir names where the experimental build goes."""
    if not patch_compiler_r3(compilers):
        return False
    parts = tuple(p for p in P1D_PARTS if p in set(parts))
    src_dir = compilers / R3_VERSION
    full = set(parts) == set(P1D_PARTS)
    if out_dir is None:
        if not full:
            sys.exit("a partial GC/2.0p1d needs --out <dir> (never GC/2.0p1d itself)")
        out_dir = compilers / P1D_VERSION
    elif not full and out_dir.resolve() == (compilers / P1D_VERSION).resolve():
        sys.exit(f"refusing to write a partial build to {P1D_VERSION}")
    src = src_dir / "mwcceppc.exe"
    dst = out_dir / "mwcceppc.exe"

    actual = patch_compiler.sha1(src)
    if actual != R3_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {R3_SHA1}; refusing to patch an unknown build")
    want = _p1d_expected_sha1(parts)
    if want and dst.exists() and patch_compiler.sha1(dst) == want:
        return True

    out_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, out_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply_p1d(bytearray(src.read_bytes()), parts)
    result = hashlib.sha1(out).hexdigest()
    if want is None:
        print(f"NOTE: no recorded SHA-1 for parts {','.join(parts)}; this build is {result}")
    elif result != want:
        sys.exit(f"derived {P1D_VERSION} ({','.join(parts)}) has SHA-1 {result}, expected {want}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


# ---- GC/2.0p1e: 2.5's const-pointee alias + three retail store/load edges ------
# See the module docstring. Five parts, each writing at fixed places; GC/2.0p1e is
# all five. The scheduler entry-4 handler chain is dss -> e3n4 -> volb -> 2.0p1a's
# entry-4 stub, skipping the parts that are off.

P1E_VERSION = "GC/2.0p1e"
P1E_PARTS = ("rep", "nps", "dss", "volb", "e3n4")
# GC/2.0p1e itself is the GC/2.5 graft only (rep + nps). dss, volb and e3n4 are
# retail-only rules without a later-compiler counterpart, resting on one or two
# functions each; they stay experimental (--p1e-parts ... --out DIR).
P1E_DEFAULT = ("rep", "nps")
P1E_SHA1 = "9d445725489050035740aaff35860eddbaf3c3c9"     # rep + nps
# Experimental subsets (--p1e-parts), checked the same way.
P1E_SUBSET_SHA1 = {
    frozenset(P1E_PARTS): "4e16e6e2e025ff0168ba93714f1fba2594ec4d39",
    frozenset(("rep",)): "8d8dc8d0a6f13a5166836c482b51b3bc404c9249",
    frozenset(("nps",)): "65ff5af729e74cc27434dadce687068d00d5d43a",
    frozenset(("dss",)): "0710f60def6e90882194538c85827b77c520578b",
    frozenset(("volb",)): "b345e0983e640be8baee941d753fc34c8e81d885",
    frozenset(("e3n4",)): "b86da3a87be9889ddf3b1c482f8712662082b241",
    frozenset(("rep", "nps")): "9d445725489050035740aaff35860eddbaf3c3c9",
    frozenset(("rep", "nps", "dss", "volb")): "352b8caaa52228fd938494d4a7544ff600f4ef41",
}

MAKE_ALIAS = 0x00512E20            # Alias.c make_alias(Object *, offset, size)
PSEUDO_TYPE = PSEUDO_OBJECT_TYPE   # 0x5bd008
MAY_ALIAS_YES = 0x00512081         # may_alias: the "may alias" answer tail
S_SMALL_STATIC = 0x0060E018        # 2.0p1a blob: (Alias *) -> whole alias if a field of a static <= 8 bytes
SCHED_DISPATCH = {                 # may_alias table word, 2.0p1a's handler
    0: (0x005BD0BC, 0x0060E57C), 1: (0x005BD0C0, 0x0060E59B),
    3: (0x005BD0C8, 0x0060E5BA), 4: (0x005BD0CC, 0x0060E5D9),
}

# rep: the pseudo-object maker's set construction -> return 2.5's plain alias.
REP_SITE = 0x0051336C
REP_OLD = bytes.fromhex("6a2ee8edd9f2ff")      # push 0x2e ; call 0x440d60 (allocate the set)

# nps: `cmp dword [reg],5 ; jcc` static tests in 2.0p1a's blob:
#      (site, reg, jcc, taken target, fall-through)
NPS_SITES = (
    (0x0060E00F, "edx", "jne", 0x0060E015, 0x0060E014),   # is_static (clause A)
    (0x0060E02C, "ebx", "je", 0x0060E035, 0x0060E031),    # clause S small static
    (0x0060E0B3, "esi", "jne", 0x0060E0E2, 0x0060E0B8),   # clause C/C+
    (0x0060E0DD, "eax", "je", 0x0060E0E6, 0x0060E0E2),
    (0x0060E1B8, "eax", "je", 0x0060E1C1, 0x0060E1BD),    # clause E3n
    (0x0060E4C2, "edx", "je", 0x0060E4CA, 0x0060E4C7),    # LICM static-read hook
    (0x0060E4EA, "ecx", "jne", 0x0060E4F9, 0x0060E4EF),   # clause V walk
)
NPS_F_SITE = 0x0060E518                        # clause F: mov ebx,[eax] ; cmp ebx,5
NPS_F_OLD = bytes.fromhex("8b1883fb05")
_X86 = {"eax": 0, "ecx": 1, "edx": 2, "ebx": 3, "esi": 6, "edi": 7}

# Fixed places in .sbpatch padding (2.0p1a ~+0x000..+0x652, p1d +0x700..+0x800,
# R3 +0xC00..+0xD52, vtmp +0xF00..+0xF1E).
NPS_VA = SECTION_VA + 0x900                    # .. +0xA6F
E3N4_VA = SECTION_VA + 0xB00
DSS_VA = SECTION_VA + 0xD60                    # entry-4 wrapper
DSS_PRED_VA = SECTION_VA + 0xD80
VOLB_VA = SECTION_VA + 0xE00                   # wrappers for entries 0, 1, 3, 4 (0x20 each)
VOLB_PRED_VA = SECTION_VA + 0xE80
P1E_REGIONS = ((0x900, 0xB00), (0xB00, 0xB40), (0xD60, 0xF00))


def _p1e_rep():
    b = bytearray()
    b += b"\x6A\x01"                                   # push 1
    b += b"\x68\xFF\xFF\x7F\x00"                       # push 0x7fffff
    b += b"\x53"                                       # push ebx (the pseudo-object)
    b += b"\xE8" + _rel32(REP_SITE + len(b) + 5, MAKE_ALIAS)
    b += b"\x83\xC4\x0C"                               # add esp,0xc
    b += b"\x5E\x5B\xC3"                               # pop esi ; pop ebx ; ret
    return bytes(b)


def _nps_stub(at, reg, jcc, taken, fall):
    """cmp dword [reg],5 as before, but a pseudo-object (type at +0xe) is not static.
    The type is compared PC-relatively, so the stub needs no base relocation."""
    r = _X86[reg]
    s = 0 if r != 0 else 1                             # scratch: eax, or ecx when reg is eax
    static_tgt, other_tgt = (taken, fall) if jcc == "je" else (fall, taken)
    b = bytearray()
    b += bytes((0x83, 0x38 | r, 0x05))                 # cmp dword [reg],5
    p0 = len(b); b += b"\x75\x00"                      # jne other
    b += bytes((0x50 | s,))                            # push s
    b += b"\xE8\x00\x00\x00\x00"                       # call $+5
    pc = at + len(b)
    b += bytes((0x58 | s,))                            # pop s
    b += bytes((0x8D, 0x80 | (s << 3) | s)) + struct.pack("<i", PSEUDO_TYPE - pc)  # lea s,[s+type]
    b += bytes((0x39, 0x40 | (s << 3) | r, 0x0E))      # cmp [reg+0xe],s
    b += bytes((0x58 | s,))                            # pop s (flags kept)
    p1 = len(b); b += b"\x74\x00"                      # je other (a pseudo-object)
    b += b"\xE9" + _rel32(at + len(b) + 5, static_tgt)
    other = len(b)
    b += b"\xE9" + _rel32(at + len(b) + 5, other_tgt)
    b[p0 + 1] = other - (p0 + 2)
    b[p1 + 1] = other - (p1 + 2)
    return bytes(b)


def _nps_f_stub(at):
    """mov ebx,[eax] ; cmp ebx,5 -- with a pseudo-object reading as word 0."""
    b = bytearray()
    b += b"\x8B\x18"                                   # mov ebx,[eax]
    b += b"\x51"                                       # push ecx
    b += b"\xE8\x00\x00\x00\x00"                       # call $+5
    pc = at + len(b)
    b += b"\x59"                                       # pop ecx
    b += b"\x8D\x89" + struct.pack("<i", PSEUDO_TYPE - pc)   # lea ecx,[ecx+type]
    b += b"\x39\x48\x0E"                               # cmp [eax+0xe],ecx
    b += b"\x59"                                       # pop ecx
    b += b"\x75\x02"                                   # jne +2
    b += b"\x31\xDB"                                   # xor ebx,ebx
    b += b"\x83\xFB\x05"                               # cmp ebx,5
    b += b"\xE9" + _rel32(at + len(b) + 5, NPS_F_SITE + 5)
    return bytes(b)


def _sched_wrapper(at, pred, nxt):
    """Scheduler dispatch entry (a = esi, b = ebp): if pred(a, b) -> may alias,
    else go on to nxt."""
    b = bytearray()
    b += b"\x55\x56"                                   # push ebp ; push esi
    b += b"\xE8" + _rel32(at + len(b) + 5, pred)
    b += b"\x83\xC4\x08\x85\xC0"                       # add esp,8 ; test eax,eax
    b += b"\x0F\x85" + _rel32(at + len(b) + 6, MAY_ALIAS_YES)
    b += b"\xE9" + _rel32(at + len(b) + 5, nxt)
    assert len(b) <= 0x20
    return bytes(b)


def _pcode_pred(body):
    """cdecl int pred(PCode *a, PCode *b) with esi = a, edi = b; body() appends
    tests and registers the short jumps that mean 'no'."""
    b = bytearray()
    b += b"\x56\x57\x8B\x74\x24\x0C\x8B\x7C\x24\x10"   # push esi ; push edi ; esi=a ; edi=b
    fails = []

    def no(op):
        b.extend(bytes((op, 0)))
        fails.append(len(b) - 1)
    body(b, no)
    b += b"\xB8\x01\x00\x00\x00\x5F\x5E\xC3"           # mov eax,1 ; pop edi ; pop esi ; ret
    fail = len(b)
    b += b"\x31\xC0\x5F\x5E\xC3"                       # xor eax,eax ; pop edi ; pop esi ; ret
    for f in fails:
        b[f] = fail - (f + 1)
    return bytes(b)


def _dss_pred():
    """a: a plain store whose displacement is a symbol, to a static (an alias that
    is not a set, object word 5); b: a plain store to a frame object (0x10005)."""
    def body(b, no):
        b += b"\x8B\x46\x14\x83\xE0\xDF\x83\xF8\x04"; no(0x75)   # a: flags & ~0x20 == 4
        b += b"\x8B\x47\x14\x83\xE0\xDF\x83\xF8\x04"; no(0x75)   # b: flags & ~0x20 == 4
        b += b"\x80\x7E\x3C\x03"; no(0x75)                       # a: operand 2 is a relocation
        b += b"\x8B\x46\x18\x85\xC0"; no(0x74)                   # ma
        b += b"\x80\x78\x2C\x02"; no(0x74)                       # not a set
        b += b"\x8B\x40\x10\x85\xC0"; no(0x74)
        b += b"\x83\x38\x05"; no(0x75)                           # a static
        b += b"\x8B\x47\x18\x85\xC0"; no(0x74)                   # mb
        b += b"\x80\x78\x2C\x02"; no(0x74)
        b += b"\x8B\x40\x10\x85\xC0"; no(0x74)
        b += b"\x81\x38" + struct.pack("<I", FRAME_WORD); no(0x75)   # a frame object
    return _pcode_pred(body)


def _volb_pred():
    """a: a volatile store (flags & ~0xa0 == 4 and flags & 0x80); b: a store."""
    def body(b, no):
        b += b"\x8B\x46\x14\x25\x5F\xFF\xFF\xFF\x83\xF8\x04"; no(0x75)
        b += b"\xF6\x46\x14\x80"; no(0x74)
        b += b"\x8B\x47\x14\x25\x5F\xFF\xFF\xFF\x83\xF8\x04"; no(0x75)
    return _pcode_pred(body)


def _e3n4_wrapper(at, nxt):
    """Entry 4: if mb is a field of a static of at most 8 bytes outside the literal
    pool (section byte 0x0b), ask p1d's gated E3n(a, b, ma, mb); else nxt."""
    b = bytearray()
    b += b"\xFF\x75\x18"                               # push [ebp+0x18]  mb
    b += b"\xE8" + _rel32(at + len(b) + 5, S_SMALL_STATIC)
    b += b"\x59\x85\xC0"                               # pop ecx ; test eax,eax
    p0 = len(b); b += b"\x74\x00"                      # jz next
    b += b"\x8B\x40\x10"                               # mov eax,[eax+0x10]  the object
    b += b"\x80\x78\x04\x0B"                           # cmp byte [eax+4],0x0b
    p1 = len(b); b += b"\x74\x00"                      # je next
    b += b"\xFF\x75\x18\xFF\x76\x18\x55\x56"           # push mb ; push ma ; push b ; push a
    b += b"\xE8" + _rel32(at + len(b) + 5, AT_E3N_VA)
    b += b"\x83\xC4\x10\x85\xC0"                       # add esp,16 ; test eax,eax
    b += b"\x0F\x85" + _rel32(at + len(b) + 6, MAY_ALIAS_YES)
    nxt_off = len(b)
    b += b"\xE9" + _rel32(at + len(b) + 5, nxt)
    b[p0 + 1] = nxt_off - (p0 + 2)
    b[p1 + 1] = nxt_off - (p1 + 2)
    assert len(b) <= 0x40
    return bytes(b)


def _apply_p1e(data: bytearray, parts) -> bytes:
    parts = set(parts)
    if not parts or parts - set(P1E_PARTS):
        sys.exit(f"--p1e-parts must be a non-empty subset of {','.join(P1E_PARTS)}")

    def text(va):
        return va - TEXT_FILE_DELTA

    def expect(off, want, what):
        if bytes(data[off:off + len(want)]) != want:
            sys.exit(f"{what} at {off:#x} is {bytes(data[off:off + len(want)]).hex()}, "
                     f"expected {want.hex()}")

    def put(va, code):
        rel = va - SECTION_VA
        if not any(lo <= rel and rel + len(code) <= hi for lo, hi in P1E_REGIONS):
            sys.exit(f"{P1E_VERSION}: {va:#x} is outside its regions")
        so = SECTION_FILE + rel
        if any(data[so:so + len(code)]):
            sys.exit(f"{P1E_VERSION} region at {so:#x} is not free in {P1D_VERSION}")
        data[so:so + len(code)] = code

    def dispatch(entry, new):
        word, old = SCHED_DISPATCH[entry]
        off = _p1e_data_offset(data, word)
        found = struct.unpack_from("<I", data, off)[0]
        if found != old:
            sys.exit(f"scheduler entry {entry} is {found:#x}, expected {old:#x}")
        struct.pack_into("<I", data, off, new)

    if len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected {P1D_VERSION} layout (file size {len(data):#x})")

    if "rep" in parts:
        o = text(REP_SITE)
        expect(o, REP_OLD, "pseudo-object set allocation")
        code = _p1e_rep()
        data[o:o + len(code)] = code

    if "nps" in parts:
        at = NPS_VA
        for site, reg, jcc, taken, fall in NPS_SITES:
            stub = _nps_stub(at, reg, jcc, taken, fall)
            r = _X86[reg]
            old = bytes((0x83, 0x38 | r, 0x05, 0x74 if jcc == "je" else 0x75,
                         (taken - (site + 5)) & 0xFF))
            o = SECTION_FILE + (site - SECTION_VA)
            expect(o, old, f"static test at {site:#x}")
            put(at, stub)
            data[o:o + 5] = b"\xE9" + _rel32(site + 5, at)
            at += (len(stub) + 0xF) & ~0xF
        stub = _nps_f_stub(at)
        o = SECTION_FILE + (NPS_F_SITE - SECTION_VA)
        expect(o, NPS_F_OLD, "clause F static test")
        put(at, stub)
        data[o:o + 5] = b"\xE9" + _rel32(NPS_F_SITE + 5, at)

    # scheduler entry 4: dss -> e3n4 -> volb -> 2.0p1a's handler
    chain = [va for name, va in (("dss", DSS_VA), ("e3n4", E3N4_VA), ("volb", VOLB_VA + 0x60))
             if name in parts]
    for i, va in enumerate(chain):
        nxt = chain[i + 1] if i + 1 < len(chain) else SCHED_DISPATCH[4][1]
        if va == DSS_VA:
            put(va, _sched_wrapper(va, DSS_PRED_VA, nxt))
        elif va == E3N4_VA:
            put(va, _e3n4_wrapper(va, nxt))
        else:
            put(va, _sched_wrapper(va, VOLB_PRED_VA, nxt))
    if chain:
        dispatch(4, chain[0])
    if "dss" in parts:
        put(DSS_PRED_VA, _dss_pred())
    if "volb" in parts:
        for k, entry in enumerate((0, 1, 3)):
            va = VOLB_VA + 0x20 * k
            put(va, _sched_wrapper(va, VOLB_PRED_VA, SCHED_DISPATCH[entry][1]))
            dispatch(entry, va)
        put(VOLB_PRED_VA, _volb_pred())
    return bytes(data)


def _p1e_data_offset(data, va):
    """File offset of `va` from the image's own section table (the may_alias
    dispatch table is in .data, not .text)."""
    rva = va - patch_compiler.IMAGE_BASE
    e = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, e + 6)[0]
    opt = struct.unpack_from("<H", data, e + 20)[0]
    o = e + 24 + opt
    for _ in range(nsec):
        vsz, sva, rsz, raw = struct.unpack_from("<IIII", data, o + 8)
        if sva <= rva < sva + max(vsz, rsz):
            return raw + rva - sva
        o += 40
    sys.exit(f"{va:#x} is in no section")


def _p1e_expected_sha1(parts):
    if set(parts) == set(P1E_DEFAULT):
        return P1E_SHA1
    return P1E_SUBSET_SHA1.get(frozenset(parts))


def patch_compiler_p1e(compilers: Path, parts=P1E_DEFAULT, out_dir: Path = None) -> bool:
    """Create GC/2.0p1e (rep + nps) next to GC/2.0p1d, deriving 2.0p1b/c/d first if
    needed. With a subset of parts, out_dir names where the experimental build goes."""
    if not patch_compiler_p1d(compilers):
        return False
    parts = tuple(p for p in P1E_PARTS if p in set(parts))
    src_dir = compilers / P1D_VERSION
    full = set(parts) == set(P1E_DEFAULT)
    if out_dir is None:
        if not full:
            sys.exit("a partial GC/2.0p1e needs --out <dir> (never GC/2.0p1e itself)")
        out_dir = compilers / P1E_VERSION
    elif not full and out_dir.resolve() == (compilers / P1E_VERSION).resolve():
        sys.exit(f"refusing to write a partial build to {P1E_VERSION}")
    src = src_dir / "mwcceppc.exe"
    dst = out_dir / "mwcceppc.exe"

    actual = patch_compiler.sha1(src)
    if actual != P1D_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {P1D_SHA1}; refusing to patch an unknown build")
    want = _p1e_expected_sha1(parts)
    if want and dst.exists() and patch_compiler.sha1(dst) == want:
        return True

    out_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, out_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply_p1e(bytearray(src.read_bytes()), parts)
    result = hashlib.sha1(out).hexdigest()
    if want is None:
        print(f"NOTE: no recorded SHA-1 for parts {','.join(parts)}; this build is {result}")
    elif result != want:
        sys.exit(f"derived {P1E_VERSION} ({','.join(parts)}) has SHA-1 {result}, expected {want}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


# ---- GC/2.0p1f: no copy propagation into an address-taken local ---------------
# See the module docstring. One byte in IroPropagate.c's IsPropagatable.

P1F_VERSION = "GC/2.0p1f"
P1F_SHA1 = "8641f1a15bab7d961b7b7558e8d0de64449c509c"
NAP_SITE = 0x00470AEC              # jne: destination not regable -> propagate
NAP_OLD = bytes.fromhex("7505")
NAP_NEW = bytes.fromhex("7528")    # jne 0x470b16: return 0 (do not propagate)


def _apply_p1f(data: bytearray) -> bytes:
    if len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected {P1E_VERSION} layout (file size {len(data):#x})")
    o = NAP_SITE - TEXT_FILE_DELTA
    if bytes(data[o:o + len(NAP_OLD)]) != NAP_OLD:
        sys.exit(f"IsPropagatable branch at {o:#x} is {bytes(data[o:o + 2]).hex()}, "
                 f"expected {NAP_OLD.hex()}")
    data[o:o + len(NAP_NEW)] = NAP_NEW
    return bytes(data)


def patch_compiler_p1f(compilers: Path) -> bool:
    """Create GC/2.0p1f next to GC/2.0p1e, deriving 2.0p1b..e first if needed."""
    if not patch_compiler_p1e(compilers):
        return False
    src_dir = compilers / P1E_VERSION
    dst_dir = compilers / P1F_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"

    actual = patch_compiler.sha1(src)
    if actual != P1E_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {P1E_SHA1}; refusing to patch an unknown build")
    if dst.exists() and patch_compiler.sha1(dst) == P1F_SHA1:
        return True

    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, dst_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply_p1f(bytearray(src.read_bytes()))
    result = hashlib.sha1(out).hexdigest()
    if result != P1F_SHA1:
        sys.exit(f"derived {P1F_VERSION} has SHA-1 {result}, expected {P1F_SHA1}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


# ---- GC/2.0p1g: clause C/C+ do not order two indirect stores to different objects
# See the module docstring. A stub in front of AliasPatch.c's clause C+.

P1G_VERSION = "GC/2.0p1g"
P1G_SHA1 = "99bd18455ff674337d7a6186164df8a1b1ba13a7"
SSI_STUB_VA = SECTION_VA + 0xFC0
CPLUS_VA = 0x0060E06C               # 2.0p1a AliasPatch.c clause C+ (a, b, ma, mb)
SSI_SITES = (0x0060E31A,            # entry 0's call of C+
             0x0060E12D)            # clause C's call of C+ (entries 1 and 3)


def ssi_stub(at):
    """C/C+ never order two INDIRECT stores (pcode+0x14 & 0x24) to DIFFERENT objects."""
    c = bytearray()
    to_cplus = []
    for arg in (4, 8):                          # a, b: pcodes
        c += bytes((0x8B, 0x44, 0x24, arg))     # mov eax,[esp+arg]
        c += bytes.fromhex("8B4814")            # mov ecx,[eax+0x14]  flags
        c += bytes.fromhex("83E124")            # and ecx,0x24        indirect | store
        c += bytes.fromhex("83F924")            # cmp ecx,0x24
        c += bytes.fromhex("7500")              # jne go
        to_cplus.append(len(c) - 1)
    c += bytes.fromhex("8B44240C")              # mov eax,[esp+0xc]   ma
    c += bytes.fromhex("8B4C2410")              # mov ecx,[esp+0x10]  mb
    c += bytes.fromhex("8B4010")                # mov eax,[eax+0x10]  ma->object
    c += bytes.fromhex("3B4110")                # cmp eax,[ecx+0x10]  mb->object
    c += bytes.fromhex("7400")                  # je go
    to_cplus.append(len(c) - 1)
    c += bytes.fromhex("31C0C3")                # xor eax,eax ; ret   no alias
    go = len(c)
    c += b"\xE9" + _rel32(at + len(c) + 5, CPLUS_VA)   # go: jmp C+
    for f in to_cplus:
        c[f] = go - (f + 1)
    return bytes(c)


def _apply_p1g(data: bytearray) -> bytes:
    if len(data) != SECTION_FILE + SECTION_SIZE:
        sys.exit(f"unexpected {P1F_VERSION} layout (file size {len(data):#x})")
    stub = ssi_stub(SSI_STUB_VA)
    so = SECTION_FILE + (SSI_STUB_VA - SECTION_VA)
    if any(data[so:so + len(stub)]):
        sys.exit(f".sbpatch region {SSI_STUB_VA:#x} is not free")
    data[so:so + len(stub)] = stub
    for site in SSI_SITES:
        o = SECTION_FILE + (site - SECTION_VA)
        old = b"\xE8" + _rel32(site + 5, CPLUS_VA)
        if bytes(data[o:o + 5]) != old:
            sys.exit(f"clause C+ call at {site:#x} is {bytes(data[o:o + 5]).hex()}, "
                     f"expected {old.hex()}")
        data[o:o + 5] = b"\xE8" + _rel32(site + 5, SSI_STUB_VA)
    return bytes(data)


def patch_compiler_p1g(compilers: Path) -> bool:
    """Create GC/2.0p1g next to GC/2.0p1f, deriving 2.0p1b..f first if needed."""
    if not patch_compiler_p1f(compilers):
        return False
    src_dir = compilers / P1F_VERSION
    dst_dir = compilers / P1G_VERSION
    src = src_dir / "mwcceppc.exe"
    dst = dst_dir / "mwcceppc.exe"

    actual = patch_compiler.sha1(src)
    if actual != P1F_SHA1:
        sys.exit(f"{src} has unexpected SHA-1 {actual}\n"
                 f"  expected {P1F_SHA1}; refusing to patch an unknown build")
    if dst.exists() and patch_compiler.sha1(dst) == P1G_SHA1:
        return True

    dst_dir.mkdir(parents=True, exist_ok=True)
    for f in src_dir.iterdir():
        if f.is_file():
            shutil.copy2(f, dst_dir / f.name)
    if dst.exists():
        dst.unlink()

    out = _apply_p1g(bytearray(src.read_bytes()))
    result = hashlib.sha1(out).hexdigest()
    if result != P1G_SHA1:
        sys.exit(f"derived {P1G_VERSION} has SHA-1 {result}, expected {P1G_SHA1}")

    tmp = dst.with_suffix(".exe.tmp")
    tmp.write_bytes(out)
    os.replace(tmp, dst)
    print(f"Patched compiler written to {dst}  (sha1 {result})")
    return True


def _opt(flag):
    if flag in sys.argv[2:]:
        i = sys.argv.index(flag)
        if i + 1 < len(sys.argv):
            return sys.argv[i + 1]
        sys.exit(f"{flag} needs a value")
    return None


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: patch_compiler_rw.py <compilers dir | GC/2.0p1b, 2.0p1c, 2.0p1d, 2.0p1e, "
                 "2.0p1f or 2.0p1g mwcceppc.exe> [--r3 | --p1d | --p1d-parts r4,at-sched,at-w,at-v"
                 " --out DIR | --p1e | --p1e-parts rep,nps,dss,volb,e3n4 --out DIR | --p1f | --p1g]")
    arg = Path(sys.argv[1])
    # Invoked from ninja with $out, i.e. <compilers>/GC/2.0p1b/mwcceppc.exe
    # (or .../GC/2.0p1c, 2.0p1d, 2.0p1e, 2.0p1f or 2.0p1g)
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    exe_dir = arg.parent.name if arg.name.endswith(".exe") else None
    parts_arg = _opt("--p1d-parts")
    p1e_arg = _opt("--p1e-parts")
    if "--p1g" in sys.argv[2:] or exe_dir == P1G_VERSION.split("/")[1]:
        ok = patch_compiler_p1g(root)
    elif "--p1f" in sys.argv[2:] or exe_dir == P1F_VERSION.split("/")[1]:
        ok = patch_compiler_p1f(root)
    elif p1e_arg is not None or "--p1e" in sys.argv[2:] or exe_dir == P1E_VERSION.split("/")[1]:
        parts = tuple(p for p in p1e_arg.split(",") if p) if p1e_arg is not None else P1E_DEFAULT
        out = _opt("--out")
        ok = patch_compiler_p1e(root, parts, Path(out) if out else None)
    elif parts_arg is not None or "--p1d" in sys.argv[2:] or exe_dir == P1D_VERSION.split("/")[1]:
        parts = tuple(p for p in parts_arg.split(",") if p) if parts_arg is not None else P1D_PARTS
        out = _opt("--out")
        ok = patch_compiler_p1d(root, parts, Path(out) if out else None)
    elif "--r3" in sys.argv[2:] or exe_dir == R3_VERSION.split("/")[1]:
        ok = patch_compiler_r3(root)
    else:
        ok = patch_compiler_rw(root)
    if not ok:
        sys.exit(f"{root / BASE_VERSION} not found")
