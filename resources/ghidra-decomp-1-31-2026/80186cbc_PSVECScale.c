// Function: PSVECScale
// Entry: 80186cbc
// Size: 28 bytes

/* WARNING: Removing unreachable block (ram,0x80186cd0) */
/* WARNING: Removing unreachable block (ram,0x80186cc8) */
/* WARNING: Removing unreachable block (ram,0x80186cc0) */
/* WARNING: Removing unreachable block (ram,0x80186cbc) */

void PSVECScale(float scale,Vec *inVec,Vec *outVec)

{
  float fVar1;
  float fVar2;
  
  fVar2 = inVec->y;
  fVar1 = inVec->z;
  outVec->x = inVec->x * scale;
  outVec->y = fVar2 * scale;
  outVec->z = fVar1 * scale;
  return;
}

