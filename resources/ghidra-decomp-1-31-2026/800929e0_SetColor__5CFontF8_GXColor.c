// Function: SetColor__5CFontF8_GXColor
// Entry: 800929e0
// Size: 80 bytes

void SetColor__5CFontF8_GXColor(CFont *font,undefined *param_2)

{
  undefined uVar1;
  undefined uVar2;
  undefined4 local_8 [2];
  
  uVar1 = param_2[1];
  font->field_0x30 = *param_2;
  uVar2 = param_2[2];
  font->field_0x31 = uVar1;
  uVar1 = param_2[3];
  font->field_0x32 = uVar2;
  font->field_0x33 = uVar1;
  local_8[0] = *(undefined4 *)&font->field_0x30;
  GXSetChanMatColor(4,local_8);
  return;
}

