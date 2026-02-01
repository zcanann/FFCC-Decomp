// Function: __ct__5CFontFv
// Entry: 80092e3c
// Size: 176 bytes

CFont * __ct__5CFontFv(CFont *font)

{
  float fVar1;
  float fVar2;
  
  __ct__4CRefFv(&font->ref);
  fVar1 = FLOAT_803306b8;
  (font->ref).vtable = &PTR_PTR_s_CFont_8020edcc;
  fVar2 = FLOAT_803306c8;
  font->field27_0x38 = (void *)0x0;
  font->texturePtr = (CTexture *)0x0;
  font->margin = fVar1;
  font->posZ = fVar1;
  font->posY = fVar1;
  font->posX = fVar1;
  font->renderFlags = font->renderFlags & 0x7f;
  font->scaleY = fVar2;
  font->scaleX = fVar2;
  font->renderFlags = font->renderFlags & 0xf7;
  font->field_0x30 = 0xff;
  font->field_0x31 = 0xff;
  font->field_0x32 = 0xff;
  font->field_0x33 = 0xff;
  font->renderFlags = font->renderFlags & 0xbf;
  font->renderFlags = font->renderFlags & 0xdf;
  font->field7_0xe = 0;
  return font;
}

