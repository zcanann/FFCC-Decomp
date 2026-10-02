# GBA compiler toolchain

The minigame is C++: its retail assertion strings name `.cpp` files, and its
static initialization code matches compiler-generated C++ constructors. Our
C and C++ frontends and preprocessor come from the complete GCC tree at
[pret/agbcc revision 476b5c86e5bc21311dfb14d0f043fbf5b870781d](https://github.com/pret/agbcc/tree/476b5c86e5bc21311dfb14d0f043fbf5b870781d).
This tree identifies itself as `2.9-arm-000512`, but contains later changes,
including ARM files dated 2002. The version string alone does not establish
the exact retail compiler release.

## Rebuilding the game compilers and preprocessor

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

Copy `cc1`, `cc1plus` and `gcc2-cpp` (the `.exe` versions on Windows) beside
`old_agbcc`, in `build/tools/gba-agbcc` or the directory passed to
`configure.py --gba-compilers`. The single-file checker accepts the same
`--gba-compilers` option. The script also produces a Linux reference driver and
its C, C++ and assembler predefines for toolchain comparisons. `cc1-reference`
is retained as an alias of the Linux C compiler for older audit workflows.

CI builds these tools from source when the compiler-build script changes or the
cached executables are missing. It downloads Zig 0.13.0 with a pinned SHA-256,
uses the same build script, and checks that all required tools are executable
before configuring the project. `old_agbcc` still comes from the private build
container. This prevents missing tools from silently excluding GBA source from
the progress report.

Both hosts use 32-bit binaries because this old tree assumes 32-bit host types.
The only compiler source change makes `.align` request explicit zero fill,
matching the retail padding and pret's assembler pipeline. It does not alter
register allocation or optimization. Windows host configuration changes disable
unavailable operating-system functions.

## Preprocessing

All preprocessing uses the original preprocessor, in the appropriate C, C++ or
assembler mode. `tools/preprocess.py` supplies the definitions emitted by the
original `thumb-elf` driver for `-O2 -mthumb-interwork` with `-fno-exceptions` in
C++, and without optimization flags for assembler inputs. These were checked
using its `-E -dM` output; the wrapper also translates the historical dependency-file target into
the target Ninja expects. Quoted includes resolve relative to the source file.

The previous pipeline used a modern preprocessor in C mode and supplied only
`__cplusplus` and `__GNUG__`. It omitted the GCC version, target, unsigned-char,
and optimization macros and inherited newer preprocessing behavior. Replacing
it with the original preprocessor produced byte-identical objects for all 15
current minigame C++ files. This establishes compatibility with those sources;
it does not make the two preprocessors interchangeable for future source.

The same comparison covers all 36 current game C objects, 48 library C objects
and 12 preprocessed assembler objects. They are byte-identical with the native
preprocessor and driver definitions. Libraries keep their explicit SDK/configure
defines; GCC version and target defines now come from the compiler environment
instead of `-D__GNUC__` (which had incorrectly given it the value 1).

## C compiler comparison

All 36 game C objects also match byte for byte when compiled with the original
`cc1` instead of pret's modern `agbcc` port, using the same optimization and
interworking flags. The build now uses that original C frontend alongside
`cc1plus`, with the same pinned source and host build.

Libraries retain `old_agbcc`: compiling their current preprocessed inputs with
the original newer `cc1` changes the machine code in 14 of 48 objects, including
both m4a builds, newlib routines and `dp-bit`. Some sizes change too: m4a grows
from 5308 to 5324 bytes and newlib `makebuf` shrinks from 220 to 208. The existing
older-compiler objects link to the exact retail images. This supports a separate
older library compiler; identical version strings do not justify replacing it.
The original SDK revision and the provenance of these older backend differences
remain open questions.

## What the matching link establishes

The generated linker script concatenates input object sections in reconstructed
order. It fixes output section origins, rather than pinning every function to
its retail address. A byte-identical linked image therefore checks code, data,
relocations, section sizes, alignment and ordering together. GBA unit names and
boundaries are reconstructed; there is no shipped GBA MAP identifying the
original build orchestrator. Exact matches do not establish whether the original
project used Make, an IDE, or another build system.
