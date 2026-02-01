// Function: pppRenderYmBreath
// Entry: 800bffec
// Size: 1292 bytes

/* WARNING: Removing unreachable block (ram,0x800c04dc) */
/* WARNING: Removing unreachable block (ram,0x800bfffc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmBreath(pppYmBreath *pppYmBreath,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  int *piVar14;
  float *pfVar15;
  Mtx *a;
  Vec *source;
  double dVar16;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  Vec local_170;
  Vec local_164;
  Mtx local_158;
  pppFMATRIX pStack_128;
  Mtx MStack_f8;
  Mtx local_c8;
  Mtx MStack_98;
  undefined8 local_68;
  longlong local_60;
  longlong local_58;
  longlong local_50;
  
  iVar8 = *param_3->m_serializedDataOffsets;
  iVar7 = param_3->m_serializedDataOffsets[1];
  source = *(Vec **)(&pppYmBreath->field_0xb0 + iVar8);
  a = *(Mtx **)(&pppYmBreath->field_0xb4 + iVar8);
  pfVar15 = *(float **)(&pppYmBreath->field_0xb8 + iVar8);
  piVar14 = *(int **)(&pppYmBreath->field_0xbc + iVar8);
  iVar13 = *(int *)(&pppYmBreath->field_0xc0 + iVar8);
  if (param_2->m_stepValue != 9.18341e-41) {
    puVar12 = *(undefined4 **)
               (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA + (int)param_2->m_stepValue * 4
               );
    pppSetBlendMode__FUc(param_2->m_payload[8]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2->m_payload + 0xb0),(pppCVector *)0x0,(pppFMATRIX *)0x0,
               param_2->m_payload[0xb6],param_2->m_payload[0xb5],param_2->m_payload[8],0,1,1,0);
    bVar2 = (&pppYmBreath->field_0x88)[iVar7];
    bVar3 = (&pppYmBreath->field_0x89)[iVar7];
    bVar4 = (&pppYmBreath->field_0x8a)[iVar7];
    bVar5 = (&pppYmBreath->field_0x8b)[iVar7];
    for (iVar7 = 0; iVar7 < iVar13; iVar7 = iVar7 + 1) {
      if (0 < *(short *)&source[2].z) {
        PSMTXIdentity(&local_158);
        local_158.value[0][0] = source[4].y * (pppMngStPtr->m_scale).x;
        local_158.value[1][1] = source[4].z * (pppMngStPtr->m_scale).y;
        local_158.value[2][2] = local_158.value[0][0];
        if (FLOAT_80330c80 != source[3].y) {
          PSMTXRotRad(FLOAT_80330c84 * source[3].y,&MStack_f8,0x7a);
          PSMTXConcat(&local_158,&MStack_f8,&local_158);
        }
        pppUnitMatrix__FR10pppFMATRIX(&pStack_128);
        PSMTXConcat(a,&(pppYmBreath->field0_0x0).m_localMatrix,&pStack_128);
        PSMTXConcat(&ppvCameraMatrix0,&pStack_128,&pStack_128);
        PSMTXMultVec(&pStack_128,source,&local_170);
        local_158.value[0][3] = local_170.x;
        local_158.value[1][3] = local_170.y;
        local_158.value[2][3] = local_170.z;
        GXLoadPosMtxImm(&local_158,0);
        local_68 = (double)CONCAT44(0x43300000,bVar5 ^ 0x80000000);
        iVar11 = (int)((float)(local_68 - DOUBLE_80330c88) - source[6].y);
        uVar6 = (uint)bVar2;
        uVar9 = (uint)bVar3;
        uVar10 = (uint)bVar4;
        iVar1 = iVar11;
        if (pfVar15 != (float *)0x0) {
          iVar1 = (int)*pfVar15;
          local_68 = (double)(longlong)(int)pfVar15[1];
          local_58 = (longlong)(int)pfVar15[2];
          local_50 = (longlong)(int)pfVar15[3];
          uVar6 = (uint)bVar2 + iVar1;
          uVar9 = (uint)bVar3 + (int)pfVar15[1];
          uVar10 = (uint)bVar4 + (int)pfVar15[2];
          iVar11 = iVar11 + (int)pfVar15[3];
        }
        local_60 = (longlong)iVar1;
        if ((int)uVar6 < 0) {
          uVar6 = 0;
        }
        else if (0xff < (int)uVar6) {
          uVar6 = 0xff;
        }
        if ((int)uVar9 < 0) {
          uVar9 = 0;
        }
        else if (0xff < (int)uVar9) {
          uVar9 = 0xff;
        }
        if ((int)uVar10 < 0) {
          uVar10 = 0;
        }
        else if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        if (iVar11 < 0) {
          iVar11 = 0;
        }
        else if (0x7f < iVar11) {
          iVar11 = 0x7f;
        }
        local_17c = CONCAT31(CONCAT21(CONCAT11((char)uVar6,(char)uVar9),(char)uVar10),(char)iVar11);
        local_174 = local_17c;
        GXSetChanAmbColor(4,&local_17c);
        pppDrawShp__FPlsP12CMaterialSetUc
                  (*puVar12,(int)*(short *)((int)&source[7].y + 2),pppEnvStPtr->m_materialSetPtr,
                   param_2->m_payload[8]);
      }
      if (a != (Mtx *)0x0) {
        a = a + 1;
      }
      if (pfVar15 != (float *)0x0) {
        pfVar15 = pfVar15 + 8;
      }
      source = source + 8;
    }
    if ((CFlat._4764_4_ & 0x200000) != 0) {
      for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)param_2->m_payload; iVar7 = iVar7 + 1) {
        if (*piVar14 == 1) {
          if (iVar7 == 2) {
            local_178 = 0x800000ff;
          }
          else if (iVar7 < 2) {
            if (iVar7 == 0) {
              local_178 = 0x800000ff;
            }
            else {
              if (iVar7 < 0) goto LAB_800c03c0;
              local_178 = 0x8080ffff;
            }
          }
          else if (iVar7 < 4) {
            local_178 = 0x808080ff;
          }
          else {
LAB_800c03c0:
            local_178 = 0x6080ff;
          }
          iVar11 = -1;
          dVar16 = (double)(float)piVar14[10];
          iVar13 = 0;
          for (uVar6 = (uint)*(ushort *)((int)&param_2->m_arg3 + 2); uVar6 != 0; uVar6 = uVar6 - 1)
          {
            if (*(char *)(piVar14[2] + iVar13) != -1) {
              iVar11 = (int)*(char *)(piVar14[1] + iVar13);
              break;
            }
            iVar13 = iVar13 + 1;
          }
          PSMTXIdentity(&local_c8);
          local_c8.value[0][0] = (float)dVar16;
          local_c8.value[1][1] = (float)dVar16;
          local_c8.value[2][2] = (float)dVar16;
          PSMTXConcat((Mtx *)(*(int *)(&pppYmBreath->field_0xb4 + iVar8) + iVar11 * 0x30),
                      &(pppYmBreath->field0_0x0).m_localMatrix,&MStack_98);
          PSMTXConcat(&ppvCameraMatrix0,&MStack_98,&MStack_98);
          PSMTXMultVec(&MStack_98,(Vec *)(piVar14 + 3),&local_164);
          local_c8.value[0][3] = local_164.x;
          local_c8.value[1][3] = local_164.y;
          local_c8.value[2][3] = local_164.z;
          local_180 = local_178;
          DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&local_c8,&local_180);
        }
        piVar14 = piVar14 + 0x17;
      }
      pppSetBlendMode__FUc(1);
      pppSetBlendMode__FUc(0);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,2);
    }
  }
  return;
}

