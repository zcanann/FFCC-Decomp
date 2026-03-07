#!/usr/bin/env python3
"""
FFCC-Decomp Target Selection Script
Selects random viable targets across multiple opportunity buckets:
- Code matching opportunities
- Data matching opportunities
"""

import json
import sys
import random
from pathlib import Path

import extract_symbols

# NOTE: MAP-derived addresses/sizes may not match your current build.
WARNING_BUILD_MISMATCH = (
    "WARNING: ADDRESS AND SIZES ARE FOR A DIFFERENT BUILD AND COULD BE WRONG. ALWAYS CHECK GHIDRA."
)
COMPLETE_THRESHOLD_PERCENT = 100

def warn_build_mismatch():
    """Print a warning immediately before reporting any address/size (scoped per output block)."""
    print(WARNING_BUILD_MISMATCH)


def load_blacklist():
    """Load recently failed units to avoid"""
    state_file = Path.home() / ".openclaw/workspace/memory/decomp-state.json"
    try:
        with open(state_file) as f:
            state = json.load(f)
        return state.get("recentFailures", [])
    except:
        return []


def is_viable_target(unit, blacklist):
    """Check if unit is a good target candidate"""
    name = unit["name"]
    measures = unit.get("measures", {})

    # Skip auto-generated units
    if unit.get("metadata", {}).get("auto_generated", False):
        return False, "auto-generated"

    # Skip recently failed units
    if name in blacklist:
        return False, "recently failed"

    # Skip units that are already effectively complete.
    fuzzy = float(measures.get("fuzzy_match_percent", 0) or 0)
    matched_code_percent = float(measures.get("matched_code_percent", 0) or 0)
    matched_data_percent = float(measures.get("matched_data_percent", 0) or 0)

    if (
        fuzzy >= COMPLETE_THRESHOLD_PERCENT
        and matched_code_percent >= COMPLETE_THRESHOLD_PERCENT
        and matched_data_percent >= COMPLETE_THRESHOLD_PERCENT
    ):
        return False, "already perfect"

    return True, "viable"

def derive_object_file(unit):
    source_path = unit.get("metadata", {}).get("source_path")
    if source_path and source_path != "unknown":
        base = Path(source_path).stem
        return f"{base}.o"
    name = unit.get("name", "")
    base = Path(name).name
    return f"{base}.o"

def derive_source_file(unit):
    source_path = unit.get("metadata", {}).get("source_path")
    if source_path and source_path != "unknown":
        return Path(source_path).name
    name = unit.get("name", "")
    base = Path(name).name
    return f"{base}.cpp"

def summarize_symbols(label, all_info):
    """Return formatted lines for symbol summary (no printing inside)."""
    if not all_info or "error" in all_info:
        err = all_info.get("error") if isinstance(all_info, dict) else "unknown error"
        return [f"  {label}: error: {err}"]

    lines = []
    functions = all_info.get("functions", [])
    globals_data = all_info.get("globals", [])
    lines.append(f"  {label}: {len(functions)} funcs, {len(globals_data)} globals (showing up to 5 funcs)")

    for func in functions[:5]:
        p = func.get("parsed", {})
        symbol = p.get("symbol", "unknown")
        size_raw = p.get("size", "unknown")
        addr = p.get("virtual_addr", "unknown")

        if size_raw not in ["unknown", "UNUSED"]:
            try:
                size_val = int(size_raw, 16)
                size = f"0x{size_val:x}"
            except ValueError:
                size = size_raw
        else:
            size = size_raw

        lines.append(f"    - {symbol} ({size}b at {addr})")

    return lines


def extract_candidates(report_path):
    """Extract viable candidates from report.json."""
    with open(report_path) as f:
        data = json.load(f)

    blacklist = load_blacklist()
    candidates = []

    units = data.get("units", [])

    for unit in units:
        viable, _reason = is_viable_target(unit, blacklist)
        if not viable:
            continue

        measures = unit.get("measures", {})
        functions = unit.get("functions", [])
        source_path = unit.get("metadata", {}).get("source_path", "unknown")
        source_file = Path(source_path).name if source_path and source_path != "unknown" else "unknown"

        entry = {
            "name": unit["name"],
            "fuzzy_match": float(measures.get("fuzzy_match_percent", 0) or 0),
            "matched_code_percent": float(measures.get("matched_code_percent", 0) or 0),
            "matched_data_percent": float(measures.get("matched_data_percent", 0) or 0),
            "total_functions": int(measures.get("total_functions", 0) or 0),
            "matched_functions": int(measures.get("matched_functions", 0) or 0),
            "func_match_percent": float(measures.get("matched_functions_percent", 0) or 0),
            "total_code": int(measures.get("total_code", 0) or 0),
            "total_data": int(measures.get("total_data", 0) or 0),
            "source_path": source_path,
            "source_file": source_file,
            "top_functions": []
        }

        for func in sorted(functions, key=lambda f: f.get("fuzzy_match_percent", 0))[:3]:
            if func.get("fuzzy_match_percent", 0) < 99:
                entry["top_functions"].append({
                    "name": func["name"],
                    "match": func.get("fuzzy_match_percent", 0),
                    "size": func.get("size", "unknown")
                })

        candidates.append(entry)

    return candidates


