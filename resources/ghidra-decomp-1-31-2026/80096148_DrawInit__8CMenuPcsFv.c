// Function: DrawInit__8CMenuPcsFv
// Entry: 80096148
// Size: 468 bytes

void DrawInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined4 *puVar1;
  undefined auStack_78 [4];
  undefined4 local_74;
  Mtx MStack_70;
  Mtx MStack_30;
  
  PSMTXIdentity(&MStack_30);
  GXLoadPosMtxImm(&MStack_30,0);
  C_MTXOrtho(FLOAT_8033080c,FLOAT_80330860,FLOAT_8033080c,FLOAT_80330864,FLOAT_8033080c,
             FLOAT_80330868,&MStack_70);
  GXSetProjection(&MStack_70,1);
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_78,0xff,0xff,0xff,0xff);
  local_74 = *puVar1;
  GXSetChanAmbColor(4,&local_74);
  GXSetZCompLoc(0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetZMode(0,7,0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetCullMode(0);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xd,1,4,0);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  return;
}

