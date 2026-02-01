// Function: draw__10CCameraPcsFv
// Entry: 80038fb4
// Size: 1180 bytes

/* WARNING: Removing unreachable block (ram,0x80039430) */
/* WARNING: Removing unreachable block (ram,0x80039428) */
/* WARNING: Removing unreachable block (ram,0x80039420) */
/* WARNING: Removing unreachable block (ram,0x80038fd4) */
/* WARNING: Removing unreachable block (ram,0x80038fcc) */
/* WARNING: Removing unreachable block (ram,0x80038fc4) */

void draw__10CCameraPcsFv(int param_1)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined auStack_108 [4];
  Mtx MStack_104;
  Mtx MStack_d4;
  Mtx MStack_a4;
  Mtx MStack_74;
  
  if ((*(int *)(param_1 + 0x444) == 0) || ((CFlat._4764_4_ & 0x1000000) != 0)) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    GXSetCullMode(1);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    uVar1 = __ct__6CColorFUcUcUcUc(auStack_108,0xff,0xff,0xff,0xff);
    DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
              ((double)FLOAT_8032fabc,&Graphic,param_1 + 4,param_1 + 0xd4,uVar1);
  }
  if (DAT_8032ecd8 != '\0') {
    dVar2 = (double)g_shadow_pos.z;
    dVar3 = (double)g_shadow_pos.y;
    dVar4 = (double)g_shadow_pos.x;
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_74);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    GXSetCullMode(1);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    PSMTXScale(FLOAT_8032fa4c,FLOAT_8032fa4c,FLOAT_8032fa4c,&MStack_a4);
    MStack_a4.value[0][3] = (float)dVar4;
    MStack_a4.value[1][3] = (float)dVar3;
    MStack_a4.value[2][3] = (float)dVar2;
    PSMTXConcat(&MStack_74,&MStack_a4,&MStack_a4);
    GXLoadPosMtxImm(&MStack_a4,0);
    local_110 = 0xff0000ff;
    local_10c = 0xff0000ff;
    GXSetChanMatColor(4,&local_10c);
    DrawSphere__8CGraphicFv(&Graphic);
    dVar2 = (double)g_shadow_refpos.x;
    dVar4 = (double)g_shadow_refpos.z;
    dVar3 = (double)g_shadow_refpos.y;
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_d4);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    GXSetZCompLoc(0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
    GXSetZMode(1,3,1);
    GXSetCullMode(1);
    GXSetNumTevStages(1);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetNumChans(1);
    GXSetChanCtrl(0,0,0,0,0,2,1);
    GXSetChanCtrl(2,0,0,0,0,2,2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxAttrFmt(0,9,1,4,0);
    PSMTXScale(FLOAT_8032fa4c,FLOAT_8032fa4c,FLOAT_8032fa4c,&MStack_104);
    MStack_104.value[0][3] = (float)dVar2;
    MStack_104.value[1][3] = (float)dVar3;
    MStack_104.value[2][3] = (float)dVar4;
    PSMTXConcat(&MStack_d4,&MStack_104,&MStack_104);
    GXLoadPosMtxImm(&MStack_104,0);
    local_114 = 0xff00ff;
    GXSetChanMatColor(4,&local_114);
    DrawSphere__8CGraphicFv(&Graphic);
  }
  return;
}

