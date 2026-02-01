// Function: Get4__10CChunkFileFv
// Entry: 800128f8
// Size: 20 bytes

undefined4 Get4__10CChunkFileFv(CChunkFile *chunkFile)

{
  uint8_t *puVar1;
  
  puVar1 = chunkFile->m_cursor;
  chunkFile->m_cursor = puVar1 + 4;
  return *(undefined4 *)puVar1;
}

