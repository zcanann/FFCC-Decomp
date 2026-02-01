// Function: SetUpPaletteEnv__FP8CTexture
// Entry: 800e54dc
// Size: 676 bytes

void SetUpPaletteEnv__FP8CTexture(CTexture *texture)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  GXSetNumTevStages(3);
  GXSetNumTexGens(1);
  local_10 = 0xffff0000;
  local_c = 0xffff;
  local_14 = 0xffff0000;
  GXSetTevColor(2,&local_14);
  local_18 = local_c;
  GXSetTevColor(3,&local_18);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (1,0,3,3,3);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (2,2,2,2,3);
  GXSetTevDirect(0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,8,4,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,0,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
  GXSetTevDirect(1);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (1,0xf,8,6,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (1,7,6,4,7);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,2);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,0xff);
  GXSetTevDirect(2);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (2,0xf,0,10,0xf);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (2,7,0,5,7);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,1,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,2,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
  GXInitTexObjTlut(&texture->field_0x28,0);
  GXLoadTexObj(&texture->field_0x28,0);
  GXInitTexObjTlut(&texture->field_0x28,1);
  GXLoadTexObj(&texture->field_0x28,1);
  GXLoadTlut(&texture->field_0x48,0);
  GXLoadTlut(&texture->field_0x54,1);
  return;
}

