// Function: GetHitFaceNormal__7CMapHitFP3Vec
// Entry: 80025dd4
// Size: 32 bytes

void GetHitFaceNormal__7CMapHitFP3Vec(CMapHit *mapHit,Vec *vec)

{
  float *pfVar1;
  
  pfVar1 = DAT_8032ec90;
  vec->x = *DAT_8032ec90;
  vec->y = pfVar1[1];
  vec->z = pfVar1[2];
  return;
}

