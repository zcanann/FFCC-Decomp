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
import math
from pathlib import Path, PurePosixPath, PureWindowsPath

try:
    from . import extract_symbols
except ImportError:
    import extract_symbols

# NOTE: MAP-derived addresses/sizes may not match your current build.
WARNING_BUILD_MISMATCH = (
    "WARNING: ADDRESS AND SIZES ARE FOR A DIFFERENT BUILD AND COULD BE WRONG. ALWAYS CHECK GHIDRA."
)
COMPLETE_THRESHOLD_PERCENT = 100

# Units permanently excluded from target selection.
# These units thrash between extab and code improvements, wasting PR cycles.
PERMANENTLY_BLACKLISTED_UNITS = {
    "main/pppSRandCV",
    "main/pppSRandHCV",
}


def _path_name(path_str):
    """Return basename for paths that may use POSIX or Windows separators."""
    if not isinstance(path_str, str) or not path_str:
        return ""
    path_obj = PureWindowsPath(path_str) if "\\" in path_str else PurePosixPath(path_str)
    return path_obj.name


def _path_stem(path_str):
    """Return stem for paths that may use POSIX or Windows separators."""
    name = _path_name(path_str)
    return PurePosixPath(name).stem if name else ""


def _has_real_source_path(source_path):
    """Return True when source_path contains a usable path, not an unknown marker."""
    if not isinstance(source_path, str):
        return False
    normalized = source_path.strip().lower()
    return normalized not in {"", "unknown", "<unknown>", "n/a", "none", "null"}


def warn_build_mismatch():
    """Print a warning immediately before reporting any address/size (scoped per output block)."""
    print(WARNING_BUILD_MISMATCH)


def safe_float(value, default=0.0):
    """Parse a float from mixed report values without throwing."""
    try:
        parsed = float(value)
        return parsed if math.isfinite(parsed) else default
    except (TypeError, ValueError, OverflowError):
        return default


def safe_int(value, default=0):
    """Parse an int from mixed report values without throwing."""
    try:
        if isinstance(value, str):
            value = value.strip()
            if not value:
                return default
            # Accept explicit integer bases while keeping plain decimal strings stable.
            # (e.g. "010" should stay decimal, not octal)
            lower_value = value.lower()
            has_explicit_base = lower_value.startswith(("+0x", "-0x", "0x", "+0o", "-0o", "0o", "+0b", "-0b", "0b"))
            try:
                return int(value, 0 if has_explicit_base else 10)
            except ValueError:
                # Some reports may serialize integral values as float-like strings (e.g. "12.0").
                parsed = float(value)
                if not math.isfinite(parsed):
                    return default
                if not parsed.is_integer():
                    return default
                return int(parsed)
        if isinstance(value, float):
            if not math.isfinite(value) or not value.is_integer():
                return default
        return int(value)
    except (TypeError, ValueError, OverflowError):
        return default


def load_blacklist():
    """Load recently failed units to avoid"""
    state_file = Path.home() / ".openclaw/workspace/memory/decomp-state.json"
    try:
        with open(state_file) as f:
            state = json.load(f)

        failures = state.get("recentFailures", [])
        if not isinstance(failures, list):
            return []

        # Keep only string unit names to avoid type errors and accidental substring matches.
        return [failure for failure in failures if isinstance(failure, str)]
    except (FileNotFoundError, OSError, json.JSONDecodeError):
        return []


def is_viable_target(unit, blacklist):
    """Check if unit is a good target candidate"""
    name = unit.get("name")
    if not isinstance(name, str) or not name:
        return False, "missing name"
    measures = unit.get("measures", {})

    # Skip auto-generated units
    if unit.get("metadata", {}).get("auto_generated", False):
        return False, "auto-generated"

    # Skip permanently blacklisted units (thrash between extab/code, waste PR cycles)
    if name in PERMANENTLY_BLACKLISTED_UNITS:
        return False, "permanently blacklisted"

    # Skip recently failed units
    if name in blacklist:
        return False, "recently failed"

    # Skip units that are already effectively complete.
    fuzzy = safe_float(measures.get("fuzzy_match_percent", 0))
    matched_code_percent = safe_float(measures.get("matched_code_percent", 0))
    matched_data_percent = safe_float(measures.get("matched_data_percent", 0))

    if (
        fuzzy >= COMPLETE_THRESHOLD_PERCENT
        and matched_code_percent >= COMPLETE_THRESHOLD_PERCENT
        and matched_data_percent >= COMPLETE_THRESHOLD_PERCENT
    ):
        return False, "already perfect"

    return True, "viable"

