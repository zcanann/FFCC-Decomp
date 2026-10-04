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

The programs are part of the PAL (`GCCP01`) build: `python configure.py --version GCCP01`
then `ninja` splits, reassembles, links and verifies both images. Their units appear
in `objdiff.json` and the progress report under the "GBA Client" and "GBA Minigame"
categories.

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
- The images are extracted from `orig/GCCP01/FFCC_PAL.iso` into `orig/GCCP01/gba/`;
  pre-extracted images there are used as-is.

## Sources

- `src/<program>/<unit>.c`: C code, compiled with `cc1 -mthumb-interwork -O2`.
- `src/<program>/<unit>.cpp`: C++ code (the minigame's game code), compiled with
  `cc1plus -mthumb-interwork -O2 -fno-exceptions`.
  Add the unit to `COMPLETE` in `tools/gba_project.py` once every function matches,
  so it links into the checked image.
- `lib/libgcc/`: agbcc's libgcc, built like agbcc does. Units named `libgcc/<object>`
  in `splits.txt` build from it and always link.
- `include/`: shared headers.

The client game files are separate units under `gba/cli/main/`, so a fully
matched file can link independently of the remaining holdouts. For example:

```sh
python gba/tools/check.py gba/src/cli/main/main.c AgbMain
```

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

- `config/<program>/symbols.txt`: symbol names, addresses, sizes; `thumb` marks Thumb functions.
  C++ functions carry their g++ 2.9 mangled names (`Init__6Camera`, `Crc8__FUi`).
  After changing a C++ signature, `python gba/tools/syncnames.py <program> --defined --apply`
  renames the entries to what the compiled objects define.
- `config/<program>/splits.txt`: address ranges per unit. Units become objdiff units.
- `tools/split.py`: generates per-unit assembly and the linker script. Instructions are
  emitted with `.inst`, and calls and pointers become relocations against symbols,
  so target objects diff cleanly against compiled code.
- `../tools/gba_project.py`: build rules, included into `build.ninja` with `subninja`.
