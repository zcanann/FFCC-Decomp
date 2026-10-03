#!/usr/bin/env python3
"""Replay the configured GBA links with another assembler and linker.

Run ninja first. Generated assembly is reused for source objects, including preprocessed
assembly. Other inputs use the existing retail assembly, converted to syntax
accepted by older GAS. This audits assembly and linking, not compiler matching
or compatibility with every handwritten assembly source.
"""

import argparse
import ast
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
OBJECT = re.compile(r"(build/[^\s()]+\.o)\(([^)]+)\)")


def legacy_syntax(source):
    if re.search(r"(?m)^[ \t]*\.inst\.w\b", source):
        raise ValueError("Thumb-2 .inst.w needs an explicit halfword conversion")
    source = re.sub(r"(?m)^[ \t]*\.syntax unified[ \t]*$", "", source)
    source = re.sub(r"(?m)^([ \t]*)\.inst\.n\b", r"\1.hword", source)
    return re.sub(r"(?m)^([ \t]*)\.inst\b", r"\1.word", source)


def run(command, log):
    result = subprocess.run(list(map(str, command)), cwd=ROOT,
                            capture_output=True, text=True)
    log.write_text(result.stdout + result.stderr, encoding="utf-8")
    if result.returncode:
        raise RuntimeError(f"Command failed; see {log}")
    return result.stdout


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--assembler", type=Path, required=True)
    parser.add_argument("--linker", type=Path, required=True)
    parser.add_argument("--objcopy", type=Path, required=True)
    parser.add_argument("--version", default="GCCP01", choices=["GCCP01"])
    parser.add_argument("--program", nargs="+", choices=["cli", "mgr"],
                        default=["cli", "mgr"])
    parser.add_argument("--work-dir", type=Path, required=True,
                        help="new output directory within the repository")
    args = parser.parse_args()
    work = args.work_dir.resolve()
    relative_work = work.relative_to(ROOT)
    if work.exists() and any(work.iterdir()):
        parser.error("work directory must be empty; previous audits are preserved")
    work.mkdir(parents=True, exist_ok=True)
    assembler, linker, objcopy = (p.resolve() for p in
                                  (args.assembler, args.linker, args.objcopy))

    # Read the build's literal program table without importing configure's dependencies.
    tree = ast.parse((ROOT / "tools/gba_project.py").read_text(encoding="utf-8"))
    programs = next(ast.literal_eval(n.value)[args.version] for n in tree.body
                    if isinstance(n, ast.AnnAssign) and isinstance(n.target, ast.Name)
                    and n.target.id == "PROGRAMS")
    result = {"tools": {}, "programs": {}}
    for name, path in (("assembler", assembler), ("linker", linker), ("objcopy", objcopy)):
        result["tools"][name] = {"path": str(path),
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "version": run([path, "--version"], work / (name + ".log")).splitlines()[0]}

    for program in args.program:
        build = Path("build") / args.version / "gba" / program
        output = relative_work / program
        (ROOT / output).mkdir()
        script = (ROOT / build / "ldscript.ld").read_text(encoding="utf-8")
        objects = {}
        jobs = []
        for original in dict.fromkeys(m[0] for m in OBJECT.findall(script)):
            path = Path(original)
            kind, *parts = path.relative_to(build).parts
            unit = Path(*parts).with_suffix("")
            destination = output / "objects" / unit.with_suffix(".o")
            (ROOT / destination).parent.mkdir(parents=True, exist_ok=True)
            generated_asm = path.with_suffix(".s")
            if kind == "src" and (ROOT / generated_asm).is_file():
                source = generated_asm
                inputs = [source, Path("gba/lib/align.s")]
                origin = "generated"
            else:
                source = output / "assembly" / unit.with_suffix(".s")
                (ROOT / source).parent.mkdir(parents=True, exist_ok=True)
                target = ROOT / build / "asm" / unit.with_suffix(".s")
                (ROOT / source).write_text(legacy_syntax(target.read_text(encoding="utf-8")),
                                          encoding="utf-8")
                inputs = [source]
                origin = "retail"
            log = ROOT / destination.with_suffix(".log")
            jobs.append(([assembler, "-mthumb-interwork", "-o", destination, *inputs], log))
            objects[original] = {"object": destination.as_posix(), "origin": origin,
                                 "assembly": source.as_posix()}
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(lambda job: run(*job), jobs))

        def select(match):
            entry = objects[match[1]]
            section = match[2]
            if entry["origin"] == "retail" and section == "COMMON":
                section = ".common"
            return f'{entry["object"]}({section})'

        private_script = output / "link.ld"
        (ROOT / private_script).write_text(OBJECT.sub(select, script), encoding="utf-8")
        elf = output / (program + ".elf")
        run([linker, "-T", private_script, "-o", elf], ROOT / output / "link.log")
        image = output / (program + ".bin")
        run([objcopy, "-O", "binary", "-j", ".text*", "-j", ".rodata*", "-j", ".data*",
             elf, image], ROOT / output / "objcopy.log")
        info = programs["gba_" + program]
        data = (ROOT / image).read_bytes()
        digest = hashlib.sha1(data).hexdigest()
        baseline = ROOT / build / Path(info["disc_path"]).name
        identical = data == baseline.read_bytes()
        result["programs"][program] = {"sha1": digest, "retail_sha1": info["sha1"],
            "matches_current_image": identical, "objects": objects}
        (work / "report.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
        if digest != info["sha1"] or not identical:
            raise RuntimeError(f"{program}: image differs; inspect {work / 'report.json'}")
        counts = {origin: sum(x["origin"] == origin for x in objects.values())
                  for origin in ("generated", "retail")}
        print(f"{program}: retail SHA-1 {digest}; inputs {counts}", flush=True)


if __name__ == "__main__":
    main()
