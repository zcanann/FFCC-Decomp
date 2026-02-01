// Function: pppCopyVector__FR3Vec3Vec
// Entry: 800573f0
// Size: 28 bytes

void pppCopyVector__FR3Vec3Vec(Vec *dest,Vec *source)

{
  float fVar1;
  float fVar2;
  
  fVar1 = source->y;
  dest->x = source->x;
  fVar2 = source->z;
  dest->y = fVar1;
  dest->z = fVar2;
  return;
}

