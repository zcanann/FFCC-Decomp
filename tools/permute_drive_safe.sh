#!/bin/bash
# Safe register-permuter driver. Usage:
#   bash tools/permute_drive_safe.sh main/<unit> src/<unit>.cpp pr/<branch> <Func1> <Func2> ...
# Env: SEEDS (default 25), ITERS (default 30). Run from a dedicated worktree;
# one driver per .cpp file at a time. Wins are committed per-function and the
# branch is pushed at the end. Merge with a full-unit report.json regression check.
unit="$1"; src="$2"; branch="$3"; shift 3
score(){ python3 -c "import json;d=json.load(open('build/GCCP01/report.json'));print('%.4f'%[u['measures']['fuzzy_match_percent'] for u in d['units'] if u['name']=='$unit'][0])"; }
git checkout -B "$branch" origin/main >/dev/null 2>&1
git checkout origin/main -- "$src" 2>/dev/null
ninja >/dev/null 2>&1
echo "START $unit baseline=$(score)"
for fn in "$@"; do
  before=$(score)
  python3 tools/permute2.py --unit "$unit" --src "$src" --func "$fn" --seeds ${SEEDS:-25} --iters ${ITERS:-30} --max-stack 4 --keep-best --quiet >/dev/null 2>&1
  ninja >/dev/null 2>&1
  after=$(score)
  if python3 -c "import sys; sys.exit(0 if float('$after')>float('$before')+0.001 else 1)"; then
    # SAFETY GUARD: reject diffs that hoist a write/modify target into a dead temp
    if git diff "$src" | grep -qE '^\+.*__p[0-9]+ *(\+\+|--|[-+*/%&|^<>]=)'; then
      echo "REJECT $fn (broken dead-temp write pattern)"; git checkout -- "$src"; continue
    fi
    git add "$src" && git commit -q -m "permute $unit $fn: $before -> $after"
    echo "WIN $fn $before -> $after"
  else
    git checkout -- "$src"; echo "noop $fn ($before)"
  fi
done
if [ -n "$(git log origin/main..HEAD --oneline 2>/dev/null)" ]; then
  git push -u origin "$branch" >/dev/null 2>&1 && echo "PUSHED $branch"
fi
echo "DONE $unit final=$(score)"
