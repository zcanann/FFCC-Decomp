#!/usr/bin/env python3

import subprocess
import sys
import re
import os
from pathlib import Path

def extract_symbols_from_objdiff(unit_name):
    """Extract symbol information using objdiff-cli"""
    try:
        # Get detailed diff output
        result = subprocess.run([
            "build/tools/objdiff-cli", "diff", "-p", ".", "-u", unit_name, "-o", "-"
        ], capture_output=True, text=True, timeout=30)
        
        if result.returncode != 0:
            print(f"objdiff-cli failed: {result.stderr}", file=sys.stderr)
            return []
        
        symbols = []
        current_function = None
        
        lines = result.stdout.split('\n')
        for line in lines:
            # Look for function headers in objdiff output
            if line.startswith("Function: "):
                # Extract function name
                func_match = re.search(r'Function: (\w+)', line)
                if func_match:
                    current_function = func_match.group(1)
            
            # Look for match percentages
            elif current_function and "%" in line and "match" in line.lower():
                # Extract percentage
                pct_match = re.search(r'(\d+(?:\.\d+)?)%', line)
                if pct_match:
                    percentage = float(pct_match.group(1))
                    symbols.append({
                        "name": current_function,
                        "match": percentage,
                        "unit": unit_name
                    })
                    current_function = None
        
        return symbols
        
    except Exception as e:
        print(f"Error extracting symbols: {e}", file=sys.stderr)
        return []

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 extract_symbols.py <unit_name>", file=sys.stderr)
        return 1
    
    unit_name = sys.argv[1]
    
    symbols = extract_symbols_from_objdiff(unit_name)
    
    if not symbols:
        print(f"No symbols found for {unit_name}", file=sys.stderr)
        return 1
    
    # Output symbols sorted by match percentage (lowest first = most improvement opportunity)
    symbols.sort(key=lambda s: s["match"])
    
    print(f"Symbols for {unit_name}:")
    for symbol in symbols:
        print(f"  {symbol['name']}: {symbol['match']:.1f}% match")
    
    # Save to file for later use
    with open("symbol_output.txt", "w") as f:
        f.write(f"Unit: {unit_name}\n")
        for symbol in symbols:
            f.write(f"{symbol['name']}: {symbol['match']:.1f}%\n")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())