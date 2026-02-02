# ROBOTS.md - FFCC-Decomp Automation Guide

## Overview

Automated decompilation workflow for bounded execution via cron jobs.
Time limit: 45 minutes per session.

## Quick Start

```bash
cd ~/Documents/projects/FFCC-Decomp
python3 -c "
# Simple target selection - pick next incomplete unit
import json, os
print('Automation session starting...')
if os.path.exists('objdiff.json'):
    print('Project configured')
else:
    print('Need to run configure.py first')
"
```

## Workflow Steps

### 1. Target Selection
```bash
# Find incomplete units (manual for now)
find src -name "*.cpp" | head -5
```

### 2. Build Check
```bash
ninja  # Ensure project builds
```

### 3. Analysis
```bash
# Check specific unit status
./build/tools/objdiff-cli diff -p . -u <unit_name> -o -
```

### 4. Implementation
```bash
# Create/modify source files based on Ghidra decomp
# Focus on function signatures first (critical for matches)
```

### 5. Validation
```bash
ninja  # Build
./build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol>
```

### 6. Commit & Push (if significant progress)
```bash
git add .
git commit -m "<unit>: <description> - <old_percent>% → <new_percent>% match"
git push origin HEAD
```

## Target Selection Criteria

1. **Existing source files** in src/ directory
2. **Small to medium functions** (32-500 bytes)
3. **Known source structure** (avoid auto-generated units)
4. **Incremental progress** opportunities

## Common Issues

- **0% matches**: Usually function signature mismatches
- **Large functions**: Need very precise implementation
- **Unknown source**: Skip auto-generated units

## Success Patterns

- Fix function signatures FIRST using Ghidra output
- Start with constructor/destructor pairs
- Use existing similar implementations as reference
- Focus on struct member access patterns

## Time Management

- **10 min**: Target selection & analysis
- **25 min**: Implementation work  
- **10 min**: Build/test/commit

## Key Tools

- `./build/tools/objdiff-cli` - Primary analysis tool
- `ninja` - Build system
- Ghidra - For function signature identification
- Git - Version control

## Session Logging

All sessions logged to `memory/ffcc-decomp-session-YYYY-MM-DD-HHMM.md`