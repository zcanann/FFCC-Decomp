// Function: Get__10CChunkFileFPvl
// Entry: 80012934
// Size: 76 bytes

void Get__10CChunkFileFPvl(CChunkFile *chunkFile,void *param_2,int param_3)

{
  memcpy(param_2,chunkFile->m_cursor,param_3);
  chunkFile->m_cursor = chunkFile->m_cursor + param_3;
  return;
}

