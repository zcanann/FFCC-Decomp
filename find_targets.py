#!/usr/bin/env python3

import json

def main():
    with open("report.json", "r") as f:
        report = json.load(f)
    
    candidates = []
    
    for unit in report["units"]:
        unit_name = unit["name"]
        measures = unit["measures"]
        
        # Skip auto-generated units
        if unit.get("metadata", {}).get("auto_generated"):
            continue
            
        # Skip units that are too small or system-level
        if any(skip in unit_name.lower() for skip in ["auto_", "ctors", "dtors", "__"]):
            continue
        
        # Get match percentage
        match_pct = measures.get("matched_code_percent", 0)
        gap = 100.0 - match_pct
        
        # Focus on units with good improvement opportunities
        if gap >= 10 and gap <= 90:  # Avoid fully complete and fully empty units
            candidates.append({
                "name": unit_name,
                "match_pct": match_pct,
                "gap": gap,
                "functions": measures.get("total_functions", 0)
            })
    
    # Sort by gap (prioritize medium-sized gaps)
    candidates.sort(key=lambda x: (-x["gap"] if 20 <= x["gap"] <= 80 else -x["gap"] * 0.5, x["name"]))
    
    # Show top 10 candidates
    print("Top automation targets:")
    for i, candidate in enumerate(candidates[:10]):
        print(f"{i+1:2}. {candidate['name']:40} {candidate['match_pct']:6.1f}% (gap: {candidate['gap']:5.1f}%) {candidate['functions']} functions")

if __name__ == "__main__":
    main()