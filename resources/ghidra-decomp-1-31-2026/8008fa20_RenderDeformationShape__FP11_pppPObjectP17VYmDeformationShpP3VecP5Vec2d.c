// Function: RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
// Entry: 8008fa20
// Size: 2584 bytes

/* WARNING: Removing unreachable block (ram,0x8009041c) */
/* WARNING: Removing unreachable block (ram,0x80090414) */
/* WARNING: Removing unreachable block (ram,0x8009040c) */
/* WARNING: Removing unreachable block (ram,0x80090404) */
/* WARNING: Removing unreachable block (ram,0x800903fc) */
/* WARNING: Removing unreachable block (ram,0x8008fa50) */
/* WARNING: Removing unreachable block (ram,0x8008fa48) */
/* WARNING: Removing unreachable block (ram,0x8008fa40) */
/* WARNING: Removing unreachable block (ram,0x8008fa38) */
/* WARNING: Removing unreachable block (ram,0x8008fa30) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
RenderDeformationShape__FP11_pppPObjectP17VYmDeformationShpP3VecP5Vec2d
          (_pppPObject *pppPObject,int *param_2,Vec *param_3,undefined4 *param_4)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  Vec *pVVar10;
  int iVar11;
  undefined4 *puVar12;
  float *pfVar13;
  uint uVar14;
  Vec4d *dest;
  uint uVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  uint local_1e8;
  uint local_1e4;
  uint local_1e0;
  uint local_1dc;
  Vec local_1d8;
  Vec4d local_1cc;
  Vec local_1bc;
  undefined4 local_1b0 [4];
  Vec local_1a0;
  float local_194 [12];
  Mtx MStack_164;
  Mtx local_134;
  Vec4d local_104;
  float local_f4;
  float local_f0;
  float local_e4;
  float local_e0;
  float local_d4;
  float local_d0;
  longlong local_c0;
  longlong local_b8;
  longlong local_b0;
  longlong local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  
  dest = &local_104;
  local_1dc = 0;
  dVar20 = (double)FLOAT_803305f8;
  local_1e0 = 0;
  dVar16 = (double)FLOAT_80330610;
  local_1e4 = 0;
  dVar17 = (double)FLOAT_80330614;
  local_1e8 = 0;
  dVar18 = (double)FLOAT_80330618;
  dVar19 = (double)FLOAT_8033061c;
  iVar11 = 0;
  pVVar10 = param_3;
  do {
    local_1bc.x = pVVar10->x;
    local_1bc.y = pVVar10->y;
    local_1bc.z = pVVar10->z;
    PSMTXMultVec((Mtx *)(pppPObject + 1),&local_1bc,&local_1d8);
    local_1cc.x = local_1d8.x;
    local_1cc.y = local_1d8.y;
    local_1cc.z = local_1d8.z;
    local_1cc.w = (float)dVar20;
    MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math,&ppvScreenMatrix,&local_1cc,dest);
    iVar11 = iVar11 + 1;
    pVVar10 = pVVar10 + 1;
    dest->x = dest->x / dest->w;
    dest->y = dest->y / dest->w;
    dest->z = dest->z / dest->w;
    dest->x = (float)(dVar16 + (double)(float)((double)dest->x / dVar17));
    dest->y = (float)(dVar18 - (double)(float)((double)dest->y / dVar19));
    dest = dest + 1;
  } while (iVar11 < 4);
  fVar2 = FLOAT_80330624;
  if (FLOAT_80330624 < local_104.x) {
    fVar2 = local_104.x;
  }
  fVar3 = FLOAT_80330624;
  if (FLOAT_80330624 < local_104.y) {
    fVar3 = local_104.y;
  }
  fVar4 = FLOAT_80330620;
  if (local_104.x < FLOAT_80330620) {
    fVar4 = local_104.x;
  }
  fVar5 = FLOAT_80330620;
  if (local_104.y < FLOAT_80330620) {
    fVar5 = local_104.y;
  }
  if (fVar2 < local_f4) {
    fVar2 = local_f4;
  }
  if (fVar3 < local_f0) {
    fVar3 = local_f0;
  }
  if (local_f4 < fVar4) {
    fVar4 = local_f4;
  }
  if (local_f0 < fVar5) {
    fVar5 = local_f0;
  }
  if (fVar2 < local_e4) {
    fVar2 = local_e4;
  }
  if (fVar3 < local_e0) {
    fVar3 = local_e0;
  }
  if (local_e4 < fVar4) {
    fVar4 = local_e4;
  }
  if (local_e0 < fVar5) {
    fVar5 = local_e0;
  }
  if (fVar2 < local_d4) {
    fVar2 = local_d4;
  }
  if (fVar3 < local_d0) {
    fVar3 = local_d0;
  }
  if (local_d4 < fVar4) {
    fVar4 = local_d4;
  }
  if (local_d0 < fVar5) {
    fVar5 = local_d0;
  }
  uVar9 = (uint)fVar4;
  local_c0 = (longlong)(int)uVar9;
  if ((uVar9 & 1 ^ uVar9 >> 0x1f) != uVar9 >> 0x1f) {
    fVar4 = fVar4 - FLOAT_803305f8;
  }
  uVar9 = (uint)fVar5;
  local_b8 = (longlong)(int)uVar9;
  if ((uVar9 & 1 ^ uVar9 >> 0x1f) != uVar9 >> 0x1f) {
    fVar5 = fVar5 - FLOAT_803305f8;
  }
  uVar9 = (uint)fVar2;
  local_b0 = (longlong)(int)uVar9;
  if ((uVar9 & 1 ^ uVar9 >> 0x1f) != uVar9 >> 0x1f) {
    fVar2 = fVar2 + FLOAT_803305f8;
  }
  uVar9 = (uint)fVar3;
  local_a8 = (longlong)(int)uVar9;
  if ((uVar9 & 1 ^ uVar9 >> 0x1f) != uVar9 >> 0x1f) {
    fVar3 = fVar3 + FLOAT_803305f8;
  }
  uVar9 = (uint)fVar4;
  local_a0 = (double)(longlong)(int)uVar9;
  uVar1 = (uint)fVar5;
  local_98 = (double)(longlong)(int)uVar1;
  local_90 = (double)(longlong)(int)fVar2;
  local_88 = (double)(longlong)(int)fVar3;
  uVar14 = (int)fVar2 - uVar9;
  uVar15 = (int)fVar3 - uVar1;
  local_1e8 = uVar15;
  local_1e4 = uVar14;
  local_1e0 = uVar1;
  local_1dc = uVar9;
  pppSetBlendMode__FUc(3);
  iVar11 = GetBackBufferRect__8CGraphicFRiRiRiRii
                     (&Graphic,&local_1dc,&local_1e0,&local_1e4,&local_1e8,0);
  *param_2 = iVar11;
  if (*param_2 == 0) {
    uVar7 = 0;
  }
  else {
    PSMTXIdentity(&local_134);
    local_90 = (double)(CONCAT44(0x43300000,local_1e8) ^ 0x80000000);
    local_88 = (double)CONCAT44(0x43300000,local_1e4 ^ 0x80000000);
    local_134.value[0][0] =
         ppvScreenMatrix.value[0][0] * (FLOAT_80330610 / (float)(local_88 - DOUBLE_80330600));
    local_134.value[1][1] =
         ppvScreenMatrix.value[1][1] * -(FLOAT_80330618 / (float)(local_90 - DOUBLE_80330600));
    local_134.value[1][0] = ppvScreenMatrix.value[1][0];
    local_134.value[2][0] = ppvScreenMatrix.value[2][0];
    local_134.value[0][1] = ppvScreenMatrix.value[0][1];
    local_134.value[2][1] = ppvScreenMatrix.value[2][1];
    local_134.value[0][2] = FLOAT_80330628;
    local_134.value[1][2] = FLOAT_80330628;
    local_134.value[2][2] = FLOAT_8033062c;
    PSMTXConcat(&local_134,(Mtx *)(pppPObject + 1),&MStack_164);
    local_1a0.z = FLOAT_803305f4;
    local_1a0.y = FLOAT_803305f4;
    local_1a0.x = FLOAT_803305f4;
    PSMTXMultVec(&MStack_164,&local_1a0,&local_1a0);
    local_1a0.x = local_1a0.x / local_1a0.z;
    local_1a0.y = local_1a0.y / local_1a0.z;
    local_134.value[0][2] = FLOAT_8033062c + local_1a0.x;
    local_134.value[1][2] = FLOAT_8033062c + local_1a0.y;
    PSMTXConcat(&local_134,(Mtx *)(pppPObject + 1),&MStack_164);
    pfVar13 = local_194;
    puVar12 = local_1b0;
    iVar11 = 0;
    pVVar10 = param_3;
    do {
      *puVar12 = pfVar13;
      PSMTXMultVec(&MStack_164,pVVar10,(Vec *)*puVar12);
      iVar11 = iVar11 + 1;
      puVar12 = puVar12 + 1;
      pVVar10 = pVVar10 + 1;
      *pfVar13 = *pfVar13 / pfVar13[2];
      pfVar13[1] = pfVar13[1] / pfVar13[2];
      pfVar13 = pfVar13 + 3;
    } while (iVar11 < 4);
    uVar8 = (uint)(local_f4 < local_104.x);
    uVar6 = (uint)(local_f0 < local_104.y);
    if (local_e4 < (&local_104)[uVar8].x) {
      uVar8 = 2;
    }
    if (local_e0 < (&local_104)[uVar6].y) {
      uVar6 = 2;
    }
    if (local_d4 < (&local_104)[uVar8].x) {
      uVar8 = 3;
    }
    if (local_d0 < (&local_104)[uVar6].y) {
      uVar6 = 3;
    }
    local_88 = (double)CONCAT44(0x43300000,local_1e4 ^ 0x80000000);
    local_90 = (double)CONCAT44(0x43300000,local_1e8 ^ 0x80000000);
    fVar2 = FLOAT_803305f8 / (float)(local_88 - DOUBLE_80330600);
    local_98 = (double)CONCAT44(0x43300000,local_1dc ^ 0x80000000);
    local_a0 = (double)CONCAT44(0x43300000,local_1e0 ^ 0x80000000);
    fVar3 = FLOAT_803305f8 / (float)(local_90 - DOUBLE_80330600);
    fVar4 = local_194[uVar8 * 3] -
            fVar2 * ((&local_104)[uVar8].x - (float)(local_98 - DOUBLE_80330600));
    if ((int)uVar9 < 0) {
      if ((int)(uVar9 + uVar14) < 0x281) {
        uVar8 = (uint)(local_104.x < local_f4);
        if ((&local_104)[uVar8].x < local_e4) {
          uVar8 = 2;
        }
        if ((&local_104)[uVar8].x < local_d4) {
          uVar8 = 3;
        }
        local_88 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
        local_90 = (double)CONCAT44(0x43300000,uVar14 ^ 0x80000000);
        local_90 = (double)CONCAT44(0x43300000,uVar14 ^ 0x80000000);
        local_134.value[0][2] =
             local_134.value[0][2] +
             ((fVar2 * (((float)(local_88 - DOUBLE_80330600) + (float)(local_90 - DOUBLE_80330600))
                       - (&local_104)[uVar8].x) + local_194[uVar8 * 3]) - FLOAT_803305f8);
      }
      else {
        local_134.value[0][2] = local_134.value[0][2] + (FLOAT_80330630 - local_1a0.x);
      }
    }
    else if ((int)(uVar9 + uVar14) < 0x281) {
      local_134.value[0][2] = local_134.value[0][2] + fVar4;
    }
    else {
      local_134.value[0][2] = local_134.value[0][2] + fVar4;
    }
    if ((int)uVar1 < 0) {
      if ((int)(uVar1 + uVar15) < 0x1c1) {
        uVar9 = (uint)(local_104.y < local_f0);
        if ((&local_104)[uVar9].y < local_e0) {
          uVar9 = 2;
        }
        if ((&local_104)[uVar9].y < local_d0) {
          uVar9 = 3;
        }
        local_88 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
        local_90 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
        local_134.value[1][2] =
             local_134.value[1][2] +
             ((fVar3 * (((float)(local_88 - DOUBLE_80330600) + (float)(local_90 - DOUBLE_80330600))
                       - (&local_104)[uVar9].y) + local_194[uVar9 * 3 + 1]) - FLOAT_803305f8);
      }
      else {
        local_134.value[1][2] = local_134.value[1][2] + (FLOAT_80330630 - local_1a0.y);
      }
    }
    else {
      local_134.value[1][2] =
           local_134.value[1][2] +
           (local_194[uVar6 * 3 + 1] -
           fVar3 * ((&local_104)[uVar6].y - (float)(local_a0 - DOUBLE_80330600)));
    }
    PSMTXConcat(&local_134,(Mtx *)(pppPObject + 1),&local_134);
    GXLoadTexMtxImm(&local_134,0x1e,0);
    GXSetTexCoordGen2(0,0,0,0x1e,0,0x7d);
    GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
    GXSetIndTexCoordScale(0,0,0);
    GXLoadTexObj(*param_2,0);
    GXBegin(0x80,7,4);
    uVar7 = 1;
    DAT_cc008000 = param_3->x;
    DAT_cc008000 = param_3->y;
    DAT_cc008000 = param_3->z;
    DAT_cc008000 = *param_4;
    DAT_cc008000 = param_4[1];
    DAT_cc008000 = *param_4;
    DAT_cc008000 = param_4[1];
    DAT_cc008000 = param_3[1].x;
    DAT_cc008000 = param_3[1].y;
    DAT_cc008000 = param_3[1].z;
    DAT_cc008000 = param_4[2];
    DAT_cc008000 = param_4[3];
    DAT_cc008000 = param_4[2];
    DAT_cc008000 = param_4[3];
    DAT_cc008000 = param_3[2].x;
    DAT_cc008000 = param_3[2].y;
    DAT_cc008000 = param_3[2].z;
    DAT_cc008000 = param_4[4];
    DAT_cc008000 = param_4[5];
    DAT_cc008000 = param_4[4];
    DAT_cc008000 = param_4[5];
    DAT_cc008000 = param_3[3].x;
    DAT_cc008000 = param_3[3].y;
    DAT_cc008000 = param_3[3].z;
    DAT_cc008000 = param_4[6];
    DAT_cc008000 = param_4[7];
    DAT_cc008000 = param_4[6];
    DAT_cc008000 = param_4[7];
  }
  return uVar7;
}