def select_unique_random(candidates, count, used_units):
    shuffled = list(candidates)
    random.shuffle(shuffled)
    result = []
    for c in shuffled:
        if c["name"] in used_units:
            continue
        result.append(c)
        used_units.add(c["name"])
        if len(result) >= count:
            break
    return result


def build_buckets(candidates, per_bucket):
    # All viable units are acceptable code targets.
    code_candidates = [c for c in candidates if c["fuzzy_match"] < COMPLETE_THRESHOLD_PERCENT]

    # Prefer units with non-trivial data still unmatched.
    data_candidates = [
        c for c in candidates
        if c["total_data"] > 0 and c["matched_data_percent"] < COMPLETE_THRESHOLD_PERCENT
    ]

    used_units = set()
    buckets = {
        "code": select_unique_random(code_candidates, per_bucket, used_units),
        "data": select_unique_random(data_candidates, per_bucket, used_units),
    }

    return buckets


def print_bucket(name, targets, pal_map, en_map):
    print(name)
    print("-" * len(name))
    if not targets:
        print("  (no candidates found)\n")
        return

    for i, c in enumerate(targets, 1):
        unit_info = {"name": c["name"], "metadata": {"source_path": c["source_path"]}}
        obj_file = derive_object_file(unit_info)
        src_file = derive_source_file(unit_info)

        print(
            f"{i:2}. Unit: {c['name']} (code {c['fuzzy_match']:.1f}%, data {c['matched_data_percent']:.2f}%)"
        )
        print(f"    Source: {c['source_path']}")
        print(f"    Object: {obj_file}")
        print(f"    Source file: {src_file}")
        print(
            f"    Functions: {c['matched_functions']}/{c['total_functions']} ({c['func_match_percent']:.1f}%)"
        )
        print(
            f"    Bytes: code {c['total_code']} total, data {c['total_data']} total"
        )

        if c["top_functions"]:
            print("    Targets:")
            warn_build_mismatch()
            for func in c["top_functions"]:
                print(f"      - {func['name']} ({func['match']:.1f}% match, {func['size']}b)")

        if pal_map.exists():
            pal_info = extract_symbols.extract_all_for_module(
                pal_map, object_file=obj_file, source_file=src_file
            )
            pal_lines = summarize_symbols("PAL symbols", pal_info)
            if pal_lines and not (len(pal_lines) == 1 and "error:" in pal_lines[0]):
                warn_build_mismatch()
            for line in pal_lines:
                print(line)

        if en_map.exists():
            en_info = extract_symbols.extract_all_for_module(
                en_map, object_file=obj_file, source_file=src_file
            )
            en_lines = summarize_symbols("EN symbols", en_info)
            if en_lines and not (len(en_lines) == 1 and "error:" in en_lines[0]):
                warn_build_mismatch()
            for line in en_lines:
                print(line)

        print()


def main():
    repo_root = Path(__file__).resolve().parent.parent
    report_path = repo_root / "build/GCCP01/report.json"
    pal_map = repo_root / "orig/GCCP01/game.MAP"
    en_map = repo_root / "orig/GCCE01/game.MAP"

    if not report_path.exists():
        print(f"ERROR: {report_path} not found. Run 'ninja' first.")
        return 1

    per_bucket = 6 if (len(sys.argv) > 1 and sys.argv[1] == "--list") else 3

    candidates = extract_candidates(report_path)

    if not candidates:
        print("No viable targets found.")
        return 1

    buckets = build_buckets(candidates, per_bucket=per_bucket)

    print("TARGET BUCKETS:")
    print("=" * 70)
    print_bucket(f"Code opportunities ({per_bucket})", buckets["code"], pal_map, en_map)
    print_bucket(f"Data opportunities ({per_bucket})", buckets["data"], pal_map, en_map)

    return 0

if __name__ == "__main__":
    exit(main())
