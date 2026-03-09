#!/usr/bin/env python3

###
# Transforms .d files, converting Windows paths to Unix paths.
# Allows usage of the mwcc -MMD flag on platforms other than Windows.
#
# Usage:
#   python3 tools/transform_dep.py build/src/file.d build/src/file.d
#
# If changes are made, please submit a PR to
# https://github.com/encounter/dtk-template
###

import argparse
import os
from platform import uname


_MAKE_ESCAPE_CHARS = {" ", "#", "$", ":"}


def _winedevices_path() -> str:
    wineprefix = os.environ.get("WINEPREFIX")
    if not wineprefix:
        wineprefix = os.path.join(os.path.expanduser("~"), ".wine")
    return os.path.join(wineprefix, "dosdevices")


def in_wsl() -> bool:
    release = uname().release.lower()
    return (
        "microsoft" in release
        or "wsl" in release
        or "WSL_DISTRO_NAME" in os.environ
    )


def _normalize_dep_path(path: str) -> str:
    """Normalize a single dependency path from Wine format to host format."""
    if not path:
        return path

    # Normalize slash style while preserving Makefile escape sequences.
    normalized = _normalize_slashes(path)

    # Only perform drive-letter mapping for absolute Windows paths (e.g. Z:/..., C:/...).
    # Drive-relative paths like C:foo/bar should remain drive-relative.
    if len(normalized) < 3 or normalized[1] != ":" or normalized[2] != "/":
        return normalized

    drive = normalized[0].lower()
    drive_path = normalized[2:]

    if drive == "z":
        # Shortcut for Wine's Z: mapping to host root.
        return drive_path

    if in_wsl():
        return os.path.join("/mnt", drive, drive_path.lstrip("/"))

    # Resolve drive mappings via $WINEPREFIX/dosdevices on non-WSL hosts.
    winedevices = _winedevices_path()
    return os.path.realpath(os.path.join(winedevices, f"{drive}:{drive_path}"))


def _normalize_slashes(path: str) -> str:
    """Convert Windows path separators while preserving Makefile escapes."""
    out = []
    idx = 0
    while idx < len(path):
        char = path[idx]
        if char == "\\" and idx + 1 < len(path):
            next_char = path[idx + 1]
            if next_char in _MAKE_ESCAPE_CHARS:
                out.append(char)
                out.append(next_char)
                idx += 2
                continue
            out.append("/")
            idx += 1
            continue
        out.append(char)
        idx += 1
    return "".join(out)


def import_d_file(in_file: str) -> str:
    out_text = ""

    with open(in_file) as file:
        for idx, line in enumerate(file):
            line_noeol = line.rstrip("\r\n")
            has_continuation = line_noeol.endswith(" \\")
            if idx == 0:
                if has_continuation:
                    out_text += _normalize_slashes(line_noeol[:-2]) + " \\\n"
                else:
                    out_text += _normalize_slashes(line_noeol) + "\n"
            else:
                suffix = ""
                if has_continuation:
                    suffix = " \\"
                    path = line_noeol.lstrip()[:-2]
                else:
                    path = line_noeol.strip()
                if path:
                    path = _normalize_dep_path(path)
                    out_text += "\t" + path + suffix + "\n"
                else:
                    out_text += suffix + "\n"

    return out_text


def main() -> None:
    parser = argparse.ArgumentParser(
        description="""Transform a .d file from Wine paths to normal paths"""
    )
    parser.add_argument(
        "d_file",
        help="""Dependency file in""",
    )
    parser.add_argument(
        "d_file_out",
        help="""Dependency file out""",
    )
    args = parser.parse_args()

    output = import_d_file(args.d_file)

    with open(args.d_file_out, "w", encoding="UTF-8") as f:
        f.write(output)


if __name__ == "__main__":
    main()
