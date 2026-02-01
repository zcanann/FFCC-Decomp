#!/usr/bin/env python3
import json
import os
from datetime import datetime, timezone

def update_state():
    state_file = '/Users/zcanann/.openclaw/workspace/memory/decomp-state.json'
    
    # Load current state
    try:
        with open(state_file, 'r') as f:
            state = json.load(f)
    except:
        state = {
            "recentFailures": [],
            "blacklisted": [],
            "attempts": [],
            "baseline": {}
        }

    # Current target info
    target = "main/MSL_C/PPCEABI/bare/H/string"
    
    # Record the attempt
    attempt = {
        "time": datetime.now(timezone.utc).isoformat(),
        "approach": "Fixed strcat function implementation - replaced incorrect strncpy logic with proper string concatenation including finding end of destination string",
        "result": "No meaningful improvement - fuzzy match 68.38% (expected ~71% baseline), function match dropped to 60%",
        "next": "Moving to different target - string library optimizations ineffective",
        "improvement": -2.71,  # Assuming 71.09 was baseline
        "target": target
    }
    
    # Update state
    state["attempts"].append(attempt)
    state["currentTarget"] = None
    state["lastAttempt"] = datetime.now(timezone.utc).isoformat()
    state["status"] = "no_improvement"
    
    # Write updated state
    with open(state_file, 'w') as f:
        json.dump(state, f, indent=2)
    
    print("State updated. Target showed no improvement.")

if __name__ == "__main__":
    update_state()