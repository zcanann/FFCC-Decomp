// Function: SetTextureTev__11CTextureManFP8CTexture
// Entry: 8003b9ec
// Size: 804 bytes

undefined4 SetTextureTev__11CTextureManFP8CTexture(CTextureMan *textureMan,CTexture *texture)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  GXSetNumIndStages(0);
  if (texture == (CTexture *)0x0) {
    GXSetNumTevStages(1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    uVar2 = 1;
  }
  else {
    bVar1 = false;
    if ((texture->field93_0x60 == 9) || (texture->field93_0x60 == 8)) {
      bVar1 = true;
    }
    if (bVar1) {
      local_10 = 0xffff0000;
      local_c = 0xffff;
      local_14 = 0xffff0000;
      GXSetTevColor(1,&local_14);
      local_18 = local_c;
      GXSetTevColor(2,&local_18);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (0,0,1,2,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (1,0,3,3,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (2,2,2,2,3);
      GXSetTevKAlphaSel(0,0);
      GXSetTevKAlphaSel(1,0);
      GXSetTevKAlphaSel(2,0);
      GXSetNumTevStages(3);
      GXSetTevDirect(0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,8,2,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
      GXSetTevDirect(1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,0xf,8,4,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,7,6,4,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,2);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,0xff);
      GXSetTevDirect(2);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (2,0xf,0,10,0xf);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (2,7,0,5,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
      uVar2 = 3;
    }
    else {
      GXSetNumTevStages(1);
      GXSetTevDirect(0);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      uVar2 = 1;
    }
  }
  return uVar2;
}

