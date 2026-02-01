// Function: __mi__7CVectorCFRC7CVector
// Entry: 800b9884
// Size: 112 bytes

void __mi__7CVectorCFRC7CVector(CVector *outVector,CVector *vectorA,CVector *vectorB)

{
  Vec local_28 [2];
  
  __ct__7CVectorFv(local_28);
  PSVECSubtract((Vec *)vectorA,(Vec *)vectorB,local_28);
  outVector->x = local_28[0].x;
  outVector->y = local_28[0].y;
  outVector->z = local_28[0].z;
  return;
}

