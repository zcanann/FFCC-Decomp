// Function: __dt__11CTextureSetFv
// Entry: 8003acb8
// Size: 120 bytes

CTextureSet * __dt__11CTextureSetFv(CTextureSet *textureSet,short param_2)

{
  if (textureSet != (CTextureSet *)0x0) {
    textureSet->vtable = &PTR_PTR_s_CTextureSet_801e9b34;
    ReleaseAndRemoveAll__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
    __dt__21CPtrArray<P8CTexture>Fv(&textureSet->textures,0xffff);
    __dt__4CRefFv((CRef *)textureSet,0);
    if (0 < param_2) {
      __dl__FPv(textureSet);
    }
  }
  return textureSet;
}

