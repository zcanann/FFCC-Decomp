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
`--gba-compilers` option and selects regional objects and preprocessing with
`--version GCCP01`, `--version GCCE01` or `--version GCCJGC` (PAL by default).
The script also produces a Linux reference driver and
its C, C++ and assembler predefines for toolchain comparisons. `cc1-reference`
is retained as an alias of the Linux C compiler for older audit workflows.

CI prepares these tools once in a `gba-compilers` job and shares them with the
PAL, USA and Japan build jobs through a short-lived artifact. Its tools-only
cache is keyed by `gba/tools/build_cc1plus.sh`; changing that recipe or missing
executables triggers a source build, not every game-source commit. The build
uses Zig 0.13.0 with a pinned download SHA-256 and the same script described
above. `old_agbcc` comes from the private build container. Each regional job
restores executable permissions after downloading the artifact and checks all
four required tools before configuring. Retail inputs and split objects are
not cached or uploaded with the compiler artifact. See
[CI documentation](../docs/github_actions.md).

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

## Assembler and linker comparison

An audit with unmodified [GNU binutils 2.10 source](https://ftp.gnu.org/gnu/binutils/binutils-2.10.tar.gz)
reproduces both retail image hashes using the current compiler assembly and
retail assembly fallbacks. The audit uses a 32-bit Linux host build; it does not
identify the original retail binutils release. The production tools remain the
current binutils package.

To repeat the image comparison after building the project, supply native tools
and a new output directory:

```sh
python3 gba/tools/audit_binutils.py --assembler /path/to/as --linker /path/to/ld \
  --objcopy /path/to/objcopy --work-dir build/gba-binutils-audit
```

The checker preserves generated source assembly, including preprocessed assembly.
For other objects it uses the generated retail assembly, expressing raw instructions as
`.hword` or `.word` instead of the newer `.inst` directive. Its JSON report records
which inputs took each path, tool hashes, and image hashes. This checks assembly
and linking; it does not replace objdiff or certify every handwritten assembly
file against an older assembler. Historical Thumb function symbols also use a
different ELF representation, so directly linking modern objects with the old
linker is not a valid substitute for reassembling them.

COMMON placement requires particular care. Binutils 2.10 and the current linker
produce the same allocation order for a sixteen-global probe, regardless of
declaration order. The old BFD symbol hash predicts that order. Renaming globals
or changing their ownership can affect placement; changing declaration order
alone is not a general solution.

Default COMMON alignment does differ: the 2.10 assembler aligns a twelve-byte
object to eight bytes, while the current assembler aligns it to sixteen. The
2.12 source retains the older rounding behavior. Existing recovered COMMON
objects have the same alignment under both assemblers. Verify this distinction
against retail placement when recovering small non-power-of-two objects, rather
than compensating with artificial source padding or per-object alignment hacks.

## What the matching link establishes

Toolchain inputs and source files are shared across the three regions; layouts,
retail hashes and source-completion claims are not. PAL keeps `gba/config/cli`
and `gba/config/mgr`; USA and Japan use `gba/config/<version>/<program>`.
Validate each selected region's source build and both final image hashes before
promoting its units. Across the full matrix this accompanies three GameCube DOL
checks, for nine final retail image checks in total. A fallback-based exact
image does not establish that every compiled source object matches.

The generated linker script concatenates input object sections in reconstructed
order. Loaded read-only and writable ranges retain separate output sections;
repeated ranges, such as minigame graphics after writable data, use numbered
section suffixes. Binary export includes all of these ranges. The linker fixes
output section origins, rather than pinning every function to its retail address.
A byte-identical linked image therefore checks code, data,
relocations, section sizes, alignment and ordering together. GBA unit names and
boundaries are reconstructed; there is no shipped GBA MAP identifying the
original build orchestrator. Exact matches do not establish whether the original
project used Make, an IDE, or another build system.

The minigame's sound work area is part of the downloaded image. Its seven typed
objects in `sound_data.c` have explicit zero initializers, which this compiler
emits in declaration order in `.data`. Newlib's four-byte `errno` follows at
`0x020158A0`, allocated from the original
`libc/reent/sbrkr.o` common definition. Its objdiff view materializes that storage
with `ld -r -d`; this comparison object is never used in the final link.
The following 256 bytes remain unclaimed.
These reconstructed unit boundaries do not establish the original source files.
The SDK still supplies tentative common definitions for four sound globals;
binutils warns that their default 16-byte common alignment exceeds the source
object's 4-byte alignment. All four final addresses are 16-byte aligned and match
the retail references; the checked image also verifies their placement.
