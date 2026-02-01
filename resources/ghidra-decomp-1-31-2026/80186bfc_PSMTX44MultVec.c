// Function: PSMTX44MultVec
// Entry: 80186bfc
// Size: 120 bytes

/* WARNING: Removing unreachable block (ram,0x80186c6c) */
/* WARNING: Removing unreachable block (ram,0x80186c64) */
/* WARNING: Removing unreachable block (ram,0x80186c38) */
/* WARNING: Removing unreachable block (ram,0x80186c34) */
/* WARNING: Removing unreachable block (ram,0x80186c30) */
/* WARNING: Removing unreachable block (ram,0x80186c2c) */
/* WARNING: Removing unreachable block (ram,0x80186c24) */
/* WARNING: Removing unreachable block (ram,0x80186c1c) */
/* WARNING: Removing unreachable block (ram,0x80186c0c) */
/* WARNING: Removing unreachable block (ram,0x80186c04) */
/* WARNING: Removing unreachable block (ram,0x80186c00) */
/* WARNING: Removing unreachable block (ram,0x80186bfc) */

void PSMTX44MultVec(Mat4x4 *mtx,Vec *source,Vec *dest)

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
  float fVar12;
  float fVar13;
  
  fVar1 = source->x;
  fVar7 = source->y;
  fVar2 = source->z;
  fVar13 = fVar2 * mtx->value[3][2] + fVar1 * mtx->value[3][0] +
           mtx->value[3][3] * 1.0 + fVar7 * mtx->value[3][1];
  fVar12 = 1.0 / fVar13;
  fVar3 = mtx->value[1][0];
  fVar8 = mtx->value[1][1];
  fVar4 = mtx->value[1][2];
  fVar9 = mtx->value[1][3];
  fVar5 = mtx->value[2][0];
  fVar10 = mtx->value[2][1];
  fVar6 = mtx->value[2][2];
  fVar11 = mtx->value[2][3];
  dest->x = (fVar2 * mtx->value[0][2] + fVar1 * mtx->value[0][0] +
            mtx->value[0][3] * 1.0 + fVar7 * mtx->value[0][1]) * fVar12;
  dest->y = (fVar2 * fVar4 + fVar1 * fVar3 + fVar9 * 1.0 + fVar7 * fVar8) * (1.0 / fVar13);
  dest->z = (fVar2 * fVar6 + fVar1 * fVar5 + fVar11 * 1.0 + fVar7 * fVar10) * fVar12;
  return;
}

