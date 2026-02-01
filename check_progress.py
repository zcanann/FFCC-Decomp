#!/usr/bin/env python3
import json

def check_unit_progress(unit_name):
    with open('report.json', 'r') as f:
        report = json.load(f)
    
    for unit in report['units']:
        if unit['name'] == unit_name:
            measures = unit['measures']
            print(f"Unit: {unit_name}")
            print(f"Fuzzy match: {measures.get('fuzzy_match_percent', 0):.2f}%")
            print(f"Func match: {measures.get('matched_functions_percent', 0):.2f}%")
            print(f"Code match: {measures.get('matched_code_percent', 0):.2f}%")
            return measures
    
    print(f"Unit {unit_name} not found")
    return None

if __name__ == "__main__":
    import sys
    unit = sys.argv[1] if len(sys.argv) > 1 else "main/MSL_C/PPCEABI/bare/H/string"
    check_unit_progress(unit)