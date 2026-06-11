#!/usr/bin/env bash
# Set up an isolated grind worktree for one decomp unit with a fast APFS
# copy-on-write clone of the main build tree (clones 3.7G in ~seconds, mtimes
# preserved so ninja stays incremental). Branch + dir are derived from the unit.
#
# Usage: tools/setup_grind_worktree.sh <unit> [branch] [emp]
#   unit   bare unit name, e.g. partyobj  (maps to src/<unit>.cpp, main/<unit>)
#   branch optional explicit branch name (default: pr/<unit>/emp<emp>)
#   emp    optional employee tag for default branch name (default: 2)
set -euo pipefail

UNIT="${1:?usage: setup_grind_worktree.sh <unit> [branch] [emp]}"
EMP="${3:-2}"
BRANCH="${2:-pr/${UNIT}/emp${EMP}}"

REPO="$(cd "$(dirname "$0")/.." && pwd)"
DIR="${REPO%/*}/ffcc-grind-emp${EMP}-${UNIT}"

if [ -e "$DIR" ]; then
  echo "worktree dir already exists: $DIR" >&2
  exit 1
fi

git -C "$REPO" worktree add -b "$BRANCH" "$DIR" main >/dev/null
# The original game image lives under orig/ and is untracked (user-provided).
# Symlink the individual file the build needs (never replace the orig/<ver> dir).
mkdir -p "$DIR/orig/GCCP01/sys"
ln -sf "$REPO/orig/GCCP01/sys/main.dol" "$DIR/orig/GCCP01/sys/main.dol"
# APFS copy-on-write clone of the build tree, preserving mtimes for incremental ninja.
cp -cRp "$REPO/build" "$DIR/build"
# A fresh worktree re-triggers ninja's one-time prebuilt-tool download rules
# (sjiswrap, binutils, ...). download_tool.py always hits GitHub's releases CDN, which
# is intermittently down (504s) — so make it offline-safe: skip when the output already
# exists (the binaries are COW-cloned and valid). assume-unchanged keeps this local edit
# out of git so it can never leak into a PR.
python3 - "$DIR/tools/download_tool.py" <<'PY'
import sys
p=sys.argv[1]; s=open(p).read()
if "Using cached" not in s:
    a="    output = Path(args.output)\n"
    s=s.replace(a, a +
        "    if output.exists() and ((output.is_dir() and any(output.iterdir())) or (output.is_file() and output.stat().st_size > 0)):\n"
        "        print(f\"Using cached {output}\")\n"
        "        return\n", 1)
    open(p,"w").write(s)
PY
( cd "$DIR" && git update-index --assume-unchanged tools/download_tool.py )
touch -t 202501010000 "$DIR/tools/download_tool.py"
( cd "$DIR" && python3 configure.py --version GCCP01 >/dev/null )
# Make build.ninja newest so ninja's configure generator doesn't loop ("manifest still
# dirty") on the fresh checkout's mtimes.
touch "$DIR/build.ninja"
( cd "$DIR" && ninja >/dev/null 2>&1 ) || { echo "build failed: $DIR" >&2; exit 1; }
echo "ready: $DIR  (branch $BRANCH)"
