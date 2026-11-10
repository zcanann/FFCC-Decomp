#!/usr/bin/env python3
"""Install GC/2.5a, the PAL and USA game compiler, from a doldecomp/mweppc release.

GC/2.5a is mweppc's GC_2_5a: GameCube 2.5 built from the decompiled compiler
source with one alias-analysis rule that FFCC's PAL and USA code needs (see
docs/compiler_baseline.md). mweppc's release archive holds one directory per
compiler version (2.0/, 2.5/, 2.5a/, ...), each with mwcceppc.exe and
lmgr326b.dll. The archive is checked against its pinned SHA-256 before
anything is written; an unchanged compiler is left untouched.

    python tools/download_mweppc.py <compilers dir | <compilers>/GC/2.5a/mwcceppc.exe>
"""
import hashlib
import io
import os
import sys
import urllib.error
import urllib.request
import zipfile
from pathlib import Path

VERSION = "GC/2.5a"
MEMBER_DIR = "2.5a"
FILES = ("mwcceppc.exe", "lmgr326b.dll")

# (archive URL, SHA-256 of the archive) of the first doldecomp/mweppc release
# that carries GC_2_5a. None until that release exists.
RELEASE = None

NO_RELEASE = (
    "GC/2.5a comes from doldecomp/mweppc's GC_2_5a "
    "(https://github.com/doldecomp/mweppc/pull/3), which has no release yet: "
    "set RELEASE in tools/download_mweppc.py to the release archive's URL and "
    "SHA-256 once it is published."
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


def install(compilers: Path) -> None:
    if RELEASE is None:
        sys.exit(NO_RELEASE)
    url, sha256 = RELEASE
    print(f"Downloading {url}")
    data = fetch(url)
    actual = hashlib.sha256(data).hexdigest()
    if actual != sha256:
        sys.exit(f"{url} has SHA-256 {actual}, expected {sha256}")
    dst_dir = compilers / VERSION
    dst_dir.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(io.BytesIO(data)) as archive:
        for name in FILES:
            content = archive.read(f"{MEMBER_DIR}/{name}")
            dst = dst_dir / name
            if dst.exists() and dst.read_bytes() == content:
                continue
            tmp = dst.with_suffix(".tmp")
            tmp.write_bytes(content)
            os.chmod(tmp, 0o755)
            tmp.replace(dst)
    print(f"{VERSION} installed in {dst_dir}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: download_mweppc.py <compilers dir | <compilers>/GC/2.5a/mwcceppc.exe>")
    arg = Path(sys.argv[1])
    root = arg.parents[2] if arg.name.endswith(".exe") else arg
    install(root)
