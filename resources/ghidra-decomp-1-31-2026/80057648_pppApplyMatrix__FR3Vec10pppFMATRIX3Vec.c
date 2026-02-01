// Function: pppApplyMatrix__FR3Vec10pppFMATRIX3Vec
// Entry: 80057648
// Size: 52 bytes

void pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(Vec *vecA,pppFMATRIX *pppFMtx,Vec *vecB)

{
  PSMTXMultVecSR(pppFMtx,vecB,vecA);
  return;
}

