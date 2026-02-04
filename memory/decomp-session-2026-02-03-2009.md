# FFCC-Decomp Automation Session 
**Date**: Feb 3, 2026 8:09 PM  
**Target**: main/__init_cpp_exceptions  
**Initial State**: 0.0% complete (100% gap), 2 functions, 116 bytes  

## Analysis
- Ghidra decomps show target functions:
  - `__init_cpp_exceptions`: 64 bytes, uses `GetR2__Fv()` and `DAT_8032ebf0`
  - `__fini_cpp_exceptions`: 52 bytes, parameter-less `__unregister_fragment()`

## Implementation Approach
- Fixed function signatures to match Ghidra decomp
- Updated variable name `fragmentID` → `DAT_8032ebf0`
- Fixed parameter signature for `__unregister_fragment()` 
- Updated data structure reference to `PTR_PTR_GetF4__10CChunkFileFv_80012850`
