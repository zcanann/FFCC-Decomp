#!/usr/bin/env python3
"""
Improved FFCC-Decomp Target Selection 
Learns from success/failure patterns and avoids repeated dead ends.
"""

import json
import random
import time
from pathlib import Path
from collections import defaultdict, Counter

def load_automation_history():
    """Load historical success/failure data"""
    state_file = Path.home() / ".openclaw/workspace/memory/decomp-state.json"
    try:
        with open(state_file) as f:
            state = json.load(f)
        return state.get("history", {
            "attempts": [],  # [{unit, timestamp, outcome, size, type}, ...]
            "success_patterns": {},  # {pattern: success_rate}
            "avoid_until": {},  # {unit: timestamp}
        })
    except:
        return {"attempts": [], "success_patterns": {}, "avoid_until": {}}

def calculate_difficulty_score(unit, measures):
    """Score difficulty (0=easy, 1=very hard)"""
    total_code = measures.get("total_code", 0)
    if isinstance(total_code, str):
        try:
            total_code = int(total_code)
        except:
            total_code = 0
    
    total_functions = measures.get("total_functions", 1)
    if isinstance(total_functions, str):
        try:
            total_functions = int(total_functions)
        except:
            total_functions = 1
            
    avg_function_size = total_code / max(total_functions, 1)
    
    # Size penalty (exponential - big functions much harder)
    size_penalty = min(1.0, (avg_function_size / 200) ** 1.5)
    
    # Complexity indicators
    name = unit["name"]
    complexity_penalty = 0
    
    # Matrix/math operations are hard
    if any(x in name.lower() for x in ["matrix", "vector", "math"]):
        complexity_penalty += 0.3
    
    # USB/network processing is hard  
    if any(x in name.lower() for x in ["usb", "network", "stream"]):
        complexity_penalty += 0.4
        
    # ppp* particle system functions are medium-hard
    if "ppp" in name.lower():
        complexity_penalty += 0.2
        
    # Very large single functions are harder than many small ones
    if total_functions == 1 and total_code > 1000:
        complexity_penalty += 0.3
    
    return min(1.0, size_penalty + complexity_penalty)

def get_function_type(unit_name):
    """Categorize function types for pattern learning"""
    name = unit_name.lower()
    
    if "matrix" in name: return "matrix"
    elif "ppp" in name: return "particle" 
    elif "usb" in name: return "usb"
    elif "card" in name: return "card"
    elif "mtx" in name: return "math"
    elif "string" in name: return "string"
    else: return "misc"

def calculate_success_rate(func_type, history):
    """Calculate historical success rate for function type"""
    attempts = history.get("attempts", [])
    type_attempts = [a for a in attempts if get_function_type(a["unit"]) == func_type]
    
    if len(type_attempts) < 3:
        return 0.5  # Unknown, assume neutral
        
    successes = len([a for a in type_attempts if a["outcome"] in ["success", "pr_created"]])
    return successes / len(type_attempts)

def is_currently_avoided(unit_name, history):
    """Check if unit is temporarily avoided"""
    avoid_until = history.get("avoid_until", {})
    current_time = time.time()
    
    if unit_name in avoid_until:
        return current_time < avoid_until[unit_name]
    return False

def diversification_penalty(unit_name, recent_attempts):
    """Penalty for selecting similar function types recently"""
    current_type = get_function_type(unit_name)
    recent_types = [get_function_type(a["unit"]) for a in recent_attempts[-5:]]
    
    # Count how many of last 5 attempts were this type
    type_count = recent_types.count(current_type)
    
    # Exponential penalty for repetition
    return min(0.8, (type_count / 5) ** 2)

def score_target(unit, measures, history):
    """Calculate overall target score (higher = better choice)"""
    # Base score from improvement potential
    fuzzy = measures.get("fuzzy_match_percent", 0)
    gap_score = (100 - fuzzy) / 100
    
    # Difficulty penalty (prefer easier targets)
    difficulty = calculate_difficulty_score(unit, measures)
    difficulty_score = 1.0 - difficulty
    
    # Success rate bonus (prefer types that work)
    func_type = get_function_type(unit["name"])
    success_rate = calculate_success_rate(func_type, history)
    success_score = success_rate
    
    # Diversification (avoid recent pattern repetition)
    recent_attempts = history.get("attempts", [])[-10:]
    diversity_score = 1.0 - diversification_penalty(unit["name"], recent_attempts)
    
    # Size sweet spot (prefer 50-200 byte functions)
    total_code = measures.get("total_code", 0)
    if isinstance(total_code, str):
        try:
            total_code = int(total_code)
        except:
            total_code = 0
    
    if 50 <= total_code <= 200:
        size_bonus = 1.2
    elif total_code <= 50:
        size_bonus = 0.9  # Too small, might be stubs
    elif total_code <= 500:
        size_bonus = 1.0  # Medium, okay
    else:
        size_bonus = 0.6  # Large, harder
    
    # Combine scores (weights tunable)
    final_score = (
        gap_score * 0.3 +           # Improvement potential
        difficulty_score * 0.3 +    # Feasibility  
        success_score * 0.25 +      # Historical success
        diversity_score * 0.15      # Avoid repetition
    ) * size_bonus
    
    return final_score

def select_improved_target(report_path):
    """Main improved selection logic"""
    with open(report_path) as f:
        data = json.load(f)
    
    history = load_automation_history()
    candidates = []
    
    for unit in data.get("units", []):
        name = unit["name"]
        measures = unit.get("measures", {})
        
        # Skip if avoided or already perfect
        if is_currently_avoided(name, history):
            continue
        if measures.get("fuzzy_match_percent", 0) >= 99.5:
            continue
        if unit.get("metadata", {}).get("auto_generated", False):
            continue
            
        score = score_target(unit, measures, history)
        candidates.append((score, unit, measures))
    
    # Sort by score and select from top candidates
    candidates.sort(key=lambda x: x[0], reverse=True)
    
    if not candidates:
        print("ERROR: No viable candidates found")
        return None
    
    # Weighted random selection from top 5 candidates
    top_candidates = candidates[:5]
    weights = [score for score, unit, measures in top_candidates]
    
    selected_score, selected_unit, selected_measures = random.choices(
        top_candidates, weights=weights)[0]
    
    # Output selection info
    name = selected_unit["name"]
    functions = selected_unit.get("functions", [])
    
    print(f"SELECTED TARGET:")
    print(f"Unit: {name}")
    print(f"Gap: {100-selected_measures.get('fuzzy_match_percent', 0):.1f}% (current: {selected_measures.get('fuzzy_match_percent', 0):.1f}%)")
    print(f"Score: {selected_score:.3f}")
    print(f"Source: {selected_unit.get('metadata', {}).get('source_path', 'unknown')}")
    print(f"Functions: {selected_measures.get('matched_functions', 0)}/{selected_measures.get('total_functions', 0)}")
    print("Target functions:")
    
    for func in functions[:3]:
        match_pct = func.get("fuzzy_match_percent", 0)
        size = func.get("size", "unknown")
        print(f"  - {func['name']} ({match_pct}% match, {size}b)")
    
    return selected_unit

if __name__ == "__main__":
    import sys
    report_path = sys.argv[1] if len(sys.argv) > 1 else "build/GCCP01/report.json"
    select_improved_target(report_path)