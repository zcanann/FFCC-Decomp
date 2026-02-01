// Function: DrawBound__8CGraphicFR6CBound8_GXColor
// Entry: 80017f6c
// Size: 916 bytes

void DrawBound__8CGraphicFR6CBound8_GXColor
               (CGraphic *graphic,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 local_48;
  undefined4 local_44;
  Mtx MStack_40;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,5,1);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetZMode(1,3,1);
  GXSetCullMode(0);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  GXSetNumChans(1);
  GXSetChanCtrl(4,0,0,0,0,2,2);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_40);
  GXLoadPosMtxImm(&MStack_40,0);
  local_44 = *param_3;
  GXSetChanMatColor(4,&local_44);
  local_48 = *param_3;
  GXSetChanAmbColor(4,&local_48);
  GXBegin(0xa8,7,0x18);
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[2];
  DAT_cc008000 = param_2[3];
  DAT_cc008000 = param_2[4];
  DAT_cc008000 = param_2[5];
  return;
}

