// Function: PSMTXMultVecSR
// Entry: 801864d4
// Size: 84 bytes

/* WARNING: Removing unreachable block (ram,0x80186520) */
/* WARNING: Removing unreachable block (ram,0x80186518) */
/* WARNING: Removing unreachable block (ram,0x80186510) */
/* WARNING: Removing unreachable block (ram,0x80186504) */
/* WARNING: Removing unreachable block (ram,0x801864fc) */
/* WARNING: Removing unreachable block (ram,0x801864f4) */
/* WARNING: Removing unreachable block (ram,0x801864ec) */
/* WARNING: Removing unreachable block (ram,0x801864e4) */
/* WARNING: Removing unreachable block (ram,0x801864dc) */
/* WARNING: Removing unreachable block (ram,0x801864d8) */
/* WARNING: Removing unreachable block (ram,0x801864d4) */

void PSMTXMultVecSR(Mtx *mtx,Vec *source,Vec *destination)

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
  
  fVar1 = source->x;
  fVar7 = source->y;
  fVar2 = mtx->value[1][0];
  fVar8 = mtx->value[1][1];
  fVar3 = mtx->value[2][0];
  fVar9 = mtx->value[2][1];
  fVar4 = source->z;
  fVar5 = mtx->value[1][2];
  fVar6 = mtx->value[2][2];
  destination->x = mtx->value[0][2] * fVar4 + mtx->value[0][0] * fVar1 + mtx->value[0][1] * fVar7;
  destination->y = fVar5 * fVar4 + fVar2 * fVar1 + fVar8 * fVar7;
  destination->z = fVar6 * fVar4 + fVar3 * fVar1 + fVar9 * fVar7;
  return;
}

