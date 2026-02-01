// Function: PSVECCrossProduct
// Entry: 80186d98
// Size: 60 bytes

/* WARNING: Removing unreachable block (ram,0x80186dcc) */
/* WARNING: Removing unreachable block (ram,0x80186dc4) */
/* WARNING: Removing unreachable block (ram,0x80186da0) */
/* WARNING: Removing unreachable block (ram,0x80186d98) */

void PSVECCrossProduct(Vec *inVecA,Vec *inVecB,Vec *outVec)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar3 = inVecB->x;
  fVar5 = inVecB->y;
  fVar1 = inVecA->z;
  fVar4 = inVecA->x;
  fVar6 = inVecA->y;
  fVar2 = inVecB->z;
  outVec->x = fVar6 * fVar2 - fVar5 * fVar1;
  outVec->y = -(fVar4 * fVar2 - fVar3 * fVar1);
  outVec->z = -(fVar6 * fVar3 - fVar5 * fVar4);
  return;
}

