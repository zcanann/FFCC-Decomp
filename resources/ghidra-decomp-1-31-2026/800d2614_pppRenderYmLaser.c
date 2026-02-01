// Function: pppRenderYmLaser
// Entry: 800d2614
// Size: 3008 bytes

/* WARNING: Removing unreachable block (ram,0x800d31b8) */
/* WARNING: Removing unreachable block (ram,0x800d31b0) */
/* WARNING: Removing unreachable block (ram,0x800d31a8) */
/* WARNING: Removing unreachable block (ram,0x800d2634) */
/* WARNING: Removing unreachable block (ram,0x800d262c) */
/* WARNING: Removing unreachable block (ram,0x800d2624) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmLaser(pppYmLaser *pppYmLaser,UnkB *param_2,UnkC *param_3)

{
  byte bVar1;
  char cVar2;
  undefined3 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  uint uVar9;
  float fVar10;
  undefined4 *puVar11;
  uint uVar12;
  float *pfVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  undefined4 local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  Vec local_2d0;
  Vec local_2c4;
  Vec local_2b8;
  pppFMATRIX local_2ac;
  pppFMATRIX local_27c;
  pppFMATRIX local_24c;
  pppFMATRIX local_21c;
  Mtx MStack_1ec;
  Mtx MStack_1bc;
  Mtx local_188;
  Mtx MStack_158;
  Mtx local_128;
  pppFMATRIX pStack_f8;
  pppFMATRIX local_c8;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  float local_88;
  float local_84;
  
  iVar5 = param_3->m_serializedDataOffsets[1];
  pfVar13 = (float *)((int)(&pppYmLaser->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  if (param_2->m_dataValIndex != 0xffff) {
    iVar6 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
    pppSetBlendMode__FUc(param_2->m_payload[0x1c]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80330dc0,(pppCVector *)(&pppYmLaser->field_0x88 + iVar5),
               &(pppYmLaser->field0_0x0).m_localMatrix,param_2->m_payload[0x39],
               param_2->m_payload[0x38],param_2->m_payload[0x1c],0,1,1,0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetCullMode(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,1,7,0);
    local_2d4 = *(undefined4 *)(&pppYmLaser->field_0x88 + iVar5);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,10,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,5);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    GXLoadTexObj(iVar6 + 0x28,0);
    dVar14 = (double)pfVar13[4];
    dVar15 = (double)*pfVar13;
    dVar16 = -dVar14;
    pppUnitMatrix__FR10pppFMATRIX(&pStack_f8);
    local_24c.value[0][0] = (pppYmLaser->field0_0x0).m_localMatrix.value[0][0];
    local_24c.value[0][1] = (pppYmLaser->field0_0x0).m_localMatrix.value[0][1];
    local_24c.value[0][2] = (pppYmLaser->field0_0x0).m_localMatrix.value[0][2];
    local_24c.value[0][3] = (pppYmLaser->field0_0x0).m_localMatrix.value[0][3];
    local_24c.value[1][0] = (pppYmLaser->field0_0x0).m_localMatrix.value[1][0];
    local_24c.value[1][1] = (pppYmLaser->field0_0x0).m_localMatrix.value[1][1];
    local_24c.value[1][2] = (pppYmLaser->field0_0x0).m_localMatrix.value[1][2];
    local_24c.value[1][3] = (pppYmLaser->field0_0x0).m_localMatrix.value[1][3];
    local_24c.value[2][0] = (pppYmLaser->field0_0x0).m_localMatrix.value[2][0];
    local_24c.value[2][1] = (pppYmLaser->field0_0x0).m_localMatrix.value[2][1];
    local_24c.value[2][2] = (pppYmLaser->field0_0x0).m_localMatrix.value[2][2];
    local_24c.value[2][3] = (pppYmLaser->field0_0x0).m_localMatrix.value[2][3];
    local_21c.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
    local_21c.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
    local_21c.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
    local_21c.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
    local_21c.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
    local_21c.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
    local_21c.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
    local_21c.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
    local_21c.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
    local_21c.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
    local_21c.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
    local_21c.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_c8,&local_21c,&local_24c);
    local_84 = ppvCameraMatrix0.value[2][1];
    local_27c.value[1][3] = ppvCameraMatrix0.value[1][3];
    local_88 = ppvCameraMatrix0.value[2][2];
    local_27c.value[2][1] = ppvCameraMatrix0.value[2][1];
    local_2ac.value[0][0] = local_c8.value[0][0];
    local_2ac.value[0][1] = local_c8.value[0][1];
    local_2ac.value[0][2] = local_c8.value[0][2];
    local_2ac.value[0][3] = local_c8.value[0][3];
    local_2ac.value[1][0] = local_c8.value[1][0];
    local_2ac.value[1][1] = local_c8.value[1][1];
    local_2ac.value[1][2] = local_c8.value[1][2];
    local_2ac.value[1][3] = local_c8.value[1][3];
    local_2ac.value[2][0] = local_c8.value[2][0];
    local_2ac.value[2][1] = local_c8.value[2][1];
    local_2ac.value[2][2] = local_c8.value[2][2];
    local_2ac.value[2][3] = local_c8.value[2][3];
    local_27c.value[0][0] = ppvCameraMatrix0.value[0][0];
    local_27c.value[0][1] = ppvCameraMatrix0.value[0][1];
    local_27c.value[0][2] = ppvCameraMatrix0.value[0][2];
    local_27c.value[0][3] = ppvCameraMatrix0.value[0][3];
    local_27c.value[1][0] = ppvCameraMatrix0.value[1][0];
    local_27c.value[1][1] = ppvCameraMatrix0.value[1][1];
    local_27c.value[1][2] = ppvCameraMatrix0.value[1][2];
    local_27c.value[2][0] = ppvCameraMatrix0.value[2][0];
    local_27c.value[2][2] = ppvCameraMatrix0.value[2][2];
    local_27c.value[2][3] = ppvCameraMatrix0.value[2][3];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&local_c8,&local_27c,&local_2ac);
    GXLoadPosMtxImm(&local_c8,0);
    GXBegin(0x98,7,4);
    DAT_cc008000 = (float)dVar16;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar16;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar15;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = *pfVar13;
    DAT_cc008000 = (float)dVar14;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar14;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar15;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc4;
    DAT_cc008000 = *pfVar13;
    GXBegin(0x98,7,4);
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar16;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar16;
    DAT_cc008000 = (float)dVar15;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = *pfVar13;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar14;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc4;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = FLOAT_80330dc0;
    DAT_cc008000 = (float)dVar14;
    DAT_cc008000 = (float)dVar15;
    DAT_cc008000 = local_2d4;
    DAT_cc008000 = FLOAT_80330dc4;
    DAT_cc008000 = *pfVar13;
    if (param_2->m_stepValue != 9.18341e-41) {
      puVar11 = *(undefined4 **)
                 (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                 (int)param_2->m_stepValue * 4);
      PSMTXIdentity(&local_128);
      local_128.value[0][0] = *(float *)(param_2->m_payload + 0x30) * (pppMngStPtr->m_scale).x;
      local_128.value[1][1] = *(float *)(param_2->m_payload + 0x30) * (pppMngStPtr->m_scale).y;
      local_128.value[2][2] = local_128.value[0][0];
      if (FLOAT_80330dc0 != pfVar13[0xe]) {
        PSMTXRotRad(pfVar13[0xe],&MStack_158,0x7a);
        PSMTXConcat(&local_128,&MStack_158,&local_128);
      }
      PSMTXMultVec(&ppvCameraMatrix0,(Vec *)pfVar13[7],&local_2b8);
      local_128.value[0][3] = local_2b8.x;
      local_128.value[1][3] = local_2b8.y;
      local_128.value[2][3] = local_2b8.z;
      GXLoadPosMtxImm(&local_128,0);
      pppDrawShp__FPlsP12CMaterialSetUc
                (*puVar11,(int)*(short *)(pfVar13 + 0xd),pppEnvStPtr->m_materialSetPtr,
                 param_2->m_payload[0x1c]);
      uStack_94 = (uint)param_2->m_payload[0x1e];
      local_98 = 0x43300000;
      dVar14 = (double)(FLOAT_80330dc4 /
                       (float)((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_80330dd0));
      if (param_2->m_initWOrk == 0xffff) {
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      }
      else {
        iVar5 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_initWOrk,pppEnvStPtr);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
        GXLoadTexObj(iVar5 + 0x28,0);
      }
      GXLoadPosMtxImm(&ppvCameraMatrix0,0);
      bVar1 = param_2->m_payload[0x2b];
      uVar9 = (uint)bVar1 / (uint)param_2->m_payload[0x1e];
      local_2d4 = *(undefined4 *)(param_2->m_payload + 0x28);
      GXBegin(0x90,7,(param_2->m_payload[0x1e] - 1) * 3 & 0xffff);
      iVar5 = 0;
      iVar6 = 0;
      uVar12 = 0;
      while ((int)uVar12 < (int)(param_2->m_payload[0x1e] - 1)) {
        uStack_94 = uVar12 ^ 0x80000000;
        cVar2 = (char)iVar5;
        uVar4 = uVar12 + 1;
        local_98 = 0x43300000;
        uStack_8c = uVar4 ^ 0x80000000;
        iVar5 = iVar5 + uVar9;
        uVar12 = uVar12 + 1;
        DAT_cc008000 = pfVar13[8];
        DAT_cc008000 = pfVar13[9];
        uVar3 = (undefined3)((uint)local_2d4 >> 8);
        fVar10 = (float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_94) -
                                                 DOUBLE_80330dd8));
        local_2d8 = CONCAT31(uVar3,bVar1 - cVar2);
        DAT_cc008000 = pfVar13[10];
        DAT_cc008000 = local_2d8;
        DAT_cc008000 = fVar10;
        DAT_cc008000 = FLOAT_80330dc4;
        local_90 = 0x43300000;
        puVar11 = (undefined4 *)((int)pfVar13[7] + iVar6);
        DAT_cc008000 = *puVar11;
        DAT_cc008000 = puVar11[1];
        DAT_cc008000 = puVar11[2];
        DAT_cc008000 = local_2d8;
        DAT_cc008000 = fVar10;
        DAT_cc008000 = FLOAT_80330dc0;
        iVar7 = (int)pfVar13[7] + iVar6;
        iVar6 = iVar6 + 0xc;
        DAT_cc008000 = *(undefined4 *)(iVar7 + 0xc);
        DAT_cc008000 = *(undefined4 *)(iVar7 + 0x10);
        local_2dc = CONCAT31(uVar3,bVar1 - (char)uVar9 * (char)uVar4);
        DAT_cc008000 = *(undefined4 *)(iVar7 + 0x14);
        DAT_cc008000 = local_2dc;
        DAT_cc008000 = (float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_8c) -
                                                       DOUBLE_80330dd8));
        DAT_cc008000 = FLOAT_80330dc0;
      }
      if ((CFlat._4764_4_ & 0x200000) != 0) {
        SetVtxFmt_POS_CLR__5CUtilFv(&DAT_8032ec70);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
        GXSetNumTexGens(0);
        pppSetBlendMode__FUc(1);
        local_2d4 = 0x80ff80ff;
        local_2e0 = 0x80ff80ff;
        GXSetChanAmbColor(4,&local_2e0);
        GXSetPointSize(0x28,0);
        GXBegin(0xb8,7,param_2->m_payload[0x1e] - 1);
        iVar6 = 0;
        iVar5 = 0;
        while (iVar6 < (int)(param_2->m_payload[0x1e] - 1)) {
          iVar6 = iVar6 + 1;
          puVar11 = (undefined4 *)((int)pfVar13[7] + iVar5);
          iVar5 = iVar5 + 0xc;
          DAT_cc008000 = *puVar11;
          DAT_cc008000 = puVar11[1];
          DAT_cc008000 = puVar11[2];
          DAT_cc008000 = local_2d4;
        }
        local_2d4 = 0x8080ffff;
        local_2e4 = 0x8080ffff;
        GXSetChanAmbColor(4,&local_2e4);
        GXSetLineWidth(0x14,0);
        GXBegin(0xa8,7,(param_2->m_payload[0x1e] - 1) * 4 & 0xfffc);
        iVar6 = 0;
        iVar5 = 0;
        while (iVar6 < (int)(param_2->m_payload[0x1e] - 1)) {
          iVar6 = iVar6 + 1;
          puVar11 = (undefined4 *)((int)pfVar13[7] + iVar5);
          DAT_cc008000 = *puVar11;
          DAT_cc008000 = puVar11[1];
          DAT_cc008000 = puVar11[2];
          DAT_cc008000 = local_2d4;
          iVar7 = (int)pfVar13[7] + iVar5;
          DAT_cc008000 = *(undefined4 *)(iVar7 + 0xc);
          DAT_cc008000 = *(undefined4 *)(iVar7 + 0x10);
          DAT_cc008000 = *(undefined4 *)(iVar7 + 0x14);
          DAT_cc008000 = local_2d4;
          puVar11 = (undefined4 *)((int)pfVar13[7] + iVar5);
          iVar5 = iVar5 + 0xc;
          DAT_cc008000 = *puVar11;
          DAT_cc008000 = puVar11[1];
          DAT_cc008000 = puVar11[2];
          DAT_cc008000 = local_2d4;
          DAT_cc008000 = pfVar13[8];
          DAT_cc008000 = pfVar13[9];
          DAT_cc008000 = pfVar13[10];
          DAT_cc008000 = local_2d4;
        }
        GXSetLineWidth(8,0);
        GXSetPointSize(8,0);
        GXSetZMode(1,3,0);
        if ((CFlat._4764_4_ & 0x200000) != 0) {
          dVar15 = (double)(pppMngStPtr->m_paramD * *(float *)(param_2->m_payload + 0x24));
          dVar14 = (double)PSVECDistance((Vec *)pfVar13[7],(Vec *)(pfVar13 + 8));
          local_2d0.x = FLOAT_80330dc0;
          local_2d0.y = FLOAT_80330dc0;
          local_2d0.z = FLOAT_80330dc4;
          local_2d4 = 0xffffffff;
          PSMTXIdentity(&local_188);
          local_188.value[0][0] = (float)dVar15;
          local_188.value[1][1] = (float)dVar15;
          local_188.value[2][2] = (float)dVar14;
          PSMTXConcat(&(pppYmLaser->field0_0x0).m_localMatrix,&local_188,&local_188);
          PSMTXConcat(&pppMngStPtr->m_matrix,&local_188,&local_188);
          PSMTXConcat(&ppvCameraMatrix0,&local_188,&local_188);
          PSMTXMultVec(&local_188,&local_2d0,&local_2c4);
          local_188.value[0][3] = local_2c4.x;
          local_188.value[1][3] = local_2c4.y;
          local_188.value[2][3] = local_2c4.z;
          local_2e8 = local_2d4;
          DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&local_188,&local_2e8);
        }
        GXLoadPosMtxImm(&pppYmLaser->field_0x40,0);
        dVar14 = (double)FLOAT_80330dc0;
        iVar5 = 0;
        local_2d4 = 0xffffffff;
        for (iVar6 = 0; iVar6 < (int)(uint)param_2->m_payload[0x1e]; iVar6 = iVar6 + 1) {
          pfVar8 = (float *)((int)pfVar13[7] + iVar5);
          if ((((double)*pfVar8 != dVar14) || ((double)pfVar8[1] != dVar14)) ||
             ((double)pfVar8[2] != dVar14)) {
            PSMTXScale(FLOAT_80330dc8,FLOAT_80330dc8,FLOAT_80330dc8,&MStack_1bc);
            fVar10 = pfVar13[7];
            MStack_1bc.value[0][3] = *(float *)((int)fVar10 + iVar5);
            MStack_1bc.value[1][3] = *(float *)((int)fVar10 + iVar5 + 4);
            MStack_1bc.value[2][3] = *(float *)((int)fVar10 + iVar5 + 8);
            PSMTXConcat(&ppvCameraMatrix0,&MStack_1bc,&MStack_1ec);
            local_2ec = local_2d4;
            DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&MStack_1ec,&local_2ec);
          }
          iVar5 = iVar5 + 0xc;
        }
        MStack_1bc.value[0][3] = pfVar13[8];
        MStack_1bc.value[1][3] = pfVar13[9];
        MStack_1bc.value[2][3] = pfVar13[10];
        PSMTXConcat(&ppvCameraMatrix0,&MStack_1bc,&MStack_1ec);
        local_2f0 = local_2d4;
        DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&MStack_1ec,&local_2f0);
        pppInitBlendMode__Fv();
      }
    }
  }
  return;
}

