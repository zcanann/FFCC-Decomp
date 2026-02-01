// Function: CalcHitPosition__7CMapObjFP3Vec
// Entry: 80028800
// Size: 76 bytes

void CalcHitPosition__7CMapObjFP3Vec(int param_1,Vec *param_2)

{
  CalcHitPosition__7CMapHitFP3Vec(*(CMapHit **)(param_1 + 0xc),param_2);
  PSMTXMultVec((Mtx *)(param_1 + 0xb8),param_2,param_2);
  return;
}

