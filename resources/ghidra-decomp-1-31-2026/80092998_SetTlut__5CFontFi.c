// Function: SetTlut__5CFontFi
// Entry: 80092998
// Size: 72 bytes

void SetTlut__5CFontFi(CFont *font,int param_2)

{
  undefined *puVar1;
  
  if (param_2 < 0) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &font->field_0x440 + param_2 * 0x40;
  }
  SetExternalTlut__8CTextureFPvi(font->texturePtr,puVar1,1);
  return;
}

