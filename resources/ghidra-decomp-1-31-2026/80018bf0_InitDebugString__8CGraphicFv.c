// Function: InitDebugString__8CGraphicFv
// Entry: 80018bf0
// Size: 452 bytes

void InitDebugString__8CGraphicFv(CGraphic *graphic)

{
  double dVar1;
  undefined auStack_d8 [32];
  Mtx MStack_b8;
  Mtx MStack_88;
  Mtx MStack_48;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  local_18 = 0x43300000;
  uStack_14 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6);
  uStack_c = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 4);
  local_10 = 0x43300000;
  C_MTXOrtho(FLOAT_8032f6c0,(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032f6d8),
             FLOAT_8032f6c0,(float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_8032f6d8),
             FLOAT_8032f6c0,FLOAT_8032f708,&MStack_88);
  GXSetProjection(&MStack_88,1);
  PSMTXIdentity(&MStack_b8);
  GXLoadPosMtxImm(&MStack_b8,0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,0,0);
  GXSetZMode(1,7,1);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,0,0,7,0);
  GXSetNumChans(0);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
  PSMTXIdentity(&MStack_b8);
  GXLoadPosMtxImm(&MStack_b8,0);
  GXSetCullMode(0);
  GXSetCurrentMtx(0);
  GXInitTexObj(auStack_d8,&DAT_801fd480,0x40,0x60,0,0,0,0);
  dVar1 = (double)FLOAT_8032f6c0;
  GXInitTexObjLOD(dVar1,dVar1,dVar1,auStack_d8,0,0,0,0,0);
  GXLoadTexObj(auStack_d8,0);
  PSMTXScale(FLOAT_8032f70c,FLOAT_8032f710,FLOAT_8032f6c4,&MStack_48);
  GXLoadTexMtxImm(&MStack_48,0x1e,1);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  return;
}

