// Function: __ct__10CChunkFileFPv
// Entry: 80012b7c
// Size: 44 bytes

void __ct__10CChunkFileFPv(CChunkFile *chunkFile,void *bufferPtr)

{
  uint uVar1;
  
  uVar1 = *(uint *)((int)bufferPtr + 4);
  chunkFile->m_base = (uint8_t *)bufferPtr;
  chunkFile->m_headerPtr = (uint8_t *)bufferPtr;
  chunkFile->m_scopeSize = uVar1 & 0xffffff;
  chunkFile->m_scopeOffset = 0;
  chunkFile->m_lastChunkSize = -1;
  chunkFile->m_stackDepth = 0;
  return;
}

