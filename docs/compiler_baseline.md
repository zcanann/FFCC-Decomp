# Regional game compiler baseline

The Game library uses GC/2.5 for PAL and USA, and GC/2.0p1 for Japan.
SDK and middleware selections are independent. These are compatibility
baselines, not identification of the original retail compiler binaries.

## Provenance

The compiler bundle's `build/compilers/info.txt` describes GC/2.0p1 as a
patched compiler for BFBB's small-data and floating-point scheduling issues.
It reports the same version as GC/2.0: 2.4.7, build 92. Do not describe
GC/2.0p1 as a separately established retail compiler release.

The bundled `mwcceppc.exe` files are both 2,064,896 bytes. Their SHA-256 hashes:

| Bundle directory | SHA-256 |
| --- | --- |
| GC/2.0 | `b79ee3e358fe18d7b492c3400169efc1a9bc5dff1a120dcb025f7869ab772022` |
| GC/2.0p1 | `afb7fecaab5c3dff9541c41476d07bb2b79f90f90ed0f577fd9b0a1ededb0e11` |

They differ at three file offsets: `0xDFD4E` (01 to 00), `0x16FD86`
(D8 to 05), and `0x16FD8C` (02 to 07). The project uses the distributed
tool binary; it does not patch the compiler during builds.

## Evidence and limits

The initial audit compiled unchanged source with identical command-line flags,
changing only the compiler and output path. GC/2.0p1 improved all fourteen
residual floating-point creation-menu functions in Japan; those same functions
became worse in PAL and USA. Unpatched GC/2.0, GC/1.3.2, GC/2.6 and GC/2.7
did not produce that Japanese improvement. Six additional Japanese menu units
had 25 improving functions, five unchanged, and one declining; the USA control
had 26 declining and five unchanged. Character-fur, caravan-status and
ring-menu code independently supported the Japanese result.

The complete regional build then exposed source issues hidden by the Western
compiler's constant reuse. Chained collision-vector and mesh-bound assignments
recover the retail single load and store order. Reusing the default depth offset
in octree drawing recovers the retail comparison and call argument. These
ordinary source repairs preserve Western output without optimizer pragmas or
per-unit game compiler exceptions.

Against staging `3201a6755`, the regional baseline and those repairs add
45,824 exactly matched Japanese code bytes, 2,072 data bytes and 91 functions.
No unit loses exact code, data or function totals. The shop-menu fuzzy score
declines slightly, from 80.75341 to 80.74551; its partially reconstructed drawing
remains work in progress. PAL and USA scores are unchanged. All configured
source builds and all nine final DOL/GBA checksums pass. Retail fallback links
alone were not used to validate the changed source.

This establishes a useful regional compatibility choice. It does not establish
the provenance of the original compiler or explain every remaining mismatch.
Continue investigating types, layout, source expressions and linkage before
attributing residual differences to the compiler.
