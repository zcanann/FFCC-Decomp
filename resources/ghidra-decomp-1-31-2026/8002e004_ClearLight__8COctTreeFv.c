// Function: ClearLight__8COctTreeFv
// Entry: 8002e004
// Size: 36 bytes

void ClearLight__8COctTreeFv(COctTree *octTree)

{
  ClearLight_r__FP8COctNode(octTree->rootNode);
  return;
}

