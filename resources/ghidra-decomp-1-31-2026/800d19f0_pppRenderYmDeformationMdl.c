// Function: pppRenderYmDeformationMdl
// Entry: 800d19f0
// Size: 1384 bytes

/* WARNING: Type propagation algorithm not settling */

void pppRenderYmDeformationMdl(pppYmDeformationMdl *pppYmDeformationMdl,UnkB *param_2,UnkC *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  pppModelSt *pppModelSt;
  short *psVar4;
  uint local_1a0;
  uint local_19c [4];
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  undefined auStack_15c [48];
  float local_12c;
  float local_128;
  float local_11c;
  float local_118;
  Mtx local_fc;
  Mtx MStack_cc;
  Mat4x4 local_9c;
  Mtx MStack_5c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  local_19c[3] = 0;
  psVar4 = (short *)(&pppYmDeformationMdl->field_0x80 + param_3->m_serializedDataOffsets[2]);
  if (param_2->m_dataValIndex != 0xffff) {
    iVar2 = param_3->m_serializedDataOffsets[1];
    pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
    iVar3 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      ((CMapMesh *)pppModelSt,pppEnvStPtr->m_materialSetPtr,local_19c + 3);
    PSMTXIdentity(&MStack_5c);
    pppSetBlendMode__FUc(0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    uVar1 = countLeadingZeros((uint)param_2->m_payload[0x18]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (*(float *)(param_2->m_payload + 0x10),
               (pppCVector *)(&pppYmDeformationMdl->field_0x88 + iVar2),
               (pppFMATRIX *)&pppYmDeformationMdl->field_0x40,param_2->m_payload[0x17],
               param_2->m_payload[0x16],param_2->m_payload[0x14],param_2->m_payload[0x15],
               (byte)(uVar1 >> 5),1,0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,1,7,0);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,1,2,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,9,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,4);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    pppSetBlendMode__FUc(param_2->m_payload[0x14]);
    if (param_2->m_payload[0x14] == '\0') {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,5,1);
    }
    if (param_2->m_payload[0x14] == '\x03') {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,1,5,1);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
    }
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,0xff);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(1,3);
    GXClearVtxDesc();
    GXSetVtxDesc(9,3);
    GXSetVtxDesc(10,3);
    GXSetVtxDesc(0xb,3);
    GXSetVtxDesc(0xd,3);
    local_19c[0] = 0x280;
    local_19c[2] = 0;
    local_19c[1] = 0;
    local_1a0 = 0x1c0;
    iVar2 = GetBackBufferRect__8CGraphicFRiRiRiRii
                      (&Graphic,local_19c + 2,local_19c + 1,local_19c,&local_1a0,0);
    if (iVar2 != 0) {
      PSMTXIdentity(&local_fc);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&local_9c);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_cc);
      uStack_1c = local_1a0 ^ 0x80000000;
      uStack_24 = local_19c[0] ^ 0x80000000;
      local_20 = 0x43300000;
      local_28 = 0x43300000;
      local_fc.value[0][0] =
           local_9c.value[0][0] *
           (FLOAT_80330d98 / (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80330db0));
      local_fc.value[1][1] =
           local_9c.value[1][1] *
           -(FLOAT_80330d9c / (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80330db0));
      local_fc.value[1][0] = local_9c.value[1][0];
      local_fc.value[2][0] = local_9c.value[2][0];
      local_fc.value[0][1] = local_9c.value[0][1];
      local_fc.value[2][1] = local_9c.value[2][1];
      local_fc.value[0][2] = FLOAT_80330da0;
      local_fc.value[1][2] = FLOAT_80330da0;
      local_fc.value[2][2] = FLOAT_80330da4;
      PSMTXConcat(&local_fc,(Mtx *)&pppYmDeformationMdl->field_0x40,&local_fc);
      GXLoadTexMtxImm(&local_fc,0x1e,0);
      GXSetTexCoordGen2(0,0,0,0x1e,0,0x7d);
      GXSetTexCoordGen2(1,1,4,0x3c,0,0x7d);
      GXSetNumIndStages(1);
      GXSetIndTexOrder(0,1,1);
      GXSetTevIndWarp(0,0,1,0,1);
      GXSetIndTexCoordScale(0,0,0);
      if ((*psVar4 == 0) || (*psVar4 == 0x168)) {
        *psVar4 = 1;
      }
      local_20 = 0x43300000;
      uStack_1c = (int)*psVar4 ^ 0x80000000;
      PSMTXRotRad(FLOAT_80330da8 * (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80330db0)
                  ,&local_12c,0x7a);
      local_164 = *(float *)(psVar4 + 2);
      local_174 = local_12c * local_164;
      local_170 = local_128 * local_164;
      local_168 = local_11c * local_164;
      local_164 = local_118 * local_164;
      local_16c = FLOAT_80330dac;
      local_160 = FLOAT_80330dac;
      GXSetIndTexMtx(1,&local_174,1);
      GXLoadTexObj(iVar2,0);
      GXLoadTexObj(iVar3 + 0x28,1);
      pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppYmDeformationMdl->field_0x70,0);
      GXSetTevDirect(1);
      GXSetNumIndStages(0);
      GXSetIndTexCoordScale(0,0,0);
      PSMTXRotRad(FLOAT_80330dac,auStack_15c,0x7a);
      local_18c = FLOAT_80330dac;
      local_188 = FLOAT_80330dac;
      local_184 = FLOAT_80330dac;
      local_180 = FLOAT_80330dac;
      local_17c = FLOAT_80330dac;
      local_178 = FLOAT_80330dac;
      GXSetIndTexMtx(1,&local_18c,1);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
      pppInitBlendMode__Fv();
    }
  }
  return;
}

