// Function: Get2__10CChunkFileFv
// Entry: 8001290c
// Size: 20 bytes

undefined2 Get2__10CChunkFileFv(CChunkFile *chunkFile)

{
  uint8_t *puVar1;
  
  puVar1 = chunkFile->m_cursor;
  chunkFile->m_cursor = puVar1 + 2;
  return *(undefined2 *)puVar1;
}

