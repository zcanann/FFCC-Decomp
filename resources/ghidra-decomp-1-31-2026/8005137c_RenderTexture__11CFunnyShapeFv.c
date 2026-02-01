// Function: RenderTexture__11CFunnyShapeFv
// Entry: 8005137c
// Size: 744 bytes

void RenderTexture__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  undefined4 in_r10;
  undefined4 uVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  if (funnyShape->field_0x60d4 != '\0') {
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    local_28 = DAT_8032fd58;
    local_30 = DAT_8032fd58;
    uVar1 = DAT_8032fd58;
    GXSetChanAmbColor(0,&local_30);
    local_34 = local_28;
    GXSetChanMatColor(0,&local_34);
    GXSetChanCtrl(0,0,0,1,0,2,1,in_r10,uVar1);
    GXSetChanCtrl(2,0,0,1,0,0,2);
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
    local_2c = DAT_8032fd5c;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,2,3);
    GXLoadTexObj(*(undefined4 *)&funnyShape->field_0x6014,0);
    uStack_1c = (int)*(short *)(*(int *)&funnyShape->field_0x6054 + 4) ^ 0x80000000;
    local_20 = 0x43300000;
    uStack_14 = (int)*(short *)(*(int *)&funnyShape->field_0x6054 + 6) ^ 0x80000000;
    local_18 = 0x43300000;
    GXSetViewport((double)FLOAT_8032fd98,(double)FLOAT_8032fd98,
                  (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8032fd88),
                  (double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032fd88),
                  (double)FLOAT_8032fd6c,(double)FLOAT_8032fd74);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xb,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxAttrFmt(0,0xb,1,5,0);
    GXSetVtxAttrFmt(0,0xd,1,4,0);
    GXBegin(0x80,0,4);
    DAT_cc008000 = FLOAT_8032fd80;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = local_2c;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = local_2c;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd80;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = local_2c;
    DAT_cc008000 = FLOAT_8032fd74;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = FLOAT_8032fd80;
    DAT_cc008000 = FLOAT_8032fd80;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = local_2c;
    DAT_cc008000 = FLOAT_8032fd6c;
    DAT_cc008000 = FLOAT_8032fd6c;
  }
  return;
}

