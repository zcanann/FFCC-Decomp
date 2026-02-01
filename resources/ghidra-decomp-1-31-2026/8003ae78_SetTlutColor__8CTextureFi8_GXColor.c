// Function: SetTlutColor__8CTextureFi8_GXColor
// Entry: 8003ae78
// Size: 116 bytes

void SetTlutColor__8CTextureFi8_GXColor(CTexture *texture,int param_2,undefined *param_3)

{
  int iVar1;
  int iVar2;
  undefined2 uStack_6;
  
  if (texture->field93_0x60 == 9) {
    iVar1 = 0x100;
  }
  else if (texture->field93_0x60 == 8) {
    iVar1 = 0x10;
  }
  else {
    iVar1 = 0;
  }
  iVar2 = *(int *)&texture->field_0x7c;
  uStack_6 = CONCAT11(param_3[1],*param_3);
  *(ushort *)(iVar2 + (param_2 + iVar1) * 2) = CONCAT11(param_3[3],param_3[2]);
  *(undefined2 *)(iVar2 + param_2 * 2) = uStack_6;
  return;
}

