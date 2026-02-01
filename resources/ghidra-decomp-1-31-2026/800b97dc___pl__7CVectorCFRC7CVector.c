// Function: __pl__7CVectorCFRC7CVector
// Entry: 800b97dc
// Size: 112 bytes

void __pl__7CVectorCFRC7CVector(CVector *outVec,CVector *vectorA,CVector *vectorB)

{
  Vec local_28 [2];
  
  __ct__7CVectorFv(local_28);
  PSVECAdd((Vec *)vectorA,(Vec *)vectorB,local_28);
  outVec->x = local_28[0].x;
  outVec->y = local_28[0].y;
  outVec->z = local_28[0].z;
  return;
}

