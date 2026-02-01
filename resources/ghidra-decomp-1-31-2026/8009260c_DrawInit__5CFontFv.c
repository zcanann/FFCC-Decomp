// Function: DrawInit__5CFontFv
// Entry: 8009260c
// Size: 768 bytes

void DrawInit__5CFontFv(CFont *font)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined auStack_c8 [4];
  undefined4 local_c4;
  undefined4 local_c0;
  Mtx MStack_bc;
  Mtx MStack_8c;
  Mtx MStack_4c;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  local_c0 = *(undefined4 *)&font->field_0x30;
  GXSetChanMatColor(4,&local_c0);
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c8,0xff,0xff,0xff,0xff);
  local_c4 = *puVar4;
  GXSetChanAmbColor(4,&local_c4);
  bVar1 = font->renderFlags;
  if (((int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0) ||
     ((int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0)) {
    C_MTXOrtho(FLOAT_803306b8,FLOAT_803306d8,FLOAT_803306b8,FLOAT_803306dc,FLOAT_803306b8,
               FLOAT_803306c8,&MStack_8c);
    MStack_8c.value[2][2] = FLOAT_803306c8;
    MStack_8c.value[2][3] = FLOAT_803306b8;
  }
  else {
    C_MTXOrtho(FLOAT_803306b8,FLOAT_803306d8,FLOAT_803306b8,FLOAT_803306dc,FLOAT_803306b8,
               FLOAT_803306c8,&MStack_8c);
  }
  GXSetProjection(&MStack_8c,1);
  PSMTXIdentity(&MStack_bc);
  GXLoadPosMtxImm(&MStack_bc,0);
  GXSetZCompLoc(0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  bVar1 = font->renderFlags;
  uVar7 = 7;
  uVar2 = (uint)bVar1 << 0x19;
  uVar3 = (uint)bVar1 << 0x1a | (uint)(bVar1 >> 6);
  uVar5 = (uint)(char)((int)uVar2 >> 0x1f);
  if ((int)uVar3 < 0) {
    uVar7 = 3;
  }
  iVar6 = 0;
  if (((int)(uVar2 | bVar1 >> 7) < 0) || ((int)uVar3 < 0)) {
    iVar6 = 1;
  }
  GXSetZMode((uint)-iVar6 >> 0x1f,uVar7,(-uVar5 | uVar5) >> 0x1f);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  PSMTXIdentity(&MStack_bc);
  GXLoadPosMtxImm(&MStack_bc,0);
  GXSetCullMode(0);
  SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,font->texturePtr);
  local_18 = 0x43300000;
  uStack_14 = font->texturePtr->field94_0x64;
  uStack_c = font->texturePtr->field95_0x68;
  local_10 = 0x43300000;
  PSMTXScale(FLOAT_803306c8 / (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_803306d0),
             FLOAT_803306c8 / (float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_803306d0),
             FLOAT_803306c8,&MStack_4c);
  GXLoadTexMtxImm(&MStack_4c,0x1e,1);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xd,1,3,1);
  SetTextureTev__11CTextureManFP8CTexture(&TextureMan,font->texturePtr);
  font->renderFlags = font->renderFlags & 0xef;
  font->renderFlags = font->renderFlags & 0xf7;
  return;
}

