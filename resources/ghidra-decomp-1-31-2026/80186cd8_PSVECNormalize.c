// Function: PSVECNormalize
// Entry: 80186cd8
// Size: 68 bytes

/* WARNING: Removing unreachable block (ram,0x80186d14) */
/* WARNING: Removing unreachable block (ram,0x80186d0c) */
/* WARNING: Removing unreachable block (ram,0x80186ce8) */
/* WARNING: Removing unreachable block (ram,0x80186ce0) */

void PSVECNormalize(Vec *inVec,Vec *outVec)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = inVec->x;
  fVar3 = inVec->y;
  fVar2 = inVec->z;
  fVar5 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
  fVar4 = 1.0 / SQRT(fVar5);
  fVar4 = -(fVar4 * fVar4 * fVar5 - FLOAT_8033371c) * fVar4 * FLOAT_80333718;
  outVec->x = fVar1 * fVar4;
  outVec->y = fVar3 * fVar4;
  outVec->z = fVar2 * fVar4;
  return;
}

