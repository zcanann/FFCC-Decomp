// Function: CacheUnLoadTexture__8CTextureFP13CAmemCacheSet
// Entry: 8003b05c
// Size: 52 bytes

void CacheUnLoadTexture__8CTextureFP13CAmemCacheSet(CTexture *texture,CAmemCacheSet *amemCacheSet)

{
  if (*(short *)&texture->field_0x72 != -1) {
    Release__13CAmemCacheSetFs(amemCacheSet,*(short *)&texture->field_0x72);
  }
  return;
}

