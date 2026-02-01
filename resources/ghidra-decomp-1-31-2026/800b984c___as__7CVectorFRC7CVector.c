// Function: __as__7CVectorFRC7CVector
// Entry: 800b984c
// Size: 28 bytes

void __as__7CVectorFRC7CVector(CVector *vectorA,CVector *vectorB)

{
  float fVar1;
  float fVar2;
  
  fVar1 = vectorB->y;
  vectorA->x = vectorB->x;
  fVar2 = vectorB->z;
  vectorA->y = fVar1;
  vectorA->z = fVar2;
  return;
}

