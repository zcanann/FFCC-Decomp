// Function: GetString__10CChunkFileFv
// Entry: 800128b0
// Size: 36 bytes

uint8_t * GetString__10CChunkFileFv(CChunkFile *chunkFile)

{
  uint8_t *puVar1;
  uint8_t *puVar2;
  
  puVar2 = chunkFile->m_cursor;
  do {
    puVar1 = chunkFile->m_cursor;
    chunkFile->m_cursor = puVar1 + 1;
  } while (*puVar1 != '\0');
  return puVar2;
}

