// Function: __ct__11CTextureSetFv
// Entry: 8003ad30
// Size: 96 bytes

CTextureSet * __ct__11CTextureSetFv(CTextureSet *textureSet)

{
  __ct__4CRefFv((CRef *)textureSet);
  textureSet->vtable = &PTR_PTR_s_CTextureSet_801e9b34;
  __ct__21CPtrArray<P8CTexture>Fv(&textureSet->textures);
  SetDefaultSize__21CPtrArray<P8CTexture>FUl(&textureSet->textures,0x10);
  SetStage__21CPtrArray<P8CTexture>FPQ27CMemory6CStage(&textureSet->textures,TextureMan.memoryStage)
  ;
  return textureSet;
}

