// Function: addtev_lightmap__12CMaterialManFl
// Entry: 80042814
// Size: 836 bytes

void addtev_lightmap__12CMaterialManFl(int param_1,int param_2)

{
  int iVar1;
  uint local_18;
  uint local_14;
  
  if (((uint)*(byte *)(param_1 + 0x208) & 1 << param_2) == 0) {
    GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
    iVar1 = param_1 + param_2 * 4;
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(iVar1 + 0x180),
               *(undefined4 *)(iVar1 + 0x158),0xff);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (*(undefined4 *)(param_1 + 0x60),0xf,8,9,0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
              (*(undefined4 *)(param_1 + 0x60),0,0);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  }
  else {
    local_14 = (uint)*(byte *)(param_1 + param_2 + 0x209);
    local_18 = local_14;
    GXSetTevKColor(param_2,&local_18);
    GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
    iVar1 = param_1 + param_2 * 4;
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(iVar1 + 0x180),
               *(undefined4 *)(iVar1 + 0x158),0xff);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (*(undefined4 *)(param_1 + 0x60),0xf,8,9,0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,2);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
              (*(undefined4 *)(param_1 + 0x60),0,0);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
    GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(iVar1 + 0x180),
               *(int *)(iVar1 + 0x158) + 1,0xff);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (*(undefined4 *)(param_1 + 0x60),0xf,8,9,0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
              (*(undefined4 *)(param_1 + 0x60),0,0);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
    GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
    GXSetTevKColorSel(*(undefined4 *)(param_1 + 0x60),param_2 + 0x1c);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
              (*(undefined4 *)(param_1 + 0x60),0xff,0xff,0xff);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (*(undefined4 *)(param_1 + 0x60),4,0,0xe,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
              (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
              (*(undefined4 *)(param_1 + 0x60),0,0);
    *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  }
  return;
}

