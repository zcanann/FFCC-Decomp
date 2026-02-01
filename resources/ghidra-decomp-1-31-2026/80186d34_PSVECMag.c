// Function: PSVECMag
// Entry: 80186d34
// Size: 68 bytes

/* WARNING: Removing unreachable block (ram,0x80186d38) */

double PSVECMag(Vec *inVec)

{
  double dVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_80333718;
  dVar2 = (double)inVec->z * (double)inVec->z + (double)inVec->x * (double)inVec->x +
          (double)inVec->y * (double)inVec->y;
  if (dVar2 != (double)(float)(dVar3 - dVar3)) {
    dVar1 = 1.0 / SQRT(dVar2);
    dVar2 = (double)(float)(dVar2 * (double)(-(float)((double)(float)(dVar1 * dVar1) * dVar2 -
                                                     (double)FLOAT_8033371c) *
                                            (float)(dVar1 * dVar3)));
  }
  return dVar2;
}

