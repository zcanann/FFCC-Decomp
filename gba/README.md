# GBA programs

The GameCube game boots these multiboot images onto connected Game Boy Advances:

| Program | Disc file | Loaded by |
|---|---|---|
| `cli` | `dvd/gba/ffcc_cli.bin` | `src/joybus.cpp` |
| `mgr` | `dvd/minigame/mgr/mgr00.bin` | `src/p_minigame.cpp` |

`mgr00.bin` is the base minigame image. The other `mgrNN`/`mgrspNN` files on the
disc are the same program with different data (tens digit: language, units digit:
variant; `sp` is a per-player variant).

The images load at `0x02000000` (EWRAM) and are mostly Thumb code, built with
the GCC 2.9 ARM/Thumb family (`-O2 -mthumb-interwork`). There are no symbols; `fn_`/`lbl_` names are
placeholders until real names are recovered.

## Building

Both programs are built for PAL (`GCCP01`), USA (`GCCE01`) and Japan (`GCCJGC`).
Select a region and build all source plus its checked images:

```sh
python configure.py --version GCCP01
ninja all_source progress build/GCCP01/report.json
```

Substitute `GCCE01` or `GCCJGC` in both commands for another region. Outputs live
under `build/<version>/gba/<program>/`; `objdiff.json` and the regional report
include the "GBA Client" and "GBA Minigame" categories. Each image has its own
retail hash. PAL has the most mature source linkage; regional layouts and
completion claims are independent, and unproven units use retail fallbacks.

Regional comparisons require mapped target objects with verified ownership.
Compiling an unmapped source validates the build without establishing a match
or source linkage. USA and Japan still have incomplete data and asset ownership;
asset units without proven regional extents retain their own retail fallbacks.

Requirements:
- Python package `capstone` (`pip install capstone`). Without it, configure prints a
  warning and leaves the GBA programs out.
- arm-none-eabi binutils: downloaded into `build/tools/gba-binutils` unless
  `--gba-binutils <dir>` is given.
- `cc1`, `cc1plus` and `gcc2-cpp`, the C/C++ compilers and preprocessor from the
  pinned 2.9-arm tree, built by `gba/tools/build_cc1plus.sh`, plus `old_agbcc`
  from [pret/agbcc](https://github.com/pret/agbcc) for libraries. Place them in
  `build/tools/gba-agbcc/` or `--gba-compilers <dir>`. Without the required tools,
  sources are not compiled. See [the toolchain notes](toolchain.md).
- Supply `ffcc_cli.bin` and `mgr00.bin` in `orig/<version>/gba/`, or let the build
  extract them from the region's uncompressed ISO/GCM:

  | Version | Disc path |
  |---|---|
  | `GCCP01` | `orig/GCCP01/FFCC_PAL.iso` |
  | `GCCE01` | `orig/GCCE01/FFCC_USA.gcm` |
  | `GCCJGC` | `orig/GCCJGC/FFCC_JP.iso` |

  Existing extracted images are read as-is. They must match the selected
  region's hashes; substituting PAL images into another region is not valid.

## Sources

- `src/<program>/<unit>.c`: C code, compiled with `cc1 -mthumb-interwork -O2`.
- `src/<program>/<unit>.cpp`: C++ code (the minigame's game code), compiled with
  `cc1plus -mthumb-interwork -O2 -fno-exceptions`.
  Source paths remain shared across regions. Add a unit to the selected region's
  `VERSION_COMPLETE` entry in `tools/gba_project.py` only after its full code,
  data and final linked placement are verified. The existing `COMPLETE` lists
  supply the PAL entry; they do not automatically promote USA or Japan.
- `lib/libgcc/`: agbcc's libgcc, built like agbcc does. Units named `libgcc/<object>`
  in `splits.txt` build from it. Library linkage is selected for the region too;
  sharing library source is not proof that every regional object matches.
- `include/`: shared headers.

The client game files are separate units under `gba/cli/main/`, so a fully
matched file can link independently of the remaining holdouts. The single-file
checker defaults to PAL; select another built region with `--version`:

```sh
python gba/tools/check.py gba/src/cli/main/main.c AgbMain
python gba/tools/check.py --version GCCE01 gba/src/cli/main/main.c AgbMain
```

The checker uses the selected region's target objects and `VERSION_<version>`
preprocessor definition. Its config must already map the requested source unit;
a missing regional unit cannot be checked against a PAL substitute. It does not
change source-link completion claims.

Their section boundaries follow the compiled objects' sizes and alignments,
checked against the recovered symbol addresses and retail image. These are
reconstructed units; no original GBA MAP is available. Gaps between objects are
linker padding and are excluded from the per-unit data totals. Unclaimed common
storage remains in the separate `bss` unit. Its disconnected ranges stay separate
in objdiff so combining them cannot add artificial alignment bytes to progress.
Recovered common storage uses a `.common` range under its owning source unit. The final linker selects that
object's `COMMON` symbols directly. For objdiff only, a relocatable link allocates
them in a `.common` section; the final image still uses the original object so
common definitions can coalesce across units. An optional `align:` on a split
records a known input-section alignment.

The client's fixed download workspace occupies `0x02038000–0x02040000`, as
bounded by `Xfer_Receive`. It remains an anonymous reservation; the gap between
the loaded image and that workspace is not counted as a source object.

## Layout

- PAL retains `config/<program>/`; USA and Japan use
  `config/<version>/<program>/`. Each contains its own `symbols.txt` and
  `splits.txt`; region paths select configuration, never a separate source tree.
- `symbols.txt`: symbol names, addresses, sizes; `thumb` marks Thumb functions.
  C++ functions carry their g++ 2.9 mangled names (`Init__6Camera`, `Crc8__FUi`).
  The PAL name-sync helper is `python gba/tools/syncnames.py <program> --defined --apply`.
  For regional work, diff the configured region in objdiff and verify that any
  symbol update applies to its own layout.
- `splits.txt`: address ranges per unit. Units become objdiff units.
- `tools/split.py`: generates per-unit assembly and the linker script. Instructions are
  emitted with `.inst`, and calls and pointers become relocations against symbols,
  so target objects diff cleanly against compiled code.
- `../tools/gba_project.py`: build rules, included into `build.ninja` with `subninja`.

## Recovering regional splits

After configuring and building the selected region, audit a whole program's
compiled objects against its retail image:

```sh
python gba/tools/recover_splits.py \
    --image orig/GCCE01/gba/ffcc_cli.bin --config gba/config/GCCE01/cli \
    --project objdiff.json --program cli \
    --output build/GCCE01/gba/cli/recovered-splits.json
```

The image may also be supplied from an extracted disc directory. The tool
requires `pyelftools` and `capstone`. For a focused audit, use repeated
`--object UNIT=PATH` arguments instead of project discovery.

The JSON contains section placements, symbol proposals, consolidated split
edits, input hashes, and reasons for rejecting candidates. A proposed initialized
section must reproduce every retail byte, including its supported relocations.
Ambiguous placements, unsupported relocations, and conflicting ownership block
proposals. Compiler mapping symbols identify literal pools that were mistaken
for functions. BSS and COMMON sizes remain unverified storage extents.

This is a dry run: it changes neither configuration nor completion claims.
Review the proposed edits, rebuild, and check objdiff plus the full regional
image hashes before promoting any units in `VERSION_COMPLETE`.
