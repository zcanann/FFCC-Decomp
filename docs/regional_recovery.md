# Regional compiled-object solver

`tools/recover_regional_splits.py` searches retail GameCube images using compiled
shared source. It produces batch placement hypotheses, full initialized-byte
proofs, symbol constraints and reviewable config snippets. It does **not** edit
configs or mark units Matching. Objdiff and the final regional links remain the
progress and completion checks.

## Compile the baseline and solve

Prepare the normal toolchain and retail inputs as described in the README.
Compile PAL source and produce its target objects, then build the selected
region's retail-matching ELF. The ELF supplies SDA bases only after the solver
checks every initialized DOL byte, including its zero alignment padding.

```sh
python configure.py --version GCCP01
ninja all_source progress build/GCCP01/report.json
python configure.py --version GCCE01
ninja all_source progress build/GCCE01/report.json
python tools/recover_regional_splits.py \
  --dol orig/GCCE01/sys/main.dol \
  --symbols config/GCCE01/symbols.txt \
  --linked-elf build/GCCE01/main.elf \
  --map orig/GCCP01/game.MAP --map orig/GCCE01/game.MAP \
  --source-dir build/GCCP01/src --source-root src \
  --pal-target-dir build/GCCP01/obj \
  --include 'ax/*' --include 'dvd/*' --include 'gx/*' \
  --output build/GCCE01/regional-candidates.json
```

Use the same compiled baseline with the Japanese DOL, symbols and linked ELF to
solve Japan independently. PAL/USA MAPs supply historical ownership evidence;
their old addresses are never used as regional addresses. Where source has
intentional regional conditionals, also run against that region's compiled
objects. A failure with PAL code does not imply a compiler-version discrepancy.

For a small dependency cluster, repeat `--object`, for example
`--object gx/GXFifo.c=build/GCCP01/src/gx/GXFifo.o`. `--include` filters source
paths when using `--source-dir`; retain the full source-directory root so that
unit paths and optional PAL target paths resolve consistently. Omit
`--pal-target-dir` to test complete compiled objects only. No compiler overrides
or source rewriting occur in this tool.

## What the solver establishes

The solver tries complete code and, when available, the PAL target's retained
function set in original source order. Functions must completely partition the
source code section before that projection is allowed. The retained set is a
proposal: each regional placement is searched and replayed independently.
References originating in omitted functions are removed; retained references
into omitted functions are rejected. An entire PAL-absent private data section
can be proposed for omission only when no retained relocation references it.
Exported data and partial data-section trimming are not silently discarded.

Searches preserve every opcode bit outside supported relocation fields. They
report ambiguity, including overlapping matches, rather than taking the first
hit. A truncated candidate search cannot establish uniqueness without an
independent named base anchor. Supported RELA types are ADDR32 (1),
ADDR16_LO/HI/HA (4/5/6), REL24 (10), REL14 (11), and EMB_SDA21 (109).
REL14 conditional branches retain their condition, prediction and link bits;
absolute branches, invalid opcodes, unaligned targets and displacements outside
the signed 16-bit range are rejected. Both word and old MWCC immediate-halfword
SDA21 offsets work.
SDA register selection uses section/register evidence; overlapping r2/r13
windows cannot be distinguished by distance alone.

Branch destinations, address words, paired HA/LO references and SDA accesses
constrain section bases and external addresses. Incompatible constraints reject
a hypothesis. Independently replayed defining sections can resolve another
object's inferred external identities in subsequent batch passes. Only complete
review-ready rows contribute these anchors: circular unresolved identities
cannot certify each other, and new conflicts retract dependent inferred anchors.
Uncorroborated
external names remain explicit hypotheses. Local definitions are resolved in
their own object, and duplicate local config names never anchor externs.

Each initialized section marked `byte_verified` has been fully relocated and
compared byte for byte, not merely compared with relocation fields masked.
`map_supported_bss` means its inferred range lies inside retail BSS and its
source objects have independent matching MAP owner, name, scope and size
evidence, covering the whole section except explicitly evidenced alignment gaps.
It does not mean zero bytes proved BSS ownership. Missing MAP evidence,
unlocated sections, inferred external identities, existing symbol overlap and
detected source optimizer pragmas remain review issues.

Named initialized objects are also compared with available MAP size, section and
scope evidence. A matching extra zero can still be a fabricated array element:
for example, the original interrupt-priority table has 11 entries and the TEV
channel table has nine. Such contradictions remain review issues even when all
initialized bytes replay. Function-static numeric suffixes are normalized for
this diagnostic because MWCC's counters differ between builds; MAP addresses
remain unused. This check does not replace a source audit or infer ownership
from absent MAP entries.

`review_ready` means this solver found no outstanding checks in its supported
model. It is **not** a source audit or matching claim. Inspect source plausibility,
compiler-generated tables, actual linker dead stripping and section alignment;
the runbook's prohibitions still apply. `split_snippet` and `symbol_snippet` can
include individually verified portions of an incomplete hypothesis, so inspect
the enclosing status and all review issues before using them. Preserve actual
object extents and distinguish linker padding from owned storage.

## Validation and current limits

### Broad fuzzy placement of game translation units

