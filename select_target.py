#!/usr/bin/env python3
import json
import sys
from datetime import datetime, timezone

def load_state():
    try:
        with open('../memory/decomp-state.json', 'r') as f:
            return json.load(f)
    except:
        return {"blacklisted": [], "recentFailures": [], "attempts": []}

def analyze_report():
    with open('report.json', 'r') as f:
        report = json.load(f)
    
    state = load_state()
    
    # Get recently attempted targets to avoid
    recent_targets = set()
    if 'attempts' in state:
        for attempt in state['attempts'][-5:]:  # Last 5 attempts
            if 'target' in attempt:
                recent_targets.add(attempt['target'])
            if 'targets_attempted' in attempt:
                for target in attempt['targets_attempted']:
                    recent_targets.add(target)
    
    # Add specific recent failures
    recent_targets.update(['main/USBStreamData', 'main/mtx/mtx44'])
    
    blacklisted = set(state.get('blacklisted', []))
    
    # Find good candidates
    candidates = []
    
    for unit in report['units']:
        name = unit['name']
        measures = unit['measures']
        
        # Skip if recently attempted or blacklisted
        if name in recent_targets or name in blacklisted:
            continue
            
        # Skip auto-generated units
        if unit.get('metadata', {}).get('auto_generated', False):
            continue
            
        # Skip if already perfect
        if measures.get('fuzzy_match_percent', 0) >= 99.5:
            continue
        
        fuzzy = measures.get('fuzzy_match_percent', 0)
        func_match = measures.get('matched_functions_percent', 0)
        code_match = measures.get('matched_code_percent', 0)
        
        # Look for units with decent function match but room for improvement
        # Prioritize units that have some progress but aren't too complex
        if 30 <= fuzzy <= 95 and func_match >= 20:
            gap = 100 - fuzzy
            # Prefer moderate-complexity units with good potential
            score = func_match + (gap * 0.5)
            
            candidates.append({
                'name': name,
                'fuzzy': fuzzy,
                'func_match': func_match,
                'code_match': code_match,
                'score': score,
                'gap': gap
            })
    
    # Sort by score (balance of existing progress and improvement potential)
    candidates.sort(key=lambda x: x['score'], reverse=True)
    
    print("Top 10 targets:")
    for i, candidate in enumerate(candidates[:10]):
        print(f"{i+1:2}. {candidate['name']:30} fuzzy:{candidate['fuzzy']:6.2f}% func:{candidate['func_match']:6.2f}% gap:{candidate['gap']:6.2f}% score:{candidate['score']:6.2f}")
    
    if candidates:
        selected = candidates[0]
        print(f"\nSelected target: {selected['name']}")
        return selected['name']
    else:
        print("\nNo suitable targets found")
        return None

if __name__ == "__main__":
    selected = analyze_report()
    if selected:
        sys.exit(0)
    else:
        sys.exit(1)