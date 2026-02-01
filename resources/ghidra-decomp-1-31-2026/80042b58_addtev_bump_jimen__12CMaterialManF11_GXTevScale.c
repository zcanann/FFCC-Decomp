// Function: addtev_bump_jimen__12CMaterialManF11_GXTevScale
// Entry: 80042b58
// Size: 264 bytes

void addtev_bump_jimen__12CMaterialManF11_GXTevScale(int param_1)

{
  GXSetIndTexMtx(1,0x8026901c,0);
  GXSetNumIndStages(1);
  GXSetIndTexOrder(0,*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(param_1 + 0x1c4));
  GXSetIndTexCoordScale(0,0,0);
  GXSetTevIndBumpXYZ(*(undefined4 *)(param_1 + 0x60),0,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x1f8),
             *(undefined4 *)(param_1 + 0x1c8),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,4,9,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  return;
}

