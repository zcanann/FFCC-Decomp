// Function: DrawDebugString__8CGraphicFv
// Entry: 80018db4
// Size: 588 bytes

void DrawDebugString__8CGraphicFv(CGraphic *graphic)

{
  uint uVar1;
  short sVar2;
  CGraphic *pCVar3;
  CGraphic *pCVar4;
  double dVar5;
  undefined auStack_e8 [32];
  Mtx MStack_c8;
  Mtx MStack_98;
  Mtx MStack_58;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  local_28 = 0x43300000;
  local_20 = 0x43300000;
  uStack_24 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6);
  uStack_1c = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 4);
  C_MTXOrtho(FLOAT_8032f6c0,(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8032f6d8),
             FLOAT_8032f6c0,(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8032f6d8),
             FLOAT_8032f6c0,FLOAT_8032f708,&MStack_98);
  GXSetProjection(&MStack_98,1);
  PSMTXIdentity(&MStack_58);
  GXLoadPosMtxImm(&MStack_58,0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,0,0);
  GXSetZMode(1,7,1);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,0,0,7,0);
  GXSetNumChans(0);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
  PSMTXIdentity(&MStack_58);
  GXLoadPosMtxImm(&MStack_58,0);
  GXSetCullMode(0);
  GXSetCurrentMtx(0);
  GXInitTexObj(auStack_e8,&DAT_801fd480,0x40,0x60,0,0,0,0);
  dVar5 = (double)FLOAT_8032f6c0;
  GXInitTexObjLOD(dVar5,dVar5,dVar5,auStack_e8,0,0,0,0,0);
  GXLoadTexObj(auStack_e8,0);
  PSMTXScale(FLOAT_8032f70c,FLOAT_8032f710,FLOAT_8032f6c4,&MStack_c8);
  GXLoadTexMtxImm(&MStack_c8,0x1e,1);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  sVar2 = 0x10;
  pCVar3 = graphic;
  pCVar4 = graphic;
  for (uVar1 = 0; uVar1 < *(uint *)&graphic->field_0x14; uVar1 = uVar1 + 1) {
    if (*(short *)&pCVar4->field_0x18 == -1) {
      DrawDebugStringDirect__8CGraphicFUlUlPcUl(graphic,0x10,sVar2,&pCVar3->field_0x1e0,0xc);
    }
    else {
      DrawDebugStringDirect__8CGraphicFUlUlPcUl
                (graphic,*(short *)&pCVar4->field_0x18 * 0xc + 0x10,
                 *(short *)&pCVar4->field_0x1a * 0xc + 0x10,&pCVar3->field_0x1e0,0xc);
    }
    pCVar4 = (CGraphic *)&pCVar4->field_0x4;
    pCVar3 = (CGraphic *)&pCVar3->field_0x70;
    sVar2 = sVar2 + 0xc;
  }
  return;
}

