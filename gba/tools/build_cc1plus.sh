#!/usr/bin/env bash
# Build the original C/C++ compilers and preprocessor for the GBA game units.
#
# pret/agbcc identifies itself as 2.9-arm-000512 (Cygnus GCC 2.9x). Its first
# commits (476b5c8, "get it to compile") still contain that tree's C++ front end
# (gcc/cp), which pret removed in the next commit. This script builds that original
# tree as configured for thumb-elf, with one change pret also made: alignment
# padding is explicit zeros (".align N, 0"). This tree's cc1 (out/cc1-reference)
# provides a reference for comparing pret's later backend changes. The version
# label alone does not identify a release: the tree contains later SDK changes.
#
# Requirements: git, make, bison, m4, python3, zig (0.13.0; ZIG=/path/to/zig), and a pret/agbcc
# clone (AGBCC_REPO, default: clones https://github.com/pret/agbcc).
# Hosts are 32-bit like the original (the 2.9x tree assumes 32-bit host types):
#   out/cc1[.exe]   C compiler (both hosts)
#   out/cc1plus      static i386 Linux (musl)
#   out/cc1plus.exe  i386 Windows
#   out/gcc2-cpp[.exe]  original preprocessor (both hosts)
#   out/thumb-elf-gcc-reference  original driver (Linux, for auditing specs)
#
#   gba/tools/build_cc1plus.sh <workdir> [<outdir>]
set -euo pipefail

WORK=$(realpath -m "${1:?usage: build_cc1plus.sh <workdir> [<outdir>]}")
OUT=$(realpath -m "${2:-$WORK/out}")
ZIG=${ZIG:-zig}
REVISION=476b5c86e5bc21311dfb14d0f043fbf5b870781d
JOBS=${JOBS:-8}

[ "$("$ZIG" version)" = 0.13.0 ] || { echo "Zig 0.13.0 is required" >&2; exit 1; }
command -v bison >/dev/null
command -v m4 >/dev/null
# Keep previous compiler builds intact. Use a fresh work directory for a rebuild.
for dir in src build build-win libiberty libiberty-build; do
    [ ! -e "$WORK/$dir" ] || { echo "$WORK/$dir exists; choose a fresh work directory" >&2; exit 1; }
done
mkdir -p "$WORK" "$OUT"
if [ -z "${AGBCC_REPO:-}" ]; then
    AGBCC_REPO=$WORK/agbcc.git
    [ -d "$AGBCC_REPO" ] || git clone --bare https://github.com/pret/agbcc "$AGBCC_REPO"
fi

# Compiler wrappers: 32-bit hosts, old C dialect. For "-c file.c" without -o, zig
# would name a Windows object file.obj where gcc's Makefiles expect file.o.
cat > "$WORK/cc-linux" <<EOF
#!/bin/sh
exec "$ZIG" cc -target x86-linux-musl -std=gnu89 -fcommon -w -fno-sanitize=undefined "\$@"
EOF
cat > "$WORK/cc-windows" <<EOF
#!/usr/bin/env bash
args=("\$@"); compile=0; out=0; src=
for a in "\$@"; do
    case "\$a" in -c) compile=1 ;; -o) out=1 ;; *.c) src=\$a ;; esac
done
if [ \$compile = 1 ] && [ \$out = 0 ] && [ -n "\$src" ]; then args+=(-o "\$(basename "\$src" .c).o"); fi
exec "$ZIG" cc -target x86-windows-gnu -std=gnu89 -fcommon -w -fno-sanitize=undefined "\${args[@]}"
EOF
chmod +x "$WORK/cc-linux" "$WORK/cc-windows"

SRC=$WORK/src
mkdir -p "$SRC"
git -C "$AGBCC_REPO" archive "$REVISION" | tar -x -C "$SRC"
# The archived tree omits the top-level copy expected by libiberty/config.table.
cp "$SRC/gcc/move-if-change" "$SRC/move-if-change"

# Like pret/agbcc: padding is zeros, not NOPs, so code sections match the retail image.
python3 - "$SRC/gcc/config/arm/thumb.h" <<'EOF'
import sys
p = sys.argv[1]
s = open(p, encoding="latin-1").read()
old = r'fprintf (STREAM, "\t.align\t%d\n", (LOG));'
assert s.count(old) == 1
open(p, "w", encoding="latin-1").write(s.replace(old, r'fprintf (STREAM, "\t.align\t%d, 0\n", (LOG));'))
EOF

# Linux host. The parsers are pre-generated in the tree (no bison needed).
mkdir -p "$WORK/build" && cd "$WORK/build"
CC="$WORK/cc-linux" "$SRC/gcc/configure" --host=i686-pc-linux-gnu --build=i686-pc-linux-gnu \
    --target=thumb-elf --enable-languages=c,c++ --disable-nls > configure.log
