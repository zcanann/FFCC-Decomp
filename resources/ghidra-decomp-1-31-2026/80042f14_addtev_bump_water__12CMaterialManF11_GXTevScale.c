// Function: addtev_bump_water__12CMaterialManF11_GXTevScale
// Entry: 80042f14
// Size: 852 bytes

void addtev_bump_water__12CMaterialManF11_GXTevScale(int param_1,undefined4 param_2)

{
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  GXSetIndTexMtx(1,0x8026901c,0);
  local_24 = FLOAT_8032faf4;
  local_28 = FLOAT_8032fb20;
  local_20 = FLOAT_8032faf4;
  local_1c = FLOAT_8032faf4;
  local_18 = FLOAT_8032fb20;
  local_14 = FLOAT_8032faf4;
  GXSetIndTexMtx(2,&local_28,1);
  GXSetNumIndStages(2);
  GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x13c),
             *(undefined4 *)(param_1 + 0x134),4);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,8,10,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,param_2,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,4,5,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
            (*(undefined4 *)(param_1 + 0x60),0,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  GXSetIndTexOrder(0,*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(param_1 + 0x1c4));
  GXSetIndTexCoordScale(0,0,0);
  GXSetIndTexOrder(1,*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(param_1 + 0x1c4));
  GXSetIndTexCoordScale(1,0,0);
  GXSetTevIndBumpXYZ(*(undefined4 *)(param_1 + 0x60),0,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 500),
             *(undefined4 *)(param_1 + 0x1c8),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,0,8,0xf);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  GXSetTevIndBumpXYZ(*(undefined4 *)(param_1 + 0x60),0,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x1f8),
             *(undefined4 *)(param_1 + 0x1c8),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,0,0xc,9);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  GXSetTevIndWarp(*(undefined4 *)(param_1 + 0x60),1,1,0,2);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x1fc),
             *(undefined4 *)(param_1 + 0x1cc),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),8,0,1,0xf);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  return;
}

