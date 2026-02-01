// Function: addtev_bump_st__12CMaterialManFi11_GXTevScale
// Entry: 80043268
// Size: 1092 bytes

void addtev_bump_st__12CMaterialManFi11_GXTevScale(int param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined auStack_30 [36];
  
  GXSetIndTexMtx(1,auStack_30,0);
  GXSetNumIndStages(1);
  GXSetIndTexOrder(0,*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(param_1 + 0x1c4));
  GXSetIndTexCoordScale(0,*(undefined *)(DAT_8032ece8 + 0x34),*(undefined *)(DAT_8032ece8 + 0x35));
  GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x13c),
             *(undefined4 *)(param_1 + 0x134),4);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,8,10,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,param_3,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,4,5,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
            (*(undefined4 *)(param_1 + 0x60),0,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  if (param_2 == 0) {
    GXSetTevIndirect(1,0,0,3,5,6,6,0,0,0);
    GXSetTevIndirect(2,0,0,3,9,6,6,1,0,0);
    GXSetTevIndirect(3,0,0,0,0,0,0,1,0,0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x1ec),
               *(uint *)(param_1 + 0x1c8) | 0x100,0xff);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(*(undefined4 *)(param_1 + 0x60),4);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x1f0),
               *(uint *)(param_1 + 0x1c8) | 0x100,0xff);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(*(undefined4 *)(param_1 + 0x60),4);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
    if (*(char *)(DAT_8032ece8 + 0xa3) == '\0') {
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 500),
                 *(undefined4 *)(param_1 + 0x1c8),0xff);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)(param_1 + 0x60),0xf,0,8,9);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)(param_1 + 0x60),0,0,1,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
      *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
    }
    else {
      uVar1 = (uint)(int)*(short *)(DAT_8032ece8 + 0x20) >> 0x1f ^ 1;
      if (uVar1 != 0) {
        GXSetTexCoordGen2(*(undefined4 *)(param_1 + 0x200),1,4,0x3c,0,0x7d);
      }
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 500),
                 *(undefined4 *)(param_1 + 0x1c8),0xff);
      uVar2 = 0;
      if (uVar1 != 0) {
        uVar2 = 0xf;
      }
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)(param_1 + 0x60),0xf,4,9,uVar2);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)(param_1 + 0x60),0,0,0,1,-uVar1 >> 0x1f);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
      *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
      if (uVar1 != 0) {
        GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x200),
                   *(undefined4 *)(param_1 + 0x1d0),0xff);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)(param_1 + 0x60),0xf,2,8,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
        *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
      }
    }
  }
  return;
}

