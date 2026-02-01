// Function: SetExternalTlut__8CTextureFPvi
// Entry: 8003af64
// Size: 204 bytes

void SetExternalTlut__8CTextureFPvi(CTexture *texture,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    param_2 = *(int *)&texture->field_0x7c;
  }
  uVar1 = 0x10;
  if (texture->field93_0x60 == 9) {
    uVar1 = 0x100;
  }
  GXInitTlutObj(&texture->field_0x48,param_2,0,uVar1);
  uVar1 = 0x10;
  if (texture->field93_0x60 == 9) {
    uVar1 = 0x100;
  }
  iVar2 = 0x10;
  if (texture->field93_0x60 == 9) {
    iVar2 = 0x100;
  }
  GXInitTlutObj(&texture->field_0x54,param_2 + iVar2 * 2,0,uVar1);
  if (param_3 != 0) {
    GXLoadTlut(&texture->field_0x48,0);
    GXLoadTlut(&texture->field_0x54,1);
  }
  return;
}

