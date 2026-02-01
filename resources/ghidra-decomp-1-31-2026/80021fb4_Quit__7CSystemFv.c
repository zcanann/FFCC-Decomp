// Function: Quit__7CSystemFv
// Entry: 80021fb4
// Size: 204 bytes

void Quit__7CSystemFv(CSystem *system)

{
  if (system->m_mapBuffer != (void *)0x0) {
    __dla__FPv(system->m_mapBuffer);
    system->m_mapBuffer = (void *)0x0;
  }
  if (system->m_mapStage != (CStage *)0x0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,system->m_mapStage);
  }
  Quit__14CMemoryCardManFv(&MemoryCardMan);
  Quit__8CFontManFv(&FontMan);
  Quit__11CTextureManFv(&TextureMan);
  Quit__12CMaterialManFv(&MaterialMan);
  Quit__8CGraphicFv(&Graphic);
  Quit__4CPadFv(&Pad);
  Quit__5CFileFv(&File);
  Quit__6CSoundFv(&Sound);
  Quit__7CMemoryFv(&Memory);
  Quit__5CMathFv(&Math);
  return;
}

