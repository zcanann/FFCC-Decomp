// Function: pppKeShpTail3XDraw
// Entry: 80089360
// Size: 2624 bytes

/* WARNING: Removing unreachable block (ram,0x80089d84) */
/* WARNING: Removing unreachable block (ram,0x80089d7c) */
/* WARNING: Removing unreachable block (ram,0x80089d74) */
/* WARNING: Removing unreachable block (ram,0x80089d6c) */
/* WARNING: Removing unreachable block (ram,0x80089d64) */
/* WARNING: Removing unreachable block (ram,0x80089d5c) */
/* WARNING: Removing unreachable block (ram,0x80089d54) */
/* WARNING: Removing unreachable block (ram,0x80089d4c) */
/* WARNING: Removing unreachable block (ram,0x80089d44) */
/* WARNING: Removing unreachable block (ram,0x80089d3c) */
/* WARNING: Removing unreachable block (ram,0x80089d34) */
/* WARNING: Removing unreachable block (ram,0x80089d2c) */
/* WARNING: Removing unreachable block (ram,0x80089d24) */
/* WARNING: Removing unreachable block (ram,0x80089d1c) */
/* WARNING: Removing unreachable block (ram,0x80089d14) */
/* WARNING: Removing unreachable block (ram,0x80089d0c) */
/* WARNING: Removing unreachable block (ram,0x80089d04) */
/* WARNING: Removing unreachable block (ram,0x800893f0) */
/* WARNING: Removing unreachable block (ram,0x800893e8) */
/* WARNING: Removing unreachable block (ram,0x800893e0) */
/* WARNING: Removing unreachable block (ram,0x800893d8) */
/* WARNING: Removing unreachable block (ram,0x800893d0) */
/* WARNING: Removing unreachable block (ram,0x800893c8) */
/* WARNING: Removing unreachable block (ram,0x800893c0) */
/* WARNING: Removing unreachable block (ram,0x800893b8) */
/* WARNING: Removing unreachable block (ram,0x800893b0) */
/* WARNING: Removing unreachable block (ram,0x800893a8) */
/* WARNING: Removing unreachable block (ram,0x800893a0) */
/* WARNING: Removing unreachable block (ram,0x80089398) */
/* WARNING: Removing unreachable block (ram,0x80089390) */
/* WARNING: Removing unreachable block (ram,0x80089388) */
/* WARNING: Removing unreachable block (ram,0x80089380) */
/* WARNING: Removing unreachable block (ram,0x80089378) */
/* WARNING: Removing unreachable block (ram,0x80089370) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppKeShpTail3XDraw(pppKeShpTail3X *pppKeShpTail3X,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  short sVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  short *psVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  undefined4 local_430;
  undefined4 local_42c;
  Vec local_428;
  Vec local_41c;
  Vec local_410;
  Vec local_404;
  Vec local_3f8;
  pppFMATRIX local_3ec;
  pppFMATRIX local_3bc;
  pppFMATRIX local_38c;
  pppFMATRIX local_35c;
  pppFMATRIX local_32c;
  float local_2f8;
  float local_2f4;
  float local_2f0;
  float local_2ec;
  float local_2e8;
  float local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  Mtx local_298;
  pppFMATRIX pStack_268;
  pppFMATRIX local_238;
  undefined4 local_208;
  uint uStack_204;
  undefined4 local_200;
  uint uStack_1fc;
  undefined4 local_1f8;
  uint uStack_1f4;
  undefined4 local_1f0;
  uint uStack_1ec;
  undefined4 local_1e8;
  uint uStack_1e4;
  undefined4 local_1e0;
  uint uStack_1dc;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  uint local_190;
  int local_18c;
  int local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  
  dVar24 = (double)FLOAT_80330520;
  psVar11 = (short *)((int)(&pppKeShpTail3X->pppPObject + 2) + *param_3->m_serializedDataOffsets);
  if (param_2->m_dataValIndex != 0xffff) {
    uVar8 = (uint)param_2->m_payload[8];
    uStack_1f4 = (int)*psVar11 >> 7 ^ 0x80000000;
    uStack_1fc = (int)*(short *)(&pppKeShpTail3X->field_0x86 + param_3->m_serializedDataOffsets[1])
                 ^ 0x80000000;
    uStack_1ec = (int)psVar11[1] >> 7 ^ 0x80000000;
    uStack_204 = uVar8 - 1 ^ 0x80000000;
    uStack_1e4 = (int)psVar11[2] >> 7 ^ 0x80000000;
    local_200 = 0x43300000;
    uStack_1dc = (int)psVar11[3] >> 7 ^ 0x80000000;
    local_1e0 = 0x43300000;
    fVar3 = (float)((double)CONCAT44(0x43300000,uStack_1fc) - DOUBLE_80330538) / FLOAT_80330524;
    local_1d8 = (double)CONCAT44(0x43300000,(int)psVar11[7] >> 7 ^ 0x80000000);
    dVar21 = (double)((float)((double)CONCAT44(0x43300000,uStack_1dc) - DOUBLE_80330538) * fVar3);
    local_208 = 0x43300000;
    dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_204) - DOUBLE_80330538);
    local_1f8 = 0x43300000;
    local_194 = (float)((double)CONCAT44(0x43300000,uStack_1f4) - DOUBLE_80330538);
    local_1f0 = 0x43300000;
    local_198 = (float)((double)CONCAT44(0x43300000,uStack_1ec) - DOUBLE_80330538);
    local_1e8 = 0x43300000;
    local_19c = (float)((double)CONCAT44(0x43300000,uStack_1e4) - DOUBLE_80330538);
    local_1d0 = (double)CONCAT44(0x43300000,(int)psVar11[4] >> 7 ^ 0x80000000);
    local_1c8 = (double)CONCAT44(0x43300000,(int)psVar11[5] >> 7 ^ 0x80000000);
    local_1c0 = (double)CONCAT44(0x43300000,(int)psVar11[6] >> 7 ^ 0x80000000);
    if (dVar15 == dVar24) {
      local_1a8 = FLOAT_80330528;
      local_1ac = FLOAT_80330528;
      local_1b0 = FLOAT_80330528;
      fVar3 = FLOAT_80330528;
    }
    else {
      local_1a8 = (float)((double)(local_198 - (float)(local_1c8 - DOUBLE_80330538)) / dVar15);
      local_1ac = (float)((double)(local_19c - (float)(local_1c0 - DOUBLE_80330538)) / dVar15);
      local_1b0 = (float)((double)(float)(dVar21 - (double)((float)(local_1d8 - DOUBLE_80330538) *
                                                           fVar3)) / dVar15);
      fVar3 = (float)((double)(local_194 - (float)(local_1d0 - DOUBLE_80330538)) / dVar15);
    }
    dVar20 = (double)fVar3;
    local_32c.value[0][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][0];
    local_32c.value[0][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][1];
    iVar9 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                      param_2->m_dataValIndex * 4);
    local_32c.value[0][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][2];
    local_32c.value[0][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][3];
    local_32c.value[1][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][0];
    local_32c.value[1][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][1];
    local_32c.value[1][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][2];
    local_32c.value[1][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][3];
    local_32c.value[2][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][0];
    local_32c.value[2][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][1];
    local_32c.value[2][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][2];
    local_32c.value[2][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&local_238,&local_32c);
    pppUnitMatrix__FR10pppFMATRIX(&pStack_268);
    dVar23 = (double)param_2->m_stepValue;
    local_1b8 = (float)((double)(float)(dVar23 - (double)(float)param_2->m_arg3) / dVar15);
    dVar15 = (double)(*(float *)(param_2->m_payload + 4) * (pppMngStPtr->m_scale).x);
    local_1b4 = (float)(dVar15 * (double)(float)((double)local_1b8 / dVar23));
    if ((double)FLOAT_80330520 == dVar15) {
      uVar8 = 0;
    }
    uVar10 = (uint)*(byte *)(psVar11 + 0xe1);
    uVar7 = uVar10 + 1;
    local_1a0 = *(float *)(psVar11 + uVar10 * 6 + 0x18);
    dVar22 = (double)*(float *)(psVar11 + uVar10 * 6 + 0x1c);
    local_1a4 = *(float *)(psVar11 + uVar10 * 6 + 0x1a);
    dVar27 = (double)local_1a0;
    dVar26 = (double)local_1a4;
    if (uVar10 == 0x1b) {
      uVar7 = 0;
    }
    dVar19 = (double)*(float *)(psVar11 + uVar7 * 6 + 0x18);
    dVar28 = (double)*(float *)(psVar11 + uVar7 * 6 + 0x1c);
    local_404.x = (float)(dVar19 - (double)local_1a0);
    dVar18 = (double)local_404.x;
    dVar29 = (double)*(float *)(psVar11 + uVar7 * 6 + 0x1a);
    local_404.z = (float)(dVar28 - dVar22);
    dVar16 = (double)local_404.z;
    local_3f8.z = FLOAT_80330520;
    local_404.y = (float)(dVar29 - (double)local_1a4);
    dVar17 = (double)local_404.y;
    local_3f8.y = FLOAT_80330520;
    local_3f8.x = FLOAT_80330520;
    dVar25 = dVar22;
    dVar12 = (double)PSVECDistance(&local_3f8,&local_404);
    local_18c = *(int *)(psVar11 + 0xdc);
    local_190 = (uint)*(short *)(iVar9 + 0x12);
    uVar6 = (uint)(ushort)psVar11[0xe0];
    sVar2 = *(short *)(iVar9 + 6);
    dVar14 = dVar12;
    if (param_2->m_payload[9] == '\0') goto LAB_80089c00;
    while( true ) {
      uVar4 = uVar6 * 0x80d + 7;
      uVar6 = uVar4 & 0xffff;
      local_1c0 = (double)(CONCAT44(0x43300000,uVar4) & 0xffffffff0000ffff);
      uVar4 = (local_18c + uVar6) / local_190;
      dVar23 = (double)(float)(dVar23 * -(double)(((float)(local_1c0 - DOUBLE_80330540) /
                                                  FLOAT_8033052c) * *(float *)param_2->m_payload -
                                                 FLOAT_80330530));
      local_410.x = local_1a0;
      local_188 = iVar9 + *(short *)(iVar9 + (uVar4 - (uVar4 / (uint)(int)sVar2) * (int)sVar2) * 8 +
                                    0x10);
      local_410.z = (float)dVar22;
      local_410.y = local_1a4;
      if (param_2->m_payload[0x3f] == '\0') {
        PSMTXScaleApply(local_238.value[0][0] * (float)(dVar23 * (double)(pppMngStPtr->m_scale).x),
                        local_238.value[1][1] * (float)(dVar23 * (double)(pppMngStPtr->m_scale).y),
                        local_238.value[2][2] * (float)(dVar23 * (double)(pppMngStPtr->m_scale).z),
                        &(pppKeShpTail3X->pppPObject).m_localMatrix,
                        (Mtx *)&pppKeShpTail3X->field_0x40);
        if ((*(short *)(param_2->m_payload + 10) != 0) && (uVar8 != 0)) {
          local_1c0 = (double)CONCAT44(0x43300000,(uint)(ushort)psVar11[uVar8 + 0xc0]);
          PSMTXRotRad(FLOAT_80330534 * (float)(local_1c0 - DOUBLE_80330540),&local_2c8,0x7a);
          local_38c.value[0][0] = *(float *)&pppKeShpTail3X->field_0x40;
          local_38c.value[0][1] = *(float *)&pppKeShpTail3X->field_0x44;
          local_38c.value[0][2] = *(float *)&pppKeShpTail3X->field_0x48;
          local_38c.value[0][3] = *(float *)&pppKeShpTail3X->field_0x4c;
          local_38c.value[1][0] = *(float *)&pppKeShpTail3X->field_0x50;
          local_38c.value[1][1] = *(float *)&pppKeShpTail3X->field_0x54;
          local_38c.value[1][2] = *(float *)&pppKeShpTail3X->field_0x58;
          local_38c.value[1][3] = *(float *)&pppKeShpTail3X->field_0x5c;
          local_38c.value[2][0] = *(float *)&pppKeShpTail3X->field_0x60;
          local_38c.value[2][1] = *(float *)&pppKeShpTail3X->field_0x64;
          local_38c.value[2][2] = *(float *)&pppKeShpTail3X->field_0x68;
          local_38c.value[2][3] = *(float *)&pppKeShpTail3X->field_0x6c;
          local_35c.value[0][0] = local_2c8;
          local_35c.value[0][1] = local_2c4;
          local_35c.value[0][2] = local_2c0;
          local_35c.value[0][3] = local_2bc;
          local_35c.value[1][0] = local_2b8;
          local_35c.value[1][1] = local_2b4;
          local_35c.value[1][2] = local_2b0;
          local_35c.value[1][3] = local_2ac;
          local_35c.value[2][0] = local_2a8;
          local_35c.value[2][1] = local_2a4;
          local_35c.value[2][2] = local_2a0;
          local_35c.value[2][3] = local_29c;
          pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX
                    ((pppFMATRIX *)&pppKeShpTail3X->field_0x40,&local_35c,&local_38c);
        }
        PSMTXMultVec(&ppvWorldMatrix,&local_410,&local_410);
        PSMTXCopy((Mtx *)&pppKeShpTail3X->field_0x40,&local_298);
      }
      else if (param_2->m_payload[0x3f] == '\x01') {
        pppUnitMatrix__FR10pppFMATRIX(&local_298);
        local_298.value[0][0] =
             (float)(dVar23 * (double)(local_238.value[0][0] * (pppMngStPtr->m_scale).x));
        local_298.value[1][1] =
             (float)(dVar23 * (double)(local_238.value[1][1] * (pppMngStPtr->m_scale).y));
        local_298.value[2][2] =
             (float)(dVar23 * (double)(local_238.value[2][2] * (pppMngStPtr->m_scale).z));
        if ((*(short *)(param_2->m_payload + 10) != 0) && (uVar8 != 0)) {
          local_1c0 = (double)CONCAT44(0x43300000,(uint)(ushort)psVar11[uVar8 + 0xc0]);
          PSMTXRotRad(FLOAT_80330534 * (float)(local_1c0 - DOUBLE_80330540),&local_2f8,0x7a);
          local_164 = local_2ec;
          local_3bc.value[0][1] = local_2f4;
          local_184 = local_2e8;
          local_3bc.value[0][3] = local_2ec;
          local_180 = local_2e4;
          local_3bc.value[1][0] = local_2e8;
          local_17c = local_2e0;
          local_3bc.value[1][1] = local_2e4;
          local_178 = local_2dc;
          local_3bc.value[1][2] = local_2e0;
          local_174 = local_2d8;
          local_3bc.value[1][3] = local_2dc;
          local_170 = local_2d4;
          local_3bc.value[2][0] = local_2d8;
          local_16c = local_2d0;
          local_3bc.value[2][1] = local_2d4;
          local_3bc.value[2][2] = local_2d0;
          local_168 = local_2cc;
          local_3ec.value[0][0] = local_298.value[0][0];
          local_3ec.value[0][1] = local_298.value[0][1];
          local_3ec.value[0][2] = local_298.value[0][2];
          local_3ec.value[0][3] = local_298.value[0][3];
          local_3ec.value[1][0] = local_298.value[1][0];
          local_3ec.value[1][1] = local_298.value[1][1];
          local_3ec.value[1][2] = local_298.value[1][2];
          local_3ec.value[1][3] = local_298.value[1][3];
          local_3ec.value[2][0] = local_298.value[2][0];
          local_3ec.value[2][1] = local_298.value[2][1];
          local_3ec.value[2][2] = local_298.value[2][2];
          local_3ec.value[2][3] = local_298.value[2][3];
          local_3bc.value[0][0] = local_2f8;
          local_3bc.value[0][2] = local_2f0;
          local_3bc.value[2][3] = local_2cc;
          pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_298,&local_3bc,&local_3ec);
        }
        PSMTXMultVec(&ppvCameraMatrix0,&local_410,&local_410);
      }
      local_298.value[0][3] = local_410.x;
      local_298.value[1][3] = local_410.y;
      local_298.value[2][3] = local_410.z;
      uVar4 = countLeadingZeros((uint)param_2->m_payload[0x41]);
      fVar3 = FLOAT_80330520;
      if (param_2->m_payload[0x3e] != '\0') {
        fVar3 = *(float *)(param_2->m_payload + 0x44);
      }
      pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                (fVar3,(pppCVector *)0x0,&local_298,0,param_2->m_payload[0x3c],
                 param_2->m_payload[0x42],0,(byte)(uVar4 >> 5),1,0);
      GXLoadPosMtxImm(&local_298,0);
      local_1c0 = (double)(longlong)(int)local_194;
      local_1c8 = (double)(longlong)(int)local_198;
      local_1d0 = (double)(longlong)(int)local_19c;
      local_1d8 = (double)(longlong)(int)dVar21;
      local_430 = CONCAT31(CONCAT21(CONCAT11((char)(int)local_194,(char)(int)local_198),
                                    (char)(int)local_19c),(char)(int)dVar21);
      local_42c = local_430;
      GXSetChanAmbColor(4,&local_430);
      pppSetBlendMode__FUc(param_2->m_payload[0x42]);
      pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc
                (local_188,pppEnvStPtr->m_materialSetPtr,param_2->m_payload[0x42]);
LAB_80089c00:
      uVar8 = uVar8 - 1;
      if (uVar8 == 0) break;
      dVar15 = (double)(float)(dVar15 - (double)local_1b4);
      dVar22 = (double)FLOAT_80330520;
      local_194 = (float)((double)local_194 - dVar20);
      local_198 = local_198 - local_1a8;
      local_19c = local_19c - local_1ac;
      dVar21 = (double)(float)(dVar21 - (double)local_1b0);
      dVar23 = (double)(float)(dVar23 - (double)local_1b8);
      if (dVar15 <= dVar22) {
        return;
      }
      for (; dVar12 < dVar15; dVar12 = (double)(float)(dVar12 + dVar14)) {
        bVar1 = uVar7 == 0x1b;
        uVar7 = uVar7 + 1;
        if (bVar1) {
          uVar7 = 0;
        }
        if (uVar7 == uVar10) {
          return;
        }
        pfVar5 = (float *)(psVar11 + uVar7 * 6 + 0x18);
        dVar24 = (double)(float)(dVar24 - dVar14);
        dVar30 = (double)pfVar5[1];
        dVar13 = (double)pfVar5[2];
        dVar26 = (double)*pfVar5;
        local_428.y = (float)(dVar30 - dVar29);
        dVar17 = (double)local_428.y;
        local_428.z = (float)(dVar13 - dVar28);
        dVar16 = (double)local_428.z;
        local_428.x = (float)(dVar26 - dVar19);
        dVar18 = (double)local_428.x;
        local_41c.z = (float)dVar22;
        local_41c.y = (float)dVar22;
        local_41c.x = (float)dVar22;
        dVar27 = dVar19;
        dVar14 = (double)PSVECDistance(&local_41c,&local_428);
        dVar19 = dVar26;
        dVar25 = dVar28;
        dVar26 = dVar29;
        dVar28 = dVar13;
        dVar29 = dVar30;
      }
      dVar13 = (double)(float)(dVar24 / dVar14);
      local_1a0 = (float)(dVar18 * dVar13 + dVar27);
      dVar22 = (double)(float)(dVar16 * dVar13 + dVar25);
      dVar24 = (double)(float)(dVar24 + dVar15);
      local_1a4 = (float)(dVar17 * dVar13 + dVar26);
      dVar12 = (double)(float)(dVar12 - dVar15);
    }
  }
  return;
}

