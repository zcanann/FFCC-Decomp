// Function: render3Dcursor__8CPartMngFv
// Entry: 8005e078
// Size: 784 bytes

/* WARNING: Removing unreachable block (ram,0x8005e36c) */
/* WARNING: Removing unreachable block (ram,0x8005e364) */
/* WARNING: Removing unreachable block (ram,0x8005e35c) */
/* WARNING: Removing unreachable block (ram,0x8005e098) */
/* WARNING: Removing unreachable block (ram,0x8005e090) */
/* WARNING: Removing unreachable block (ram,0x8005e088) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void render3Dcursor__8CPartMngFv(CPartMng *partMng)

{
  double dVar1;
  double dVar2;
  double dVar3;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  Mtx MStack_ac;
  Mtx MStack_6c;
  
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  C_MTXOrtho(FLOAT_8032fe5c,FLOAT_8032fe60,FLOAT_8032fe5c,FLOAT_8032fe64,FLOAT_8032fe5c,
             FLOAT_8032fe68,&MStack_ac);
  GXSetProjection(&MStack_ac,1);
  PSMTXIdentity(&MStack_6c);
  GXLoadPosMtxImm(&MStack_6c,0);
  GXSetZCompLoc(0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetZMode(0,7,0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetCullMode(0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  GXSetNumTexGens(0);
  GXSetNumTevStages(1);
  GXSetProjection(&ppvScreenMatrix,0);
  GXLoadPosMtxImm(&ppvCameraMatrix0,0);
  pppSetBlendMode__FUc(3);
  dVar3 = (double)*(float *)(partMng->m_cursorPacket).m_cursorPacketRaw;
  dVar2 = (double)*(float *)((partMng->m_cursorPacket).m_cursorPacketRaw + 4);
  dVar1 = (double)*(float *)((partMng->m_cursorPacket).m_cursorPacketRaw + 8);
  local_b0 = 0xff8080ff;
  local_b8 = 0xff8080ff;
  GXSetChanAmbColor(4,&local_b8);
  local_b4 = local_b0;
  GXSetChanMatColor(4,&local_b4);
  GXBegin(0xa8,5,2);
  DAT_cc008000 = (float)(dVar3 - (double)FLOAT_8032fe70);
  DAT_cc008000 = (float)dVar2;
  DAT_cc008000 = (float)dVar1;
  DAT_cc008000 = (float)(dVar3 + (double)FLOAT_8032fe70);
  DAT_cc008000 = (float)dVar2;
  local_b0 = 0x80ff80ff;
  DAT_cc008000 = (float)dVar1;
  local_c0 = 0x80ff80ff;
  GXSetChanAmbColor(4,&local_c0);
  local_bc = local_b0;
  GXSetChanMatColor(4,&local_bc);
  GXBegin(0xa8,5,2);
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)(dVar2 - (double)FLOAT_8032fe70);
  DAT_cc008000 = (float)dVar1;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)(dVar2 + (double)FLOAT_8032fe70);
  local_b0 = 0xffff80ff;
  DAT_cc008000 = (float)dVar1;
  local_c8 = 0xffff80ff;
  GXSetChanAmbColor(4,&local_c8);
  local_c4 = local_b0;
  GXSetChanMatColor(4,&local_c4);
  GXBegin(0xa8,5,2);
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)dVar2;
  DAT_cc008000 = (float)(dVar1 - (double)FLOAT_8032fe70);
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = (float)dVar2;
  DAT_cc008000 = (float)(dVar1 + (double)FLOAT_8032fe70);
  return;
}

