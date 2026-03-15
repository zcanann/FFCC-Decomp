Final Fantasy Crystal Chronicles Decompilation
[![Build Status]][actions] [![Progress]][progress site] [![DOL Progress]][progress site]
===============================
[Build Status]: https://github.com/zcanann/FFCC-Decomp/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/zcanann/FFCC-Decomp/actions/workflows/build.yml
[Progress]: https://decomp.dev/zcanann/FFCC-Decomp.svg?mode=shield&measure=code&label=Code&category=all
[DOL Progress]: https://decomp.dev/zcanann/FFCC-Decomp.svg?mode=shield&measure=code&label=DOL&category=dol
[progress site]: https://decomp.dev/zcanann/FFCC-Decomp
This is the decompilation for Final Fantasy Crystal Chronicles for the Nintendo GameCube.

There are 3 versions of this game: JP, EN, and PAL (EU).

Fortunately, the EN build contains a debug symbol file, and the PAL version contains a release symbol file (although for a different build). These have greatly simplified the decompilation process for FFCC. These symbols allowed us to recover exact function and class names, as well as all parameters to each function, and class hierarchies.

**⚠️ Assets are not bundled with this repository. You must obtain these on your own. ⚠️**

# Contribution Guide

## Beginners Contribution Guide
The most direct way to contribute with minimal setup is to pick any non-perfect section from [the decomp tracker](https://decomp.dev/zcanann/FFCC-Decomp), then improve overall progress (code match, data match, or linkage).

Refer to the sections on building and diffing. Once set up, modify `.cpp`/`.h` files and, when needed, `configure.py` flags to improve output.

Small regressions can be acceptable when outweighed by larger gains in another category (for example, a minor code-byte loss with substantial data or linkage progress).

If progress appears stuck at 0% for a unit/function, check linkage and declarations first. Common symptoms include unexpected Metrowerks mangled names, missing `extern "C"`, or missing special pragmas.

Avoid leaving hardcoded offset-based member access (for example `(this + 0x28)`) in final contributions. Prefer proper types and named data members, even if the offset form currently matches.

## Advanced Contribution Guide
For experienced reverse-engineers, there are still quite a few harder tasks remaining.

### Unmapped Splits
There are several splits that are still unmapped, even though we have access to the PAL game.MAP symbols from a stale build. There are only a few remaining, so this is a pretty small effort, but it requires reverse-engineering precision.

The stale PAL MAP and the current PAL symbol/split state do not perfectly agree anymore. At the moment:

- `TRK_MINNOW_DOLPHIN/main_gdev.c` is already mapped at `0x801AF2B0..0x801AF5FC`.
- `os/OSError.c` is already mapped at `0x8017DD68..0x8017E2E8`.
- `os/OSFont.c` is already mapped at `0x8017E2E8..0x8017E340`.
- `ax/AXProf.c` is already mapped at `0x80193E28..0x80193E70`.

Those are no longer open split-boundary issues in `config/GCCP01/splits.txt`.

These two seem to cause the DTK template configuration to completely hang:
os/OSStopwatch.c:
	.text       start:0x80180814 end:0x80180970
	
os/OSSync.c:
	.text       start:0x80180970 end:0x801809F4

The current repo pins decomp-toolkit to `v1.7.4`. Upstream decomp-toolkit has since added analysis controls that are likely relevant here:

- `v1.8.0` added `skip_cfa_ranges` to `config.yml` for problematic ranges that prevent analysis from finishing.
- `v1.8.3` is the current latest release and includes additional extab handling fixes.

If the framework/tooling gets updated later, this `0x80180814..0x801809F4` range is the first place to retry.

`os/OSFatal.c` is still unresolved in the current PAL split state, but the old PAL MAP range from the stale build should not be trusted as-is. The current PAL symbol set does not currently expose a verified text boundary for it, and `configure.py` still lists the source even though no corresponding unit is generated in `build/GCCP01/config.json`.

### EN & JPN Versions

The EN & JPN versions are deliberately being left for last. However, if someone wishes to begin this effort early, this is more than welcome.

# Dependencies

## Windows

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

## macOS

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

## Linux

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

## Building

- Clone the repository:

  ```sh
  git clone https://github.com/my/repo.git
  ```

- Copy your game's disc image to `orig/GAMEID`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `GAMEID` (USA), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

## Diffing

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
