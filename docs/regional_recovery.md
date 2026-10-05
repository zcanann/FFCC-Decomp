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
independent named base anchor. Supported RELA types are ADDR32 (1), ADDR16_LO/HI/HA (4/5/6), REL24 (10), and
EMB_SDA21 (109). Both word and old MWCC immediate-halfword SDA21 offsets work.
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
