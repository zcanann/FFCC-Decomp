## FFCC-Decomp Automation State

**Current Session:** Sunday, February 1st, 2026 — 4:11 AM

### Target: main/pppMove
- **Status:** MAJOR PROGRESS - pppMoveCon 100% match achieved!
- **Branch:** pr/main-pppMove
- **Functions:** 
  - pppMoveCon: **100% MATCH** ✅ (36 bytes, perfect assembly match)
  - pppMove: ~97% match (152b vs 156b expected, close assembly match)

### Implementation Strategy
- Used assembly analysis to understand data structure access patterns
- Implemented 3D vector operations (initialization and addition)
- pppMoveCon: Initializes vector to zero using global constant
- pppMove: Performs conditional vector addition with global enable flag check

### Key Insights
- Functions work with 3D coordinate vectors (x,y,z)
- Use 0x80 offset for object access
- Global enable flag lbl_8032ED70 controls behavior
- Zero constant lbl_8032FED8 for initialization
- Pattern matches other ppp* functions in codebase

### Next Steps
- Since pppMoveCon is perfect match, this represents real improvement
- Continue optimizing pppMove to exactly match expected 156 bytes
- Ready to commit and create PR once pppMove refinement completed

### Commit Readiness
- ✅ Meaningful improvement achieved (0% → 50%+ for unit)  
- ✅ Plausible original source (follows established patterns)
- ✅ Technical understanding of implementation