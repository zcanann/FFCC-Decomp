# FFCC-Decomp Session: main/pppBreathModel (Feb 3, 2026)

## Target Selection
- **Unit**: main/pppBreathModel
- **Gap**: 99.6% (current: 0.4%)
- **Functions**: 7 total, focused on largest 3

## Key Achievement
- **BirthParticle function**: 0.3% → **39.08%** match (+38.78% improvement!)
- Size: 1568 bytes (largest function in unit)
- Successfully implemented complex particle initialization logic

## Implementation Details
- Converted Ghidra decompilation to C++ source
- Used field offset access pattern: `*(float*)((int)struct + offset)`
- Proper extern "C" linkage for ppp* functions
- Fixed Math.RandF() vs math.RandF() casing
- Resolved PSMTXCopy parameter signature issues

## Technical Patterns Established
- Particle data structure initialization with memset
- Random value generation for particle properties
- Flag-based conditional randomization logic
- Matrix copying for world transforms
- Lifetime and velocity parameter setup

## Build Success
- All functions compile without errors
- Significant assembly alignment improvement in BirthParticle
- Other functions remain as placeholders for future sessions

## Key Learning
- Large particle system functions (1500+ bytes) are viable automation targets
- Basic framework implementation can achieve substantial match improvements
- Field offset access avoids struct definition dependencies

**Status**: Ready for PR - real progress achieved with compilable code