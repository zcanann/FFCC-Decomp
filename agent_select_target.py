#!/usr/bin/env python3

import json
import sys
import os
from pathlib import Path

def load_decomp_state():
    """Load automation state from memory/decomp-state.json"""
    state_path = Path("memory/decomp-state.json")
    if state_path.exists():
        with open(state_path, 'r') as f:
            return json.load(f)
    return {"successfulTargets": []}

def get_unit_progress(unit_name):
    """Get unit progress by running objdiff-cli on it"""
    try:
        import subprocess
        result = subprocess.run([
            "build/tools/objdiff-cli", "diff", "-p", ".", "-u", unit_name, "-s"
        ], capture_output=True, text=True, timeout=10)
        
        if result.returncode == 0:
            # Parse objdiff-cli summary output for progress percentage
            lines = result.stdout.strip().split('\n')
            for line in lines:
                if "%" in line and "functions" in line.lower():
                    # Extract percentage from output like "12 of 15 functions (80.0%)"
                    if "(" in line and "%" in line:
                        pct_str = line.split("(")[-1].split("%")[0]
                        try:
                            return float(pct_str)
                        except ValueError:
                            pass
    except Exception as e:
        print(f"Error getting progress for {unit_name}: {e}", file=sys.stderr)
    return None

def main():
    # Load objdiff configuration
    with open("objdiff.json", "r") as f:
        config = json.load(f)
    
    # Load automation state
    state = load_decomp_state()
    successful_targets = set(state.get("successfulTargets", []))
    
    # Find candidate units
    candidates = []
    
    for unit in config["units"]:
        unit_name = unit["name"]
        
        # Skip auto-generated units
        if unit.get("metadata", {}).get("auto_generated"):
            continue
            
        # Skip already successful units
        if unit_name in successful_targets:
            continue
            
        # Skip units that are too small or system-level
        if any(skip in unit_name.lower() for skip in ["auto_", "ctors", "dtors", "__"]):
            continue
            
        # Get current progress
        progress = get_unit_progress(unit_name)
        if progress is not None:
            gap = 100.0 - progress
            candidates.append({
                "name": unit_name,
                "progress": progress,
                "gap": gap
            })
    
    if not candidates:
        print("No suitable targets found", file=sys.stderr)
        return 1
    
    # Sort by gap (high gap = more improvement opportunity)
    # But prefer medium-sized gaps (20-80%) over very large (>90%) for automation
    candidates.sort(key=lambda x: (
        -x["gap"] if 20 <= x["gap"] <= 80 else -x["gap"] * 0.5,  # De-prioritize huge gaps
        x["name"]  # Secondary sort by name for consistency
    ))
    
    # Output the best target
    best = candidates[0]
    print(f"{best['name']}")
    print(f"Progress: {best['progress']:.1f}% (gap: {best['gap']:.1f}%)", file=sys.stderr)
    
    return 0

if __name__ == "__main__":
    sys.exit(main())