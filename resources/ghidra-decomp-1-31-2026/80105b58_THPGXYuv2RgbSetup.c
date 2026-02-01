// Function: THPGXYuv2RgbSetup
// Entry: 80105b58
// Size: 1268 bytes

void THPGXYuv2RgbSetup(int param_1)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  Mtx MStack_a4;
  Mtx MStack_74;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  uVar2 = (uint)*(ushort *)(param_1 + 4);
  uVar1 = (uint)*(ushort *)(param_1 + 6);
  GXSetPixelFmt(0,0);
  uStack_2c = uVar1 ^ 0x80000000;
  uStack_24 = uVar2 ^ 0x80000000;
  local_30 = 0x43300000;
  local_28 = 0x43300000;
  C_MTXOrtho(FLOAT_80331884,(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80331890),
             FLOAT_80331884,(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80331890),
             FLOAT_80331884,FLOAT_80331888,&MStack_74);
  GXSetProjection(&MStack_74,1);
  uStack_1c = uVar2 ^ 0x80000000;
  uStack_14 = uVar1 ^ 0x80000000;
  dVar3 = (double)FLOAT_80331884;
  local_20 = 0x43300000;
  local_18 = 0x43300000;
  GXSetViewport(dVar3,dVar3,
                (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80331890),
                (double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80331890),dVar3,
                (double)FLOAT_8033188c);
  GXSetScissor(0,0,uVar2,uVar1);
  PSMTXIdentity(&MStack_a4);
  GXLoadPosMtxImm(&MStack_a4,0);
  GXSetCurrentMtx(0);
  GXSetZMode(1,7,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,1,0,0);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(0);
  GXSetDispCopyGamma(0);
  GXSetNumChans(0);
  GXSetNumTexGens(2);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetTexCoordGen2(1,1,4,0x3c,0,0x7d);
  GXInvalidateTexAll();
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(7,9,1,3,0);
  GXSetVtxAttrFmt(7,0xd,1,2,0);
  GXSetNumTevStages(4);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,1,1,0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,8,0xe,2);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,0,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,4,6,1);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,1,0,0,0,0);
  GXSetTevKColorSel(0,0xc);
  GXSetTevKAlphaSel(0,0x1c);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,2,0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (1,0xf,8,0xe,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,1,0,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (1,7,4,6,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,1,0,0,0,0);
  GXSetTevKColorSel(1,0xd);
  GXSetTevKAlphaSel(1,0x1d);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0,0,0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (2,0xf,8,0xc,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (2,4,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(3,0xff,0xff,0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (3,1,0,0xe,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (3,7,7,7,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3,0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3,0,0);
  GXSetTevKColorSel(3,0xe);
  local_ac = DAT_80331870;
  local_a8 = DAT_80331874;
  GXSetTevColorS10(1,&local_ac);
  local_b0 = DAT_80331878;
  GXSetTevKColor(0,&local_b0);
  local_b4 = DAT_8033187c;
  GXSetTevKColor(1,&local_b4);
  local_b8 = DAT_80331880;
  GXSetTevKColor(2,&local_b8);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  GXSetCullMode(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,0,0,7,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,0,0);
  return;
}

