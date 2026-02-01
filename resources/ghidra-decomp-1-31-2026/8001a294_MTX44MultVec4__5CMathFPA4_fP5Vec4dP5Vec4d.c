// Function: MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d
// Entry: 8001a294
// Size: 100 bytes

/* WARNING: Removing unreachable block (ram,0x8001a2f0) */
/* WARNING: Removing unreachable block (ram,0x8001a2d4) */
/* WARNING: Removing unreachable block (ram,0x8001a2d0) */
/* WARNING: Removing unreachable block (ram,0x8001a2c8) */
/* WARNING: Removing unreachable block (ram,0x8001a2c0) */
/* WARNING: Removing unreachable block (ram,0x8001a2b8) */
/* WARNING: Removing unreachable block (ram,0x8001a2b0) */
/* WARNING: Removing unreachable block (ram,0x8001a2a8) */
/* WARNING: Removing unreachable block (ram,0x8001a2a0) */
/* WARNING: Removing unreachable block (ram,0x8001a29c) */
/* WARNING: Removing unreachable block (ram,0x8001a298) */
/* WARNING: Removing unreachable block (ram,0x8001a294) */

void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d
               (undefined4 param_1,Mat4x4 *sourceMtx,Vec4d *sourceVec,Vec4d *dest)

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
  float fVar16;
  
  fVar1 = sourceVec->x;
  fVar9 = sourceVec->y;
  fVar2 = sourceVec->z;
  fVar10 = sourceVec->w;
  fVar3 = sourceMtx->value[1][0];
  fVar11 = sourceMtx->value[1][1];
  fVar4 = sourceMtx->value[1][2];
  fVar12 = sourceMtx->value[1][3];
  fVar5 = sourceMtx->value[2][0];
  fVar13 = sourceMtx->value[2][1];
  fVar6 = sourceMtx->value[2][2];
  fVar14 = sourceMtx->value[2][3];
  fVar7 = sourceMtx->value[3][0];
  fVar15 = sourceMtx->value[3][1];
  fVar8 = sourceMtx->value[3][2];
  fVar16 = sourceMtx->value[3][3];
  dest->x = fVar2 * sourceMtx->value[0][2] + fVar1 * sourceMtx->value[0][0] +
            fVar10 * sourceMtx->value[0][3] + fVar9 * sourceMtx->value[0][1];
  dest->y = fVar2 * fVar4 + fVar1 * fVar3 + fVar10 * fVar12 + fVar9 * fVar11;
  dest->z = fVar2 * fVar6 + fVar1 * fVar5 + fVar10 * fVar14 + fVar9 * fVar13;
  dest->w = fVar2 * fVar8 + fVar1 * fVar7 + fVar10 * fVar16 + fVar9 * fVar15;
  return;
}

