"""Build rules for the GBA multiboot programs sent to linked Game Boy Advances.

Each program is split into per-unit assembly (gba/tools/split.py), reassembled,
linked, and checked against the retail image. The target objects are added to
objdiff.json so the programs count toward the version's progress report.

Units with source are compiled and diffed against their target objects:
- gba/src/<program>/<unit>.c, built with agbcc
- libgcc/<object>, built from gba/lib/libgcc like agbcc's own libgcc
- libagbsyscall/<routine>, libc/<dir>/<file>, m4a/<file>: libraries in gba/lib
Units listed in COMPLETE, and all libgcc, libagbsyscall and libc units, link
their compiled objects into the checked image.
"""

import importlib.util
import os
import re
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional

from . import ninja_syntax
from .project import ProgressCategory, ProjectConfig

GBA_DIR = Path("gba")
LIBGCC_DIR = GBA_DIR / "lib" / "libgcc"
M4A_DIR = GBA_DIR / "lib" / "m4a"
SYSCALL_DIR = GBA_DIR / "lib" / "libagbsyscall"
LIBC_DIR = GBA_DIR / "lib" / "libc"
# agbcc's libc (newlib) build: flags, and objects built from another source with defines.
LIBC_CPPFLAGS = ("-I gba/lib/ginclude -I gba/lib/libc/include -nostdinc -undef -DABORT_PROVIDED "
                 "-DHAVE_GETTIMEOFDAY -D__thumb__ -DARM_RDI_MONITOR -D__GNUC__ -DINTERNAL_NEWLIB "
                 "-D__USER_LABEL_PREFIX__=")
LIBC_VARIANTS = {
    "stdlib/mallocr": ("stdlib/mallocr.c", "-DDEFINE_MALLOC"),
    "stdlib/freer": ("stdlib/mallocr.c", "-DDEFINE_FREE"),
    "stdlib/reallocr": ("stdlib/mallocr.c", "-DDEFINE_REALLOC"),
    "stdlib/callocr": ("stdlib/mallocr.c", "-DDEFINE_CALLOC"),
    "stdlib/cfreer": ("stdlib/mallocr.c", "-DDEFINE_CFREE"),
    "stdlib/malignr": ("stdlib/mallocr.c", "-DDEFINE_MEMALIGN"),
    "stdlib/vallocr": ("stdlib/mallocr.c", "-DDEFINE_VALLOC"),
    "stdlib/pvallocr": ("stdlib/mallocr.c", "-DDEFINE_PVALLOC"),
    "stdlib/mallinfor": ("stdlib/mallocr.c", "-DDEFINE_MALLINFO"),
    "stdlib/mallstatsr": ("stdlib/mallocr.c", "-DDEFINE_MALLOC_STATS"),
    "stdlib/msizer": ("stdlib/mallocr.c", "-DDEFINE_MALLOC_USABLE_SIZE"),
    "stdlib/malloptr": ("stdlib/mallocr.c", "-DDEFINE_MALLOPT"),
    "stdio/vfiprintf": ("stdio/vfprintf.c", "-DINTEGER_ONLY"),
}

# Programs per game version: category id -> program info.
PROGRAMS: Dict[str, Dict[str, Dict[str, str]]] = {
    "GCCP01": {
        "gba_cli": {
            "config": "cli",
            "name": "GBA Client",
            "disc_path": "dvd/gba/ffcc_cli.bin",
            "sha1": "ec0579f21b9211f2fec4d17fe5943f23309c5f4c",
            "m4a_defines": "-DM4A_SOUND_FREQ=SOUND_MODE_FREQ_13379",
        },
        "gba_mgr": {
            "config": "mgr",
            "name": "GBA Minigame",
            "disc_path": "dvd/minigame/mgr/mgr00.bin",
            "sha1": "6ef574cc6ae34e8a05bccb1a28f78e833fde58fa",
            "m4a_defines": "-DM4A_SOUND_FREQ=SOUND_MODE_FREQ_15768",
        },
    },
}

