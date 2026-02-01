// Function: GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
// Entry: 80012988
// Size: 192 bytes

undefined4
GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(CChunkFile *chunkFile,CChunkFile *chunkFileB)

{
  uint uVar1;
  int iVar2;
  uint32_t *puVar3;
  uint8_t *puVar4;
  int32_t *piVar5;
  
  if (chunkFile->m_lastChunkSize < 0) {
    iVar2 = 0;
  }
  else {
    uVar1 = chunkFile->m_lastChunkSize + 0xf;
    iVar2 = (((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0)) * 0x10 + 0x10;
  }
  chunkFile->m_scopeOffset = chunkFile->m_scopeOffset + iVar2;
  chunkFile->m_headerPtr = chunkFile->m_headerPtr + iVar2;
  chunkFile->m_cursor = chunkFile->m_headerPtr;
  if ((int)chunkFile->m_scopeSize <= chunkFile->m_scopeOffset) {
    return 0;
  }
  puVar3 = (uint32_t *)chunkFile->m_cursor;
  chunkFile->m_cursor = (uint8_t *)(puVar3 + 1);
  chunkFileB->m_scopeSize = *puVar3;
  puVar4 = chunkFile->m_cursor;
  chunkFile->m_cursor = puVar4 + 4;
  chunkFileB->m_base = *(uint8_t **)puVar4;
  piVar5 = (int32_t *)chunkFile->m_cursor;
  chunkFile->m_cursor = (uint8_t *)(piVar5 + 1);
  chunkFileB->m_lastChunkSize = *piVar5;
  piVar5 = (int32_t *)chunkFile->m_cursor;
  chunkFile->m_cursor = (uint8_t *)(piVar5 + 1);
  chunkFileB->m_scopeOffset = *piVar5;
  chunkFile->m_lastChunkSize = (int32_t)chunkFileB->m_base;
  return 1;
}

