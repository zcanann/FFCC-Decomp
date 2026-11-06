# Regional game compiler baseline

The Game library uses GC/2.5 for PAL and USA, and GC/2.0p1k for Japan.
GC/2.0p1k is derived during the build from the bundled GC/2.0p1 (see below).
SDK and middleware selections are independent. These are compatibility
baselines, not identification of the original retail compiler binaries.

## Provenance

The compiler bundle's `build/compilers/info.txt` describes GC/2.0p1 as a
patched compiler for BFBB's small-data and floating-point scheduling issues.
It reports the same version as GC/2.0: 2.4.7, build 92. Do not describe
GC/2.0p1 as a separately established retail compiler release.

The bundled `mwcceppc.exe` files are both 2,064,896 bytes. Their SHA-256 hashes:

| Bundle directory | SHA-256 |
| --- | --- |
| GC/2.0 | `b79ee3e358fe18d7b492c3400169efc1a9bc5dff1a120dcb025f7869ab772022` |
| GC/2.0p1 | `afb7fecaab5c3dff9541c41476d07bb2b79f90f90ed0f577fd9b0a1ededb0e11` |

They differ at three file offsets: `0xDFD4E` (01 to 00), `0x16FD86`
(D8 to 05), and `0x16FD8C` (02 to 07). The project uses the distributed
tool binary; it does not patch the compiler during builds.

## Evidence and limits

The initial audit compiled unchanged source with identical command-line flags,
changing only the compiler and output path. GC/2.0p1 improved all fourteen
residual floating-point creation-menu functions in Japan; those same functions
became worse in PAL and USA. Unpatched GC/2.0, GC/1.3.2, GC/2.6 and GC/2.7
did not produce that Japanese improvement. Six additional Japanese menu units
had 25 improving functions, five unchanged, and one declining; the USA control
had 26 declining and five unchanged. Character-fur, caravan-status and
ring-menu code independently supported the Japanese result.

The complete regional build then exposed source issues hidden by the Western
compiler's constant reuse. Chained collision-vector and mesh-bound assignments
recover the retail single load and store order. Reusing the default depth offset
in octree drawing recovers the retail comparison and call argument. These
ordinary source repairs preserve Western output without optimizer pragmas or
per-unit game compiler exceptions.

Against staging `3201a6755`, the regional baseline and those repairs add
45,824 exactly matched Japanese code bytes, 2,072 data bytes and 91 functions.
No unit loses exact code, data or function totals. The shop-menu fuzzy score
declines slightly, from 80.75341 to 80.74551; its partially reconstructed drawing
remains work in progress. PAL and USA scores are unchanged. All configured
source builds and all nine final DOL/GBA checksums pass. Retail fallback links
alone were not used to validate the changed source.

This establishes a useful regional compatibility choice. It does not establish
the provenance of the original compiler or explain every remaining mismatch.
Continue investigating types, layout, source expressions and linkage before
attributing residual differences to the compiler.

## Japanese game compiler: GC/2.0p1g

Japanese game units build with GC/2.0p1g, the compiler the BFBB decomp derived
to model the retail CodeWarrior that built BFBB (released October 2003, two
months after FFCC Japan). `tools/patch_compiler.py` derives GC/2.0p1a and
`tools/patch_compiler_rw.py` derives GC/2.0p1b through GC/2.0p1g, both imported
from BFBB. They run as ninja pre-compile steps from the bundled stock GC/2.0p1
(SHA-1 `74bc177b10d1bbe8a60a21a6c0aa86d2dd9c0668`) and check the SHA-1 of every
input and output. The derived GC/2.0p1g is
`99bd18455ff674337d7a6186164df8a1b1ba13a7`, byte-identical to BFBB's.

The patches narrow stock 2.0p1's alias analysis: a `.sdata2` literal is not
hoisted above stores, a store to a small static kills a cached literal, whole
static reads are not loop-invariant, and several behaviours present in GC/2.5
(const-pointer LICM, the large-loop veto, const-pointee aliasing) are grafted
back. BFBB's `docs/COMPILER_VARIANTS.md` documents each clause and its class.

Rebuilding all Japanese source with each derived compiler, otherwise unchanged:

| compiler | exact code % | exact functions | vs stock 2.0p1 |
| --- | --- | --- | --- |
| GC/2.0p1 | 59.00 | 5135 | |
| GC/2.0p1a | 63.55 | 5221 | +109 / -23 |
| GC/2.0p1d | 64.92 | 5250 | +116 / -1 |
| GC/2.0p1g | 65.14 | 5252 | +117 / -0 |

Each BFBB step moves FFCC Japan in the same direction it moved BFBB; the
GC/2.5-derived clauses in 2.0p1d recover every function 2.0p1a lost. As a
control, building PAL with GC/2.0p1g instead of GC/2.5 loses 505 exact
functions, so these behaviours are specific to the 2003 Japanese build.
Japanese source previously tuned against stock GC/2.0p1 should be re-audited.

