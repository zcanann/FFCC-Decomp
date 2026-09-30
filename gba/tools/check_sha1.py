#!/usr/bin/env python3
"""Compare a file's SHA-1 against the expected hash and touch a stamp on success."""

import hashlib
import sys
from pathlib import Path


def main() -> None:
    path, expected, stamp = Path(sys.argv[1]), sys.argv[2].lower(), Path(sys.argv[3])
    actual = hashlib.sha1(path.read_bytes()).hexdigest()
    if actual != expected:
        sys.exit(f"{path}: SHA-1 mismatch\n  expected {expected}\n  actual   {actual}")
    print(f"{path}: OK")
    stamp.write_text(actual + "\n")


if __name__ == "__main__":
    main()
