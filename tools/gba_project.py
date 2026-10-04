"""Build rules for the GBA multiboot programs sent to linked Game Boy Advances.

Each program is split into per-unit assembly (gba/tools/split.py), reassembled,
linked, and checked against the retail image. The target objects are added to
objdiff.json so the programs count toward the version's progress report.

Units with source are compiled and diffed against their target objects:
- gba/src/<program>/<unit>.c, built with the original tree's cc1
- gba/src/<program>/<unit>.cpp, built with cc1plus (the C++ compiler from
  agbcc's 2.9-arm tree, built by gba/tools/build_cc1plus.sh)
- gba/src/<program>/<unit>/: C, C++ and assembly files linked with ld -r, in the
  order given by gba/config/<program>/link_order.txt (data layout follows it)
- libgcc/<object>, built from gba/lib/libgcc like agbcc's own libgcc
- libagbsyscall/<routine>, libc/<dir>/<file>, m4a/<file>: libraries in gba/lib
Units listed in COMPLETE, and all libgcc, libagbsyscall and libc units, link
their compiled objects into the checked image.
Symbols marked `asset` (or `asset:asm`) in symbols.txt are extracted from the
retail image into build/<version>/gba/<program>/assets/ (gba/tools/assets.py),
for assembly files in the source directory to .incbin (or .include).
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
LIBC_CPPFLAGS = ("-I gba/lib/ginclude -I gba/lib/libc/include -DABORT_PROVIDED "
                 "-DHAVE_GETTIMEOFDAY -DARM_RDI_MONITOR -DINTERNAL_NEWLIB "
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
            # The game code is C++, whose globals are defined in .bss; the sound
            # tables' C globals sit there too, never in common.
            "cflags": "-fno-common",
        },
    },
}

DISC_IMAGES = {"GCCP01": "FFCC_PAL.iso"}
ASFLAGS = "-mcpu=arm7tdmi -mthumb-interwork"
CPPFLAGS = "-I gba/include -I gba/lib/m4a/include -I gba/lib/ginclude"
CFLAGS = "-quiet -mthumb-interwork -O2"
# Without exception handling: with it, register copies are not propagated across
# calls (regmove), which the retail code shows they were.
CXXFLAGS = "-quiet -mthumb-interwork -O2 -fno-exceptions"
SOURCE_SUFFIXES = (".c", ".cpp", ".s")

# Game units whose compiled source links into the checked image, per program.
COMPLETE: Dict[str, List[str]] = {
    "cli": [
        "crt0", "joy_reset", "m4a/m4a_1", "m4a/m4a",
        "main/main", "main/xfer", "main/link", "main/text", "main/obj", "main/mode", "main/widget",
        "main/artifact", "main/cmake", "main/cmdlist", "main/equip", "main/family", "main/item", "main/letter", "main/menu",
        "main/radar", "main/radarmap", "main/gil", "main/scouter", "main/session", "main/smith", "main/favorite",
        "main/tmpartifact", "main/msg", "main/textmask", "main/msg_sys", "main/msg_item",
        "main/msg_monster", "main/backdrop_gfx", "main/m4a_tables", "main/sound_assets",
        "main/sound_data", "main/sound_assets_2", "main/backdrop", "main/font_gfx",
    ],
    "mgr": ["crt0", "main", "MgJoyBus", "obj", "effect", "camera", "field", "route", "text",
            "sound", "random", "sintable", "fixmath", "chunk", "param", "m4a_tables", "sound_data",
            "sound_assets", "m4a/m4a_1", "m4a/m4a", "joy_reset", "course", "menu_gfx", "obj_gfx",
            "config", "field_gfx", "font_gfx"],
}

# libgcc routines assembled from lib1thumb.asm; the rest are C.
LIBGCC_ASM = {"_udivsi3", "_divsi3", "_umodsi3", "_modsi3", "_dvmd_tls", "_call_via_rX"}


def _units(config_dir: Path) -> List[str]:
    text = (config_dir / "splits.txt").read_text(encoding="utf-8")
    return list(dict.fromkeys(re.findall(r"^(\S+):\s*$", text, re.M)))


def _common_units(config_dir: Path) -> set:
    """Units with recovered COMMON storage, materialized only for objdiff."""
    units = set()
    unit = None
    for line in (config_dir / "splits.txt").read_text(encoding="utf-8").splitlines():
        match = re.match(r"^(\S+):\s*$", line)
        if match:
            unit = match.group(1)
        elif unit is not None and re.match(r"^\s+\.common\s", line):
            units.add(unit)
    return units


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


def _link_order(config_dir: Path) -> Dict[str, List[str]]:
    """Per-unit source file link order from link_order.txt ("unit:" then indented files)."""
    path = config_dir / "link_order.txt"
    order: Dict[str, List[str]] = {}
    if not path.is_file():
        return order
    unit = None
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#")[0].rstrip()
        m = re.match(r"^(\S+):$", line)
        if m:
            unit = m.group(1)
            order[unit] = []
        elif line.strip() and unit is not None:
            order[unit].append(line.strip())
    return order


def _unit_files(unit_dir: Path, order: List[str]) -> List[Path]:
    """A source directory's files: listed ones in link order, then the rest sorted by name."""
    files = sorted(f for f in unit_dir.iterdir()
                   if f.suffix in SOURCE_SUFFIXES and not f.name.startswith("_"))
    listed = [unit_dir / name for name in order if (unit_dir / name) in files]
    return listed + [f for f in files if f not in listed]


