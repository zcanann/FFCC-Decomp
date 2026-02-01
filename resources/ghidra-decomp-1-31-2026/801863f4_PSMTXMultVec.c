// Function: PSMTXMultVec
// Entry: 801863f4
// Size: 84 bytes

/* WARNING: Removing unreachable block (ram,0x80186440) */
/* WARNING: Removing unreachable block (ram,0x80186434) */
/* WARNING: Removing unreachable block (ram,0x8018642c) */
/* WARNING: Removing unreachable block (ram,0x80186424) */
/* WARNING: Removing unreachable block (ram,0x8018641c) */
/* WARNING: Removing unreachable block (ram,0x80186414) */
/* WARNING: Removing unreachable block (ram,0x8018640c) */
/* WARNING: Removing unreachable block (ram,0x80186404) */
/* WARNING: Removing unreachable block (ram,0x801863fc) */
/* WARNING: Removing unreachable block (ram,0x801863f8) */
/* WARNING: Removing unreachable block (ram,0x801863f4) */

void PSMTXMultVec(Mtx *mtx,Vec *source,Vec *dest)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar1 = source->x;
  fVar7 = source->y;
  fVar2 = source->z;
  fVar3 = mtx->value[1][0];
  fVar8 = mtx->value[1][1];
  fVar4 = mtx->value[1][2];
  fVar9 = mtx->value[1][3];
  dest->x = mtx->value[0][2] * fVar2 + mtx->value[0][0] * fVar1 +
            mtx->value[0][3] * 1.0 + mtx->value[0][1] * fVar7;
  fVar5 = mtx->value[2][0];
  fVar10 = mtx->value[2][1];
  fVar6 = mtx->value[2][2];
  fVar11 = mtx->value[2][3];
  dest->y = fVar4 * fVar2 + fVar3 * fVar1 + fVar9 * 1.0 + fVar8 * fVar7;
  dest->z = fVar6 * fVar2 + fVar5 * fVar1 + fVar11 * 1.0 + fVar10 * fVar7;
  return;
}

