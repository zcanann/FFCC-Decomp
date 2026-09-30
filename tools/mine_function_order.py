#!/usr/bin/env python3
"""Find function-order mismatches in built game objects without editing sources.

Examples:
  python tools/mine_function_order.py --limit 20
  python tools/mine_function_order.py --unit main/p_light --details
  python tools/mine_function_order.py --diff-json build/old_diff.json --details

Uses retail split objects, not MAP addresses. Run ninja first: this command reads
existing objects only. Moves describe compiled function order; deferred generation
can reverse source order. Special members and runtime helpers require separate
review. Constant pools, missing functions and aliases are not automatic fixes.
"""
from __future__ import annotations

import argparse
from bisect import bisect_left
from collections import Counter
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def retained_subsequence(current: list[str], wanted: list[str]) -> set[str]:
    """Find a longest subsequence already in retail order (unique names only)."""
    rank = {name: i for i, name in enumerate(wanted)}
    tails, indices = [], []
    previous = [-1] * len(current)
    for i, name in enumerate(current):
        value = rank[name]
        slot = bisect_left(tails, value)
        if slot:
            previous[i] = indices[slot - 1]
        if slot == len(tails):
            tails.append(value)
            indices.append(i)
        else:
            tails[slot], indices[slot] = value, i
    keep = set()
    i = indices[-1] if indices else -1
    while i >= 0:
        keep.add(current[i])
        i = previous[i]
    return keep


def plan_moves(current: list[str], wanted: list[str]) -> list[dict]:
    keep = retained_subsequence(current, wanted)
    order = current[:]
    moves = []
    anchor = None
    for name in reversed(wanted):
        if name not in keep:
            order.remove(name)
            order.insert(order.index(anchor) if anchor is not None else len(order), name)
            moves.append({"function": name, "before": anchor,
                          "special_member_or_runtime": name.startswith(("__ct__", "__dt__", "__sinit", "__"))})
        anchor = name
    if order != wanted:
        raise ValueError("Move plan did not reproduce the retail sequence")
    return moves


def functions(side: dict) -> tuple[dict, int]:
    rows = [s for s in side.get("symbols", [])
            if "instructions" in s and int(s.get("size", 0)) > 0
            and not s["name"].startswith("[")]
    names = Counter(s["name"] for s in rows)
    addresses = Counter(int(s.get("address", 0)) for s in rows)
    # Aliases sharing an address have no meaningful relative order.
    valid = {s["name"]: s for s in rows
             if names[s["name"]] == 1 and addresses[int(s.get("address", 0))] == 1}
    return valid, len(rows) - len(valid)


def analyze(diff: dict, name: str) -> dict:
    left, left_aliases = functions(diff["left"])
    right, right_aliases = functions(diff["right"])
    common = left.keys() & right.keys()
    wanted = sorted(common, key=lambda n: int(left[n].get("address", 0)))
    current = sorted(common, key=lambda n: int(right[n].get("address", 0)))
    moves = plan_moves(current, wanted)
    sections = {s["name"]: {"size": int(s.get("size", 0)),
                             "match_percent": s.get("match_percent")}
                for s in diff["left"].get("sections", [])
                if s["name"] in ("extab", "extabindex")}
    scores = [float(left[n].get("match_percent", 0)) for n in common]
    return {"unit": name, "common_functions": len(common), "minimum_moves": len(moves),
            "near_matching_functions": sum(v >= 99 for v in scores),
            "missing_functions": sorted(left.keys() - right.keys()),
            "extra_functions": sorted(right.keys() - left.keys()),
            "ignored_aliases": {"retail": left_aliases, "compiled": right_aliases},
            "size_differences": [n for n in wanted if int(left[n]["size"]) != int(right[n]["size"])],
            "exception_sections": sections, "moves": moves,
            "retail_order": wanted, "compiled_order": current}


def find_cli() -> Path:
    for directory in (ROOT / "build/tools", ROOT / "tools"):
        for name in ("objdiff-cli.exe", "objdiff-cli"):
            path = directory / name
            if path.is_file():
                return path
    raise FileNotFoundError("objdiff-cli not found; prepare the repository first")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--unit", action="append", default=[], help="Exact objdiff unit name; repeatable")
    parser.add_argument("--diff-json", type=Path, help="Analyze an existing objdiff diff instead of scanning")
    parser.add_argument("--json", type=Path, help="Save complete diagnostics, including already ordered units")
    parser.add_argument("--limit", type=int, default=20, help="Maximum candidates to print (default: 20)")
    parser.add_argument("--details", action="store_true", help="Print proposed object-order moves")
    args = parser.parse_args()
    if args.limit < 1:
        parser.error("--limit must be positive")
    if args.diff_json and args.unit:
        parser.error("--diff-json cannot be combined with --unit")
    results, errors = [], []
    if args.diff_json:
        results.append(analyze(json.loads(args.diff_json.read_text()), str(args.diff_json)))
    else:
        config = json.loads((ROOT / "objdiff.json").read_text())
        units = config["units"]
        if args.unit:
            unknown = set(args.unit) - {u["name"] for u in units}
            if unknown:
                parser.error("Unknown units: " + ", ".join(sorted(unknown)))
            units = [u for u in units if u["name"] in args.unit]
        else:
            units = [u for u in units if "game" in u.get("metadata", {}).get("progress_categories", [])
                     and not u.get("metadata", {}).get("complete")
                     and u.get("metadata", {}).get("source_path", "").endswith((".cpp", ".c"))]
        cli = find_cli()
        for i, unit in enumerate(units, 1):
            if i == 1 or i % 20 == 0:
                print(f"Reading built objects: {i}/{len(units)}", file=sys.stderr, flush=True)
            try:
                for key in ("target_path", "base_path"):
                    if not (ROOT / unit[key]).is_file():
                        raise FileNotFoundError(unit[key])
                proc = subprocess.run([str(cli), "diff", "-p", str(ROOT), "-u", unit["name"], "-o", "-"],
                                      cwd=ROOT, capture_output=True, text=True, check=True, timeout=60)
                result = analyze(json.loads(proc.stdout), unit["name"])
                result["source"] = unit.get("metadata", {}).get("source_path")
                results.append(result)
            except (OSError, subprocess.SubprocessError, ValueError, KeyError) as exc:
                errors.append({"unit": unit["name"], "error": str(exc)})
    candidates = [r for r in results if r["minimum_moves"]]
    candidates.sort(key=lambda r: (bool(r["size_differences"] or r["missing_functions"]),
                                   all(m["special_member_or_runtime"] for m in r["moves"]),
                                   r["minimum_moves"], -r["near_matching_functions"], r["unit"]))
    print(f"{len(candidates)} order candidates / {len(results)} analyzed units; {len(errors)} errors")
    print("Moves are compiled-order suggestions, not source patches or guaranteed matching-byte gains.")
    for result in candidates[:args.limit]:
        print(f"{result['unit']}: {result['minimum_moves']} moves, "
              f"{result['near_matching_functions']}/{result['common_functions']} functions >=99%, "
              f"{len(result['size_differences'])} size differences, {len(result['missing_functions'])} missing")
        if args.details:
            for move in result["moves"]:
                destination = "before " + move["before"] if move["before"] else "to end"
                tag = " [special member/runtime]" if move["special_member_or_runtime"] else ""
                print(f"  {move['function']} {destination}{tag}")
    if args.json:
        args.json.write_text(json.dumps({"units": results, "errors": errors}, indent=2) + "\n")
    for error in errors:
        print(f"{error['unit']}: {error['error']}", file=sys.stderr)
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
