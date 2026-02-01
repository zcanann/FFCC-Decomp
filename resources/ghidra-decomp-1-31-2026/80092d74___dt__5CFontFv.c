// Function: __dt__5CFontFv
// Entry: 80092d74
// Size: 200 bytes

CFont * __dt__5CFontFv(CFont *font,short param_2)

{
  int iVar1;
  CTexture *pCVar2;
  
  if (font != (CFont *)0x0) {
    (font->ref).vtable = &PTR_PTR_s_CFont_8020edcc;
    pCVar2 = font->texturePtr;
    if (pCVar2 != (CTexture *)0x0) {
      iVar1 = *(int *)&pCVar2->field_0x4 + -1;
      *(int *)&pCVar2->field_0x4 = iVar1;
      if ((iVar1 == 0) && (pCVar2 != (CTexture *)0x0)) {
        (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
      }
      font->texturePtr = (CTexture *)0x0;
    }
    if (font->field7_0xe == 0) {
      if (font->field27_0x38 != (void *)0x0) {
        __dla__FPv(font->field27_0x38);
        font->field27_0x38 = (void *)0x0;
      }
    }
    __dt__4CRefFv(&font->ref,0);
    if (0 < param_2) {
      __dl__FPv(font);
    }
  }
  return font;
}

