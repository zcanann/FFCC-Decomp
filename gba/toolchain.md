# GBA compiler toolchain

The minigame is C++: its retail assertion strings name `.cpp` files, and its
static initialization code matches compiler-generated C++ constructors. Our
C++ frontend and preprocessor come from the complete GCC tree at
[pret/agbcc revision 476b5c86e5bc21311dfb14d0f043fbf5b870781d](https://github.com/pret/agbcc/tree/476b5c86e5bc21311dfb14d0f043fbf5b870781d).
This tree identifies itself as `2.9-arm-000512`, but contains later changes,
including ARM files dated 2002. The version string alone does not establish
the exact retail compiler release.

## Rebuilding C++ tools

Use Linux (including WSL), Git, Make, Bison, M4, Python 3 and Zig **0.13.0**:

```sh
ZIG=/path/to/zig bash gba/tools/build_cc1plus.sh /tmp/ffcc-cxx-build /path/to/output
```

Choose a fresh work directory; the script refuses to erase a previous build.
`AGBCC_REPO` can point to a local clone containing the pinned revision, including
an offline clone. Otherwise the script fetches upstream. The compiler source is
GPL-2.0-or-later; its license is copied into the output directory. The script
records the source revision, host compiler, patch and binary hashes in
`cxx-toolchain.json`.

Copy `cc1plus` and `gcc2-cpp` (the `.exe` versions on Windows) beside `agbcc`
and `old_agbcc`, in `build/tools/gba-agbcc` or the directory passed to
`configure.py --gba-compilers`. The single-file checker accepts the same
`--gba-compilers` option. The script also produces Linux reference C and driver
binaries, and the native driver's C++ predefines, for toolchain comparisons.

Both hosts use 32-bit binaries because this old tree assumes 32-bit host types.
The only compiler source change makes `.align` request explicit zero fill,
matching the retail padding and pret's assembler pipeline. It does not alter
register allocation or optimization. Windows host configuration changes disable
unavailable operating-system functions.

## Preprocessing

C++ uses the original preprocessor in `-lang-c++` mode. `tools/preprocess.py`
supplies the definitions emitted by the original `thumb-elf` driver for
`-O2 -mthumb-interwork -fno-exceptions`. These were checked using its `-E -dM`
output; the wrapper also translates the historical dependency-file target into
the target Ninja expects. Quoted includes resolve relative to the source file.

The previous pipeline used a modern preprocessor in C mode and supplied only
`__cplusplus` and `__GNUG__`. It omitted the GCC version, target, unsigned-char,
and optimization macros and inherited newer preprocessing behavior. Replacing
it with the original preprocessor produced byte-identical objects for all 15
current minigame C++ files. This establishes compatibility with those sources;
it does not make the two preprocessors interchangeable for future source.

C sources, libgcc, newlib and m4a retain their separate `agbcc`/`old_agbcc`
configuration and modern preprocessing for now. Their compiler and header
provenance need separate comparisons before changing that pipeline.

## What the matching link establishes

The generated linker script concatenates input object sections in reconstructed
order. It fixes output section origins, rather than pinning every function to
its retail address. A byte-identical linked image therefore checks code, data,
relocations, section sizes, alignment and ordering together. GBA unit names and
boundaries are reconstructed; there is no shipped GBA MAP identifying the
original build orchestrator. Exact matches do not establish whether the original
project used Make, an IDE, or another build system.
