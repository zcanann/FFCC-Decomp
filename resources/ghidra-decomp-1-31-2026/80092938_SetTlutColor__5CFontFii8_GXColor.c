// Function: SetTlutColor__5CFontFii8_GXColor
// Entry: 80092938
// Size: 96 bytes

void SetTlutColor__5CFontFii8_GXColor(CFont *font,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = font->texturePtr->field93_0x60;
  if (iVar1 == 9) {
    uVar2 = 0x100;
  }
  else if (iVar1 == 8) {
    uVar2 = 0x10;
  }
  else {
    uVar2 = 0;
  }
  SetExternalTlutColor__8CTextureFPviiR8_GXColor(&font->field_0x440 + param_2 * 0x40,uVar2);
  return;
}

