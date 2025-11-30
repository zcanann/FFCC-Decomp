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
import sys
from pathlib import Path
from typing import Any, Dict, List

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
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
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
args = parser.parse_args()

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
config.dtk_tag = "v1.7.4"
config.objdiff_tag = "v3.4.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.0-beta.5"

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
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
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
cflags_game = [
    *cflags_base
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
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
    "-inline deferred"
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


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "objects": [
            Object(NonMatching, "pppFovAdjustMatrix.cpp"),
            Object(NonMatching, "ref.cpp"),
            Object(NonMatching, "vector.cpp"),
        ]
    },
    DolphinLib(
        "base",
        [
            Object(NonMatching, "base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(NonMatching, "os/__start.c"),
            Object(NonMatching, "os/__ppc_eabi_init.cpp"),
            Object(NonMatching, "os/OS.c"),
            Object(NonMatching, "os/OSAddress.c"),
            Object(NonMatching, "os/OSAlarm.c"),
            Object(NonMatching, "os/OSAlloc.c"),
            Object(NonMatching, "os/OSArena.c"),
            Object(NonMatching, "os/OSAudioSystem.c"),
            Object(NonMatching, "os/OSCache.c"),
            Object(NonMatching, "os/OSContext.c"),
            Object(NonMatching, "os/OSError.c"),
            Object(NonMatching, "os/OSFatal.c"),
            Object(NonMatching, "os/OSFont.c"),
            Object(NonMatching, "os/OSInterrupt.c"),
            Object(NonMatching, "os/OSLink.c"),
            Object(NonMatching, "os/OSMemory.c"),
            Object(NonMatching, "os/OSMessage.c"),
            Object(NonMatching, "os/OSMutex.c"),
            Object(NonMatching, "os/OSReboot.c"),
            Object(NonMatching, "os/OSReset.c"),
            Object(NonMatching, "os/OSResetSW.c"),
            Object(NonMatching, "os/OSRtc.c"),
            Object(NonMatching, "os/OSSemaphore.c"),
            Object(NonMatching, "os/OSStopwatch.c"),
            Object(NonMatching, "os/OSSync.c"),
            Object(NonMatching, "os/OSThread.c"),
            Object(NonMatching, "os/OSTime.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(NonMatching, "exi/EXIBios.c"),
            Object(NonMatching, "exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(NonMatching, "si/SIBios.c"),
            Object(NonMatching, "si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(NonMatching, "db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "mtx/mtx.c"),
            Object(NonMatching, "mtx/mtxvec.c"),
            Object(NonMatching, "mtx/mtx44.c"),
            Object(NonMatching, "mtx/mtx44vec.c"),
            Object(NonMatching, "mtx/vec.c"),
            Object(NonMatching, "mtx/quat.c"),
            Object(NonMatching, "mtx/psmtx.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(NonMatching, "dvd/dvd.c"),
            Object(NonMatching, "dvd/dvderror.c"),
            Object(NonMatching, "dvd/dvdFatal.c"),
            Object(NonMatching, "dvd/dvdfs.c"),
            Object(NonMatching, "dvd/dvdidutils.c"),
            Object(NonMatching, "dvd/dvdlow.c"),
            Object(NonMatching, "dvd/dvdqueue.c"),
            Object(NonMatching, "dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "vi/gpioexi.c"),
            Object(NonMatching, "vi/i2c.c"),
            Object(NonMatching, "vi/initphilips.c"),
            Object(NonMatching, "vi/vi.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(NonMatching, "pad/Padclamp.c"),
            Object(NonMatching, "pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(NonMatching, "ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "ar/ar.c"),
            Object(NonMatching, "ar/arq.c"),
        ],
    ),
    DolphinLib(
        "ax",
        [
            Object(NonMatching, "ax/AX.c"),
            Object(NonMatching, "ax/AXAlloc.c"),
            Object(NonMatching, "ax/AXAux.c"),
            Object(NonMatching, "ax/AXCL.c"),
            Object(NonMatching, "ax/AXOut.c"),
            Object(NonMatching, "ax/AXProf.c"),
            Object(NonMatching, "ax/AXSPB.c"),
            Object(NonMatching, "ax/AXVPB.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(NonMatching, "axfx/axfx.c"),
            Object(NonMatching, "axfx/chorus.c"),
            Object(NonMatching, "axfx/delay.c"),
            Object(NonMatching, "axfx/reverb_hi.c"),
            Object(NonMatching, "axfx/reverb_hi_4ch.c"),
            Object(NonMatching, "axfx/reverb_std.c"),
        ],
    ),
    DolphinLib(
        "mix",
        [
            Object(NonMatching, "mix/mix.c"),
        ],
    ),
    DolphinLib(
        "axart",
        [
            Object(NonMatching, "axart/axart.c"),
            Object(NonMatching, "axart/axart3d.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(NonMatching, "dsp/dsp.c"),
            Object(NonMatching, "dsp/dsp_debug.c"),
            Object(NonMatching, "dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(NonMatching, "card/CARDBios.c"),
            Object(NonMatching, "card/CARDBlock.c"),
            Object(NonMatching, "card/CARDCheck.c"),
            Object(NonMatching, "card/CARDCreate.c"),
            Object(NonMatching, "card/CARDDelete.c"),
            Object(NonMatching, "card/CARDDir.c"),
            Object(NonMatching, "card/CARDFormat.c"),
            Object(NonMatching, "card/CARDMount.c"),
            Object(NonMatching, "card/CARDNet.c"),
            Object(NonMatching, "card/CARDOpen.c"),
            Object(NonMatching, "card/CARDRdwr.c"),
            Object(NonMatching, "card/CARDRead.c"),
            Object(NonMatching, "card/CARDStat.c"),
            Object(NonMatching, "card/CARDUnlock.c"),
            Object(NonMatching, "card/CARDWrite.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "gx/GXAttr.c"),
            Object(NonMatching, "gx/GXBump.c"),
            Object(NonMatching, "gx/GXDisplayList.c"),
            Object(NonMatching, "gx/GXFifo.c"),
            Object(NonMatching, "gx/GXFrameBuf.c"),
            Object(NonMatching, "gx/GXGeometry.c"),
            Object(NonMatching, "gx/GXInit.c"),
            Object(NonMatching, "gx/GXLight.c"),
            Object(NonMatching, "gx/GXMisc.c"),
            Object(NonMatching, "gx/GXPerf.c"),
            Object(NonMatching, "gx/GXPixel.c"),
            Object(NonMatching, "gx/GXSave.c"),
            Object(NonMatching, "gx/GXStubs.c"),
            Object(NonMatching, "gx/GXTev.c"),
            Object(NonMatching, "gx/GXTexture.c"),
            Object(NonMatching, "gx/GXTransform.c"),
            Object(NonMatching, "gx/GXVerifRAS.c"),
            Object(NonMatching, "gx/GXVerifXF.c"),
            Object(NonMatching, "gx/GXVerify.c"),
            Object(NonMatching, "gx/GXVert.c"),
        ],
    ),
    #DolphinLib(
        #"gba",
        #[
            # Object(Matching, "gba/GBA.c"),
            #Object(Matching, "gba/GBAGetProcessStatus.c"),
            #Object(Matching, "gba/GBAJoyBoot.c"),
            #Object(Matching, "gba/GBAKey.c"),
            #Object(Matching, "gba/GBARead.c"),
            #Object(Matching, "gba/GBAWrite.c"),
            #Object(Matching, "gba/GBAXfer.c"),
        #],
    #),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "Runtime.PPCEABI.H/__va_arg.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/CPlusLibPPC.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/GCN_mem_alloc.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/New.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/NMWException.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/ptmf.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/runtime.c"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": config.linker_version,
        "cflags": cflags_msl,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/abort_exit.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/alloc.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/ansi_files.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/ansi_fp.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/buffer_io.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/critical_regions_gamecube.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/ctype.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/direct_io.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/extras.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_acos.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_atan2.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_fmod.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_pow.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_rem_pio2.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/e_sqrt.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/file_io.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/FILE_POS.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/k_cos.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/k_rem_pio2.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/k_sin.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/k_tan.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/math_ppc.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/mbstring.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/mem.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/mem_funcs.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/misc_io.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/printf.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/rand.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/signal.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/string.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_atan.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/s_copysign.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_cos.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_floor.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_frexp.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_ldexp.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_modf.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_sin.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/s_tan.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/uart_console_io_gcn.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/wchar_io.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/w_acos.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/w_atan2.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/w_fmod.c"),
            Object(Matching, "MSL_C/PPCEABI/bare/H/w_pow.c"),
            Object(NonMatching, "MSL_C/PPCEABI/bare/H/w_sqrt.c"),
        ],
    },
    {
        "lib": "OdemuExi2",
        "mw_version": "GC/1.3",
        "cflags": cflags_odemuexi,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "OdemuExi2/DebuggerDriver.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.3",
        "cflags": cflags_trk,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/CircleBuffer.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/main.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msg.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msghndlr.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mslsupp.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/MWCriticalSection_gc.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/MWTrace.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/notify.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/serpoll.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/support.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/target_options.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targimpl.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targsupp.s"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/UDP_Stubs.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/usr_put.c"),
        ],
    },
    {
        "lib": "amcstubs",
        "mw_version": config.linker_version,
        "cflags": cflags_amcstub,
        "objects": [
            Object(Matching, "amcstubs/AmcExi2Stubs.c"),
        ],
    },
    {
        "lib": "odenotstub",
        "mw_version": config.linker_version,
        "cflags": cflags_odenotstub,
        "objects": [
            Object(Matching, "odenotstub/odenotstub.c"),
        ],
    },
    {
        "lib": "thp",
        "mw_version": "GC/1.2.5",
        "cflags": cflags_thp,
        "objects": [
            Object(NonMatching, "thp/THPDec.c"),
            Object(NonMatching, "thp/THPAudio.c"),
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
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
