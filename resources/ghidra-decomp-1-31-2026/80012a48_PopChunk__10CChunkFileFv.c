// Function: PopChunk__10CChunkFileFv
// Entry: 80012a48
// Size: 116 bytes

void PopChunk__10CChunkFileFv(CChunkFile *chunkFile)

{
  chunkFile->m_stackDepth = chunkFile->m_stackDepth + -1;
  chunkFile->m_scopeSize = chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_scopeSize;
  chunkFile->m_lastChunkSize = chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_lastChunkSize;
  chunkFile->m_scopeOffset = chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_scopeOffset;
  chunkFile->m_headerPtr = chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_base;
  chunkFile->m_cursor = chunkFile->m_chunkScopes[chunkFile->m_stackDepth].m_headerPtr;
  return;
}

