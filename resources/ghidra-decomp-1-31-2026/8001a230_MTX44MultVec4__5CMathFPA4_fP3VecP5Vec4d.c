// Function: MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d
// Entry: 8001a230
// Size: 100 bytes

/* WARNING: Removing unreachable block (ram,0x8001a28c) */
/* WARNING: Removing unreachable block (ram,0x8001a270) */
/* WARNING: Removing unreachable block (ram,0x8001a26c) */
/* WARNING: Removing unreachable block (ram,0x8001a264) */
/* WARNING: Removing unreachable block (ram,0x8001a25c) */
/* WARNING: Removing unreachable block (ram,0x8001a254) */
/* WARNING: Removing unreachable block (ram,0x8001a24c) */
/* WARNING: Removing unreachable block (ram,0x8001a244) */
/* WARNING: Removing unreachable block (ram,0x8001a23c) */
/* WARNING: Removing unreachable block (ram,0x8001a238) */
/* WARNING: Removing unreachable block (ram,0x8001a234) */
/* WARNING: Removing unreachable block (ram,0x8001a230) */

void MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d
               (undefined4 param_1,Mat4x4 *sourceMtx,Vec *sourceVec,Vec4d *dest)

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
  float fVar14;
  float fVar15;
  
  fVar1 = sourceVec->x;
  fVar9 = sourceVec->y;
  fVar2 = sourceVec->z;
  fVar3 = sourceMtx->value[1][0];
  fVar10 = sourceMtx->value[1][1];
  fVar4 = sourceMtx->value[1][2];
  fVar11 = sourceMtx->value[1][3];
  fVar5 = sourceMtx->value[2][0];
  fVar12 = sourceMtx->value[2][1];
  fVar6 = sourceMtx->value[2][2];
  fVar13 = sourceMtx->value[2][3];
  fVar7 = sourceMtx->value[3][0];
  fVar14 = sourceMtx->value[3][1];
  fVar8 = sourceMtx->value[3][2];
  fVar15 = sourceMtx->value[3][3];
  dest->x = fVar2 * sourceMtx->value[0][2] + fVar1 * sourceMtx->value[0][0] +
            sourceMtx->value[0][3] * 1.0 + fVar9 * sourceMtx->value[0][1];
  dest->y = fVar2 * fVar4 + fVar1 * fVar3 + fVar11 * 1.0 + fVar9 * fVar10;
  dest->z = fVar2 * fVar6 + fVar1 * fVar5 + fVar13 * 1.0 + fVar9 * fVar12;
  dest->w = fVar2 * fVar8 + fVar1 * fVar7 + fVar15 * 1.0 + fVar9 * fVar14;
  return;
}

