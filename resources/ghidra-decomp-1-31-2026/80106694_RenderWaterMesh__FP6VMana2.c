// Function: RenderWaterMesh__FP6VMana2
// Entry: 80106694
// Size: 1472 bytes

undefined4 RenderWaterMesh__FP6VMana2(int param_1)

{
  undefined2 *puVar1;
  undefined uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  uVar9 = *(undefined4 *)(param_1 + 0x3c);
  uVar8 = *(undefined4 *)(param_1 + 0x40);
  uVar7 = *(undefined4 *)(param_1 + 0x54);
  uVar6 = *(undefined4 *)(param_1 + 0x58);
  puVar5 = *(undefined2 **)(param_1 + 0x50);
  uVar3 = *(undefined4 *)(param_1 + 0x5c);
  uVar10 = *(undefined4 *)(param_1 + 0x28);
  GXClearVtxDesc();
  GXSetVtxDesc(9,3);
  GXSetVtxDesc(10,3);
  GXSetVtxDesc(0xb,3);
  GXSetVtxDesc(0xd,3);
  GXSetVtxDesc(0xe,3);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,10,0,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  GXSetVtxAttrFmt(7,0xe,1,4,0);
  GXSetNumTexGens(2);
  GXSetCullMode(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,0xf);
  GXSetChanCtrl(4,0,0,1,0,0,2);
  GXSetZMode(1,3,0);
  GXSetNumChans(1);
  local_28 = 0xffffffff;
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  GXSetArray(9,uVar9,0xc);
  GXSetArray(10,uVar8,0xc);
  GXSetArray(0xb,uVar3,4);
  GXSetArray(0xd,uVar7,8);
  GXSetArray(0xe,uVar6,8);
  iVar4 = *(int *)(param_1 + 0x7c);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
  uVar2 = *(undefined *)(param_1 + 0xe0);
  local_28 = 0x80808080;
  local_2c = CONCAT31(CONCAT21(CONCAT11(uVar2,uVar2),uVar2),uVar2);
  GXSetTevDirect(0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  GXLoadTexObj(iVar4 + 0x28,0);
  local_30 = local_2c;
  GXSetTevKColor(1,&local_30);
  GXSetTevKColorSel(0,0xd);
  GXSetTevKAlphaSel(0,0x1d);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,0xf,0xf,8);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,6,4,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  GXSetTevDirect(1);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,1,4);
  GXLoadTexObj(*(undefined4 *)(param_1 + 0x28),1);
  local_34 = local_28;
  GXSetTevKColor(0,&local_34);
  GXSetTevKColorSel(1,0xc);
  GXSetTevKAlphaSel(1,0x1c);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (1,0xb,0xe,8,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,8,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (1,7,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,1,1,0);
  GXSetTevDirect(2);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,1,2,4);
  GXLoadTexObj(*(undefined4 *)(param_1 + 0x2c),2);
  local_38 = local_28;
  GXSetTevKColor(0,&local_38);
  GXSetTevKColorSel(2,0xc);
  GXSetTevKAlphaSel(2,0x1c);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (2,0xe,0xb,8,0);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,8,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (2,7,7,7,0);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2,0,0,0,1,0);
  GXSetNumTevStages(3);
  GXBegin(0x90,7,0x600);
  iVar4 = 0x180;
  do {
    DAT_cc008000._0_2_ = *puVar5;
    DAT_cc008000._0_2_ = *puVar5;
    DAT_cc008000._0_2_ = *puVar5;
    DAT_cc008000._0_2_ = *puVar5;
    DAT_cc008000._0_2_ = *puVar5;
    DAT_cc008000._0_2_ = puVar5[1];
    DAT_cc008000._0_2_ = puVar5[1];
    DAT_cc008000._0_2_ = puVar5[1];
    DAT_cc008000._0_2_ = puVar5[1];
    DAT_cc008000._0_2_ = puVar5[1];
    DAT_cc008000._0_2_ = puVar5[2];
    DAT_cc008000._0_2_ = puVar5[2];
    DAT_cc008000._0_2_ = puVar5[2];
    DAT_cc008000._0_2_ = puVar5[2];
    DAT_cc008000._0_2_ = puVar5[2];
    DAT_cc008000._0_2_ = puVar5[3];
    DAT_cc008000._0_2_ = puVar5[3];
    DAT_cc008000._0_2_ = puVar5[3];
    DAT_cc008000._0_2_ = puVar5[3];
    puVar1 = puVar5 + 3;
    puVar5 = puVar5 + 4;
    DAT_cc008000._0_2_ = *puVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,5,0xf);
  GXSetNumTevStages(1);
  GXLoadTexObj(uVar10,0);
  return 1;
}

