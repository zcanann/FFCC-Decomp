// Function: DrawSphere__8CGraphicFPA4_f8_GXColor
// Entry: 80018764
// Size: 304 bytes

void DrawSphere__8CGraphicFPA4_f8_GXColor(CGraphic *graphic,undefined4 param_2,undefined4 *param_3)

{
  undefined4 local_18;
  undefined4 local_14 [2];
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,5,1);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetZMode(1,3,1);
  GXSetCullMode(0);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  GXSetNumChans(1);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXLoadPosMtxImm(param_2,0);
  local_14[0] = *param_3;
  GXSetChanMatColor(4,local_14);
  local_18 = *param_3;
  GXSetChanAmbColor(4,&local_18);
  GXSetLineWidth(8,0);
  GXCallDisplayList(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  return;
}