The RedSound library, which is byte-identical in all three regions, also builds
with GC/2.0p1g. Against stock GC/2.0p1 it is +1 / -0 exact functions over all
eight RedSound units: `GetRandomData` schedules its `t_RandomData` load before
the `m_RandomIndex` increment only when the table is declared without a bound and
defined after the function, and stock GC/2.0p1 never orders the two accesses.
GC/2.0p1a alone loses six RedCommand, RedMemory and RedMidiCtrl functions that
2.0p1g recovers.

## GC/2.0p1h: two further corrections from FFCC Japan

`tools/patch_compiler_ffcc.py` derives GC/2.0p1h from GC/2.0p1g
(`99bd18455ff674337d7a6186164df8a1b1ba13a7` to
`6114c0c66bc9b4ded51a1a278402a753ab12792c`) with 13 byte edits, each checked
against the expected old bytes. The x86 source of the added predicates is kept
in the script. No stock compiler (1.3.2, 2.0, 2.0p1, 2.5, 2.7, 3.0a) produces
the retail shapes below, so both are emulation corrections in BFBB's sense, not
grafts; the deciding alias queries were identified with BFBB's in-process
may-alias probe.

- `e3ns` corrects BFBB's clause E3n. A store with a subrange alias into a frame
  object whose address escapes is ordered before a later whole literal-pool
  load of at most 8 bytes, including struct-copy stores (pcode flag 0x40) and
  locals of inlined functions or compiler temporaries, which E3n's predicate
  rejected. Typical case: an inlined `CMapPcs::CheckHitCylinderNear` filling a
  local `CMapCylinder` before storing the radius literal.
- `dsl` orders a direct-operand store to a named static before a later
  register access to an `@`-named static: the `__sinit_*` vtable store before
  the pointer-to-member constant loads.

Measured over all Japanese game units against GC/2.0p1g: e3ns +13 / -0 exact
functions, dsl +2 / -0 plus 12 exact exception-table sections, together
+15 / -0 (38 functions improve, 2 partials dip slightly: `__sinit_p_map_cpp`
and `CGPartyObj::gpmCol`). On a frozen BFBB checkout (built on 2.0p1e, where
the parts were first developed) e3ns is 0 / -1 on game code, the one loss being
`xBoxFromCircle`, BFBB's documented E3n counter-witness, and 0 / 0 on
RenderWare; dsl is 0 / 0 on both. PAL and USA (GC/2.5) are unaffected.

## GC/2.0p1i: three more corrections (ksa, pwcp, c3a)

`tools/patch_compiler_ffcc2.py` derives GC/2.0p1i from GC/2.0p1h
(`6114c0c66bc9b4ded51a1a278402a753ab12792c` to
`58c5e3ccd07f5ce533695ecedd1a2a7f1eca1d13`) with 8 byte edits, each checked
against its expected old bytes; the research source is kept in the script. None
of these behaviours exists in a stock compiler (1.3.2 to 3.0a5.2), so all are
emulation corrections, each located with BFBB's in-process may-alias probe:

- `ksa`: Alias.c's per-access pass no longer downgrades an access to worst_case
  because another reaching definition of its base register has no alias; the
  access keeps its own alias (three bytes at 0x5124D7, 0x5124E2, 0x5124EE).
  Example: `target = cond ? &gPppDefaultValueBuffer[0] : workArea + off`
  followed by byte stores through `target`, where retail loads the int-to-float
  constant once and hoists the target loads.
- `pwcp`: prologue worst_case stores (stw/stwu/stmw) may alias a later load of
  a stack-passed parameter, so those loads stay below the register saves
  (functions with more than eight arguments).
- `c3a`: a subrange store to a named static orders a later whole `@` literal
  load of at most 8 bytes, whatever its flags (may_alias entry 3).

Measured against GC/2.0p1h on the current tree: Japan +23 / -0 exact functions,
no partial score lower in any region, one more Japanese unit linked; PAL and USA
unaffected. On a frozen BFBB checkout the three parts together are +4 / -0
(game +3, RenderWare +1) with no partial losses. The accompanying source fix
declares `gPppDefaultValueBuffer[0x40]` with its real size; the incomplete
array type had made 2.0p1a's clause S treat its halves as aliasing.

## GC/2.0p1j: dsl limited to small-data stores (dsls)

`tools/patch_compiler_ffcc3.py` derives GC/2.0p1j from GC/2.0p1i
(`58c5e3ccd07f5ce533695ecedd1a2a7f1eca1d13` to
`c900a720e9981e7e470b0a0c5558b81ac6f1bb43`) with two edits: a 52-byte wrapper
in free `.sbpatch` space and the redirected call to it.

