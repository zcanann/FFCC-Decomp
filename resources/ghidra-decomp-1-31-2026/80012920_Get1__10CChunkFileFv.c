// Function: Get1__10CChunkFileFv
// Entry: 80012920
// Size: 20 bytes

uint8_t Get1__10CChunkFileFv(CChunkFile *chunkFile)

{
  uint8_t *puVar1;
  
  puVar1 = chunkFile->m_cursor;
  chunkFile->m_cursor = puVar1 + 1;
  return *puVar1;
}

