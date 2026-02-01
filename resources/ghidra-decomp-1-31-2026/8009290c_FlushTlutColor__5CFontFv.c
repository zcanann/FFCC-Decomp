// Function: FlushTlutColor__5CFontFv
// Entry: 8009290c
// Size: 44 bytes

void FlushTlutColor__5CFontFv(CFont *font)

{
  FlushExternalTlut__8CTextureFPv(font->texturePtr,&font->field_0x440);
  return;
}

