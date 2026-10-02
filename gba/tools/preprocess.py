#!/usr/bin/env python3
"""Run the GCC 2.9 C++ preprocessor with the thumb-elf driver's definitions."""

import argparse
import subprocess
from pathlib import Path


# gcc/cp/lang-specs.h and gcc/config/arm/{thumb,telf}.h at
# pret/agbcc 476b5c86e5bc21311dfb14d0f043fbf5b870781d, for
# g++ -O2 -mthumb-interwork -fno-exceptions. Verified against xgcc -E -dM.
# Invoke cpp directly because the original driver isn't portable to all hosts.
CXX_DEFINES = (
    "__GNUC__=2", "__GNUC_MINOR__=9", "__GNUG__=2", "__cplusplus",
    "__OPTIMIZE__", "__CHAR_UNSIGNED__", "thumb", "thumbelf", "__thumb",
    "__thumb__", "__thumbelf", "__thumbelf__", "__ARMEL__", "__THUMBEL__",
)


def preprocess(cpp: Path, source: Path, output: Path, includes: list,
               depfile: Path = None) -> None:
    # The historical preprocessor recognizes '/' as a directory separator on
    # every host; backslashes break its quoted-header search on Windows.
    command = [cpp.as_posix(), "-lang-c++", "-undef", "-nostdinc"]
    command += [f"-D{definition}" for definition in CXX_DEFINES]
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
    parser.add_argument("-I", dest="includes", action="append", default=[])
    parser.add_argument("--depfile", type=Path)
    parser.add_argument("source", type=Path)
    parser.add_argument("-o", "--output", type=Path, required=True)
    args = parser.parse_args()
    preprocess(args.cpp, args.source, args.output, args.includes, args.depfile)


if __name__ == "__main__":
    main()
