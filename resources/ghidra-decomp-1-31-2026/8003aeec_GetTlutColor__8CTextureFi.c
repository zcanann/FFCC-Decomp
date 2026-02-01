// Function: GetTlutColor__8CTextureFi
// Entry: 8003aeec
// Size: 120 bytes

undefined4 GetTlutColor__8CTextureFi(CTexture *texture,int param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined uStack_7;
  undefined uStack_6;
  undefined uStack_5;
  
  if (texture->field93_0x60 == 9) {
    iVar3 = 0x100;
  }
  else if (texture->field93_0x60 == 8) {
    iVar3 = 0x10;
  }
  else {
    iVar3 = 0;
  }
  uVar1 = *(undefined2 *)(*(int *)&texture->field_0x7c + (param_2 + iVar3) * 2);
  uVar2 = *(undefined2 *)(*(int *)&texture->field_0x7c + param_2 * 2);
  uStack_5 = (undefined)uVar2;
  uStack_6 = (undefined)((ushort)uVar2 >> 8);
  uStack_7 = (undefined)uVar1;
  return CONCAT22(CONCAT11(uStack_5,uStack_6),CONCAT11(uStack_7,(char)((ushort)uVar1 >> 8)));
}

