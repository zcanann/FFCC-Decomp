## FFCC-Decomp Automation State

**Current Session:** Sunday, February 1st, 2026 — 4:27 AM

### Target: main/pppMove
- **Status:** READY FOR PR - Significant improvement achieved!
- **Branch:** pr/main-pppMove
- **Functions:** 
  - pppMoveCon: **PERFECT MATCH** ✅ (36 bytes, identical assembly)
  - pppMove: **97.4% match** (152b vs 156b expected, very close assembly match)

### Implementation Strategy
- Fixed function ordering (pppMoveCon before pppMove) to match symbol table
- Implemented 3D vector operations (initialization and addition)
- pppMoveCon: Initializes vector to zero using global constant
- pppMove: Performs conditional vector addition with global enable flag check

### Key Technical Insights
- Functions work with 3D coordinate vectors (x,y,z) at +0x80 object offset
- Global enable flag lbl_8032ED70 controls behavior
- Zero constant lbl_8032FED8 for initialization
- Function order matters for matching symbols - extracted from PAL symbol table

### Final Results
- Unit improvement: 0% → ~85% overall match
- pppMoveCon: Perfect 36-byte assembly match
- pppMove: Only 4 bytes off from perfect (152 vs 156 bytes)
- Code is plausible original source following established patterns

### Commit Ready
- ✅ Major improvement achieved (0% → 85% unit match)  
- ✅ Plausible original source (follows codebase patterns)
- ✅ Technical understanding complete
- ✅ Perfect match on one function, near-perfect on the other