`dsl` recovers the retail `__sinit_*` order for the small-data Pcs singletons
(`SystemPcs`, `McPcs` and `GbaPcs` are in `.sbss`, stored through `@sda21`),
but it also fired for the large `.bss` object `MapPcs`, whose vtables are stored
through a base register. Retail `__sinit_p_map_cpp` does not order those stores
before the PTMF constant loads, and stock GC/2.0p1, GC/2.0p1g and GC/2.5 all
produce the retail shape; only the `dsl` step broke it (97.73 to 85.34 in
isolation).

- `dsls`: `dsl` answers may-alias only when the stored static's type size
  (Object `+0xE`, Type `+0x2`) is at most 8 bytes, the `-sdata` threshold.

Rebuilding every Japanese unit against GC/2.0p1i: one function changes,
`__sinit_p_map_cpp` 89.08 to 100.00 (+976 exact bytes, +1 exact function); no
other function or section moves, and `p_system`, `p_mc` and `p_gba` keep their
`dsl` scores. Checking only the store's object size distinguishes the cases
without a BFBB probe; the type-size offset was confirmed by that measurement
(offsets 4 and 8 lose the `dsl` gains). PAL and USA are unaffected.

## GC/2.0p1k: dsl accepts update-form loads (dslu)

`tools/patch_compiler_ffcc4.py` derives GC/2.0p1k from GC/2.0p1j
(`c900a720e9981e7e470b0a0c5558b81ac6f1bb43` to
`abeb8e6e85568dd4e904e26ae3ca55b5b2cc5bcd`) with two edits: a 30-byte stub in
free `.sbpatch` space and a jump to it replacing one test in `f_dsl`.

This corrects the implementation of `dsl` to its documented behaviour (a later
access *through a register* to an `@`-named static). `f_dsl` rejected every
load whose offset operand is symbolic (operand kind 3), treating it as a direct
operand. That is right for an `@sda21` load, whose base operand is `r0`. After
register allocation, however, the peephole pass merges `addi rB,rB,@N@l` and
`lwz rX,0(rB)` into `lwzu rX,@N@l(rB)`. That load goes through the base
register `rB`, but its offset operand is symbolic. The post-allocation
scheduler therefore had no edge from the singleton's vtable store (`stw`,
`@sda21`) to it, and hoisted the PTMF constant load above the store.

- `dslu`: the load test also accepts a symbolic offset operand when the base
  operand is a register other than `r0`. This covers `@l(rB)` and update-form
  loads. Direct `r0`-based operands (the `@sda21` form) are still rejected.

Rebuilding every Japanese game unit (268) against GC/2.0p1j, the objects that
change are `p_game`, `p_system`, `p_mc` and `p_gba`. Every other object is
byte-identical, including data and exception tables. In each of the four, the
`__sinit_*` function becomes exact: `__sinit_p_game_cpp` 99.48,
`__sinit_p_system_cpp` 86.21, `__sinit_p_mc_cpp` 86.21 and `__sinit_p_gba_cpp`
76.47 to 100. That is +4 / -0 exact functions and +744 exact code bytes, with no
partial losses. Each was its unit's only Japanese mismatch, so all four units
now link in Japan. BFBB builds only up to GC/2.0p1g and never uses the FFCC
steps; `dsl` itself was 0 / 0 on BFBB when it was introduced. PAL and USA are
unaffected.

### Not adopted: a write-after-read mirror of e3ns

A further candidate predicate orders a whole load of a small named static
(alias kind 0, size 1 to 8 bytes, not `@`-named) before a later subrange store
into a frame object whose address escapes. It is the write-after-read mirror of
`e3ns`. On top of GC/2.0p1j it is +2 / -0 over every Japanese unit
(`pppConstructYmMoveCircle` 92.29 and `pppParHitSphMat` 96.15 to 100), with no
partial losses. It is not adopted, for these reasons:

- No neighbouring compiler produces the retail shape. Neither function reaches
  100 with GC/1.2.5, 1.3, 1.3.2, 2.0, 2.0p1, 2.5, 2.6, 2.7, 3.0a3 to 3.0a5.2 or
  any derived step from 2.0p1a to 2.0p1k. The best is stock 2.0p1 at 93.01 for
  `pppConstructYmMoveCircle`; `pppParHitSphMat` never exceeds 96.15. Without
  that signal, the project decompiles towards likely source instead of adding a
  clause.
- The predicate is fitted to these cases rather than derived from a documented
  BFBB behaviour. Its size limit was added only because the unlimited form
  broke `pppFrameYmMoveCircle`. It covers named statics, and only for a read
  before a write. `e3ns` covers only `@` literals for a read after a write, so
  together they do not form one consistent alias rule. A related widening of
  `e3ns` to whole-object frame stores loses `makeFurTex`.
- `pppFrameYmCheckBGHeight` would also need a source reorder that holds only
  under this predicate (it scores 90 without it). That would tune source to the
  candidate compiler.
