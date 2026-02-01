// Function: GetF4__10CChunkFileFv
// Entry: 800128d4
// Size: 36 bytes

double GetF4__10CChunkFileFv(CChunkFile *chunkFile)

{
  float *pfVar1;
  
  pfVar1 = (float *)chunkFile->m_cursor;
  chunkFile->m_cursor = (uint8_t *)(pfVar1 + 1);
  return (double)*pfVar1;
}

