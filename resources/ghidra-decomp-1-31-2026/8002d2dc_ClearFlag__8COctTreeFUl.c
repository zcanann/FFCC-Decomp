// Function: ClearFlag__8COctTreeFUl
// Entry: 8002d2dc
// Size: 44 bytes

void ClearFlag__8COctTreeFUl(COctTree *octTree,uint param_2)

{
  DAT_8032ecac = ~param_2;
  ClearFlag_r__FP8COctNode(octTree->rootNode);
  return;
}

