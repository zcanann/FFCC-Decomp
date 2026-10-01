#!/usr/bin/env python3
"""Compile one GBA C file and report per-function matches against its target unit.

    python gba/tools/check.py gba/src/mgr/main/sound.c            # all functions in the file
    python gba/tools/check.py gba/src/mgr/main/sound.c fn_0200022C  # instruction diff for one

Works without ninja (safe to run in parallel): the file is compiled into a private
temporary directory with the same cpp/agbcc/as pipeline as the build, and diffed
against the unit's target object in build/GCCP01/gba (run `ninja` once first).
"""

import argparse
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXE = ".exe" if sys.platform == "win32" else ""
TOOLS = ROOT / "build" / "tools"
CPPFLAGS = ["-undef", "-nostdinc", "-Wno-trigraphs", "-I", str(ROOT / "gba" / "include"),
            "-I", str(ROOT / "gba" / "lib" / "m4a" / "include"), "-I", str(ROOT / "gba" / "lib" / "ginclude")]
CFLAGS = ["-mthumb-interwork", "-O2", "-fhex-asm"]


def binutil(name):
    return str(TOOLS / "gba-binutils" / "bin" / f"arm-none-eabi-{name}{EXE}")


def compile_c(source: Path, out_dir: Path) -> Path:
    pre = out_dir / "a.i"
    asm = out_dir / "a.s"
    obj = out_dir / "a.o"
    steps = [
        [binutil("cpp"), *CPPFLAGS, "-iquote", str(source.parent), str(source), "-o", str(pre)],
        [str(TOOLS / "gba-agbcc" / f"agbcc{EXE}"), *CFLAGS, str(pre), "-o", str(asm)],
        [binutil("as"), "-mcpu=arm7tdmi", "-mthumb-interwork", "-o", str(obj), str(asm), str(ROOT / "gba" / "lib" / "align.s")],
    ]
    for step in steps:
        result = subprocess.run(step, capture_output=True, text=True)
        if result.returncode:
            sys.stdout.write(result.stdout + result.stderr)
            sys.exit(1)
    return obj


def defined_functions(obj: Path):
    out = subprocess.run([binutil("nm"), "--defined-only", str(obj)], capture_output=True, text=True).stdout
    names = [line.split()[2] for line in out.splitlines() if len(line.split()) == 3 and line.split()[1] in "Tt"]
    return [n for n in names if not n.startswith(".") and not n.startswith("gcc2_compiled")]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("function", nargs="?")
    args = parser.parse_args()

    source = args.source.resolve()
    parts = source.relative_to(ROOT / "gba" / "src").parts
    program = parts[0]
    unit = parts[1] if len(parts) > 2 else Path(parts[1]).stem
    target = ROOT / "build" / "GCCP01" / "gba" / program / "obj" / f"{unit}.o"
    if not target.exists():
        sys.exit(f"{target} missing; run ninja first")

    with tempfile.TemporaryDirectory() as tmp:
        obj = compile_c(source, Path(tmp))
        # Units with several code ranges use per-range section names (.text.<addr>);
        # objdiff pairs code by section name, so rename them to match the compiled object.
        sections = subprocess.run([binutil("objdump"), "-h", str(target)], capture_output=True, text=True).stdout
        renames = []
        for name in re.findall(r"^\s*\d+\s+(\.text\.[0-9A-F]+)\s", sections, re.M):
            renames += ["--rename-section", f"{name}=.text"]
        if renames:
            merged = Path(tmp) / "target.o"
            subprocess.run([binutil("objcopy"), *renames, str(target), str(merged)], check=True)
            target = merged
        names = [args.function] if args.function else defined_functions(obj)
        objdiff = str(TOOLS / f"objdiff-cli{EXE}")
        total = 0.0
        # One objdiff run covers every function in the file.
        command = [objdiff, "diff", "-1", str(target), "-2", str(obj), "-o", "-"]
        if args.function:
            command.append(args.function)
        result = subprocess.run(command, capture_output=True, text=True)
        try:
            data = json.loads(result.stdout)
        except json.JSONDecodeError:
            sys.exit(f"objdiff failed: {result.stderr.strip()[:300]}")
        for name in names:
            left = [s for s in data["left"]["symbols"] if s.get("name") == name]
            right = [s for s in data["right"]["symbols"] if s.get("name") == name]
            if not left:
                print(f"{name}: not in target {unit}")
                continue
            percent = left[0].get("match_percent")
            if percent is None:
                # objdiff omits the score in two-object mode; derive it from the instruction diff.
                li = left[0].get("instructions", [])
                ri = right[0].get("instructions", []) if right else []
                same = sum(1 for a, b in zip(li, ri) if not a.get("diff_kind") and not b.get("diff_kind"))
                percent = 100.0 * same / max(len(li), len(ri), 1) if ri else 0.0
            total += percent
            print(f"{name}: {percent:.2f}%")
            if args.function and right and percent < 100:
                for a, b in zip(left[0].get("instructions", []), right[0].get("instructions", [])):
                    kind = a.get("diff_kind") or b.get("diff_kind") or ""
                    la = a.get("instruction", {}).get("formatted", "")
                    lb = b.get("instruction", {}).get("formatted", "")
                    mark = " " if not kind else "|" if "ARG" in kind else ">" if "INSERT" in kind else "<" if "DELETE" in kind else "!"
                    print(f"  {la:<42} {mark} {lb}")
        if len(names) > 1:
            print(f"-- {len(names)} functions, average {total / max(len(names), 1):.2f}%")


if __name__ == "__main__":
    main()
