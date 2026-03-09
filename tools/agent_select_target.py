#!/usr/bin/env python3
"""
FFCC-Decomp Target Selection Script
Selects random viable targets across multiple opportunity buckets:
- Code matching opportunities
- Data matching opportunities
"""

import argparse
import json
import os
import random
import sys
from pathlib import Path
from json import JSONDecodeError

try:
    from . import extract_symbols
except ImportError:
    import extract_symbols

# NOTE: MAP-derived addresses/sizes may not match your current build.
WARNING_BUILD_MISMATCH = (
    "WARNING: ADDRESS AND SIZES ARE FOR A DIFFERENT BUILD AND COULD BE WRONG. ALWAYS CHECK GHIDRA."
)
COMPLETE_THRESHOLD_PERCENT = 100
STATE_FILE_ENV_VARS = ("AGENT_SELECT_TARGET_STATE_FILE", "DECOMP_STATE_FILE")
DEFAULT_STATE_FILE_CANDIDATES = (
    Path(".openclaw/workspace/memory/decomp-state.json"),
    Path(".codex/workspace/memory/decomp-state.json"),
)


def _metadata_dict(unit):
    """Return metadata as a dict even when report rows use null/invalid types."""
    metadata = unit.get("metadata")
    return metadata if isinstance(metadata, dict) else {}


def _dict_or_empty(value):
    """Return dict value when valid; otherwise an empty dict."""
    return value if isinstance(value, dict) else {}


def _list_or_empty(value):
    """Return list value when valid; otherwise an empty list."""
    return value if isinstance(value, list) else []


def _safe_float(value, default=0.0):
    """Convert mixed report values to float without raising on malformed data."""
    try:
        return float(value)
    except (TypeError, ValueError):
        return default


def _safe_int(value, default=0):
    """Convert mixed report values to int while tolerating malformed strings."""
    try:
        return int(value)
    except (TypeError, ValueError):
        return default


def _state_file_candidates():
    for env_var in STATE_FILE_ENV_VARS:
        raw_path = os.getenv(env_var)
        if raw_path and raw_path.strip():
            yield Path(raw_path.strip()).expanduser()
            return

    home = Path.home()
    for candidate in DEFAULT_STATE_FILE_CANDIDATES:
        yield home / candidate


def _normalize_recent_failures(recent_failures):
    if not isinstance(recent_failures, list):
        return []

    normalized = []
    for item in recent_failures:
        if isinstance(item, str):
            name = item
        elif isinstance(item, dict):
            name = item.get("name")
        else:
            continue

        if isinstance(name, str) and name and name not in normalized:
            normalized.append(name)

    return normalized


def warn_build_mismatch():
    """Print a warning immediately before reporting any address/size (scoped per output block)."""
    print(WARNING_BUILD_MISMATCH)


def load_blacklist():
    """Load recently failed units to avoid"""
    for state_file in _state_file_candidates():
        try:
            with open(state_file, encoding="utf-8") as f:
                state = json.load(f)
            if not isinstance(state, dict):
                continue
            return _normalize_recent_failures(state.get("recentFailures", []))
        except (OSError, JSONDecodeError):
            continue
    return []


def is_viable_target(unit, blacklist):
    """Check if unit is a good target candidate"""
    if not isinstance(unit, dict):
        return False, "invalid unit row"

    name = unit.get("name")
    if not name:
        return False, "missing name"
    measures = _dict_or_empty(unit.get("measures"))

    # Skip auto-generated units
    if _metadata_dict(unit).get("auto_generated", False):
        return False, "auto-generated"

    # Skip recently failed units
    if name in blacklist:
        return False, "recently failed"

    # Skip units that are already effectively complete.
    fuzzy = _safe_float(measures.get("fuzzy_match_percent", 0) or 0)
    matched_code_percent = _safe_float(measures.get("matched_code_percent", 0) or 0)
    matched_data_percent = _safe_float(measures.get("matched_data_percent", 0) or 0)

    if (
        fuzzy >= COMPLETE_THRESHOLD_PERCENT
        and matched_code_percent >= COMPLETE_THRESHOLD_PERCENT
        and matched_data_percent >= COMPLETE_THRESHOLD_PERCENT
    ):
        return False, "already perfect"

    return True, "viable"

def derive_object_file(unit):
    source_path = _metadata_dict(unit).get("source_path")
    if source_path and source_path != "unknown":
        base = Path(source_path).stem
        return f"{base}.o"
    name = unit.get("name", "")
    parsed_name = Path(name)
    if parsed_name.suffix == ".o":
        return parsed_name.name
    base = parsed_name.stem
    return f"{base}.o"

