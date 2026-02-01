// Function: SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
// Entry: 8003bd10
// Size: 180 bytes

undefined4
SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
          (CTextureMan *textureMan,int param_2,CTexture *texture)

{
  bool bVar1;
  
  bVar1 = false;
  if ((texture->field93_0x60 == 9) || (texture->field93_0x60 == 8)) {
    bVar1 = true;
  }
  if (bVar1) {
    GXInitTexObjTlut(&texture->field_0x28,0);
  }
  GXLoadTexObj(&texture->field_0x28,param_2);
  if (bVar1) {
    GXInitTexObjTlut(&texture->field_0x28,1);
    GXLoadTexObj(&texture->field_0x28,param_2 + 1);
    GXLoadTlut(&texture->field_0x48,0);
    GXLoadTlut(&texture->field_0x54,1);
  }
  return 0;
}

