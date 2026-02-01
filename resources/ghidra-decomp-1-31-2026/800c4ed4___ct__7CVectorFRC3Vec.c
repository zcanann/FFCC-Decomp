// Function: __ct__7CVectorFRC3Vec
// Entry: 800c4ed4
// Size: 28 bytes

void __ct__7CVectorFRC3Vec(CVector *vector,Vec *vec3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = vec3->y;
  vector->x = vec3->x;
  fVar2 = vec3->z;
  vector->y = fVar1;
  vector->z = fVar2;
  return;
}

