#!/usr/bin/env python3
"""Run the GCC 2.9 preprocessor with the thumb-elf driver's definitions."""

import argparse
import subprocess
from pathlib import Path


# gcc/gcc.c, gcc/cp/lang-specs.h and gcc/config/arm/{thumb,telf}.h at
# pret/agbcc 476b5c86e5bc21311dfb14d0f043fbf5b870781d, for
# -O2 -mthumb-interwork (-fno-exceptions for C++). Assembler inputs use
# no optimization flags. All three sets were verified against xgcc -E -dM.
# Invoke cpp directly because the original driver isn't portable to all hosts.
TARGET_DEFINES = (
    "__CHAR_UNSIGNED__", "thumb", "thumbelf", "__thumb",
    "__thumb__", "__thumbelf", "__thumbelf__", "__ARMEL__", "__THUMBEL__",
)
C_DEFINES = (*TARGET_DEFINES, "__GNUC__=2", "__GNUC_MINOR__=9", "__OPTIMIZE__")
CXX_DEFINES = (*C_DEFINES, "__GNUG__=2", "__cplusplus")
ASM_DEFINES = (*TARGET_DEFINES, "__ASSEMBLER__")
LANGUAGES = {
    "c": ("c", C_DEFINES),
    "c++": ("c++", CXX_DEFINES),
    "assembler-with-cpp": ("asm", ASM_DEFINES),
}


def preprocess(cpp: Path, source: Path, output: Path, includes: list,
               depfile: Path = None, language: str = "c++", defines: tuple = ()) -> None:
    # The historical preprocessor recognizes '/' as a directory separator on
    # every host; backslashes break its quoted-header search on Windows.
    mode, predefined = LANGUAGES[language]
    command = [cpp.as_posix(), f"-lang-{mode}", "-undef", "-nostdinc"]
    if mode == "asm":
        command.append("-$")
    command += [f"-D{definition}" for definition in (*predefined, *defines)]
    for directory in includes:
        command += ["-I", Path(directory).as_posix()]
    if depfile is not None:
        command += ["-MMD", depfile.as_posix()]
    command += [source.as_posix(), "-o", output.as_posix()]
    subprocess.run(command, check=True)
    if depfile is not None:
        # GCC 2.9 predates -MT/-MF and always names the target <source>.o.
        # Keep its header dependencies, replacing only the target for Ninja.
        dependencies = depfile.read_text().partition(" :")[2]
        if not dependencies:
            raise ValueError(f"Unrecognized GCC 2.9 dependency file: {depfile}")
        target = output.as_posix().replace("$", "$$").replace(" ", "\\ ")
        depfile.write_text(target + ":" + dependencies)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cpp", type=Path, required=True)
    parser.add_argument("--language", choices=LANGUAGES, default="c")
    parser.add_argument("-I", dest="includes", action="append", default=[])
    parser.add_argument("-D", dest="defines", action="append", default=[])
    parser.add_argument("--depfile", type=Path)
    parser.add_argument("source", type=Path)
    parser.add_argument("-o", "--output", type=Path, required=True)
    args = parser.parse_args()
    preprocess(args.cpp, args.source, args.output, args.includes, args.depfile,
               args.language, args.defines)


if __name__ == "__main__":
    main()