def derive_source_file(unit):
    source_path = _metadata_dict(unit).get("source_path")
    if source_path and source_path != "unknown":
        return Path(source_path).name
    name = unit.get("name", "")
    parsed_name = Path(name)
    if parsed_name.suffix in {".c", ".cc", ".cpp", ".cxx", ".s", ".asm"}:
        return parsed_name.name
    base = parsed_name.stem
    return f"{base}.cpp"

def summarize_symbols(label, all_info):
    """Return formatted lines for symbol summary (no printing inside)."""
    if not isinstance(all_info, dict):
        return [f"  {label}: error: unknown error"]

    if not all_info or "error" in all_info:
        err = all_info.get("error", "unknown error")
        return [f"  {label}: error: {err}"]

    lines = []
    functions = all_info.get("functions", [])
    globals_data = all_info.get("globals", [])
    if not isinstance(functions, list):
        functions = []
    if not isinstance(globals_data, list):
        globals_data = []
    lines.append(f"  {label}: {len(functions)} funcs, {len(globals_data)} globals (showing up to 5 funcs)")

    for func in functions[:5]:
        if not isinstance(func, dict):
            continue
        p = func.get("parsed", {})
        if not isinstance(p, dict):
            p = {}
        symbol = p.get("symbol", "unknown")
        size_raw = p.get("size", "unknown")
        addr = p.get("virtual_addr", "unknown")

        if size_raw not in ["unknown", "UNUSED"]:
            try:
                size_val = int(size_raw, 16)
                size = f"0x{size_val:x}"
            except (TypeError, ValueError):
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

    units = _list_or_empty(data.get("units")) if isinstance(data, dict) else []

    for unit in units:
        viable, _reason = is_viable_target(unit, blacklist)
        if not viable:
            continue

        measures = _dict_or_empty(unit.get("measures"))
        functions = _list_or_empty(unit.get("functions"))
        source_path = _metadata_dict(unit).get("source_path", "unknown")
        source_file = Path(source_path).name if source_path and source_path != "unknown" else "unknown"
        unit_name = unit.get("name")
        if not unit_name:
            continue

        entry = {
            "name": unit_name,
            "fuzzy_match": _safe_float(measures.get("fuzzy_match_percent", 0) or 0),
            "matched_code_percent": _safe_float(measures.get("matched_code_percent", 0) or 0),
            "matched_data_percent": _safe_float(measures.get("matched_data_percent", 0) or 0),
            "total_functions": _safe_int(measures.get("total_functions", 0) or 0),
            "matched_functions": _safe_int(measures.get("matched_functions", 0) or 0),
            "func_match_percent": _safe_float(measures.get("matched_functions_percent", 0) or 0),
            "total_code": _safe_int(measures.get("total_code", 0) or 0),
            "total_data": _safe_int(measures.get("total_data", 0) or 0),
            "source_path": source_path,
            "source_file": source_file,
            "top_functions": []
        }

        dict_functions = [func for func in functions if isinstance(func, dict)]
        for func in sorted(dict_functions, key=lambda f: _safe_float(f.get("fuzzy_match_percent", 0), default=100.0))[:3]:
            func_match = _safe_float(func.get("fuzzy_match_percent", 0), default=100.0)
            if func_match < 99:
                func_name = func.get("name", "unknown")
                entry["top_functions"].append({
                    "name": func_name,
                    "match": func_match,
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


def _parse_args(argv=None):
    parser = argparse.ArgumentParser(
        description="Select random viable decomp targets grouped by opportunity buckets.",
    )
    parser.add_argument(
        "--list",
        action="store_true",
        help="Show a longer list of candidates per bucket (default is 6).",
    )
    parser.add_argument(
        "--per-bucket",
        type=int,
        default=None,
        help="Explicit number of targets per bucket (overrides --list).",
    )
    return parser.parse_args(argv)


def main(argv=None):
    args = _parse_args(argv)
    repo_root = Path(__file__).resolve().parent.parent
    report_path = repo_root / "build/GCCP01/report.json"
    pal_map = repo_root / "orig/GCCP01/game.MAP"
    en_map = repo_root / "orig/GCCE01/game.MAP"

    if not report_path.exists():
        print(f"ERROR: {report_path} not found. Run 'ninja' first.")
        return 1

    per_bucket = 6 if args.list else 3
    if args.per_bucket is not None:
        if args.per_bucket < 1:
            print("ERROR: --per-bucket must be >= 1.")
            return 1
        per_bucket = args.per_bucket

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
    exit(main(sys.argv[1:]))
