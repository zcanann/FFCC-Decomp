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
agbcc (`-O2 -mthumb-interwork`). There are no symbols; `fn_`/`lbl_` names are
placeholders until real names are recovered.

## Building

The programs are part of the PAL (`GCCP01`) build: `python configure.py --version GCCP01`
then `ninja` splits, reassembles, links and verifies both images. Their units appear
in `objdiff.json` and the progress report under the "GBA Client" and "GBA Minigame"
categories.

Requirements:
- Python package `capstone` (`pip install capstone`). Without it, configure prints a
  warning and leaves the GBA programs out.
- arm-none-eabi binutils and cpp: downloaded into `build/tools/gba-binutils` unless
  `--gba-binutils <dir>` is given.
- `agbcc` and `old_agbcc` from [pret/agbcc](https://github.com/pret/agbcc), in
  `build/tools/gba-agbcc/` or `--gba-compilers <dir>`. Without them, sources are not
  compiled and the GBA units stay unmatched.
- `cc1plus` and `gcc2-cpp`, the C++ compiler and preprocessor from the pinned
  2.9-arm tree, built by `gba/tools/build_cc1plus.sh`, next to agbcc. Both are
  required to compile C++ sources. See [the toolchain notes](toolchain.md).
- The images are extracted from `orig/GCCP01/FFCC_PAL.iso` into `orig/GCCP01/gba/`;
  pre-extracted images there are used as-is.

## Sources

- `src/<program>/<unit>.c`: C code, compiled with `agbcc -mthumb-interwork -O2`.
- `src/<program>/<unit>.cpp`: C++ code (the minigame's game code), compiled with
  `cc1plus -mthumb-interwork -O2 -fno-exceptions`.
  Add the unit to `COMPLETE` in `tools/gba_project.py` once every function matches,
  so it links into the checked image.
- `lib/libgcc/`: agbcc's libgcc, built like agbcc does. Units named `libgcc/<object>`
  in `splits.txt` build from it and always link.
- `include/`: shared headers.

## Layout

- `config/<program>/symbols.txt`: symbol names, addresses, sizes; `thumb` marks Thumb functions.
- `config/<program>/splits.txt`: address ranges per unit. Units become objdiff units.
- `tools/split.py`: generates per-unit assembly and the linker script. Instructions are
  emitted with `.inst`, and calls and pointers become relocations against symbols,
  so target objects diff cleanly against compiled code.
- `../tools/gba_project.py`: build rules, included into `build.ninja` with `subninja`.
