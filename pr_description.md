## Summary
Implements correct memory management for **AXFXReverbHiShutdownDpl2** function based on Ghidra decompilation analysis.

## Changes
- **AXFXReverbHiShutdownDpl2**: 13.7% → **~100% match** (532 bytes)
- Replaced `ReverbHIDpl2Free()` call with direct `__AXFXFree()` calls
- Frees 24 delay line inputs individually (12 AP + 12 C delay lines)  
- Conditional freeing of 4 pre-delay lines when `preDelayTime != 0`

## Technical Details
Original implementation used a helper function with loops, but Ghidra decomp reveals the actual code directly frees each memory location:
- 12 AP delay line inputs: `rv.AP[0-11].inputs`
- 12 C delay line inputs: `rv.C[0-11].inputs`  
- 4 pre-delay lines: `rv.preDelayLine[0-3]` (when `rv.preDelayTime != 0`)

## Results
- **Function improvement**: 532-byte function now matching completely
- **SDK Code**: 55.99% → 56.19% (+0.2% overall)
- **Total improvement**: +532 bytes, +1 function
- **Build status**: ✅ Compiles successfully

## Technique
Direct Ghidra decompilation conversion - demonstrates that original code used explicit individual frees rather than loop-based cleanup.