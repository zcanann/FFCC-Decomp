// Function: PushChunk__10CChunkFileFv
// Entry: 80012abc
// Size: 148 bytes

void PushChunk__10CChunkFileFv(CChunkFile *chunkFile)

{
  chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_scopeSize = chunkFile->m_scopeSize;
  chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_lastChunkSize = chunkFile->m_lastChunkSize;
  chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_scopeOffset = chunkFile->m_scopeOffset;
  chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_base = chunkFile->m_headerPtr;
  chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_headerPtr = chunkFile->m_cursor;
  chunkFile->m_stackDepth = chunkFile->m_stackDepth + 1;
  chunkFile->m_scopeSize = chunkFile->m_lastChunkSize;
  chunkFile->m_scopeOffset = 0;
  chunkFile->m_lastChunkSize = -1;
  chunkFile->m_headerPtr = chunkFile->m_cursor;
  return;
}