make c-parse.y > /dev/null
cp "$SRC/gcc/c-parse.c" "$SRC/gcc/c-parse.h" .
cp "$SRC/gcc/cp/parse.c" "$SRC/gcc/cp/parse.h" cp/
sleep 1
touch c-parse.c c-parse.h cp/parse.c cp/parse.h "$SRC/gcc/cp/hash.h" "$SRC/gcc/c-gperf.h"
mkdir -p "$WORK/libiberty-build" && (cd "$WORK/libiberty-build" &&
    CC="$WORK/cc-linux" "$SRC/libiberty/configure" --host=i686-pc-linux-gnu > configure.log &&
    make CC="$WORK/cc-linux" CFLAGS=-O2 > make.log && mkdir -p "$WORK/libiberty" &&
    cp libiberty.a "$WORK/libiberty/")
make -j"$JOBS" cc1 cc1plus cpp xgcc CC="$WORK/cc-linux" HOST_CC="$WORK/cc-linux" CFLAGS=-O2 > make.log 2>&1 ||
    { tail -20 make.log; exit 1; }
cp cc1plus "$OUT/cc1plus"
cp cc1 "$OUT/cc1"
cp cc1 "$OUT/cc1-reference"
cp cpp "$OUT/gcc2-cpp"
cp xgcc "$OUT/thumb-elf-gcc-reference"
./xgcc -B./ -E -dM -x c++ -O2 -mthumb-interwork -fno-exceptions -nostdinc /dev/null \
    | sort > "$OUT/cxx-predefines.txt"
./xgcc -B./ -E -dM -x c -O2 -mthumb-interwork -nostdinc /dev/null \
    | sort > "$OUT/c-predefines.txt"
./xgcc -B./ -E -dM -x assembler-with-cpp -mthumb-interwork -nostdinc /dev/null \
    | sort > "$OUT/asm-predefines.txt"

# Windows host: reuse the generated sources and generator programs.
cp -a "$WORK/build" "$WORK/build-win" && cd "$WORK/build-win"
rm -f ./*.o cp/*.o cc1 cc1plus
python3 - auto-host.h <<'EOF'
import sys
missing = {"SYS_WAIT_H", "BCMP", "BCOPY", "BZERO", "FPUTC_UNLOCKED", "GETRLIMIT", "SETRLIMIT", "INDEX",
           "RINDEX", "KILL", "STRSIGNAL", "SYSCONF", "SYS_FILE_H", "GETTIMEOFDAY", "SYS_RESOURCE_H",
           "SYS_TIMES_H", "GETRUSAGE", "TIMES", "SYS_PARAM_H", "PUTC_UNLOCKED", "FPUTS_UNLOCKED", "POPEN"}
p = sys.argv[1]
out = []
for line in open(p).read().splitlines():
    f = line.split()
    out.append(f"/* {f[1]}: not on Windows */" if len(f) == 3 and f[0] == "#define"
               and f[1].startswith("HAVE_") and f[1][5:] in missing else line)
open(p, "w").write("\n".join(out) + "\n")
EOF
KEEP=""
for f in gen* s-*; do
    case $f in *.c|*.o) ;; *) [ -f "$f" ] && KEEP="$KEEP -o $f" ;; esac
done
make -j"$JOBS" $KEEP $(sed 's#\.\./##g' stamp-objlist) c-common.o c-pragma.o hash.o obstack.o \
    CC="$WORK/cc-windows" HOST_CC="$WORK/cc-linux" CFLAGS=-O2 > make.log 2>&1 || { tail -20 make.log; exit 1; }
make $KEEP cc1 cc1plus cpp CC="$WORK/cc-windows" HOST_CC="$WORK/cc-linux" CFLAGS=-O2 >> make.log 2>&1 ||
    { tail -20 make.log; exit 1; }
cp cc1plus "$OUT/cc1plus.exe"
cp cc1 "$OUT/cc1.exe"
cp cpp "$OUT/gcc2-cpp.exe"
cp "$SRC/gcc/COPYING" "$OUT/COPYING"
python3 - "$OUT" "$REVISION" <<'EOF'
import hashlib
import json
import pathlib
import sys

out = pathlib.Path(sys.argv[1])
names = ("cc1", "cc1.exe", "cc1-reference", "cc1plus", "cc1plus.exe", "gcc2-cpp", "gcc2-cpp.exe",
         "thumb-elf-gcc-reference")
manifest = {
    "source": "https://github.com/pret/agbcc",
    "revision": sys.argv[2],
    "host_compiler": "Zig 0.13.0",
    "patches": ["ASM_OUTPUT_ALIGN emits explicit zero fill"],
    "sha256": {name: hashlib.sha256((out / name).read_bytes()).hexdigest() for name in names},
}
(out / "cxx-toolchain.json").write_text(json.dumps(manifest, indent=2) + "\n")
EOF
ls -la "$OUT"
