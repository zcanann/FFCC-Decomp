// Function: pppRenderYmMegaBirthShpTail2
// Entry: 8008acc4
// Size: 1840 bytes

/* WARNING: Removing unreachable block (ram,0x8008b3d8) */
/* WARNING: Removing unreachable block (ram,0x8008b3d0) */
/* WARNING: Removing unreachable block (ram,0x8008b3c8) */
/* WARNING: Removing unreachable block (ram,0x8008b3c0) */
/* WARNING: Removing unreachable block (ram,0x8008b3b8) */
/* WARNING: Removing unreachable block (ram,0x8008b3b0) */
/* WARNING: Removing unreachable block (ram,0x8008b3a8) */
/* WARNING: Removing unreachable block (ram,0x8008b3a0) */
/* WARNING: Removing unreachable block (ram,0x8008b398) */
/* WARNING: Removing unreachable block (ram,0x8008b390) */
/* WARNING: Removing unreachable block (ram,0x8008b388) */
/* WARNING: Removing unreachable block (ram,0x8008b380) */
/* WARNING: Removing unreachable block (ram,0x8008b378) */
/* WARNING: Removing unreachable block (ram,0x8008b370) */
/* WARNING: Removing unreachable block (ram,0x8008b368) */
/* WARNING: Removing unreachable block (ram,0x8008b360) */
/* WARNING: Removing unreachable block (ram,0x8008b358) */
/* WARNING: Removing unreachable block (ram,0x8008b350) */
/* WARNING: Removing unreachable block (ram,0x8008ad5c) */
/* WARNING: Removing unreachable block (ram,0x8008ad54) */
/* WARNING: Removing unreachable block (ram,0x8008ad4c) */
/* WARNING: Removing unreachable block (ram,0x8008ad44) */
/* WARNING: Removing unreachable block (ram,0x8008ad3c) */
/* WARNING: Removing unreachable block (ram,0x8008ad34) */
/* WARNING: Removing unreachable block (ram,0x8008ad2c) */
/* WARNING: Removing unreachable block (ram,0x8008ad24) */
/* WARNING: Removing unreachable block (ram,0x8008ad1c) */
/* WARNING: Removing unreachable block (ram,0x8008ad14) */
/* WARNING: Removing unreachable block (ram,0x8008ad0c) */
/* WARNING: Removing unreachable block (ram,0x8008ad04) */
/* WARNING: Removing unreachable block (ram,0x8008acfc) */
/* WARNING: Removing unreachable block (ram,0x8008acf4) */
/* WARNING: Removing unreachable block (ram,0x8008acec) */
/* WARNING: Removing unreachable block (ram,0x8008ace4) */
/* WARNING: Removing unreachable block (ram,0x8008acdc) */
/* WARNING: Removing unreachable block (ram,0x8008acd4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmMegaBirthShpTail2
               (pppYmMegaBirthShpTail2 *pppYmMegaBirthShpTail2,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  byte bVar2;
  short sVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
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
  double dVar36;
  double dVar37;
  undefined4 local_260;
  undefined4 local_25c;
  Vec local_258;
  Vec local_24c;
  Vec local_240;
  Vec local_230;
  Vec local_220;
  Vec local_210;
  Vec local_204;
  pppFMATRIX local_1f8;
  undefined4 local_1c8;
  uint uStack_1c4;
  undefined4 local_1c0;
  uint uStack_1bc;
  undefined4 local_1b8;
  uint uStack_1b4;
  undefined4 local_1b0;
  uint uStack_1ac;
  undefined4 local_1a8;
  uint uStack_1a4;
  undefined4 local_1a0;
  uint uStack_19c;
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  undefined8 local_180;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  
  iVar12 = param_3->m_serializedDataOffsets[2];
  iVar10 = param_3->m_serializedDataOffsets[1];
  iVar5 = *(int *)(&pppYmMegaBirthShpTail2->field_0xbc + iVar12);
  iVar11 = *(int *)(&pppYmMegaBirthShpTail2->field_0xc0 + iVar12);
  iVar13 = *(int *)(&pppYmMegaBirthShpTail2->field_0xc4 + iVar12);
  if (iVar5 == 0) {
    bVar1 = false;
  }
  else if (iVar11 == 0) {
    bVar1 = false;
  }
  else if ((param_2->m_payload[0x55] == '\0') || (iVar13 != 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (param_2->m_dataValIndex != 0xffff)) {
    iVar18 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                       param_2->m_dataValIndex * 4);
    uVar6 = countLeadingZeros((uint)param_2->m_payload[0x57]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2->m_payload + 0x74),(pppCVector *)0x0,
               (pppFMATRIX *)&pppYmMegaBirthShpTail2->field_0x40,param_2->m_payload[0x78],
               *(undefined *)&param_2->m_stepValue,param_2->m_payload[0x5a],0,(byte)(uVar6 >> 5),1,0
              );
    pppSetBlendMode__FUc(param_2->m_payload[0x5a]);
    for (uVar6 = 0; uVar6 < *(uint *)(&pppYmMegaBirthShpTail2->field_0xc8 + iVar12);
        uVar6 = uVar6 + 1) {
      if (*(short *)(iVar5 + 0x22) != 0) {
        uStack_19c = (uint)param_2->m_payload[0x67];
        uStack_1bc = (int)*(short *)(&pppYmMegaBirthShpTail2->field_0x86 + iVar10) ^ 0x80000000;
        uVar7 = (uint)*(ushort *)(param_2->m_payload + 0x70);
        local_1c0 = 0x43300000;
        uStack_1c4 = uVar7 - 1 ^ 0x80000000;
        local_1a0 = 0x43300000;
        fVar4 = (float)((double)CONCAT44(0x43300000,uStack_1bc) - DOUBLE_80330578) / FLOAT_80330564;
        uStack_1b4 = (uint)param_2->m_payload[100];
        uStack_1ac = (uint)param_2->m_payload[0x65];
        local_198 = (double)CONCAT44(0x43300000,(uint)param_2->m_payload[0x6b]);
        uStack_1a4 = (uint)param_2->m_payload[0x66];
        dVar24 = (double)((float)((double)CONCAT44(0x43300000,uStack_19c) - DOUBLE_80330580) * fVar4
                         );
        local_1c8 = 0x43300000;
        dVar27 = (double)FLOAT_80330560;
        dVar22 = (double)(float)((double)CONCAT44(0x43300000,uStack_1c4) - DOUBLE_80330578);
        sVar3 = *(short *)(iVar18 + (uint)*(ushort *)(iVar5 + 0x20) * 8 + 0x10);
        uVar15 = *(byte *)(iVar5 + 0x37) - 1;
        uVar16 = (uint)*(byte *)(iVar5 + 0x38);
        local_1b8 = 0x43300000;
        local_160 = (float)((double)CONCAT44(0x43300000,uStack_1b4) - DOUBLE_80330580);
        local_1b0 = 0x43300000;
        local_164 = (float)((double)CONCAT44(0x43300000,uStack_1ac) - DOUBLE_80330580);
        local_1a8 = 0x43300000;
        local_168 = (float)((double)CONCAT44(0x43300000,uStack_1a4) - DOUBLE_80330580);
        local_190 = (double)CONCAT44(0x43300000,(uint)param_2->m_payload[0x68]);
        local_188 = (double)CONCAT44(0x43300000,(uint)param_2->m_payload[0x69]);
        local_180 = (double)CONCAT44(0x43300000,(uint)param_2->m_payload[0x6a]);
        if (dVar22 == dVar27) {
          local_16c = FLOAT_80330568;
          local_170 = FLOAT_80330568;
          local_174 = FLOAT_80330568;
          fVar4 = FLOAT_80330568;
        }
        else {
          local_16c = (float)((double)(local_164 - (float)(local_188 - DOUBLE_80330580)) / dVar22);
          local_170 = (float)((double)(local_168 - (float)(local_180 - DOUBLE_80330580)) / dVar22);
          local_174 = (float)((double)(float)(dVar24 - (double)((float)(local_198 - DOUBLE_80330580)
                                                               * fVar4)) / dVar22);
          fVar4 = (float)((double)(local_160 - (float)(local_190 - DOUBLE_80330580)) / dVar22);
        }
        dVar37 = (double)fVar4;
        pppUnitMatrix__FR10pppFMATRIX(&local_1f8);
        dVar26 = (double)*(float *)(param_2->m_payload + 0x5c);
        iVar14 = iVar5 + 0x40;
        bVar2 = *(byte *)(iVar5 + 0x38);
        pfVar8 = (float *)(iVar14 + uVar16 * 0xc);
        uVar17 = uVar16 + 1;
        dVar25 = (double)*pfVar8;
        local_178 = (float)((double)(float)(dVar26 - (double)*(float *)(param_2->m_payload + 0x60))
                           / dVar22);
        dVar23 = (double)pfVar8[1];
        dVar22 = (double)pfVar8[2];
        if (uVar16 == uVar15) {
          uVar17 = 0;
        }
        pfVar8 = (float *)(iVar14 + uVar17 * 0xc);
        dVar36 = (double)*pfVar8;
        dVar32 = (double)pfVar8[1];
        dVar31 = (double)pfVar8[2];
        local_210.x = (float)(dVar36 - dVar25);
        dVar35 = (double)local_210.x;
        local_210.y = (float)(dVar32 - dVar23);
        dVar34 = (double)local_210.y;
        local_210.z = (float)(dVar31 - dVar22);
        dVar33 = (double)local_210.z;
        local_204.z = FLOAT_80330560;
        local_204.y = FLOAT_80330560;
        local_204.x = FLOAT_80330560;
        dVar28 = dVar22;
        dVar29 = dVar23;
        dVar30 = dVar25;
        dVar19 = (double)PSVECDistance(&local_204,&local_210);
        dVar20 = dVar19;
        if (param_2->m_payload[0x72] == '\0') goto LAB_8008b210;
        for (uVar7 = (uint)*(ushort *)(param_2->m_payload + 0x70); 0 < (int)uVar7; uVar7 = uVar7 - 1
            ) {
          iVar9 = iVar5 + uVar17 * 0xc;
          if (((FLOAT_80330560 != *(float *)(iVar9 + 0x40)) ||
              (FLOAT_80330560 != *(float *)(iVar9 + 0x44))) ||
             (FLOAT_80330560 != *(float *)(iVar9 + 0x48))) {
            pppUnitMatrix__FR10pppFMATRIX(&local_1f8);
            local_1f8.value[0][0] = (float)(dVar26 * (double)(pppMngStPtr->m_scale).x);
            local_1f8.value[1][1] = (float)(dVar26 * (double)(pppMngStPtr->m_scale).y);
            local_1f8.value[2][2] = (float)(dVar26 * (double)(pppMngStPtr->m_scale).z);
            local_230.x = (float)dVar25;
            local_230.y = (float)dVar23;
            local_230.z = (float)dVar22;
            if (param_2->m_payload[0x79] == '\0') {
              PSMTXMultVec(&ppvWorldMatrix,&local_230,&local_220);
            }
            else if (param_2->m_payload[0x79] == '\x01') {
              local_240.x = (pppMngStPtr->m_matrix).value[0][3];
              local_240.y = (pppMngStPtr->m_matrix).value[1][3];
              local_240.z = (pppMngStPtr->m_matrix).value[2][3];
              PSVECAdd(&local_240,&local_230,&local_230);
              PSMTXMultVec(&ppvCameraMatrix0,&local_230,&local_220);
            }
            local_1f8.value[0][3] = local_220.x;
            local_1f8.value[1][3] = local_220.y;
            local_1f8.value[2][3] = local_220.z;
            GXLoadPosMtxImm(&local_1f8,0);
            local_180 = (double)(longlong)(int)local_160;
            local_188 = (double)(longlong)(int)local_164;
            local_190 = (double)(longlong)(int)local_168;
            local_25c = ((int)local_164 & 0xffU) << 0x10;
            local_25c = CONCAT13((char)(int)local_160,local_25c._1_3_);
            iVar9 = (int)(dVar24 * (double)(FLOAT_8033056c *
                                           (FLOAT_80330570 - *(float *)(iVar5 + 0x30))));
            local_198 = (double)(longlong)iVar9;
            local_25c = CONCAT31(CONCAT21(local_25c._0_2_,(char)(int)local_168),(char)iVar9);
            local_260 = local_25c;
            GXSetChanAmbColor(4,&local_260);
            pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc
                      (iVar18 + sVar3,pppEnvStPtr->m_materialSetPtr,param_2->m_payload[0x5a]);
LAB_8008b210:
            local_160 = (float)((double)local_160 - dVar37);
            dVar22 = (double)FLOAT_80330560;
            local_164 = local_164 - local_16c;
            local_168 = local_168 - local_170;
            dVar24 = (double)(float)(dVar24 - (double)local_174);
            dVar26 = (double)(float)(dVar26 - (double)local_178);
            if ((double)*(float *)(param_2->m_payload + 0x6c) <= dVar22) break;
            for (; dVar21 = (double)*(float *)(param_2->m_payload + 0x6c), dVar19 < dVar21;
                dVar19 = (double)(float)(dVar19 + dVar20)) {
              bVar1 = uVar17 == uVar15;
              uVar17 = uVar17 + 1;
              if (bVar1) {
                uVar17 = 0;
              }
              if (uVar17 == bVar2) goto LAB_8008b324;
              pfVar8 = (float *)(iVar14 + uVar17 * 0xc);
              dVar27 = (double)(float)(dVar27 - dVar20);
              dVar25 = (double)pfVar8[1];
              dVar23 = (double)pfVar8[2];
              dVar21 = (double)*pfVar8;
              local_258.y = (float)(dVar25 - dVar32);
              dVar34 = (double)local_258.y;
              local_258.z = (float)(dVar23 - dVar31);
              dVar33 = (double)local_258.z;
              local_258.x = (float)(dVar21 - dVar36);
              dVar35 = (double)local_258.x;
              local_24c.z = (float)dVar22;
              local_24c.y = (float)dVar22;
              local_24c.x = (float)dVar22;
              dVar20 = (double)PSVECDistance(&local_24c,&local_258);
              dVar28 = dVar31;
              dVar29 = dVar32;
              dVar30 = dVar36;
              dVar31 = dVar23;
              dVar32 = dVar25;
              dVar36 = dVar21;
            }
            dVar25 = (double)(float)((double)(float)((double)(float)(dVar35 * dVar27) / dVar20) +
                                    dVar30);
            dVar23 = (double)(float)((double)(float)((double)(float)(dVar34 * dVar27) / dVar20) +
                                    dVar29);
            dVar22 = (double)(float)((double)(float)((double)(float)(dVar33 * dVar27) / dVar20) +
                                    dVar28);
            dVar27 = (double)(float)(dVar27 + dVar21);
            dVar19 = (double)(float)(dVar19 - dVar21);
          }
        }
      }
LAB_8008b324:
      if (iVar11 != 0) {
        iVar11 = iVar11 + 0x30;
      }
      if (iVar13 != 0) {
        iVar13 = iVar13 + 0x20;
      }
      iVar5 = iVar5 + 0x1b8;
    }
  }
  return;
}

