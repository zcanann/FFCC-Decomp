// Function: ClearShadow__8COctTreeFv
// Entry: 8002da1c
// Size: 36 bytes

void ClearShadow__8COctTreeFv(COctTree *octTree)

{
  ClearShadow_r__FP8COctNode(octTree->rootNode);
  return;
}

