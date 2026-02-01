// Function: pppRenderYmMegaBirthShpTail3
// Entry: 8008ca98
// Size: 2316 bytes

/* WARNING: Removing unreachable block (ram,0x8008d388) */
/* WARNING: Removing unreachable block (ram,0x8008d380) */
/* WARNING: Removing unreachable block (ram,0x8008d378) */
/* WARNING: Removing unreachable block (ram,0x8008d370) */
/* WARNING: Removing unreachable block (ram,0x8008d368) */
/* WARNING: Removing unreachable block (ram,0x8008d360) */
/* WARNING: Removing unreachable block (ram,0x8008d358) */
/* WARNING: Removing unreachable block (ram,0x8008d350) */
/* WARNING: Removing unreachable block (ram,0x8008d348) */
/* WARNING: Removing unreachable block (ram,0x8008d340) */
/* WARNING: Removing unreachable block (ram,0x8008d338) */
/* WARNING: Removing unreachable block (ram,0x8008d330) */
/* WARNING: Removing unreachable block (ram,0x8008d328) */
/* WARNING: Removing unreachable block (ram,0x8008d320) */
/* WARNING: Removing unreachable block (ram,0x8008d318) */
/* WARNING: Removing unreachable block (ram,0x8008d310) */
/* WARNING: Removing unreachable block (ram,0x8008d308) */
/* WARNING: Removing unreachable block (ram,0x8008d300) */
/* WARNING: Removing unreachable block (ram,0x8008cb30) */
/* WARNING: Removing unreachable block (ram,0x8008cb28) */
/* WARNING: Removing unreachable block (ram,0x8008cb20) */
/* WARNING: Removing unreachable block (ram,0x8008cb18) */
/* WARNING: Removing unreachable block (ram,0x8008cb10) */
/* WARNING: Removing unreachable block (ram,0x8008cb08) */
/* WARNING: Removing unreachable block (ram,0x8008cb00) */
/* WARNING: Removing unreachable block (ram,0x8008caf8) */
/* WARNING: Removing unreachable block (ram,0x8008caf0) */
/* WARNING: Removing unreachable block (ram,0x8008cae8) */
/* WARNING: Removing unreachable block (ram,0x8008cae0) */
/* WARNING: Removing unreachable block (ram,0x8008cad8) */
/* WARNING: Removing unreachable block (ram,0x8008cad0) */
/* WARNING: Removing unreachable block (ram,0x8008cac8) */
/* WARNING: Removing unreachable block (ram,0x8008cac0) */
/* WARNING: Removing unreachable block (ram,0x8008cab8) */
/* WARNING: Removing unreachable block (ram,0x8008cab0) */
/* WARNING: Removing unreachable block (ram,0x8008caa8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmMegaBirthShpTail3
               (pppYmMegaBirthShpTail3 *pppYmMegaBirthShpTail3,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint unaff_r19;
  uint unaff_r20;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
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
  double dVar31;
  double dVar32;
  double dVar33;
  double dVar34;
  double dVar35;
  undefined4 local_340;
  undefined4 local_33c;
  Vec local_338;
  Vec local_32c;
  Vec local_320;
  Vec local_310;
  Vec local_300;
  Vec local_2f0;
  Vec local_2e4;
  pppFMATRIX local_2d8;
  pppFMATRIX local_2a8;
  float local_278;
  float local_274;
  float local_270;
  float local_26c;
  float local_268;
  float local_264;
  float local_260;
  float local_25c;
  float local_258;
  float local_254;
  float local_250;
  float local_24c;
  pppFMATRIX local_248;
  undefined4 local_218;
  uint uStack_214;
  undefined4 local_210;
  uint uStack_20c;
  undefined4 local_208;
  uint uStack_204;
  undefined4 local_200;
  uint uStack_1fc;
  undefined4 local_1f8;
  uint uStack_1f4;
  undefined4 local_1f0;
  uint uStack_1ec;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  uint local_1ac;
  uint local_1a8;
  int local_1a4;
  undefined *local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  
  iVar9 = param_3->m_serializedDataOffsets[2];
  iVar7 = *(int *)(&pppYmMegaBirthShpTail3->field_0xbc + iVar9);
  local_1a0 = (undefined *)
              ((int)(&pppYmMegaBirthShpTail3->field0_0x0 + 2) + param_3->m_serializedDataOffsets[1])
  ;
  iVar15 = *(int *)(&pppYmMegaBirthShpTail3->field_0xc4 + iVar9);
  iVar3 = *(int *)(&pppYmMegaBirthShpTail3->field_0xc0 + iVar9);
  if (iVar7 == 0) {
    bVar1 = false;
  }
  else if (iVar3 == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (param_2->m_dataValIndex != 0xffff)) {
    iVar14 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                       param_2->m_dataValIndex * 4);
    uVar4 = countLeadingZeros((uint)param_2->m_payload[0x55]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2->m_payload + 0xa0),(pppCVector *)0x0,
               (pppFMATRIX *)&pppYmMegaBirthShpTail3->field_0x40,param_2->m_payload[0xa4],
               *(undefined *)&param_2->m_stepValue,param_2->m_payload[0x58],0,(byte)(uVar4 >> 5),1,0
              );
    pppSetBlendMode__FUc(param_2->m_payload[0x58]);
    for (uVar4 = 0; uVar4 < *(uint *)(&pppYmMegaBirthShpTail3->field_0xc8 + iVar9);
        uVar4 = uVar4 + 1) {
      if (*(short *)(iVar7 + 0x22) != 0) {
        uVar10 = (uint)*(ushort *)(param_2->m_payload + 0x9c);
        uStack_20c = (int)*(short *)(local_1a0 + 6) ^ 0x80000000;
        local_210 = 0x43300000;
        uStack_214 = uVar10 - 1 ^ 0x80000000;
        uVar12 = *(byte *)(iVar7 + 0x37) - 1;
        uStack_204 = (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xd0 + iVar9) >> 7 ^ 0x80000000;
        uStack_1fc = (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xd2 + iVar9) >> 7 ^ 0x80000000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_20c) - DOUBLE_803305b8) / FLOAT_803305a0;
        local_1f0 = 0x43300000;
        uStack_1ec = (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xd6 + iVar9) >> 7 ^ 0x80000000;
        uStack_1f4 = (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xd4 + iVar9) >> 7 ^ 0x80000000;
        local_1e8 = (double)CONCAT44(0x43300000,
                                     (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xde + iVar9) >>
                                     7 ^ 0x80000000);
        local_218 = 0x43300000;
        dVar22 = (double)((float)((double)CONCAT44(0x43300000,uStack_1ec) - DOUBLE_803305b8) * fVar2
                         );
        local_1c8 = (float)((double)CONCAT44(0x43300000,uStack_214) - DOUBLE_803305b8);
        local_208 = 0x43300000;
        uVar16 = (uint)*(byte *)(iVar7 + 0x38);
        local_1b0 = (float)((double)CONCAT44(0x43300000,uStack_204) - DOUBLE_803305b8);
        local_200 = 0x43300000;
        dVar26 = (double)*(float *)(param_2->m_payload + 0x98);
        local_1b4 = (float)((double)CONCAT44(0x43300000,uStack_1fc) - DOUBLE_803305b8);
        local_1f8 = 0x43300000;
        dVar23 = (double)(float)((double)CONCAT44(0x43300000,uStack_1f4) - DOUBLE_803305b8);
        local_1e0 = (double)CONCAT44(0x43300000,
                                     (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xd8 + iVar9) >>
                                     7 ^ 0x80000000);
        local_1d8 = (double)CONCAT44(0x43300000,
                                     (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xda + iVar9) >>
                                     7 ^ 0x80000000);
        local_1d0 = (double)CONCAT44(0x43300000,
                                     (int)*(short *)(&pppYmMegaBirthShpTail3->field_0xdc + iVar9) >>
                                     7 ^ 0x80000000);
        if (local_1c8 != FLOAT_803305a4) {
          local_1b8 = (local_1b0 - (float)(local_1e0 - DOUBLE_803305b8)) / local_1c8;
          local_1bc = (local_1b4 - (float)(local_1d8 - DOUBLE_803305b8)) / local_1c8;
          local_1c0 = (float)(dVar23 - (double)(float)(local_1d0 - DOUBLE_803305b8)) / local_1c8;
          local_1c4 = (float)(dVar22 - (double)((float)(local_1e8 - DOUBLE_803305b8) * fVar2)) /
                      local_1c8;
        }
        dVar25 = (double)*(float *)(param_2->m_payload + 0x5c);
        iVar11 = iVar7 + 0x80;
        pfVar5 = (float *)(iVar11 + uVar16 * 0xc);
        dVar24 = (double)*pfVar5;
        uVar13 = uVar16 + 1;
        dVar21 = (double)pfVar5[1];
        local_1c8 = (float)(dVar25 - (double)*(float *)(param_2->m_payload + 0x60)) / local_1c8;
        dVar20 = (double)pfVar5[2];
        if (uVar16 == uVar12) {
          uVar13 = 0;
        }
        pfVar5 = (float *)(iVar11 + uVar13 * 0xc);
        dVar35 = (double)*pfVar5;
        dVar31 = (double)pfVar5[1];
        dVar30 = (double)pfVar5[2];
        local_2f0.x = (float)(dVar35 - dVar24);
        dVar34 = (double)local_2f0.x;
        local_2f0.y = (float)(dVar31 - dVar21);
        dVar33 = (double)local_2f0.y;
        local_2f0.z = (float)(dVar30 - dVar20);
        dVar32 = (double)local_2f0.z;
        local_2e4.z = FLOAT_803305a4;
        local_2e4.y = FLOAT_803305a4;
        local_2e4.x = FLOAT_803305a4;
        dVar27 = dVar20;
        dVar28 = dVar21;
        dVar29 = dVar24;
        dVar18 = (double)PSVECDistance(&local_2e4,&local_2f0);
        dVar19 = dVar18;
        if (param_2->m_payload[0x9e] == '\0') goto LAB_8008d1bc;
        local_1a8 = (uint)*(ushort *)(iVar7 + 0x1c);
        unaff_r20 = (uint)*(ushort *)
                           ((int)pppYmMegaBirthShpTail3[1].field0_0x0.m_localMatrix.value[0] + iVar9
                           );
        local_1ac = (uint)*(short *)(iVar14 + 0x12);
        unaff_r19 = (uint)*(short *)(iVar14 + 6);
        for (uVar10 = (uint)*(ushort *)(param_2->m_payload + 0x9c); 0 < (int)uVar10;
            uVar10 = uVar10 - 1) {
          iVar6 = iVar7 + uVar13 * 0xc;
          if (((FLOAT_803305a4 != *(float *)(iVar6 + 0x80)) ||
              (FLOAT_803305a4 != *(float *)(iVar6 + 0x84))) ||
             (FLOAT_803305a4 != *(float *)(iVar6 + 0x88))) {
            unaff_r20 = unaff_r20 * 0x80d + 7 & 0xffff;
            uVar8 = (local_1a8 + unaff_r20) / local_1ac;
            local_1a4 = iVar14 + *(short *)(iVar14 + (uVar8 - (uVar8 / unaff_r19) * unaff_r19) * 8 +
                                                     0x10);
            pppUnitMatrix__FR10pppFMATRIX(&local_248);
            local_248.value[0][0] = (float)(dVar25 * (double)(pppMngStPtr->m_scale).x);
            local_248.value[1][1] = (float)(dVar25 * (double)(pppMngStPtr->m_scale).y);
            local_248.value[2][2] = (float)(dVar25 * (double)(pppMngStPtr->m_scale).z);
            if (*(short *)(param_2->m_payload + 0x94) != 0) {
              local_1d0 = (double)CONCAT44(0x43300000,(uint)*(ushort *)(iVar7 + uVar10 * 2 + 0x40));
              PSMTXRotRad(FLOAT_803305a8 * (float)(local_1d0 - DOUBLE_803305c0),&local_278,0x7a);
              local_16c = local_248.value[2][3];
              local_2d8.value[2][1] = local_248.value[2][1];
              local_19c = local_278;
              local_2d8.value[2][3] = local_248.value[2][3];
              local_198 = local_274;
              local_2a8.value[0][0] = local_278;
              local_194 = local_270;
              local_2a8.value[0][1] = local_274;
              local_190 = local_26c;
              local_2a8.value[0][2] = local_270;
              local_18c = local_268;
              local_2a8.value[0][3] = local_26c;
              local_188 = local_264;
              local_2a8.value[1][0] = local_268;
              local_184 = local_260;
              local_2a8.value[1][1] = local_264;
              local_180 = local_25c;
              local_2a8.value[1][2] = local_260;
              local_17c = local_258;
              local_2a8.value[1][3] = local_25c;
              local_178 = local_254;
              local_2a8.value[2][0] = local_258;
              local_174 = local_250;
              local_2a8.value[2][1] = local_254;
              local_2a8.value[2][2] = local_250;
              local_170 = local_24c;
              local_2d8.value[0][0] = local_248.value[0][0];
              local_2d8.value[0][1] = local_248.value[0][1];
              local_2d8.value[0][2] = local_248.value[0][2];
              local_2d8.value[0][3] = local_248.value[0][3];
              local_2d8.value[1][0] = local_248.value[1][0];
              local_2d8.value[1][1] = local_248.value[1][1];
              local_2d8.value[1][2] = local_248.value[1][2];
              local_2d8.value[1][3] = local_248.value[1][3];
              local_2d8.value[2][0] = local_248.value[2][0];
              local_2d8.value[2][2] = local_248.value[2][2];
              local_2a8.value[2][3] = local_24c;
              pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_248,&local_2a8,&local_2d8)
              ;
            }
            local_310.x = (float)dVar24;
            local_310.y = (float)dVar21;
            local_310.z = (float)dVar20;
            if (param_2->m_payload[0xa5] == '\0') {
              PSMTXMultVec(&ppvWorldMatrix,&local_310,&local_300);
            }
            else if (param_2->m_payload[0xa5] == '\x01') {
              local_320.x = (pppMngStPtr->m_matrix).value[0][3];
              local_320.y = (pppMngStPtr->m_matrix).value[1][3];
              local_320.z = (pppMngStPtr->m_matrix).value[2][3];
              PSVECAdd(&local_320,&local_310,&local_310);
              PSMTXMultVec(&ppvCameraMatrix0,&local_310,&local_300);
            }
            local_248.value[0][3] = local_300.x;
            local_248.value[1][3] = local_300.y;
            local_248.value[2][3] = local_300.z;
            GXLoadPosMtxImm(&local_248,0);
            local_1e0 = (double)(longlong)(int)dVar23;
            local_1d0 = (double)(longlong)(int)local_1b0;
            local_1d8 = (double)(longlong)(int)local_1b4;
            uVar8 = (uint)(dVar22 * (double)(FLOAT_803305ac *
                                            (FLOAT_803305b0 - *(float *)(iVar7 + 0x30))));
            local_1e8 = (double)(longlong)(int)uVar8;
            local_33c = CONCAT13((char)(int)local_1b0,
                                 CONCAT21((short)(int)local_1b4,(char)(int)dVar23) << 8);
            local_33c._3_1_ = (char)uVar8;
            if (0x7f < (uVar8 & 0xff)) {
              local_33c._3_1_ = 0x7f;
            }
            local_340 = local_33c;
            GXSetChanAmbColor(4,&local_340);
            pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc
                      (local_1a4,pppEnvStPtr->m_materialSetPtr,param_2->m_payload[0x58]);
LAB_8008d1bc:
            local_1b0 = local_1b0 - local_1b8;
            dVar20 = (double)FLOAT_803305a4;
            local_1b4 = local_1b4 - local_1bc;
            dVar23 = (double)(float)(dVar23 - (double)local_1c0);
            dVar22 = (double)(float)(dVar22 - (double)local_1c4);
            dVar25 = (double)(float)(dVar25 - (double)local_1c8);
            if ((double)*(float *)(param_2->m_payload + 0x98) <= dVar20) break;
            for (; dVar17 = (double)*(float *)(param_2->m_payload + 0x98), dVar18 < dVar17;
                dVar18 = (double)(float)(dVar18 + dVar19)) {
              bVar1 = uVar13 == uVar12;
              uVar13 = uVar13 + 1;
              if (bVar1) {
                uVar13 = 0;
              }
              if (uVar13 == uVar16) goto LAB_8008d2c4;
              pfVar5 = (float *)(iVar11 + uVar13 * 0xc);
              dVar26 = (double)(float)(dVar26 - dVar19);
              dVar24 = (double)pfVar5[1];
              dVar21 = (double)pfVar5[2];
              dVar17 = (double)*pfVar5;
              local_338.y = (float)(dVar24 - dVar31);
              dVar33 = (double)local_338.y;
              local_338.z = (float)(dVar21 - dVar30);
              dVar32 = (double)local_338.z;
              local_338.x = (float)(dVar17 - dVar35);
              dVar34 = (double)local_338.x;
              local_32c.z = (float)dVar20;
              local_32c.y = (float)dVar20;
              local_32c.x = (float)dVar20;
              dVar19 = (double)PSVECDistance(&local_32c,&local_338);
              dVar27 = dVar30;
              dVar28 = dVar31;
              dVar29 = dVar35;
              dVar30 = dVar21;
              dVar31 = dVar24;
              dVar35 = dVar17;
            }
            dVar20 = (double)(float)(dVar26 / dVar19);
            dVar24 = (double)(float)((double)(float)(dVar34 * dVar20) + dVar29);
            dVar21 = (double)(float)((double)(float)(dVar33 * dVar20) + dVar28);
            dVar20 = (double)(float)((double)(float)(dVar32 * dVar20) + dVar27);
            dVar26 = (double)(float)(dVar26 + dVar17);
            dVar18 = (double)(float)(dVar18 - dVar17);
          }
        }
      }
LAB_8008d2c4:
      if (iVar3 != 0) {
        iVar3 = iVar3 + 0x30;
      }
      if (iVar15 != 0) {
        iVar15 = iVar15 + 0x20;
      }
      *(short *)(iVar7 + 0x1c) = *(short *)(iVar7 + 0x1c) + (short)param_2->m_initWOrk;
      iVar7 = iVar7 + 0x1f8;
    }
  }
  return;
}

