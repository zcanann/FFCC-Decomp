#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import os
import sys
from pathlib import Path
from typing import Any, Dict, List, Set

from tools.gba_project import configure_gba
from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GCCE01",  # 0
    "GCCP01",  # 1
    "GCCJGC",  # 2
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--gba-binutils",
    metavar="DIR",
    type=Path,
    help="directory containing arm-none-eabi binutils for the GBA programs (optional)",
)
parser.add_argument(
    "--gba-compilers",
    metavar="DIR",
    type=Path,
    help="directory containing cc1, cc1plus, gcc2-cpp and old_agbcc for GBA (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    default=True,
    help="generate map file(s) (default: enabled)",
)
parser.add_argument(
    "--no-map",
    dest="map",
    action="store_false",
    help="disable map file generation",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args, extra_args = parser.parse_known_args()
trailing_mode = None
if len(extra_args) == 1 and extra_args[0] in {"configure", "progress"}:
    trailing_mode = extra_args[0]
elif len(extra_args) > 0:
    parser.error(f"unrecognized arguments: {' '.join(extra_args)}")

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20250812"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    *([] if config.version in ("GCCP01", "GCCE01") else ["-multibyte"]),  # PAL/USA retail strings were built without SJIS awareness
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")
    
# Game flags
cflags_fmadd = [f for f in cflags_base if '-fp ' not in f and '-fp_contract' not in f] + ["-fp fmadd"]
cflags_game = [
    *cflags_base,
    "-use_lmw_stmw on",
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-Cpp_exceptions on",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# Metrowerks library flags
cflags_msl = [
    *cflags_base,
    "-char signed",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline auto,deferred",
]

# Metrowerks library flags
cflags_trk = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-rostr",
    "-str reuse",
    "-gccinc",
    "-common off",
    "-inline deferred,auto",
    "-char signed",
    "-sdata 0",
    "-sdata2 0",
]

cflags_odemuexi = [
    *cflags_base,
    "-inline deferred",
    "-use_lmw_stmw on",
]

cflags_amcstub = [
    *cflags_base,
    "-inline auto,deferred",
]

cflags_odenotstub = [
    *cflags_base,
    "-inline auto,deferred",
]

cflags_thp = [
    *cflags_base,
]

def replace_flag_prefix(flags: List[str], prefix: str, new_flag: str) -> List[str]:
    out = [f for f in flags if not f.startswith(prefix)]
    out.append(new_flag)
    return out


cflags_game_cpp_exceptions = replace_flag_prefix(
    cflags_game, "-Cpp_exceptions ", "-Cpp_exceptions on"
)


def redsound_flags_from_profile(profile: str) -> List[str]:
    base = list(cflags_game)
    if profile == "game":
        return base
    if profile == "char_signed":
        return [*base, "-char signed"]
    if profile == "inline_deferred":
        return replace_flag_prefix(base, "-inline ", "-inline deferred")
    if profile == "opt_level0_sched":
        flags = replace_flag_prefix(base, "-inline ", "-inline deferred")
        flags = [flag for flag in flags if not flag.startswith("-O")]
        return [*flags, "-opt level=0, peephole, schedule, nospace"]
    if profile == "inline_auto_deferred":
        return replace_flag_prefix(base, "-inline ", "-inline auto,deferred")
    if profile == "str_pool_common_off":
        return [
            *replace_flag_prefix(base, "-str ", "-str reuse,pool,readonly"),
            "-common off",
        ]
    if profile == "runtime_like":
        return [
            *replace_flag_prefix(base, "-str ", "-str reuse,pool,readonly"),
            "-common off",
            "-use_lmw_stmw on",
            "-gccinc",
            "-inline auto",
        ]
    if profile == "trk_like":
        return [
            *replace_flag_prefix(base, "-inline ", "-inline deferred,auto"),
            "-str reuse",
            "-char signed",
            "-common off",
            "-use_lmw_stmw on",
            "-gccinc",
            "-rostr",
            "-sdata 0",
            "-sdata2 0",
        ]
    print(f"Unknown FFCC_REDSOUND_PROFILE={profile!r}, using 'game' profile")
    return base


def parse_unit_env_set(name: str) -> Set[str]:
    value = os.environ.get(name, "")
    return {part.strip() for part in value.split(",") if part.strip()}


def parse_flag_env_list(name: str) -> List[str]:
    value = os.environ.get(name, "")
    return [part.strip() for part in value.split(";") if part.strip()]


# RedSound is built pragma-free. Reference projects use this Metrowerks
# library-style opt profile for some shipped objects, and it matches RedSound's
# stack/register patterns far better than source-local optimization pragmas.
redsound_profile = os.environ.get("FFCC_REDSOUND_PROFILE", "opt_level0_sched")
redsound_cflags = redsound_flags_from_profile(redsound_profile)
redsound_cpp_exceptions_cflags = replace_flag_prefix(
    redsound_cflags, "-Cpp_exceptions ", "-Cpp_exceptions on"
)
# PAL RedSound objects carry exception tables across the library; keep the
# source build configured the same way instead of faking extab data.
redsound_cpp_exceptions_units = {
    "RedCommand",
    "RedDriver",
    "RedEntry",
    "RedExecute",
    "RedMemory",
    "RedMidiCtrl",
    "RedSound",
    "RedStream",
    *parse_unit_env_set("FFCC_REDSOUND_CPP_EXCEPTIONS_UNITS"),
}
redsound_opt0_units = parse_unit_env_set("FFCC_REDSOUND_OPT0_UNITS")
# These RedSound objects' code report measures are unchanged by inline-off,
# but their generated exception table layouts move closer to the MAP/object
# targets with this unit-local flag.
redsound_inline_off_units = {
    "RedCommand",
    "RedEntry",
    "RedExecute",
    "RedMemory",
    "RedSound",
    "RedStream",
    *parse_unit_env_set("FFCC_REDSOUND_INLINE_OFF_UNITS"),
}
redsound_inline_deferred_units = parse_unit_env_set(
    "FFCC_REDSOUND_INLINE_DEFERRED_UNITS"
)
redsound_no_inline_flag_units = {
    "RedDriver",
    "RedMidiCtrl",
    *parse_unit_env_set("FFCC_REDSOUND_NO_INLINE_FLAG_UNITS"),
}
redsound_remove_flag_prefixes = parse_flag_env_list("FFCC_REDSOUND_REMOVE_PREFIXES")
redsound_extra_flags = parse_flag_env_list("FFCC_REDSOUND_EXTRA_FLAGS")


def redsound_unit_cflags(unit_name: str, *, cpp_exceptions: bool = False) -> List[str]:
    has_cpp_exceptions = cpp_exceptions or unit_name in redsound_cpp_exceptions_units
    flags = redsound_cpp_exceptions_cflags if has_cpp_exceptions else redsound_cflags
    for prefix in redsound_remove_flag_prefixes:
        flags = [flag for flag in flags if not flag.startswith(prefix)]
    if unit_name in redsound_opt0_units:
        flags = replace_flag_prefix(flags, "-O", "-O0")
    if unit_name in redsound_no_inline_flag_units:
        flags = [flag for flag in flags if not flag.startswith("-inline ")]
    elif unit_name in redsound_inline_off_units:
        flags = replace_flag_prefix(flags, "-inline ", "-inline off")
    elif unit_name in redsound_inline_deferred_units:
        flags = replace_flag_prefix(flags, "-inline ", "-inline deferred")
    flags = [*flags, *redsound_extra_flags]
    return flags

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


def RedSoundLib(objects: List[Object]) -> Dict[str, Any]:
    return {
        # PAL MAP ownership attributes these units to RedSound.a rather than
        # the main game archive, so keep their shared flags at the library level.
        "lib": "RedSound",
        "mw_version": "GC/2.0p1",
        "cflags": redsound_cflags,
        "progress_category": "redsound",
        "objects": objects,
    }


# Existing matching claims were verified against PAL. Other revisions must be
# verified separately and opted in with MatchingFor before linking source.
Matching = config.version == "GCCP01"
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    RedSoundLib([
        Object(NonMatching, "RedSound/RedCommand.cpp", cflags=redsound_unit_cflags("RedCommand")),
        Object(NonMatching, "RedSound/RedDriver.cpp", cflags=redsound_unit_cflags("RedDriver")),
        Object(NonMatching, "RedSound/RedEntry.cpp", cflags=redsound_unit_cflags("RedEntry")),
        Object(NonMatching, "RedSound/RedExecute.cpp", cflags=redsound_unit_cflags("RedExecute")),
        Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "RedSound/RedMemory.cpp", cflags=redsound_unit_cflags("RedMemory")),
        Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "RedSound/RedMidiCtrl.cpp", cflags=redsound_unit_cflags("RedMidiCtrl")),
        Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "RedSound/RedSound.cpp", cflags=redsound_unit_cflags("RedSound")),
        Object(
            NonMatching,
            "RedSound/RedStream.cpp",
            cflags=redsound_unit_cflags("RedStream"),
        ),
    ]),
    {
        "lib": "Game",
        # Japanese compatibility baseline; provenance: docs/compiler_baseline.md.
        "mw_version": "GC/2.0p1i" if config.version == "GCCJGC" else "GC/2.5",
        "cflags": cflags_game_cpp_exceptions,
        "progress_category": "game",
        "objects": [
            Object(NonMatching, "astar.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "baseobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly"]),
            Object(NonMatching, "bonus_menu.cpp", extra_cflags=["-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "cflat_data.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "cflat_r2class.cpp"),
            Object(
                NonMatching,
                "cflat_r2system.cpp",
                extra_cflags=["-str reuse,nopool,readonly", "-use_lmw_stmw on", "-inline auto,deferred"],
            ),
            Object(NonMatching, "cflat_runtime.cpp", extra_cflags=["-RTTI on", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "cflat_runtime2.cpp", extra_cflags=["-RTTI on", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(
                NonMatching,
                "chara_anim.cpp",
                extra_cflags=["-RTTI on", "-str reuse,readonly", "-inline auto,deferred"],
            ),
            Object(NonMatching, "chara_fur.cpp", extra_cflags=["-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "chara.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "charaobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "chunkfile.cpp", extra_cflags=["-inline auto,deferred"]),
            Object(NonMatching, "cmake.cpp", extra_cflags=["-str reuse,readonly", "-inline noauto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "color.cpp"),
            Object(NonMatching, "file.cpp", extra_cflags=["-inline auto,deferred", "-RTTI on", "-sdata 8", "-str reuse,nopool,readonly"]),
            Object(Matching, "strcase.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "fontman.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "FS_USB_Process.cpp", cflags=cflags_game_cpp_exceptions),
            Object(NonMatching, "FunnyShape.cpp"),
            Object(NonMatching, "game.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "gbaque.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "gobject.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(NonMatching, "gobjwork.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "goout.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "graphic.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "graphic_dbgfont.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gxfunc.cpp"),
            Object(NonMatching, "itemobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "joybus.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "KeLns.cpp"),
            Object(NonMatching, "LocationTitle2.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "main.cpp"),
            Object(NonMatching, "manager.cpp"),
            Object(NonMatching, "map.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mapanim.cpp", extra_cflags=["-RTTI on", "-str reuse,readonly"]),
            Object(NonMatching, "maphit.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "maplight.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mapmesh.cpp", extra_cflags=["-sdata 8"]),
            Object(NonMatching, "mapobj.cpp", extra_cflags=["-RTTI on", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mapocttree.cpp", extra_cflags=["-sdata 8"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mapshadow.cpp", cflags=cflags_game_cpp_exceptions, extra_cflags=["-sdata2 8"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "maptexanim.cpp", extra_cflags=["-RTTI on", "-str reuse,pool,readonly"]),
            Object(NonMatching, "materialman.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "math.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ME_AppRequest.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ME_USB_process.cpp", cflags=[*cflags_game_cpp_exceptions, "-sdata2 8", "-str reuse,readonly"]),
            Object(NonMatching, "memory.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "memorycard.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "menu.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "menu_arti.cpp"),
            Object(NonMatching, "menu_cmd.cpp", extra_cflags=["-str reuse,nopool,readonly", "-pool off", "-inline auto,deferred"]),
            Object(NonMatching, "menu_compa.cpp", cflags=cflags_game_cpp_exceptions),
            Object(NonMatching, "menu_equip.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "menu_favo.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(NonMatching, "menu_item.cpp"),
            Object(NonMatching, "menu_letter.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "menu_lst.cpp"),
            Object(NonMatching, "menu_money.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "menu_tmparti.cpp"),
            Object(NonMatching, "MenuUtil.cpp", extra_cflags=["-sdata2 8", "-str reuse,readonly", "-inline noauto,deferred"]),
            Object(NonMatching, "mes.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(NonMatching, "mesmenu.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-inline auto,deferred", "-str reuse,readonly"]),
            Object(NonMatching, "monobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "monobj_boss.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "monobj_table.cpp", extra_cflags=["-pooldata off"]),
            Object(NonMatching, "p_camera.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-inline auto,deferred", "-str reuse,readonly"]),
            Object(NonMatching, "p_chara.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_chara_viewer.cpp", extra_cflags=["-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_dbgmenu.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_FunnyShape.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_game.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_gba.cpp", cflags=[*cflags_game_cpp_exceptions, "-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "p_graphic.cpp", cflags=[*cflags_game_cpp_exceptions, "-RTTI on", "-sdata 8", "-str reuse,pool,readonly", "-pooldata off", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_light.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_map.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_MaterialEditor.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_mc.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(NonMatching, "p_menu.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "p_minigame.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-common off", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_sample.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_sound.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01"), "p_system.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_tina.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "p_usb.cpp", extra_cflags=["-pooldata off", "-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pad.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "partMng.cpp", extra_cflags=["-RTTI on", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppsintbl.cpp"),
            Object(NonMatching, "partyobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppAccele.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppAlignmentScale.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppAngAccele.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppAngle.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppAngMove.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppBindOnlyPos.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppBlurChara.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppBreathModel.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppCallBackDistance.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppChangeBGColor.cpp"),
            Object(NonMatching, "pppChangeTex.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(NonMatching, "pppCharaBreak.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppCharaZEnvCtrl.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppColAccele.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppColMove.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppColor.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppColum.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppConformBGNormal.cpp"),
            Object(NonMatching, "pppConstrainCameraDir.cpp", cflags=cflags_game_cpp_exceptions),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppConstrainCameraDir2.cpp", cflags=cflags_game_cpp_exceptions),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppConstrainCameraForLoc.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppCorona.cpp"),
            Object(NonMatching, "pppCrystal.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(NonMatching, "pppCrystal2.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrixFront.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrixFrontLnr.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrixLoc.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrixNoRot.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMatrixWood.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMdl.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMdlTs.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawMng.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawShape.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppDrawShape2.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppEmission.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppEraseCharaParts.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppFilter.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppFovAdjustMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixX.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixXYZ.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixXZY.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixY.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixYXZ.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixYZX.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixZ.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixZXY.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppGetRotMatrixZYX.cpp"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "pppKeDMat.cpp",
                cflags=[*cflags_game, "-Cpp_exceptions on", "-use_lmw_stmw on"],
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppKeLns.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppKeShpTail.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppKeShpTail2X.cpp"),
            Object(NonMatching, "pppKeShpTail3X.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppKeZCrctShp.cpp"),
            Object(NonMatching, "pppLaser.cpp", extra_cflags=["-str reuse,pool,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppLensFlare.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppLerpPos.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppLight.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppLocationTitle.cpp"),
            Object(NonMatching, "pppMana2.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixLoc.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixScl.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixXYZ.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixXZY.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixYXZ.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixYZX.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixZXY.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMatrixZYX.cpp"),
            Object(NonMatching, "pppMiasma.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppMove.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppParHitSph.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppParHitSphMat.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppParMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppParMoveLine.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppParMoveMatrix.cpp", cflags=cflags_game_cpp_exceptions),
            Object(NonMatching, "pppPart.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppPObjPoint.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppPoint.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppPointAp.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppPointApMtx.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppPointRAp.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRain.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandChar.cpp"),
            Object(Equivalent, "pppRandCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandDownChar.cpp"),
            Object(Equivalent, "pppRandDownCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandDownFloat.cpp"),
            Object(Equivalent, "pppRandDownFV.cpp"),
            Object(Equivalent, "pppRandDownHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandDownInt.cpp"),
            Object(Equivalent, "pppRandDownIV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandDownShort.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandFloat.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppRandFV.cpp"),
            Object(Equivalent, "pppRandHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandInt.cpp"),
            Object(Equivalent, "pppRandIV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandShort.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandUpChar.cpp"),
            Object(Equivalent, "pppRandUpCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandUpFloat.cpp"),
            Object(Equivalent, "pppRandUpFV.cpp"),
            Object(Equivalent, "pppRandUpHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandUpInt.cpp"),
            Object(Equivalent, "pppRandUpIV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppRandUpShort.cpp"),
            Object(NonMatching, "pppRyjMegaBirth.cpp"),
            Object(NonMatching, "pppRyjMegaBirthModel.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppScale.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppScaleLoopAuto.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSclAccele.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSclMove.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppScreenBlur.cpp"),
            Object(NonMatching, "pppScreenBreak.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppScreenQuake.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSDrawMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppShape.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSpMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandDownCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandDownFV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandDownHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandFV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandUpCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandUpFV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppSRandUpHCV.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVertexAp.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVertexApAt.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVertexApLc.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVertexApMtx.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVertexAttend.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppVtMime.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppfunctbl.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppWDrawMatrix.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppWDrawMatrixFront.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppWDrawMatrixFrontLoop.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppWDrawMatrixLoop.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmBreath.cpp", cflags=cflags_game_cpp_exceptions),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmCallBack.cpp"),
            Object(NonMatching, "pppYmChangeTex.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppYmCheckBGHeight.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmDeformationMdl.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmDeformationScreen.cpp"),
            Object(NonMatching, "pppYmDeformationShp.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmDrawMdlTexAnm.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppYmEnv.cpp", extra_cflags=["-char unsigned", "-str reuse,readonly"]),
            Object(NonMatching, "pppYmLaser.cpp", extra_cflags=["-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmLookOn.cpp"),
            Object(NonMatching, "pppYmMana.cpp", extra_cflags=["-str reuse,readonly"]),
            Object(NonMatching, "pppYmMegaBirthShpTail2.cpp", extra_cflags=["-inline auto,deferred"]),
            Object(NonMatching, "pppYmMegaBirthShpTail3.cpp", extra_cflags=["-inline auto,deferred"]),
            Object(NonMatching, "pppYmMelt.cpp", cflags=cflags_game),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmMiasma.cpp", cflags=cflags_game),
            Object(MatchingFor("GCCP01", "GCCE01"), "pppYmMoveCircle.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmMoveParabola.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmTraceMove.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmTracer.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pppYmTracer2.cpp", cflags=cflags_game),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "prgobj.cpp", extra_cflags=["-inline auto,deferred", "-RTTI on", "-str reuse,pool,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "quadobj.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ref.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,pool,readonly"]),
            Object(NonMatching, "ringmenu.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-inline auto,deferred", "-str reuse,readonly"]),
            Object(NonMatching, "shopmenu.cpp", extra_cflags=["-inline noauto,deferred"]),
            Object(NonMatching, "singmenu.cpp", extra_cflags=["-str reuse,readonly", "-pool off"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "sound.cpp", extra_cflags=["-inline auto,deferred", "-RTTI on", "-str reuse,nopool,readonly", "-sdata 8"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "stopwatch.cpp", extra_cflags=["-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "system.cpp", extra_cflags=["-inline auto,deferred", "-RTTI on", "-sdata 8", "-str reuse,readonly"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "texanim.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,nopool,readonly", "-inline auto,deferred"]),
            Object(NonMatching, "textureman.cpp", extra_cflags=["-inline auto,deferred", "-RTTI on", "-sdata 8", "-str reuse,nopool,readonly"]),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "THPDraw.cpp",
                cflags=[
                    *replace_flag_prefix(cflags_thp, "-Cpp_exceptions ", "-Cpp_exceptions on"),
                    "-use_lmw_stmw on",
                ],
            ),
            Object(MatchingFor("GCCE01", "GCCJGC"), "THPSimple.cpp", extra_cflags=["-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "usb.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "USBStreamData.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "util.cpp", extra_cflags=["-RTTI on", "-sdata 8", "-str reuse,readonly", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "vector.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01"), "wind.cpp"),
            Object(NonMatching, "wm_menu.cpp", extra_cflags=["-RTTI on", "-str reuse,readonly", "-inline auto,deferred"]),
            # Retail addresses local message tables separately and stores literals read-only.
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "wmm_str.cpp", extra_cflags=["-str reuse,readonly", "-pooldata off", "-inline auto,deferred"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "zlist.cpp"),
        ]
    },
    DolphinLib(
        "base",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "dolphin/os/__start.c",
                source="os/__start.c",
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "dolphin/os/__ppc_eabi_init.cpp",
                source="os/__ppc_eabi_init.cpp",
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OS.c"),
            Object(Matching, "os/OSAddress.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSAlarm.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSAlloc.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSArena.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSAudioSystem.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSCache.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSContext.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSError.c"),
            Object(Matching, "os/OSFatal.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSFont.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSInterrupt.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSLink.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSMemory.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSMessage.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSMutex.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSReboot.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSReset.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSResetSW.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSRtc.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSSemaphore.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSStopwatch.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSSync.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSThread.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "os/OSTime.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "exi/EXIBios.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "si/SIBios.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "db/db.c"),
        ],
    ),
    {
        "lib": "mtx",
        "mw_version": "GC/1.2.5n",
        "cflags": [*cflags_fmadd, "-DGEKKO"],
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/mtx.c", cflags=[*replace_flag_prefix(cflags_fmadd, "-fp ", "-fp hardware"), "-DGEKKO"]),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/mtxvec.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/mtx44.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/mtx44vec.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/vec.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mtx/quat.c"),
            Object(Matching, "mtx/psmtx.c"),
        ],
    },
    DolphinLib(
        "dvd",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvd.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvderror.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvdFatal.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvdfs.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvdidutils.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvdlow.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/dvdqueue.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(Matching, "vi/gpioexi.c"),
            Object(Matching, "vi/i2c.c"),
            Object(Matching, "vi/initphilips.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "vi/vi.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pad/Padclamp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ar/ar.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ar/arq.c"),
        ],
    ),
    DolphinLib(
        "ax",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AX.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXAlloc.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXAux.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXCL.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXOut.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXProf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXSPB.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXVPB.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/AXComp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "ax/DSPCode.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axfx/axfx.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axfx/chorus.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axfx/delay.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axfx/reverb_hi.c",
                cflags=replace_flag_prefix(
                    replace_flag_prefix(cflags_base, "-fp_contract ", ""),
                    "-fp ", "-fp fmadd"
                ),
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "axfx/reverb_hi_4ch.c",
                cflags=replace_flag_prefix(cflags_base, "-fp_contract ", "-fp_contract off"),
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "axfx/reverb_std.c",
                cflags=replace_flag_prefix(cflags_base, "-fp_contract ", "-fp_contract off"),
            ),
        ],
    ),
    DolphinLib(
        "mix",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "mix/mix.c"),
        ],
    ),
    DolphinLib(
        "axart",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axart/axart.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "axart/axart3d.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dsp/dsp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dsp/dsp_debug.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDBios.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDBlock.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDCheck.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDCreate.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDDelete.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDDir.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDFormat.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDMount.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDNet.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDOpen.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDRdwr.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDRead.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDStat.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDUnlock.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "card/CARDWrite.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXAttr.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXBump.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXDisplayList.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXFifo.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXFrameBuf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXGeometry.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXInit.c", extra_cflags=["-opt nopeephole"]),
            Object(Matching, "gx/GXGet.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "gx/GXLight.c",
                cflags=replace_flag_prefix(cflags_base, "-fp_contract ", "-fp_contract off"),
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXMisc.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXPerf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXPixel.c"),
            Object(Matching, "gx/GXSave.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXStubs.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXTev.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gx/GXTexture.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "gx/GXTransform.c",
                cflags=replace_flag_prefix(cflags_base, "-fp_contract ", "-fp_contract off"),
            ),
            Object(Matching, "gx/GXVerifRAS.c"),
            Object(Matching, "gx/GXVerifXF.c"),
            Object(Matching, "gx/GXVerify.c"),
            Object(Matching, "gx/GXVert.c"),
        ],
    ),
    DolphinLib(
        "gba",
        [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBA.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBAGetProcessStatus.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBAJoyBoot.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBARead.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBAWrite.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "gba/GBAXfer.c"),
                Object(
                    MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                    "gba/GBAKey.c",
                    cflags=replace_flag_prefix(cflags_base, "-inline ", "-inline auto"),
                ),
        ],
    ),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "Runtime.PPCEABI.H/__va_arg.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "Runtime.PPCEABI.H/CPlusLibPPC.cp"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "Runtime.PPCEABI.H/GCN_mem_alloc.c",
                cflags=replace_flag_prefix(cflags_runtime, "-Cpp_exceptions ", "-Cpp_exceptions off"),
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cp",
                mw_version="GC/2.6",
                extra_cflags=["-char signed", "-RTTI on", "-str reuse,nopool,readonly"],
                extab_padding=[0x02, 0x55],
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "Runtime.PPCEABI.H/global_destructor_chain.c",
                cflags=replace_flag_prefix(cflags_runtime, "-Cpp_exceptions ", "-Cpp_exceptions off"),
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "Runtime.PPCEABI.H/New.cp",
                mw_version="GC/2.6",
                cflags=replace_flag_prefix(cflags_runtime, "-RTTI ", "-RTTI on"),
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "Runtime.PPCEABI.H/NMWException.cp",
                mw_version="GC/1.3.2" if config.version == "GCCJGC" else "GC/2.5",
                extra_cflags=["-inline auto,deferred"],
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "Runtime.PPCEABI.H/ptmf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "Runtime.PPCEABI.H/runtime.c"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": config.linker_version,
        "cflags": cflags_msl,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/abort_exit.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "MSL_C/PPCEABI/bare/H/alloc.c",
                mw_version="GC/2.7",
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/errno.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "MSL_C/PPCEABI/bare/H/ansi_files.c",
                mw_version="GC/2.0" if config.version == "GCCJGC" else "GC/2.7",
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/ansi_fp.c", mw_version="GC/2.7"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/buffer_io.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/gamecube.c", mw_version="GC/2.6"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/ctype.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/direct_io.c"),
            Object(MatchingFor("GCCP01", "GCCE01"), "MSL_C/PPCEABI/bare/H/extras.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/e_acos.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/e_atan2.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/e_fmod.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/e_pow.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/e_rem_pio2.c"),
            Object(MatchingFor("GCCP01", "GCCE01"), "MSL_C/PPCEABI/bare/H/e_sqrt.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/file_io.c", mw_version="GC/2.7"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/FILE_POS.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/k_cos.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/k_rem_pio2.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/k_sin.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/k_tan.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/math_ppc.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/mbstring.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/mem.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "MSL_C/PPCEABI/bare/H/mem_funcs.c",
                mw_version="GC/2.0",
                cflags=replace_flag_prefix(
                    cflags_msl,
                    "-inline ",
                    "-inline deferred,auto",
                ),
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/misc_io.c", mw_version="GC/2.6"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "MSL_C/PPCEABI/bare/H/printf.c",
                # Japan retains the older MSL formatter; all 13 functions verify.
                mw_version="GC/2.0" if config.version == "GCCJGC" else "GC/2.6",
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/rand.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/signal.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/string.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/float.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_atan.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_copysign.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_cos.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_floor.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_frexp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_ldexp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_modf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_sin.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/s_tan.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/uart_console_io_gcn.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/wchar_io.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/w_acos.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/w_atan2.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/w_fmod.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "MSL_C/PPCEABI/bare/H/w_pow.c"),
            Object(MatchingFor("GCCP01", "GCCE01"), "MSL_C/PPCEABI/bare/H/w_sqrt.c"),
        ],
    },
    {
        "lib": "OdemuExi2",
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_odemuexi,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "OdemuExi2/DebuggerDriver.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_trk,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/__exception.s"),
            Object(MatchingFor("GCCP01", "GCCE01"), "TRK_MINNOW_DOLPHIN/CircleBuffer.c", mw_version="GC/2.6"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(MatchingFor("GCCP01", "GCCE01"), "TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c", mw_version="GC/2.6"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01"),
                "TRK_MINNOW_DOLPHIN/main.c",
                cflags=[f for f in cflags_trk if f not in ("-sdata 0", "-sdata2 0")],
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01"),
                "TRK_MINNOW_DOLPHIN/main_gdev.c",
                mw_version="GC/1.3.2",
                cflags=[f for f in cflags_trk if f not in ("-sdata 0", "-sdata2 0")],
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/msg.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/msghndlr.c", mw_version="GC/2.6"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/mslsupp.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(MatchingFor("GCCP01", "GCCE01"), "TRK_MINNOW_DOLPHIN/MWCriticalSection_gc.c", mw_version="GC/2.6"),
            Object(MatchingFor("GCCP01", "GCCE01"), "TRK_MINNOW_DOLPHIN/MWTrace.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/notify.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "TRK_MINNOW_DOLPHIN/serpoll.c",
                mw_version="GC/2.6",
                cflags=cflags_trk if config.version == "GCCJGC" else [
                    f for f in cflags_trk if f not in ("-sdata 0", "-sdata2 0")
                ],
            ),
            Object(
                MatchingFor("GCCP01", "GCCE01"),
                "TRK_MINNOW_DOLPHIN/support.c",
                mw_version="GC/2.6",
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/target_options.c", mw_version="GC/2.6"),
            Object(
                MatchingFor("GCCP01", "GCCE01", "GCCJGC"),
                "TRK_MINNOW_DOLPHIN/targimpl.c",
                mw_version="GC/2.6",
                cflags=[
                    "-nodefaults",
                    "-proc gekko",
                    "-align powerpc",
                    "-enum int",
                    "-fp hardware",
                    "-Cpp_exceptions off",
                    "-O4,p",
                    "-inline auto",
                    '-pragma "cats off"',
                    '-pragma "warn_notinlined off"',
                    "-maxerrors 1",
                    "-nosyspath",
                    "-RTTI off",
                    "-fp_contract on",
                    "-str reuse",
                    "-multibyte",
                    "-i include",
                    f"-i build/{config.version}/include",
                    f"-DBUILD_VERSION={version_num}",
                    f"-DVERSION_{config.version}",
                    "-DNDEBUG=1",
                    "-use_lmw_stmw on",
                    "-rostr",
                    "-str reuse",
                    "-gccinc",
                    "-common off",
                    "-inline deferred,auto",
                    "-char signed",
                    "-sdata 0",
                    "-sdata2 0",
                ],
            ),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/targsupp.s"),
            Object(MatchingFor("GCCP01", "GCCE01"), "TRK_MINNOW_DOLPHIN/UDP_Stubs.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "TRK_MINNOW_DOLPHIN/usr_put.c"),
        ],
    },
    {
        "lib": "amcstubs",
        "mw_version": config.linker_version,
        "cflags": cflags_amcstub,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "amcstubs/AmcExi2Stubs.c"),
        ],
    },
    {
        "lib": "odenotstub",
        "mw_version": config.linker_version,
        "cflags": cflags_odenotstub,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "odenotstub/odenotstub.c"),
        ],
    },
    {
        "lib": "thp",
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_thp,
        "progress_category": "sdk",
        "objects": [
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "thp/THPDec.c"),
            Object(MatchingFor("GCCP01", "GCCE01", "GCCJGC"), "thp/THPAudio.c"),
        ],
    },
]

# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("redsound", "RedSound"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    "--deduplicate",
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    "--config", "functionRelocDiffs=none",
    # "--config", "functionRelocDiffs=data_value",
]

# Japanese game compiler: GC/2.0p1i, derived during the build from the stock
# GC/2.0p1 by tools/patch_compiler.py (2.0p1a) and tools/patch_compiler_rw.py
# (2.0p1b..g), both imported from the BFBB decomp, then by
# tools/patch_compiler_ffcc.py (2.0p1h) and tools/patch_compiler_ffcc2.py
# (2.0p1i). Every step is guarded by the SHA-1 of its input and output. See
# docs/compiler_baseline.md.
BFBB_COMPILER = "GC/2.0p1g"
FFCC_COMPILER_H = "GC/2.0p1h"
JP_GAME_COMPILER = "GC/2.0p1i"
_compilers_dir = Path(config.compilers_path) if config.compilers_path else config.build_dir / "compilers"
config.custom_build_rules = [
    {
        "name": "patch_compiler",
        "command": "$python tools/patch_compiler.py $out",
        "description": "PATCH $out",
        "restat": True,
    },
    {
        "name": "patch_compiler_rw",
        "command": "$python tools/patch_compiler_rw.py $out",
        "description": "PATCH $out",
        "restat": True,
    },
    {
        "name": "patch_compiler_ffcc",
        "command": "$python tools/patch_compiler_ffcc.py $out",
        "description": "PATCH $out",
        "restat": True,
    },
    {
        "name": "patch_compiler_ffcc2",
        "command": "$python tools/patch_compiler_ffcc2.py $out",
        "description": "PATCH $out",
        "restat": True,
    },
]
config.custom_build_steps = {
    "pre-compile": [
        {
            "outputs": [_compilers_dir / "GC/2.0p1a" / "mwcceppc.exe"],
            "rule": "patch_compiler",
            "implicit": [
                Path("tools") / "patch_compiler.py",
                Path("tools") / "aliaspatch_link.py",
                Path("tools") / "aliaspatch_asm.py",
                Path("tools") / "aliaspatch_blob.py",
            ]
            + ([_compilers_dir] if config.compilers_path is None else []),
        },
        {
            "outputs": [_compilers_dir / BFBB_COMPILER / "mwcceppc.exe"],
            "rule": "patch_compiler_rw",
            "implicit": [
                _compilers_dir / "GC/2.0p1a" / "mwcceppc.exe",
                Path("tools") / "patch_compiler_rw.py",
                Path("tools") / "patch_compiler.py",
            ],
        },
        {
            "outputs": [_compilers_dir / FFCC_COMPILER_H / "mwcceppc.exe"],
            "rule": "patch_compiler_ffcc",
            "implicit": [
                _compilers_dir / BFBB_COMPILER / "mwcceppc.exe",
                Path("tools") / "patch_compiler_ffcc.py",
            ],
        },
        {
            "outputs": [_compilers_dir / JP_GAME_COMPILER / "mwcceppc.exe"],
            "rule": "patch_compiler_ffcc2",
            "implicit": [
                _compilers_dir / FFCC_COMPILER_H / "mwcceppc.exe",
                Path("tools") / "patch_compiler_ffcc2.py",
            ],
        },
    ]
}

mode = trailing_mode or args.mode

if mode == "configure":
    # GBA multiboot programs are part of the PAL build and progress report
    configure_gba(config, args.gba_binutils, args.gba_compilers)
    # Write build.ninja and objdiff.json
    generate_build(config)
elif mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + str(mode))
