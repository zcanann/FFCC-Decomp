// Function: addtev_full_shadow__12CMaterialManFl
// Entry: 80042180
// Size: 724 bytes

void addtev_full_shadow__12CMaterialManFl(int param_1,int param_2)

{
  int iVar1;
  uint local_18;
  uint local_14;
  
  GXLoadTexMtxImm(param_1 + 100,*(undefined4 *)(param_1 + 0x19c),0);
  GXLoadTexObj(*(undefined4 *)(param_1 + 0xc4),*(undefined4 *)(param_1 + 0x194));
  GXSetTexCoordGen2(*(undefined4 *)(param_1 + 0x1a4),0,0,*(undefined4 *)(param_1 + 0x19c),0,0x7d);
  GXLoadTexMtxImm(param_1 + 0x94,*(undefined4 *)(param_1 + 0x1b4),0);
  GXLoadTexObj(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x1ac));
  GXSetTexCoordGen2(*(undefined4 *)(param_1 + 0x1bc),0,0,*(undefined4 *)(param_1 + 0x1b4),0,0x7d);
  local_14 = (uint)*(byte *)(param_1 + 0x204);
  local_18 = local_14;
  GXSetTevColor(1,&local_18);
  GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
  iVar1 = param_1 + param_2 * 4;
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(iVar1 + 0x1bc),
             *(undefined4 *)(iVar1 + 0x1ac),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0xf,0xf,0xf,8);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,1);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
            (*(undefined4 *)(param_1 + 0x60),0,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
  iVar1 = param_1 + param_2 * 4;
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(iVar1 + 0x1a4),
             *(undefined4 *)(iVar1 + 0x194),0xff);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),2,8,3,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),8,0,0,1,1);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
            (*(undefined4 *)(param_1 + 0x60),0,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  GXSetTevDirect(*(undefined4 *)(param_1 + 0x60));
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
            (*(undefined4 *)(param_1 + 0x60),0xff,0xff,4);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (*(undefined4 *)(param_1 + 0x60),0,0xf,2,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (*(undefined4 *)(param_1 + 0x60),7,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
            (*(undefined4 *)(param_1 + 0x60),0,0,0,1,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
            (*(undefined4 *)(param_1 + 0x60),0,0);
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  return;
}

