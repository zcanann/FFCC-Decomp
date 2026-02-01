// Function: SetEnvMap__FP7PYmManaP7VYmMana
// Entry: 800d7ff8
// Size: 1816 bytes

void SetEnvMap__FP7PYmManaP7VYmMana(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  
  GXSetNumChans(1);
  GXSetChanCtrl(4,0,0,1,0,0,2);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,0xf);
  iVar1 = *(int *)(param_2 + 0x80);
  local_20 = 0xffffffff;
  local_18 = (uint)*(byte *)(param_2 + 0xe8);
  local_1c = CONCAT31(0xffffff,*(byte *)(param_2 + 0xe8));
  local_24 = 0xffffffff;
  GXSetChanAmbColor(4,&local_24);
  local_28 = local_20;
  GXSetChanMatColor(4,&local_28);
  local_2c = local_18;
  GXSetTevKColor(0,&local_2c);
  local_30 = local_1c;
  GXSetTevKColor(1,&local_30);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (1,3,3,3,3);
  GXSetTevDirect(0);
  GXLoadTexObj(iVar1 + 0x28,0);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,0xf,0xf,0xc);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,7,7,4);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,2,1,1);
  GXSetTevDirect(1);
  GXLoadTexObj(iVar1 + 0x28,0);
  GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (1,0xf,0xf,0xf,0xc);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (1,7,7,7,4);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,2,1,2);
  GXSetTevDirect(2);
  GXLoadTexObj(*(undefined4 *)(param_2 + 0x2c),1);
  GXSetTexCoordGen2(2,1,4,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,2,1,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
  local_34 = local_18;
  GXSetTevKColor(0,&local_34);
  GXSetTevKColorSel(2,0xc);
  GXSetTevKAlphaSel(2,0x1c);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (2,10,0xe,8,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,8,0,0,1,3);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (2,7,7,7,1);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,0,1,0);
  GXSetTevDirect(3);
  GXLoadTexObj(*(undefined4 *)(param_2 + 0x2c),1);
  GXSetTexCoordGen2(3,1,4,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(3,3,0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3,0,0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (3,0xf,6,9,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3,0,0,0,1,3);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (3,7,7,7,1);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3,0,0,0,1,0);
  GXSetTevDirect(4);
  GXLoadTexObj(*(undefined4 *)(param_2 + 0x28),2);
  GXSetTexCoordGen2(4,1,5,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(4,4,2,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(4,0,0);
  local_38 = local_1c;
  GXSetTevKColor(1,&local_38);
  GXSetTevKColorSel(4,0xd);
  GXSetTevKAlphaSel(4,0x1d);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (4,0xe,0xb,8,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(4,8,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (4,7,7,7,2);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(4,0,0,0,1,0);
  GXSetTevDirect(5);
  GXLoadTexObj(*(undefined4 *)(param_2 + 0x28),2);
  GXSetTexCoordGen2(5,1,5,0x3c,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(5,5,0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(5,0,0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (5,0xf,0,9,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(5,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (5,7,7,7,2);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(5,0,0,0,1,0);
  GXSetTevDirect(6);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(6,0xff,0xff,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(6,0,0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (6,0xf,6,0xc,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(6,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (6,7,1,6,2);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(6,0,0,0,1,0);
  GXSetTevDirect(7);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(7,0xff,0xff,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(7,0,0);
  GXSetTevKAlphaSel(7,0x1c);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (7,0xf,0xf,0xf,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(7,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (7,7,0,6,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(7,0,0,0,1,0);
  GXSetNumTevStages(8);
  GXSetNumTexGens(6);
  return;
}