`tools/locate_regional_tus.py` ranks regional compiled code against a selected
retail DOL before exact section ownership is available. Start with the largest
game objects, then add independent function rankings to expose internal drift:

```sh
python tools/locate_regional_tus.py \
  --dol orig/GCCE01/sys/main.dol --source-dir build/GCCE01/src \
  --symbols config/GCCE01/symbols.txt --top 30 --functions \
  --output build/GCCE01/fuzzy-game.json
```

Use the corresponding `GCCJGC` paths for Japan. The default `*.o` glob selects
objects directly inside the source directory; `--include '**/*.o'` also includes
SDK subdirectories. `--top 0` selects every matching object. Compile the selected
region first; the output records each object hash and the retail DOL hash.

The locator indexes eight-instruction windows over executable DOL sections.
Distinctive windows vote on a common section base, then every candidate with a
full in-bounds window receives whole-window normalized, opcode and raw-word
scores. Register shapes remain significant; branch displacements, D-form
immediates and SDA base registers are masked. This deliberately masks some
ordinary constants too: **a normalized match is not an exact code match**.
Very common anchors are excluded rather than truncated into false uniqueness.
Candidate display limits do not limit scoring or runner-up calculation.

Results include anchor distribution across sixteen relative bins, runner-up
margin, and existing global named-function agreement or conflicts. A single
surviving base means unique among the sampled distinctive-anchor candidates,
not exhaustive proof against all possible fuzzy placements. Low whole-window
scores or narrowly clustered anchors often indicate changed function lengths,
dead stripping or reordered code. They do not establish TU boundaries.

`--functions` ranks functions separately, reports provisional compiled-size
envelopes, source-order neighbor agreement and per-function base shifts. Its
`strong_ranking` filter requires at least 80% normalized score, two distinctive
anchors spanning eight bins, no known-name conflicts, and a ten-percentage-point
runner-up margin when a runner-up exists. These are review heuristics, not
probabilities or verified identity. REL24 call destinations provide additional
checks where independent function rankings or existing named externs resolve
the target and the call site's neighboring instruction shapes still agree.
Call disagreement remains visible; it does not silently alter a ranking.

An initial thirty-object batch covered 881,436 compiled code bytes in each of
USA and Japan in about nine seconds per region. Adding function rankings took
about fifteen seconds: 1,329 functions were examined, with 766 USA and 591 Japan
strong rankings covering 521,744 and 335,812 compiled bytes respectively. These
measure discovery coverage, **not objdiff or linkage progress**; source and
retail revisions affect both coverage and timing.
Including callgraph checks took about seventeen seconds and found 2,179 USA
and 1,309 Japan resolved call destinations in agreement with the ranked or
previously named targets.

COMMON and mixed data are allowed because only executable sections are being
ranked. No data/BSS ownership, function end, symbol name, split or `Matching`
claim follows automatically. Review MAP ownership and regional retail
boundaries, then validate proposed claims with DTK/objdiff and the exact solver
where applicable. Source-generated tables and linker padding still need their
own evidence. Run focused tests with
`python -m unittest tools.tests.test_locate_regional_tus`.

Add `--pal-target-dir build/GCCP01/obj` to propose whole-unit boundaries from
PAL retail function order. This implies `--functions`. Independently ranked
source function names vote on a common offset into the regional configuration's
function-boundary list. The output preserves competing votes, actual regional
function sizes, existing-name conflicts and gaps. When PAL has exception-index
records, the locator searches the entire retail DOL for the complete proposed
function-pointer/length sequence and checks that its EH pointers address
initialized storage. This corroborates boundary extents and table structure;
it does not establish function identities or prove that PAL's order survives.

PAL order and function count remain hypotheses. The report flags every function
identity without an independent code ranking or existing named anchor, as well
as unsupported first/last functions, fuzzy call
disagreements, and overlaps between different unit proposals. A complete EH
subsequence alone does not establish names, even if every function has an EH
record. Review each unanchored identity through actual code, calls or other
retail references. Missing PAL objects or unsupported exception references remain
explicit errors for that hint. These diagnostics must be reviewed before any
config changes; an empty issue list is not a matching or source-linkage claim.

The initial hundred-object batch covered 1,388,876 compiled code bytes and
2,280 functions per region in about sixteen seconds. Boundary sequence and EH
checks took about twenty-three seconds and produced 99 USA and 90 Japan unit
hypotheses. Their competing envelopes and unsupported edges illustrate why
discovery coverage must remain separate from verified regional ownership.

After reviewing and applying a coherent subset, compile all three regions with
`ninja all_source progress build/<version>/report.json`, inspect affected objdiff
units and require all nine DOL/GBA checksums. Promote only regions whose complete
unit ownership and source link are verified. A source compilation followed by a
retail fallback link is insufficient to establish a new matching claim.

The first solver supports ordinary allocated PROGBITS/NOBITS sections and RELA
relocations. COMMON, unsupported relocations, partially discarded data pools,
function reordering and differing function bodies remain unresolved. PAL hints
cannot discover arbitrary new regional retain sets. Unknown HI-only address
references lack enough information to infer a full address. The smaller
`recover_code_splits.py` remains useful for conservative known-relocation,
complete code-only proofs.

Run the focused regression suite with:

```sh
python -m unittest tools.tests.test_recover_regional_splits
```
