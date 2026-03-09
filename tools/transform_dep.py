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
from typing import Optional, Tuple


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


def _is_escaped(text: str, idx: int) -> bool:
    """Return True when text[idx] is escaped by an odd run of backslashes."""
    backslashes = 0
    cur = idx - 1
    while cur >= 0 and text[cur] == "\\":
        backslashes += 1
        cur -= 1
    return (backslashes % 2) == 1


def _split_makefile_words(fragment: str) -> list[str]:
    """Split Makefile words by unescaped space or tab."""
    words = []
    cur = []

    for idx, char in enumerate(fragment):
        if char in {" ", "\t"} and not _is_escaped(fragment, idx):
            if cur:
                words.append("".join(cur))
                cur = []
            continue
        cur.append(char)

    if cur:
        words.append("".join(cur))

    return words


def _normalize_dependency_fragment(fragment: str) -> str:
    """Normalize all dependency words in a fragment."""
    if not fragment:
        return fragment

    words = _split_makefile_words(fragment)
    normalized_words = [_normalize_dep_path(word) for word in words if word]
    return " ".join(normalized_words)


def _split_first_line_target_and_deps(line: str) -> Optional[Tuple[str, str]]:
    """Split first depfile line into target and dependency fragment.

    Finds the first unescaped rule separator ":" while ignoring Windows
    drive-letter colons such as "C:/" or "Z:\\".
    """
    for idx, char in enumerate(line):
        if char != ":":
            continue

        if _is_escaped(line, idx):
            continue

        prev_char = line[idx - 1] if idx > 0 else ""
        next_char = line[idx + 1] if idx + 1 < len(line) else ""
        if prev_char.isalpha() and next_char in {"/", "\\"}:
            continue

        deps = line[idx + 1 :].lstrip()
        return line[:idx], deps

    return None


def _normalize_first_line(line: str) -> str:
    """Normalize target and inline dependencies on the first .d line."""
    parts = _split_first_line_target_and_deps(line)
    if parts is None:
        return _normalize_slashes(line)

    target, deps = parts
    normalized_target = _normalize_slashes(target)
    normalized_deps = _normalize_dependency_fragment(deps)
    if normalized_deps:
        return f"{normalized_target}: {normalized_deps}"
    return f"{normalized_target}:"


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
                normalized_line = _normalize_first_line(line_noeol[:-2] if has_continuation else line_noeol)
                if has_continuation:
                    out_text += normalized_line + " \\\n"
                else:
                    out_text += normalized_line + "\n"
            else:
                suffix = ""
                if has_continuation:
                    suffix = " \\"
                    path = line_noeol.lstrip()[:-2]
                else:
                    path = line_noeol.strip()
                if path:
                    path = _normalize_dependency_fragment(path)
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
