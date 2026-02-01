// Function: __dt__8COctTreeFv
// Entry: 8002f384
// Size: 120 bytes

COctTree * __dt__8COctTreeFv(COctTree *octTree,short param_2)

{
  COctNode *pCVar1;
  
  if (octTree != (COctTree *)0x0) {
    pCVar1 = octTree->rootNode;
    if (pCVar1 != (COctNode *)0x0) {
      if (pCVar1 != (COctNode *)0x0) {
        __dla__FPv(&pCVar1[-1].meshIndex);
      }
      octTree->rootNode = (COctNode *)0x0;
    }
    octTree->field2_0x8 = (void *)0x0;
    *(undefined2 *)((int)&octTree->vtable + 2) = 0;
    if (0 < param_2) {
      __dl__FPv(octTree);
    }
  }
  return octTree;
}

