#!/usr/bin/env python3
"""Download arm-none-eabi binutils (as, ld, objcopy, objdump) from the xPack release."""

import argparse
import io
import platform
import shutil
import sys
import tarfile
import urllib.request
import zipfile
from pathlib import Path

VERSION = "15.2.1-1.1"
BASE_URL = f"https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v{VERSION}"
TOOLS = ("as", "ld", "objcopy", "objdump", "nm", "readelf")


def archive_name() -> str:
    system = platform.system()
    machine = platform.machine().lower()
    if system == "Windows":
        return f"xpack-arm-none-eabi-gcc-{VERSION}-win32-x64.zip"
    if system == "Linux":
        arch = "arm64" if machine in ("aarch64", "arm64") else "x64"
        return f"xpack-arm-none-eabi-gcc-{VERSION}-linux-{arch}.tar.gz"
    if system == "Darwin":
        arch = "arm64" if machine == "arm64" else "x64"
        return f"xpack-arm-none-eabi-gcc-{VERSION}-darwin-{arch}.tar.gz"
    sys.exit(f"Unsupported platform: {system}")


def wanted(name: str) -> bool:
    # Keep bin/arm-none-eabi-<tool>[.exe] plus any shared libraries they need.
    parts = name.split("/")
    if len(parts) < 3 or parts[1] not in ("bin", "lib", "libexec"):
        return False
    leaf = parts[-1]
    if parts[1] == "bin":
        stem = leaf[:-4] if leaf.endswith(".exe") else leaf
        return stem in {f"arm-none-eabi-{t}" for t in TOOLS} or leaf.endswith(".dll")
    return leaf.endswith((".dll", ".so")) or ".so." in leaf or leaf.endswith(".dylib")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("output", type=Path, help="output directory")
    args = parser.parse_args()

    stamp = args.output / ".version"
    if stamp.is_file() and stamp.read_text().strip() == VERSION:
        return

    name = archive_name()
    print(f"Downloading {name}")
    with urllib.request.urlopen(f"{BASE_URL}/{name}") as response:
        data = response.read()

    if args.output.exists():
        shutil.rmtree(args.output)
    args.output.mkdir(parents=True)

    if name.endswith(".zip"):
        with zipfile.ZipFile(io.BytesIO(data)) as archive:
            for info in archive.infolist():
                if info.is_dir() or not wanted(info.filename):
                    continue
                dest = args.output / "/".join(info.filename.split("/")[1:])
                dest.parent.mkdir(parents=True, exist_ok=True)
                dest.write_bytes(archive.read(info))
    else:
        with tarfile.open(fileobj=io.BytesIO(data)) as archive:
            for member in archive.getmembers():
                if not (member.isfile() or member.issym()) or not wanted(member.name):
                    continue
                member.name = "/".join(member.name.split("/")[1:])
                archive.extract(member, args.output)

    stamp.write_text(VERSION)


if __name__ == "__main__":
    main()
