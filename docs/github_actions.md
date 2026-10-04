# GitHub Actions

The [Build workflow](../.github/workflows/build.yml) compiles and verifies PAL
(`GCCP01`), USA (`GCCE01`) and Japan (`GCCJGC`) separately. Each region builds
all configured source, the GameCube executable, and both GBA programs:

```sh
python configure.py --map --version GCCP01
ninja all_source progress build/GCCP01/report.json
```

Use the selected version in both commands. Source compilation includes
GameCube units not yet mapped into that region's split configuration. A full
matrix run requires three DOL and six GBA image checksum checks. PAL remains
the most mature matching target; USA and Japan retain partial recovered layouts
and retail fallbacks. Passing hashes verifies the chosen source/fallback link,
not 100% source recovery. Match and linkage claims are per region.

Linux builds use wibo 1.0.3, which includes the upstream
[signed 16-bit handle compatibility fix](https://github.com/decompals/wibo/commit/ec0486f77f0f00021e62b5fdd50ca6f8ef034085).
Older wibo builds can fail large regional links with "Can't read library file"
even when the object exists: Metrowerks sign-extends handles at `0x8000`.
This is a host compatibility issue; it requires no compiler or source tuning.

The pin also preserves sjiswrap compatibility with older MWCC releases. Wibo
1.2.0 returns null for the missing `FormatMessageA` export, which makes
sjiswrap reject those compilers during loading; see
[the upstream export fix](https://github.com/decompals/wibo/pull/139).
Before upgrading the wrapper, validate every configured compiler through
sjiswrap and the large USA/Japan links. Version 1.0.3 passes all 488 configured
GameCube source compilations and both regional DOL checksum checks on Linux.

## Private inputs

The job image is `ghcr.io/zcanann/ffcc-decomp-build:main`, maintained in the
private FFCC-Decomp-build repository. It contains only the required retail
inputs for the three regions, along with build dependencies. Each region has:

- `orig/<version>/sys/main.dol`
- `orig/<version>/gba/ffcc_cli.bin`
- `orig/<version>/gba/mgr00.bin`

The nine inputs are hash-verified when preparing the image. Build jobs copy
`/orig` into the workspace and run `sha1sum -c orig/SHA1SUMS` before configuring.
Refresh the private image when its inputs or dependencies change; ordinary
source commits reuse it. Keep both the build repository and package private,
and grant the source repository Read under the package's Manage Actions access.

The workflow pulls the image using its short-lived `GITHUB_TOKEN` with
`packages: read`. Checkout uses `persist-credentials: false`. Private-image jobs
run for pushes and same-repository pull requests; fork pull requests do not run
against private inputs. Review external changes before bringing them onto a
trusted repository branch. Do not execute fork code with these inputs through
`pull_request_target`.

## Compiler preparation and caching

A single `gba-compilers` job prepares `cc1`, `cc1plus`, `gcc2-cpp` and
`old_agbcc`. The first three are built from the pinned historical tree only
when absent from cache or when `gba/tools/build_cc1plus.sh` changes. The build
checks its Zig 0.13.0 download hash; `old_agbcc` comes from the private image.
A one-day compiler artifact supplies all three regional jobs, which restore
executable permissions and check the tools before use. See
[the toolchain notes](../gba/toolchain.md) for a local rebuild.

Actions caches contain tools only. Do not cache or upload `orig/`, retail split
objects, extracted assets, or the entire `build/` tree. The workflow uploads the
compiler tools and a report/map allowlist, with each region's reports named
`<version>_report` and maps named `<version>_maps`. Reports are generated from
`build/<version>/report.json`.

`tools/report.py` runs objdiff separately for the GameCube executable and each
GBA image, then combines the unchanged unit results. Symbol deduplication stays
within each linked image: independent implementations of names such as `memcpy`
must count in each executable, while duplicate weak functions within one image
remain deduplicated. Aggregate and category measures follow objdiff's report
formulas; this changes counting scope, not matching or source-linkage claims.

## Local validation

Prepare the selected region's inputs and GBA dependencies as described in
[README.md](../README.md) and [gba/README.md](../gba/README.md). Configure and
run the source/progress commands above for each region affected by a change;
shared source or build-tool changes require all three. `build.ninja` and
`objdiff.json` describe the current configuration, so reconfigure between local
regional builds or use separate worktrees. Keep each original input and expected
checksum tied to its region throughout validation.
