#!/usr/bin/env python3

import json
from pathlib import Path

def main():
    # Load objdiff configuration
    with open("objdiff.json", "r") as f:
        config = json.load(f)
    
    # Load automation state
    state_path = Path("memory/decomp-state.json")
    if state_path.exists():
        with open(state_path, 'r') as f:
            state = json.load(f)
    else:
        state = {"successfulTargets": []}
    
    successful_targets = set(state.get("successfulTargets", []))
    
    print(f"Total units: {len(config['units'])}")
    print(f"Successful targets: {successful_targets}")
    
    non_auto = []
    for unit in config["units"]:
        unit_name = unit["name"]
        is_auto = unit.get("metadata", {}).get("auto_generated", False)
        
        if not is_auto and unit_name not in successful_targets:
            non_auto.append(unit_name)
    
    print(f"\nNon-auto, non-successful units ({len(non_auto)}):")
    for unit in non_auto[:20]:
        print(f"  {unit}")
    
    if non_auto:
        print(f"\nFirst target would be: {non_auto[0]}")
    else:
        print("\nNo valid targets found!")

if __name__ == "__main__":
    main()