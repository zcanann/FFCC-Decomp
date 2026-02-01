// Function: PSVECSubtract
// Entry: 80186c98
// Size: 36 bytes

/* WARNING: Removing unreachable block (ram,0x80186cb4) */
/* WARNING: Removing unreachable block (ram,0x80186cac) */
/* WARNING: Removing unreachable block (ram,0x80186ca8) */
/* WARNING: Removing unreachable block (ram,0x80186ca4) */
/* WARNING: Removing unreachable block (ram,0x80186c9c) */
/* WARNING: Removing unreachable block (ram,0x80186c98) */

void PSVECSubtract(Vec *vecA,Vec *vecB,Vec *outVec)

{
  float fVar1;
  float fVar2;
  
  fVar1 = vecA->y;
  fVar2 = vecB->y;
  outVec->x = vecA->x - vecB->x;
  outVec->y = fVar1 - fVar2;
  outVec->z = vecA->z - vecB->z;
  return;
}

