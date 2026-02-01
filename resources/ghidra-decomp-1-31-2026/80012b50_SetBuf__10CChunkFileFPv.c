// Function: SetBuf__10CChunkFileFPv
// Entry: 80012b50
// Size: 44 bytes

void SetBuf__10CChunkFileFPv(CChunkFile *chunkFile,uint8_t *buffer)

{
  uint uVar1;
  
  uVar1 = *(uint *)(buffer + 4);
  chunkFile->m_base = buffer;
  chunkFile->m_headerPtr = buffer;
  chunkFile->m_scopeSize = uVar1 & 0xffffff;
  chunkFile->m_scopeOffset = 0;
  chunkFile->m_lastChunkSize = -1;
  chunkFile->m_stackDepth = 0;
  return;
}

