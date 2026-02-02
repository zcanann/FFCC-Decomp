# pppRandChar Decomp Attempt - 2026-02-01

## Target
- **Unit:** main/pppRandChar
- **Function:** pppRandChar (0.0% → ?)
- **Size:** 320 bytes original

## Analysis
- Fixed function signature: void -> (void*, void*, void*)
- Used PowerPC assembly analysis to understand data flow
- Function modifies character data with random values
- Two main paths: generate new randoms vs modify existing data

## Implementation Result  
- **Size:** 304 bytes (16 bytes smaller than original)
- **Match:** 0.0% (expected for first attempt)
- **Status:** Compiles successfully, logic implemented

## Key Insights
- CMath::RandF() returns void but stores result in f1 register
- Function uses complex floating point arithmetic for char manipulation
- Multiple parameter structures with specific offset access patterns

## Next Steps
- Analyze instruction differences to improve match percentage
- Refine memory access patterns
- Adjust floating point operations to match original assembly

## Files Modified
- `src/pppRandChar.cpp` - implemented function logic
- `include/ffcc/pppRandChar.h` - fixed function signature