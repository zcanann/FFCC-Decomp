// Function: Align__10CChunkFileFUl
// Entry: 80012880
// Size: 48 bytes

void Align__10CChunkFileFUl(CChunkFile *chunkFile,uint param_2)

{
  chunkFile->m_cursor =
       chunkFile->m_base +
       ((uint)(chunkFile->m_cursor + (param_2 - (int)chunkFile->m_base) + -1) / param_2) * param_2;
  return;
}

