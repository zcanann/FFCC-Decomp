#!/usr/bin/env python3
"""Install a compiler built from PrimeDecomp/mwcc-tools' gc2 sources.

mwcc-tools' gc2/ builds the GameCube 2.x compilers from the decompiled
CodeWarrior source, including versions with no original binary that model a
game's retail compiler (see docs/compiler_baseline.md). The version is taken
from the output path: <compilers>/GC/<v>/mwcceppc.exe.

mwcc-tools does not publish these compilers yet, so RELEASE is unset. Until it
is, a compiler that is already in place is kept as it is; build one with
mwcc-tools (in gc2/: `python configure.py --version <name> && ninja`) and copy
build/<name>/clang/mwcceppc.exe to the output path. Once RELEASE is set, the
archive is checked against its pinned SHA-256 before anything is written, and
an unchanged compiler is left untouched.

    python tools/download_mwcc_tools.py <compilers>/GC/2.5ffcc/mwcceppc.exe
"""
import hashlib
import io
import os
import sys
import urllib.error
import urllib.request
import zipfile
from pathlib import Path

# FFCC compiler version -> its name in mwcc-tools' gc2/config
VERSIONS = {
    "GC/2.5ffcc": "GC_2_5ffcc",
    "GC/2.0ffcc": "GC_2_0ffcc",
}

# (archive URL, SHA-256 of the archive) of the first PrimeDecomp/mwcc-tools
# release that carries the compilers above, with one directory per gc2 name
# holding mwcceppc.exe. None until that release exists.
RELEASE = None

NO_RELEASE = (
    "{version} is {name} of PrimeDecomp/mwcc-tools' gc2, which no mwcc-tools "
    "release carries yet. Build it there (in gc2/: python configure.py "
    "--version {name} && ninja) and copy build/{name}/clang/mwcceppc.exe to "
    "{dst}, or set RELEASE in tools/download_mwcc_tools.py to a release "
    "archive's URL and SHA-256 once one is published."
)


def fetch(url: str) -> bytes:
    request = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    try:
        with urllib.request.urlopen(request) as response:
            return response.read()
    except urllib.error.URLError as e:
        if "CERTIFICATE_VERIFY_FAILED" not in str(e):
            raise
        import certifi
        import ssl

        context = ssl.create_default_context(cafile=certifi.where())
        with urllib.request.urlopen(request, context=context) as response:
            return response.read()


def install(dst: Path, version: str) -> None:
    name = VERSIONS.get(version)
    if name is None:
        sys.exit(f"{version} is not an mwcc-tools compiler (expected one of {', '.join(VERSIONS)})")
    if RELEASE is None:
        if dst.exists():
            print(f"{version}: keeping {dst} (mwcc-tools has no release to check it against)")
            return
        sys.exit(NO_RELEASE.format(version=version, name=name, dst=dst))
    url, sha256 = RELEASE
    print(f"Downloading {url}")
    data = fetch(url)
    actual = hashlib.sha256(data).hexdigest()
    if actual != sha256:
        sys.exit(f"{url} has SHA-256 {actual}, expected {sha256}")
    with zipfile.ZipFile(io.BytesIO(data)) as archive:
        content = archive.read(f"{name}/{dst.name}")
    if dst.exists() and dst.read_bytes() == content:
        return
    dst.parent.mkdir(parents=True, exist_ok=True)
    tmp = dst.with_suffix(".tmp")
    tmp.write_bytes(content)
    os.chmod(tmp, 0o755)
    tmp.replace(dst)
    print(f"{version} installed in {dst.parent}")


if __name__ == "__main__":
    if len(sys.argv) != 2 or not sys.argv[1].endswith("mwcceppc.exe"):
        sys.exit("usage: download_mwcc_tools.py <compilers>/GC/<version>/mwcceppc.exe")
    exe = Path(sys.argv[1])
    install(exe, f"{exe.parent.parent.name}/{exe.parent.name}")
