// Function: C_VECReflect
// Entry: 80186dd4
// Size: 212 bytes

void C_VECReflect(Vec *inVecA,Vec *inVecB,Vec *outVec)

{
  float fVar1;
  double dVar2;
  Vec local_24;
  Vec local_18;
  
  local_18.x = -inVecA->x;
  local_18.y = -inVecA->y;
  local_18.z = -inVecA->z;
  PSVECNormalize(&local_18,&local_18);
  PSVECNormalize(inVecB,&local_24);
  dVar2 = (double)PSVECDotProduct(&local_18,&local_24);
  fVar1 = FLOAT_80333720;
  outVec->x = (float)((double)(FLOAT_80333720 * local_24.x) * dVar2) - local_18.x;
  outVec->y = (float)((double)(fVar1 * local_24.y) * dVar2) - local_18.y;
  outVec->z = (float)((double)(fVar1 * local_24.z) * dVar2) - local_18.z;
  PSVECNormalize(outVec,outVec);
  return;
}

