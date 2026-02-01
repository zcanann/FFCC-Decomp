// Function: PSVECAdd
// Entry: 80186c74
// Size: 36 bytes

/* WARNING: Removing unreachable block (ram,0x80186c90) */
/* WARNING: Removing unreachable block (ram,0x80186c88) */
/* WARNING: Removing unreachable block (ram,0x80186c84) */
/* WARNING: Removing unreachable block (ram,0x80186c80) */
/* WARNING: Removing unreachable block (ram,0x80186c78) */
/* WARNING: Removing unreachable block (ram,0x80186c74) */

void PSVECAdd(Vec *vecA,Vec *vecB,Vec *outVec)

{
  float fVar1;
  float fVar2;
  
  fVar1 = vecA->y;
  fVar2 = vecB->y;
  outVec->x = vecA->x + vecB->x;
  outVec->y = fVar1 + fVar2;
  outVec->z = vecA->z + vecB->z;
  return;
}

