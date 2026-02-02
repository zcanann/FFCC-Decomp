#!/usr/bin/env python3
"""
FFCC-Decomp Target Selection Script
Randomly selects viable targets (0-90% match) to avoid getting stuck on problematic 0% functions.
"""

import json
import sys
import random
from pathlib import Path

def load_blacklist():
    """Load recently failed units to avoid"""
    state_file = Path.home() / ".openclaw/workspace/memory/decomp-state.json"
    try:
        with open(state_file) as f:
            state = json.load(f)
        return state.get("recentFailures", [])
    except:
        return []

def calculate_gap(measures):
    """Calculate improvement potential (gap between current and 100%)"""
    fuzzy = measures.get("fuzzy_match_percent", 0)
    return 100.0 - fuzzy

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
    
    # Get match percentages
    fuzzy = measures.get("fuzzy_match_percent", 0)
    gap = calculate_gap(measures)
    
    # Skip units that are already perfect
    if fuzzy >= 99.5:
        return False, "already perfect"
    
    return True, "viable"

def extract_targets(report_path, max_targets=10):
    """Extract viable targets from report.json"""
    with open(report_path) as f:
        # Stream parse to avoid loading full 1MB+ into memory
        data = json.load(f)
    
    blacklist = load_blacklist()
    candidates = []
    
    # Extract units array from the report structure
    units = data.get("units", [])
    
    for unit in units:
        viable, reason = is_viable_target(unit, blacklist)
        if not viable:
            continue
            
        measures = unit.get("measures", {})
        functions = unit.get("functions", [])
        
        # Extract key metrics
        entry = {
            "name": unit["name"],
            "fuzzy_match": measures.get("fuzzy_match_percent", 0),
            "gap": calculate_gap(measures),
            "total_functions": measures.get("total_functions", 0),
            "matched_functions": measures.get("matched_functions", 0),
            "func_match_percent": measures.get("matched_functions_percent", 0),
            "total_code": measures.get("total_code", 0),
            "source_path": unit.get("metadata", {}).get("source_path", "unknown"),
            "top_functions": []
        }
        
        # Extract 2-3 most promising functions (lowest match %)
        for func in sorted(functions, key=lambda f: f.get("fuzzy_match_percent", 0))[:3]:
            if func.get("fuzzy_match_percent", 0) < 99:  # Include 0% and imperfect functions
                entry["top_functions"].append({
                    "name": func["name"],
                    "match": func.get("fuzzy_match_percent", 0),
                    "size": func.get("size", "unknown")
                })
        
        candidates.append(entry)
    
    if not candidates:
        return []
    
    # Filter to 0-90% match range (avoid perfect matches, include all others)
    viable_candidates = [c for c in candidates if 0 <= c["fuzzy_match"] <= 90]
    
    # Simple random shuffle instead of gap-based prioritization
    random.shuffle(viable_candidates)
    
    # Return up to max_targets
    return viable_candidates[:max_targets]

def select_target(candidates):
    """Select one target randomly from viable candidates"""
    if not candidates:
        return None
    
    # Simple random selection - no weighting
    selected = random.choice(candidates)
    
    return selected

def main():
    report_path = Path(__file__).parent.parent / "build/GCCP01/report.json"
    
    if not report_path.exists():
        print(f"ERROR: {report_path} not found. Run 'ninja' first.")
        return 1
    
    if len(sys.argv) > 1 and sys.argv[1] == "--list":
        # List mode: show top candidates
        candidates = extract_targets(report_path, max_targets=15)
        print("Top target candidates:")
        print("=" * 60)
        for i, c in enumerate(candidates, 1):
            print(f"{i:2}. {c['name']} (gap: {c['gap']:.1f}%)")
            print(f"    Source: {c['source_path']}")
            print(f"    Functions: {c['matched_functions']}/{c['total_functions']} ({c['func_match_percent']:.1f}%)")
            if c['top_functions']:
                print(f"    Targets: {', '.join(f['name'] for f in c['top_functions'][:2])}")
            print()
        return 0
    
    # Selection mode: pick one target
    candidates = extract_targets(report_path, max_targets=20)
    
    if not candidates:
        print("No viable targets found.")
        return 1
    
    selected = select_target(candidates)
    
    print("SELECTED TARGET:")
    print(f"Unit: {selected['name']}")
    print(f"Gap: {selected['gap']:.1f}% (current: {selected['fuzzy_match']:.1f}%)")
    print(f"Source: {selected['source_path']}")
    print(f"Functions: {selected['matched_functions']}/{selected['total_functions']}")
    
    if selected['top_functions']:
        print("Target functions:")
        for func in selected['top_functions']:
            print(f"  - {func['name']} ({func['match']:.1f}% match, {func['size']}b)")
    
    return 0

if __name__ == "__main__":
    exit(main())