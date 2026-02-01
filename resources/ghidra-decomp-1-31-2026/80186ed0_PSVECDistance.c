// Function: PSVECDistance
// Entry: 80186ed0
// Size: 84 bytes

/* WARNING: Removing unreachable block (ram,0x80186ee0) */
/* WARNING: Removing unreachable block (ram,0x80186edc) */
/* WARNING: Removing unreachable block (ram,0x80186ed4) */
/* WARNING: Removing unreachable block (ram,0x80186ed0) */

double PSVECDistance(Vec *inVecA,Vec *inVecB)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  
  dVar2 = (double)inVecA->y - (double)inVecB->y;
  dVar4 = (double)inVecA->z - (double)inVecB->z;
  dVar1 = (double)inVecA->x - (double)inVecB->x;
  dVar3 = (double)FLOAT_80333718;
  dVar1 = dVar1 * dVar1 + dVar2 * dVar2 + dVar4 * dVar4;
  if ((double)(float)(dVar3 - dVar3) != dVar1) {
    dVar2 = 1.0 / SQRT(dVar1);
    dVar1 = (double)(float)(dVar1 * (double)(-(float)((double)(float)(dVar2 * dVar2) * dVar1 -
                                                     (double)FLOAT_8033371c) *
                                            (float)(dVar2 * dVar3)));
  }
  return dVar1;
}

