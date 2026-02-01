// Function: GetRotateY__7CVectorFv
// Entry: 800c4e50
// Size: 76 bytes

double GetRotateY__7CVectorFv(CVector *vector)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80330cd8;
  if ((dVar1 != (double)vector->x) || (dVar1 != (double)vector->z)) {
    dVar1 = (double)atan2((double)vector->x,(double)vector->z);
    dVar1 = (double)(float)dVar1;
  }
  return dVar1;
}