def derive_object_file(unit):
    source_path = unit.get("metadata", {}).get("source_path")
    if _has_real_source_path(source_path):
        base = _path_stem(source_path)
        if base:
            return f"{base}.o"
    name = unit.get("name", "")
    base = _path_stem(name)
    if not base:
        base = "unknown"
    return f"{base}.o"

def derive_source_file(unit):
    source_path = unit.get("metadata", {}).get("source_path")
    if _has_real_source_path(source_path):
        source_name = _path_name(source_path)
        if source_name:
            return source_name
    name = unit.get("name", "")
    path_name = _path_name(name)
    if not path_name:
        return "unknown.cpp"
    path = PurePosixPath(path_name)
    if path.suffix.lower() in {".c", ".cc", ".cpp", ".cxx"}:
        return path_name
    stem = path.stem or "unknown"
    return f"{stem}.cpp"

def summarize_symbols(label, all_info):
    """Return formatted lines for symbol summary (no printing inside)."""
    if not all_info or "error" in all_info:
        err = all_info.get("error") if isinstance(all_info, dict) else "unknown error"
        return [f"  {label}: error: {err}"]

    lines = []
    functions = all_info.get("functions", [])
    if not isinstance(functions, list):
        functions = []
    globals_data = all_info.get("globals", [])
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

        if size_raw in ["unknown", "UNUSED"]:
            size = size_raw
        elif isinstance(size_raw, int):
            size = f"0x{size_raw:x}"
        elif isinstance(size_raw, str):
            # Sizes are usually hex-ish strings from MAP output, but some paths
            # may provide decimal or base-prefixed values.
            parsed_size = safe_int(size_raw, None)
            if parsed_size is not None:
                size = f"0x{parsed_size:x}"
            else:
                size = size_raw
        else:
            size = str(size_raw)

        lines.append(f"    - {symbol} ({size}b at {addr})")

    return lines


def extract_candidates(report_path):
    """Extract viable candidates from report.json."""
    with open(report_path) as f:
        data = json.load(f)

    blacklist = load_blacklist()
    candidates = []

    units = data.get("units", [])
    if not isinstance(units, list):
        return []

    for unit in units:
        if not isinstance(unit, dict):
            continue
        viable, _reason = is_viable_target(unit, blacklist)
        if not viable:
            continue

        measures = unit.get("measures", {})
        if not isinstance(measures, dict):
            measures = {}
        functions = unit.get("functions", [])
        if not isinstance(functions, list):
            functions = []
        metadata = unit.get("metadata", {})
        if not isinstance(metadata, dict):
            metadata = {}
        source_path = metadata.get("source_path", "unknown")
        if not _has_real_source_path(source_path):
            source_path = "unknown"
        source_file = _path_name(source_path) if source_path and source_path != "unknown" else "unknown"

        entry = {
            "name": unit["name"],
            "fuzzy_match": safe_float(measures.get("fuzzy_match_percent", 0)),
            "matched_code_percent": safe_float(measures.get("matched_code_percent", 0)),
            "matched_data_percent": safe_float(measures.get("matched_data_percent", 0)),
            "total_functions": safe_int(measures.get("total_functions", 0), 0),
            "matched_functions": safe_int(measures.get("matched_functions", 0), 0),
            "func_match_percent": safe_float(measures.get("matched_functions_percent", 0)),
            "total_code": safe_int(measures.get("total_code", 0), 0),
            "total_data": safe_int(measures.get("total_data", 0), 0),
            "source_path": source_path,
            "source_file": source_file,
            "top_functions": []
        }

        function_dicts = [func for func in functions if isinstance(func, dict)]
        for func in sorted(function_dicts, key=lambda f: safe_float(f.get("fuzzy_match_percent", 0)))[:3]:
            func_match = safe_float(func.get("fuzzy_match_percent", 0))
            if func_match < 99:
                func_name = func.get("name")
                if not isinstance(func_name, str) or not func_name:
                    func_name = "unknown"
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