DISC_IMAGES = {"GCCP01": "FFCC_PAL.iso"}
ASFLAGS = "-mcpu=arm7tdmi -mthumb-interwork"
CPPFLAGS = "-undef -nostdinc -Wno-trigraphs -I gba/include"
CFLAGS = "-mthumb-interwork -O2 -fhex-asm"

# Game units whose compiled source links into the checked image, per program.
COMPLETE: Dict[str, List[str]] = {
    "cli": ["crt0", "joy_reset", "m4a/m4a_1", "m4a/m4a"],
    "mgr": ["crt0", "joy_reset", "m4a/m4a_1", "m4a/m4a"],
}

# libgcc routines assembled from lib1thumb.asm; the rest are C.
LIBGCC_ASM = {"_udivsi3", "_divsi3", "_umodsi3", "_modsi3", "_dvmd_tls", "_call_via_rX"}


def _units(config_dir: Path) -> List[str]:
    text = (config_dir / "splits.txt").read_text(encoding="utf-8")
    return list(dict.fromkeys(re.findall(r"^(\S+):\s*$", text, re.M)))


def _arm_units(config_dir: Path) -> set:
    """Units containing ARM-state functions (symbols without the thumb flag)."""
    arm = []
    for m in re.finditer(r"^\S+ = \.text:0x([0-9A-Fa-f]+); // type:function (.*)$",
                         (config_dir / "symbols.txt").read_text(encoding="utf-8"), re.M):
        if "thumb" not in m.group(2).split():
            arm.append(int(m.group(1), 16))
    units = set()
    unit = None
    for line in (config_dir / "splits.txt").read_text(encoding="utf-8").splitlines():
        m = re.match(r"^(\S+):\s*$", line)
        if m:
            unit = m.group(1)
            continue
        m = re.match(r"^\s+\.text\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)", line)
        if m and any(int(m.group(1), 16) <= a < int(m.group(2), 16) for a in arm):
            units.add(unit)
    return units


def _path(path: Any) -> str:
    return str(path).replace(os.sep, "/")


