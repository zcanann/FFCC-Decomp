// Function: RenderShape__11CFunnyShapeFv
// Entry: 80051110
// Size: 620 bytes

void RenderShape__11CFunnyShapeFv(CFunnyShape *param_1)

{
  undefined4 uVar1;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  if ((param_1->field_0x60d4 != '\0') && (*(int *)&param_1->field_0x6010 != 0)) {
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    GXSetVtxAttrFmt(0,0xd,1,4,0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,2,3);
    GXLoadTexObj(*(undefined4 *)&param_1->field_0x6014,0);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,1,0,2,1);
    GXSetChanCtrl(2,0,0,1,0,0,2);
    GXSetNumTevStages(1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,10,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,4,5,7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,1,1,0)
    ;
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0);
    GXSetZMode(1,3,0);
    uVar1 = DAT_8032fd60;
    local_20 = DAT_8032fd60;
    GXSetChanAmbColor(0,&local_20);
    local_1c = uVar1;
    GXSetChanMatColor(0,&local_1c);
    local_10 = FLOAT_8032fd90;
    local_c = FLOAT_8032fd94;
    local_18 = FLOAT_8032fd90;
    local_14 = FLOAT_8032fd94;
    RenderShape__11CFunnyShapeFP16FS_tagOAN3_SHAPE5Vec2df
              ((double)FLOAT_8032fd6c,param_1,*(undefined4 *)&param_1->field_0x6010,&local_18);
  }
  return;
}

