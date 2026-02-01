// Function: PSVECSquareMag
// Entry: 80186d1c
// Size: 24 bytes

/* WARNING: Removing unreachable block (ram,0x80186d1c) */

double PSVECSquareMag(Vec *inVec)

{
  return (double)inVec->z * (double)inVec->z + (double)inVec->x * (double)inVec->x +
         (double)inVec->y * (double)inVec->y;
}