def configure_gba(config: ProjectConfig, binutils_dir: Optional[Path], compilers_dir: Optional[Path]) -> None:
    programs = PROGRAMS.get(config.version)
    if not programs:
        return
    if importlib.util.find_spec("capstone") is None:
        print(
            "Warning: Python package 'capstone' not found; GBA programs are excluded "
            "from the build and progress report (pip install capstone)",
            file=sys.stderr,
        )
        return

    exe = ".exe" if sys.platform == "win32" else ""
    build = config.build_dir / config.version / "gba"
    orig = Path("orig") / config.version / "gba"
    tools = GBA_DIR / "tools"
    if binutils_dir is not None:
        prefix = binutils_dir / "arm-none-eabi-"
        binutils_stamp: List[str] = []
    else:
        prefix = config.build_dir / "tools" / "gba-binutils" / "bin" / "arm-none-eabi-"
        binutils_stamp = [_path(config.build_dir / "tools" / "gba-binutils" / ".version")]
    prefix_str = os.path.normpath(prefix)
    if compilers_dir is None:
        compilers_dir = config.build_dir / "tools" / "gba-agbcc"
    agbcc = compilers_dir / f"agbcc{exe}"
    old_agbcc = compilers_dir / f"old_agbcc{exe}"
    have_compilers = agbcc.is_file() and old_agbcc.is_file()
    if not have_compilers:
        print(
            f"Warning: agbcc/old_agbcc not found in {compilers_dir}; GBA sources are not "
            "compiled (build pret/agbcc and pass --gba-compilers)",
            file=sys.stderr,
        )

    ninja_path = build / "build.ninja"
    ninja_path.parent.mkdir(parents=True, exist_ok=True)
    with open(ninja_path, "w", encoding="utf-8") as f:
        n = ninja_syntax.Writer(f)
        n.comment("GBA multiboot programs (generated by tools/gba_project.py)")
        n.variable("gba_asflags", ASFLAGS)
        n.newline()
        n.rule("gba_binutils", f"$python {_path(tools / 'download_binutils.py')} $outdir",
               description="TOOL $out")
        n.rule("gba_extract", f"$python {_path(tools / 'extract.py')} $in $outdir $paths",
               description="EXTRACT $out")
        n.rule("gba_split",
               f"$python {_path(tools / 'split.py')} $bin $config --asm-dir $asmdir "
               "--ldscript $ldscript --object-dir $objdir $overrides",
               description="SPLIT $config")
        n.rule("gba_as", f"{prefix_str}as{exe} $gba_asflags $asincludes -o $out $in", description="AS $out")
        n.rule("gba_cpp", f"{prefix_str}cpp{exe} $cppflags -MMD -MT $out -MF $out.d $in -o $out",
               description="CPP $in", depfile="$out.d", deps="gcc")
        n.rule("gba_cc", "$cc $cflags $in -o $out", description="AGBCC $out")
        n.rule("gba_ld", f"{prefix_str}ld{exe} -T $ldscript -o $out --no-warn-rwx-segments -Map $map",
               description="LINK $out")
        n.rule("gba_ld_r", f"{prefix_str}ld{exe} -r -o $out $in", description="LINK $out")
        n.rule("gba_strip_attributes", f"{prefix_str}objcopy{exe} -R .ARM.attributes $in $out",
               description="OBJCOPY $out")
        n.rule("gba_objcopy", f"{prefix_str}objcopy{exe} -O binary -j .text -j .rodata $in $out",
               description="OBJCOPY $out")
        n.rule("gba_sha1", f"$python {_path(tools / 'check_sha1.py')} $in $sha1 $out",
               description="CHECK $in")
        n.newline()

        if binutils_stamp:
            n.build(binutils_stamp, "gba_binutils", implicit=_path(tools / "download_binutils.py"),
                    variables={"outdir": _path(Path(binutils_stamp[0]).parent)})

        bins = {cat: orig / Path(info["disc_path"]).name for cat, info in programs.items()}
        if not all(b.is_file() for b in bins.values()):
            n.build([_path(b) for b in bins.values()], "gba_extract",
                    _path(Path("orig") / config.version / DISC_IMAGES[config.version]),
                    implicit=_path(tools / "extract.py"),
                    variables={"outdir": _path(orig),
                               "paths": " ".join(info["disc_path"] for info in programs.values())})
        n.newline()

        def assemble_arm(source: Path, stem: str, base: str) -> str:
            """Assemble hand-written source that may contain ARM code."""
            # For ARM-state bx under ARMv4T, as emits R_ARM_V4BX relocations, which
            # objdiff cannot read. Assembling for v5t gives the same bytes without them;
            # the v5t attributes are then dropped since objdiff rejects that arch too.
            v5 = stem + ".v5.o"
            n.build(v5, "gba_as", _path(source), implicit=binutils_stamp,
                    variables={"asincludes": f"-I {_path(GBA_DIR / 'lib')} -I {_path(GBA_DIR / 'include')}",
                               "gba_asflags": "-march=armv5t -mthumb-interwork"})
            n.build(base, "gba_strip_attributes", v5, implicit=binutils_stamp)
            return base

        def compile_source(unit: str, src_dir: Path, out: Path, info: Dict[str, str]) -> Optional[str]:
            """Emit rules for a unit's source; returns the compiled object or None."""
            base = _path(out / "src" / f"{unit}.o")
            stem = _path(out / "src" / unit)
            # Like pret and agbcc's libgcc, compiler output ends with an explicit
            # zero-filled word alignment, so the section is padded with zeros.
            align = _path(GBA_DIR / "lib" / "align.s")
            if unit.startswith("libgcc/"):
                name = unit.split("/", 1)[1]
                if name in LIBGCC_ASM:
                    pre = stem + ".s"
                    n.build(pre, "gba_cpp", _path(LIBGCC_DIR / "lib1thumb.asm"), implicit=binutils_stamp,
                            variables={"cppflags": f"-undef -nostdinc -DL{name} -x assembler-with-cpp"})
                    n.build(base, "gba_as", [pre, align], implicit=binutils_stamp)
                    return base
                bit = name in ("fp-bit", "dp-bit")
                source = LIBGCC_DIR / (f"{name}.c" if bit else "libgcc2.c")
                defines = "" if bit else f" -DL{name}"
                pre = stem + ".i"
                asm = stem + ".s"
                n.build(pre, "gba_cpp", _path(source), implicit=binutils_stamp,
                        variables={"cppflags": f"-undef -nostdinc -I {_path(GBA_DIR / 'lib' / 'ginclude')}{defines}"})
                n.build(asm, "gba_cc", pre, variables={"cc": os.path.normpath(old_agbcc), "cflags": "-O2"})
                n.build(base, "gba_as", [asm, align], implicit=binutils_stamp)
                return base
            if unit.startswith("libagbsyscall/"):
                # One object per routine, like pret's granular libagbsyscall build.
                name = unit.split("/", 1)[1]
                n.build(base, "gba_as", _path(SYSCALL_DIR / "libagbsyscall.s"), implicit=binutils_stamp,
                        variables={"asincludes": f"-I {_path(GBA_DIR / 'lib')} --defsym L_{name}=1"})
                return base
            if unit.startswith("libc/"):
                name = unit.split("/", 1)[1]
                source, defines = LIBC_VARIANTS.get(name, (f"{name}.c", ""))
                extra = " -fshort-enums" if name == "stdlib/mbtowc_r" else ""
                pre = stem + ".i"
                asm = stem + ".s"
                n.build(pre, "gba_cpp", _path(LIBC_DIR / source), implicit=binutils_stamp,
                        variables={"cppflags": f"{LIBC_CPPFLAGS} {defines} -iquote {_path((LIBC_DIR / source).parent)}"})
                n.build(asm, "gba_cc", pre,
                        variables={"cc": os.path.normpath(old_agbcc), "cflags": f"-O2 -fno-builtin{extra}"})
                n.build(base, "gba_as", [asm, align], implicit=binutils_stamp)
                return base
            if unit.startswith("m4a/"):
                name = unit.split("/", 1)[1]
                if (M4A_DIR / f"{name}.s").is_file():
                    return assemble_arm(M4A_DIR / f"{name}.s", stem, base)
                source = M4A_DIR / f"{name}.c"
                if not source.is_file():
                    return None
                pre = stem + ".i"
                asm = stem + ".s"
                n.build(pre, "gba_cpp", _path(source), implicit=binutils_stamp,
                        variables={"cppflags": f"-undef -nostdinc -I {_path(M4A_DIR / 'include')} "
                                               f"-I {_path(GBA_DIR / 'lib' / 'ginclude')} "
                                               f"{info.get('m4a_defines', '')}"})
                n.build(asm, "gba_cc", pre,
                        variables={"cc": os.path.normpath(old_agbcc), "cflags": "-mthumb-interwork -O2"})
                n.build(base, "gba_as", [asm, align], implicit=binutils_stamp)
                return base
            asm_source = src_dir / f"{unit}.s"
            if asm_source.is_file():
                return assemble_arm(asm_source, stem, base)
            # A unit's source is <unit>.c, or a directory of C files linked together.
            source = src_dir / f"{unit}.c"
            files = sorted(f for f in (src_dir / unit).glob("*.c") if not f.name.startswith("_")) if (src_dir / unit).is_dir() else []
            if source.is_file():
                files = [source]
            if not files:
                return None
            objects = []
            for file in files:
                file_stem = stem if file == source else _path(out / "src" / unit / file.stem)
                pre = file_stem + ".i"
                asm = file_stem + ".s"
                obj = file_stem + ".o" if file != source else base
                n.build(pre, "gba_cpp", _path(file), implicit=binutils_stamp,
                        variables={"cppflags": f"{CPPFLAGS} -iquote {_path(file.parent)}"})
                n.build(asm, "gba_cc", pre, variables={"cc": os.path.normpath(agbcc), "cflags": CFLAGS})
                n.build(obj, "gba_as", [asm, align], implicit=binutils_stamp)
                objects.append(obj)
            if files != [source]:
                n.build(base, "gba_ld_r", objects, implicit=binutils_stamp)
            return base

        split_deps = [_path(tools / "split.py"), _path(tools / "gbaanalysis.py")]
        for category, info in programs.items():
            config_dir = GBA_DIR / "config" / info["config"]
            src_dir = GBA_DIR / "src" / info["config"]
            out = build / info["config"]
            units = _units(config_dir)
            arm_units = _arm_units(config_dir)
            bases = {}
            if have_compilers:
                for unit in units:
                    base = compile_source(unit, src_dir, out, info)
                    if base:
                        bases[unit] = base
            complete = {u for u in bases if u.startswith(("libgcc/", "libagbsyscall/", "libc/"))
                        or u in COMPLETE.get(info["config"], [])}

            asm = [_path(out / "asm" / f"{u}.s") for u in units]
            ldscript = _path(out / "ldscript.ld")
            overrides = " ".join(f"--object {u}={bases[u]}" for u in sorted(complete))
            n.build(asm + [ldscript], "gba_split", _path(bins[category]),
                    implicit=split_deps + [_path(config_dir / "symbols.txt"), _path(config_dir / "splits.txt")],
                    variables={"bin": _path(bins[category]), "config": _path(config_dir),
                               "asmdir": _path(out / "asm"), "ldscript": ldscript,
                               "objdir": _path(out / "obj"), "overrides": overrides})
            objects = []
            linked = []
            for unit in units:
                obj = _path(out / "obj" / f"{unit}.o")
                if unit in arm_units:
                    # Assembled like hand-written ARM source so branches keep their relocations.
                    assemble_arm(out / "asm" / f"{unit}.s", _path(out / "obj" / unit), obj)
                else:
                    n.build(obj, "gba_as", _path(out / "asm" / f"{unit}.s"), implicit=binutils_stamp)
                objects.append(obj)
                linked.append(bases[unit] if unit in complete else obj)
                unit_config: Dict[str, Any] = {
                    "name": f"gba/{info['config']}/{unit}",
                    "target_path": obj,
                    "metadata": {
                        "complete": unit in complete,
                        "progress_categories": [category],
                    },
                }
                if unit in bases:
                    objects.append(bases[unit])
                    unit_config["base_path"] = bases[unit]
                    source = src_dir / f"{unit}.c"
                    if not source.is_file():
                        source = src_dir / f"{unit}.s"
                    if source.is_file():
                        unit_config["metadata"]["source_path"] = _path(source)
                    elif unit.startswith("m4a/"):
                        unit_config["metadata"]["source_path"] = _path(M4A_DIR / unit.split("/", 1)[1])
                else:
                    unit_config["metadata"]["auto_generated"] = True
                config.extra_objdiff_units.append(unit_config)

            elf = _path(out / f"{info['config']}.elf")
            n.build(elf, "gba_ld", implicit=linked + [ldscript],
                    variables={"ldscript": ldscript, "map": _path(out / f"{info['config']}.map")})
            image = _path(out / bins[category].name)
            n.build(image, "gba_objcopy", elf)
            ok = _path(out / "ok")
            n.build(ok, "gba_sha1", image, implicit=_path(tools / "check_sha1.py"),
                    variables={"sha1": info["sha1"]})
            n.newline()

            config.extra_source_inputs += objects + [ok]
            config.progress_categories.append(ProgressCategory(category, info["name"]))
            config.reconfig_deps = (config.reconfig_deps or []) + [config_dir / "splits.txt"]
            if src_dir.is_dir():
                config.reconfig_deps.append(src_dir)
                config.reconfig_deps += [d for d in src_dir.iterdir() if d.is_dir()]

    config.subninjas.append(ninja_path)
    config.reconfig_deps = (config.reconfig_deps or []) + [Path(__file__)]
