// Function: drawOverlap__9CCharaPcsFv
// Entry: 800771c4
// Size: 1816 bytes

void drawOverlap__9CCharaPcsFv(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  CCharaPcsCHandle *handle;
  int iVar5;
  uint uVar6;
  undefined4 local_168;
  undefined4 local_164;
  undefined auStack_160 [4];
  undefined4 local_15c;
  undefined auStack_158 [4];
  undefined4 local_154;
  undefined auStack_150 [4];
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  float local_138;
  float local_134;
  float local_130;
  Mtx MStack_12c;
  Mat4x4 MStack_fc;
  Mtx MStack_bc;
  Mtx MStack_8c;
  Mtx MStack_5c;
  
  if (*(int *)(param_1 + 0x24) != 0) {
    local_144 = 0x280;
    local_13c = 0;
    local_140 = 0;
    local_148 = 0x1c0;
    uVar2 = GetBackBufferRect__8CGraphicFRiRiRiRii
                      (&Graphic,&local_13c,&local_140,&local_144,&local_148,0);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_5c);
    C_MTXOrtho(FLOAT_80330288,FLOAT_803302c8,FLOAT_80330288,FLOAT_803302cc,FLOAT_803302a8,
               FLOAT_803302d0,(Mtx *)&MStack_fc);
    GXSetProjection(&MStack_fc,1);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_150,0,0,0,0xff);
    local_14c = *puVar3;
    GXSetChanMatColor(4,&local_14c);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetNumTevStages(1);
    GXSetZMode(1,7,1);
    GXSetTevDirect(0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (0,0,1,2,3);
    SetFog__8CGraphicFii(&Graphic,0,0);
    PSMTXIdentity(&MStack_12c);
    GXLoadPosMtxImm(&MStack_12c,0);
    GXSetCullMode(0);
    GXBegin(0x98,0,4);
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302d4;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302d4;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_803302d4;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_803302d4;
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_fc);
    GXSetProjection(&MStack_fc,0);
    local_138 = FLOAT_80330288;
    local_134 = FLOAT_8033028c;
    local_130 = FLOAT_80330288;
    C_MTXLookAt(&MStack_8c,(Vec *)(param_1 + 0x2c),&local_138,(Vec *)(param_1 + 0x38));
    PSMTXCopy(&MStack_8c,&CameraPcs.m_cameraMatrix);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (0,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,1,2,3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (2,0,1,2,3);
    SetFog__8CGraphicFii(&Graphic,1,0);
    local_168 = *(undefined4 *)(param_1 + 0xe8);
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs,&local_168);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,3);
    uVar6 = 0;
    iVar4 = param_1;
    iVar5 = param_1;
    do {
      local_164 = *(undefined4 *)(iVar5 + 0xf0);
      uVar1 = countLeadingZeros(2 - uVar6);
      SetDiffuse__9CLightPcsFUl8_GXColorP3Veci
                (&LightPcs,uVar6,&local_164,iVar4 + 0x108,uVar1 >> 5 & 0xff);
      uVar6 = uVar6 + 1;
      iVar4 = iVar4 + 0xc;
      iVar5 = iVar5 + 4;
    } while (uVar6 < 3);
    handle = *(CCharaPcsCHandle **)(*(int *)(param_1 + 0x4c) + 0x160);
    while( true ) {
      if (*(CCharaPcsCHandle **)(param_1 + 0x4c) == handle) break;
      if ((MiniGamePcs._25732_4_ & 0x8000) != 0) {
        draw__Q29CCharaPcs7CHandleFii(handle,0,1);
      }
      handle = handle->m_next;
    }
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    puVar3 = (undefined4 *)
             __ct__6CColorFUcUcUcUc(auStack_158,0,0,0,*(uint *)(param_1 + 0x28) & 0xff);
    local_154 = *puVar3;
    GXSetChanMatColor(4,&local_154);
    PSMTXIdentity(&MStack_12c);
    GXLoadPosMtxImm(&MStack_12c,0);
    GXSetCullMode(0);
    C_MTXOrtho(FLOAT_80330288,FLOAT_803302c8,FLOAT_80330288,FLOAT_803302cc,FLOAT_80330288,
               FLOAT_803302d8,(Mtx *)&MStack_fc);
    GXSetProjection(&MStack_fc,1);
    PSMTXIdentity(&MStack_12c);
    GXLoadPosMtxImm(&MStack_12c,0);
    GXSetCurrentMtx(0);
    GXSetZMode(0,7,0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetNumTevStages(1);
    SetFog__8CGraphicFii(&Graphic,0,0);
    GXSetTevDirect(0);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    GXBegin(0x98,0,4);
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_80330288;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
    puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_160,0xff,0xff,0xff,0xff);
    local_15c = *puVar3;
    GXSetChanMatColor(4,&local_15c);
    GXLoadTexObj(uVar2,0);
    PSMTXScale(FLOAT_803302dc,FLOAT_803302e0,FLOAT_8033028c,&MStack_bc);
    GXLoadTexMtxImm(&MStack_bc,0x1e,1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xd,1,3,0);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
    GXBegin(0x98,0,4);
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000._0_2_ = 0x280;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000._0_2_ = 0;
    DAT_cc008000._0_2_ = 0x1c0;
    DAT_cc008000 = FLOAT_803302cc;
    DAT_cc008000 = FLOAT_803302c8;
    DAT_cc008000 = FLOAT_80330288;
    DAT_cc008000._0_2_ = 0x280;
    DAT_cc008000._0_2_ = 0x1c0;
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_fc);
    GXSetProjection(&MStack_fc,0);
    PSMTXCopy(&MStack_5c,&CameraPcs.m_cameraMatrix);
  }
  return;
}