def _unit_source(src_dir: Path, unit: str) -> Optional[Path]:
    """A unit's single C or C++ source file, if it has one."""
    for suffix in (".c", ".cpp"):
        if (src_dir / f"{unit}{suffix}").is_file():
            return src_dir / f"{unit}{suffix}"
    return None


def _assets(config_dir: Path) -> List[str]:
    """Files extracted for symbols marked asset (<name>.bin) or asset:asm (<name>.inc)."""
    return [f"{name}.inc" if kind else f"{name}.bin" for name, kind in
            re.findall(r"^(\S+) = \.\w+:0x[0-9A-Fa-f]+; //.*\basset(:asm)?(?:\s|$)",
                       (config_dir / "symbols.txt").read_text(encoding="utf-8"), re.M)]


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
    cc1 = compilers_dir / f"cc1{exe}"
    old_agbcc = compilers_dir / f"old_agbcc{exe}"
    cpp = compilers_dir / f"gcc2-cpp{exe}"
    cpp_inputs = [_path(cpp), _path(tools / "preprocess.py")]
    have_compilers = cc1.is_file() and old_agbcc.is_file() and cpp.is_file()
    if not have_compilers:
        print(
            f"Warning: cc1/old_agbcc/gcc2-cpp not found in {compilers_dir}; GBA sources are not "
            "compiled (see gba/toolchain.md and pass --gba-compilers)",
            file=sys.stderr,
        )
    cc1plus = compilers_dir / f"cc1plus{exe}"
    have_cxx = have_compilers and cc1plus.is_file()
    if have_compilers and not have_cxx:
        print(
            f"Warning: cc1plus not found in {compilers_dir}; GBA C++ sources are not "
            "compiled (build it with gba/tools/build_cc1plus.sh)",
            file=sys.stderr,
        )

    ninja_path = build / "build.ninja"
    ninja_path.parent.mkdir(parents=True, exist_ok=True)
    with open(ninja_path, "w", encoding="utf-8") as f:
        n = ninja_syntax.Writer(f)
        n.comment("GBA multiboot programs (generated by tools/gba_project.py)")
        n.variable("gba_asflags", ASFLAGS)
        n.newline()
        # These generators preserve unchanged outputs. Let Ninja record that a
        # newer input was checked without rebuilding every downstream object.
        n.rule("gba_binutils", f"$python {_path(tools / 'download_binutils.py')} $outdir",
               description="TOOL $out", restat=True)
        n.rule("gba_extract", f"$python {_path(tools / 'extract.py')} $in $outdir $paths",
               description="EXTRACT $out")
        n.rule("gba_assets", f"$python {_path(tools / 'assets.py')} $in $config $outdir",
               description="ASSETS $config", restat=True)
        n.rule("gba_split",
               f"$python {_path(tools / 'split.py')} $bin $config --asm-dir $asmdir "
               "--ldscript $ldscript --object-dir $objdir $overrides",
               description="SPLIT $config", restat=True)
        n.rule("gba_as", f"{prefix_str}as{exe} $gba_asflags $asincludes -o $out $in", description="AS $out")
        n.rule("gba_cpp", f"$python {_path(tools / 'preprocess.py')} "
               f'--cpp "{_path(cpp)}" $cppflags --depfile $out.d $in -o $out',
               description="CPP $in", depfile="$out.d", deps="gcc")
        n.rule("gba_cc", "$cc $cflags $in -o $out", description="AGBCC $out")
        n.rule("gba_ld", f"{prefix_str}ld{exe} -T $ldscript -o $out --no-warn-rwx-segments -Map $map",
               description="LINK $out")
        n.rule("gba_ld_r", f"{prefix_str}ld{exe} -r -o $out $in", description="LINK $out")
        n.rule("gba_common_view", f"{prefix_str}ld{exe} -r -d -T {_path(tools / 'common.ld')} -o $out $in",
               description="COMMON $out")
        n.rule("gba_rename_data", f"{prefix_str}objcopy{exe} --rename-section .rodata=.rodata.$name "
               "--rename-section .data=.data.$name $in $out", description="OBJCOPY $out")
        n.rule("gba_strip_attributes", f"{prefix_str}objcopy{exe} -R .ARM.attributes $in $out",
               description="OBJCOPY $out")
        n.rule("gba_objcopy", f'{prefix_str}objcopy{exe} -O binary -j ".text*" -j ".rodata*" -j ".data*" $in $out',
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

        def assemble_arm(source: Path, stem: str, base: str, assets_dir: Optional[Path] = None,
                         assets: Optional[List[str]] = None) -> str:
            """Assemble hand-written source that may contain ARM code."""
            # For ARM-state bx under ARMv4T, as emits R_ARM_V4BX relocations, which
            # objdiff cannot read. Assembling for v5t gives the same bytes without them;
            # the v5t attributes are then dropped since objdiff rejects that arch too.
            # Data modules .incbin files from the extracted assets.
            v5 = stem + ".v5.o"
            includes = f"-I {_path(GBA_DIR / 'lib')} -I {_path(GBA_DIR / 'include')}"
            if assets_dir is not None:
                includes += f" -I {_path(assets_dir)}"
            n.build(v5, "gba_as", _path(source), implicit=binutils_stamp + (assets or []),
                    variables={"asincludes": includes,
                               "gba_asflags": "-march=armv5t -mthumb-interwork"})
            n.build(base, "gba_strip_attributes", v5, implicit=binutils_stamp)
            return base

        def compile_source(unit: str, src_dir: Path, out: Path, info: Dict[str, str]) -> Optional[str]:
            """Emit rules for a unit's source; returns the compiled object or None."""
            base = _path(out / "src" / f"{unit}.o")
            stem = _path(out / "src" / unit)
            # Like pret and agbcc's libgcc, compiler output ends with an explicit
            # zero-filled word alignment, so the section is padded with zeros.
            # Its .bss is word-aligned too: the original objects' static
            # variables (.lcomm) each start on a word boundary.
            align = _path(GBA_DIR / "lib" / "align.s")
            if unit.startswith("libgcc/"):
                name = unit.split("/", 1)[1]
                if name in LIBGCC_ASM:
                    pre = stem + ".s"
                    n.build(pre, "gba_cpp", _path(LIBGCC_DIR / "lib1thumb.asm"), implicit=cpp_inputs,
                            variables={"cppflags": f"-DL{name} --language assembler-with-cpp"})
                    n.build(base, "gba_as", [pre, align], implicit=binutils_stamp)
                    return base
                bit = name in ("fp-bit", "dp-bit")
                source = LIBGCC_DIR / (f"{name}.c" if bit else "libgcc2.c")
                defines = "" if bit else f" -DL{name}"
                pre = stem + ".i"
                asm = stem + ".s"
                n.build(pre, "gba_cpp", _path(source), implicit=cpp_inputs,
                        variables={"cppflags": f"-I {_path(GBA_DIR / 'lib' / 'ginclude')}{defines}"})
                n.build(asm, "gba_cc", pre, implicit=[_path(old_agbcc)],
                        variables={"cc": os.path.normpath(old_agbcc), "cflags": "-O2"})
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
                if not (LIBC_DIR / source).is_file():
                    return None
                extra = " -fshort-enums" if name == "stdlib/mbtowc_r" else ""
                pre = stem + ".i"
                asm = stem + ".s"
                n.build(pre, "gba_cpp", _path(LIBC_DIR / source), implicit=cpp_inputs,
                        variables={"cppflags": f"{LIBC_CPPFLAGS} {defines}"})
                n.build(asm, "gba_cc", pre, implicit=[_path(old_agbcc)],
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
                n.build(pre, "gba_cpp", _path(source), implicit=cpp_inputs,
                        variables={"cppflags": f"-I {_path(M4A_DIR / 'include')} "
                                               f"-I {_path(GBA_DIR / 'lib' / 'ginclude')} "
                                               f"{info.get('m4a_defines', '')}"})
                n.build(asm, "gba_cc", pre, implicit=[_path(old_agbcc)],
                        variables={"cc": os.path.normpath(old_agbcc), "cflags": "-mthumb-interwork -O2"})
                n.build(base, "gba_as", [asm, align], implicit=binutils_stamp)
                return base
            asm_source = src_dir / f"{unit}.s"
            if asm_source.is_file():
                return assemble_arm(asm_source, stem, base, out / "assets", assets)
            # A unit's source is <unit>.c or <unit>.cpp, or a directory of C, C++ and
            # assembly files linked together in link order (see _link_order).
            source = _unit_source(src_dir, unit)
            files = _unit_files(src_dir / unit, link_order.get(unit, [])) if (src_dir / unit).is_dir() else []
            if source is not None:
                files = [source]
            if not files or (not have_cxx and any(f.suffix == ".cpp" for f in files)):
                return None
            objects = []
            for file in files:
                file_stem = stem if file == source else _path(out / "src" / unit / file.stem)
                obj = file_stem + ".o" if file != source else base
                if file.suffix == ".s":
                    # Data modules; .incbin paths resolve against the extracted assets.
                    n.build(obj, "gba_as", _path(file), implicit=binutils_stamp + assets,
                            variables={"asincludes": f"-I {_path(out / 'assets')}"})
                elif file.suffix == ".cpp":
                    pre = file_stem + ".ii"
                    asm = file_stem + ".s"
                    n.build(pre, "gba_cpp", _path(file), implicit=cpp_inputs,
                            variables={"cppflags": f"--language c++ {CPPFLAGS}"})
                    n.build(asm, "gba_cc", pre, implicit=[_path(cc1plus)],
                            variables={"cc": os.path.normpath(cc1plus),
                                                           "cflags": CXXFLAGS})
                    n.build(obj, "gba_as", [asm, align], implicit=binutils_stamp)
                else:
                    pre = file_stem + ".i"
                    asm = file_stem + ".s"
                    n.build(pre, "gba_cpp", _path(file), implicit=cpp_inputs,
                            variables={"cppflags": CPPFLAGS})
                    n.build(asm, "gba_cc", pre, implicit=[_path(cc1)],
                            variables={"cc": os.path.normpath(cc1),
                                                           "cflags": f"{CFLAGS} {info.get('cflags', '')}".strip()})
                    n.build(obj, "gba_as", [asm, align], implicit=binutils_stamp)
                if file != source and info.get("object_data_sections"):
                    # Keep each file's data in its own section (see PROGRAMS).
                    renamed = file_stem + ".sections.o"
                    n.build(renamed, "gba_rename_data", obj, implicit=binutils_stamp,
                            variables={"name": file.stem})
                    obj = renamed
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
            link_order = _link_order(config_dir)
            # Binary assets (symbols marked "asset") are extracted from the retail
            # image into the build directory, never committed.
            assets = [_path(out / "assets" / name) for name in _assets(config_dir)]
            if assets:
                n.build(assets, "gba_assets", _path(bins[category]),
                        implicit=split_deps + [_path(tools / "assets.py")]
                        + [_path(config_dir / name) for name in ("symbols.txt", "splits.txt", "constants.txt",
                                                                 "references.txt") if (config_dir / name).is_file()],
                        variables={"config": _path(config_dir), "outdir": _path(out / "assets")})
            bases = {}
            if have_compilers:
                for unit in units:
                    base = compile_source(unit, src_dir, out, info)
                    if base:
                        bases[unit] = base
            complete = {u for u in bases if u.startswith(("libgcc/", "libagbsyscall/", "libc/"))
                        or u in COMPLETE.get(info["config"], [])}
            # Objdiff needs section-backed storage to compare COMMON symbols.
            # Keep this view separate: linking it would turn tentative definitions
            # into strong definitions and prevent normal cross-object coalescing.
            comparison_bases = dict(bases)
            for unit in sorted(_common_units(config_dir) & bases.keys()):
                view = _path(out / "src" / f"{unit}.common.o")
                n.build(view, "gba_common_view", bases[unit],
                        implicit=binutils_stamp + [_path(tools / "common.ld")])
                comparison_bases[unit] = view

            asm = [_path(out / "asm" / f"{u}.s") for u in units]
            ldscript = _path(out / "ldscript.ld")
            overrides = " ".join(f"--object {u}={bases[u]}" for u in sorted(complete))
            n.build(asm + [ldscript], "gba_split", _path(bins[category]),
                    implicit=split_deps + [_path(config_dir / "symbols.txt"), _path(config_dir / "splits.txt")]
                    + [_path(config_dir / name) for name in ("constants.txt", "references.txt")
                       if (config_dir / name).is_file()],
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
                    objects.append(comparison_bases[unit])
                    unit_config["base_path"] = comparison_bases[unit]
                    source = _unit_source(src_dir, unit) or src_dir / f"{unit}.s"
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
            config.reconfig_deps = (config.reconfig_deps or []) + [config_dir / "splits.txt",
                                                                   config_dir / "symbols.txt"]
            if (config_dir / "link_order.txt").is_file():
                config.reconfig_deps.append(config_dir / "link_order.txt")
            if src_dir.is_dir():
                config.reconfig_deps.append(src_dir)
                config.reconfig_deps += [d for d in src_dir.iterdir() if d.is_dir()]

    config.subninjas.append(ninja_path)
    config.reconfig_deps = (config.reconfig_deps or []) + [Path(__file__)]
