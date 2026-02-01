// Function: SetTexture__8CMenuPcsFQ28CMenuPcs3TEX
// Entry: 80095bd0
// Size: 212 bytes

void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs *menuPcs,int param_2)

{
  CTexture *texture;
  Mtx MStack_48;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  if (param_2 == -1) {
    texture = (CTexture *)0x0;
  }
  else {
    texture = *(CTexture **)(&menuPcs->field_0x18c + param_2 * 4);
    SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,texture);
    uStack_14 = texture->field94_0x64;
    uStack_c = texture->field95_0x68;
    local_18 = 0x43300000;
    local_10 = 0x43300000;
    PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80330840),
               FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_80330840),
               FLOAT_80330808,&MStack_48);
    GXLoadTexMtxImm(&MStack_48,0x1e,1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  }
  SetTextureTev__11CTextureManFP8CTexture(&TextureMan,texture);
  return;
}

