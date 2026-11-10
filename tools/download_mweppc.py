#!/usr/bin/env python3
"""Install a compiler built by doldecomp/mweppc from one of its releases.

mweppc builds the GameCube compilers from the decompiled CodeWarrior source,
including versions with no original binary that model a game's retail
compiler (see docs/compiler_baseline.md). Its release archive holds one
directory per compiler version (2.0/, 2.0p3/, ...), each with mwcceppc.exe
and lmgr326b.dll. The version is taken from the output path: GC/<v> is
installed from the archive's <v>/ directory. The archive is checked against
its pinned SHA-256 before anything is written; an unchanged compiler is left
untouched.

    python tools/download_mweppc.py <compilers>/GC/2.0p3/mwcceppc.exe
"""
import hashlib
import io
import os
import sys
import urllib.error
import urllib.request
import zipfile
from pathlib import Path

FILES = ("mwcceppc.exe", "lmgr326b.dll")

# (archive URL, SHA-256 of the archive) of the first doldecomp/mweppc release
# that carries every version below. None until that release exists.
RELEASE = None
VERSIONS = ("GC/2.0p3",)

NO_RELEASE = (
    "{version} comes from doldecomp/mweppc, which has no release carrying it "
    "yet: set RELEASE in tools/download_mweppc.py to the release archive's URL "
    "and SHA-256 once it is published."
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


def install(compilers: Path, version: str) -> None:
    if version not in VERSIONS:
        sys.exit(f"{version} is not an mweppc compiler (expected one of {', '.join(VERSIONS)})")
    if RELEASE is None:
        sys.exit(NO_RELEASE.format(version=version))
    url, sha256 = RELEASE
    print(f"Downloading {url}")
    data = fetch(url)
    actual = hashlib.sha256(data).hexdigest()
    if actual != sha256:
        sys.exit(f"{url} has SHA-256 {actual}, expected {sha256}")
    dst_dir = compilers / version
    dst_dir.mkdir(parents=True, exist_ok=True)
    member_dir = version.split("/", 1)[1]
    with zipfile.ZipFile(io.BytesIO(data)) as archive:
        for name in FILES:
            content = archive.read(f"{member_dir}/{name}")
            dst = dst_dir / name
            if dst.exists() and dst.read_bytes() == content:
                continue
            tmp = dst.with_suffix(".tmp")
            tmp.write_bytes(content)
            os.chmod(tmp, 0o755)
            tmp.replace(dst)
    print(f"{version} installed in {dst_dir}")


if __name__ == "__main__":
    if len(sys.argv) != 2 or not sys.argv[1].endswith("mwcceppc.exe"):
        sys.exit("usage: download_mweppc.py <compilers>/GC/<version>/mwcceppc.exe")
    exe = Path(sys.argv[1])
    install(exe.parents[2], f"{exe.parent.parent.name}/{exe.parent.name}")
