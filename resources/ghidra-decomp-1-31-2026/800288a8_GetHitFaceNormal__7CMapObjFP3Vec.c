// Function: GetHitFaceNormal__7CMapObjFP3Vec
// Entry: 800288a8
// Size: 76 bytes

void GetHitFaceNormal__7CMapObjFP3Vec(int param_1,Vec *param_2)

{
  GetHitFaceNormal__7CMapHitFP3Vec(*(CMapHit **)(param_1 + 0xc),param_2);
  PSMTXMultVecSR((Mtx *)(param_1 + 0xb8),param_2,param_2);
  return;
}

