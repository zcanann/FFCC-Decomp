// Function: PSVECSquareDistance
// Entry: 80186ea8
// Size: 40 bytes

/* WARNING: Removing unreachable block (ram,0x80186eb8) */
/* WARNING: Removing unreachable block (ram,0x80186eb4) */
/* WARNING: Removing unreachable block (ram,0x80186eac) */
/* WARNING: Removing unreachable block (ram,0x80186ea8) */

double PSVECSquareDistance(Vec *inVecA,Vec *inVecB)

{
  double dVar1;
  double dVar2;
  double dVar3;
  
  dVar2 = (double)inVecA->y - (double)inVecB->y;
  dVar3 = (double)inVecA->z - (double)inVecB->z;
  dVar1 = (double)inVecA->x - (double)inVecB->x;
  return dVar1 * dVar1 + dVar2 * dVar2 + dVar3 * dVar3;
}

