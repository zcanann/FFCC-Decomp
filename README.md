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

Fortunately, the EN build contains a debug symbol file, and the PAL version contains a release symbol file (although for a different build). This has made the decompilation process very easy to match the original source code incredibly closely. These symbols allowed us to recover exact function and class names, as well as all parameters to each function, and class hierarchies.

**⚠️ Assets are not bundled with this repository. You must obtain these on your own.⚠️ **

Contribution Guide
-------------

Coming soon.

Remaining Work
-------------
Aside from the obvious remaining work of decompiling all code and data, this section of the readme is dedicated to tracking known issues or cleanup tasks that are not directly tied to progress.

# Unmapped Splits
These two seem to cause the DTK template configuration to completely hang:
os/OSStopwatch.c:
	.text       start:0x80180814 end:0x80180970
	
os/OSSync.c:
	.text       start:0x80180970 end:0x801809F4

These I have not entirely figured out the boundaries for:

TRK_MINNOW_DOLPHIN/main.c:
	.text       start:0x801af2b0 end:0x801af5fc

Runtime/PPCEABI/H/__init_cpp_exceptions.p:
	.text       start:0x801b063c end:0x801b06b8
	
os/OSError.c:
	.text       start:0x8017dd68 end:0x80000000

os/OSFatal.c:
	.text       start:0x80000000 end:0x80000000

os/OSFont.c:
	.text       start:0x80000000 end:0x80000000

ax/AXProf.c:
	.text       start:0x80193E28 end:0x80193E70

# EN & JPN Versions

The EN & JPN versions are deliberately being left for last. However, if someone wishes to begin this effort early, this is more than welcome.

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

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

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
