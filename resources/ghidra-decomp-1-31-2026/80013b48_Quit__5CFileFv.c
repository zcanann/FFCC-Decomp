// Function: Quit__5CFileFv
// Entry: 80013b48
// Size: 112 bytes

void Quit__5CFileFv(CFile *file)

{
  uint32_t uVar1;
  
  if (file->m_readBuffer != (void *)0x0) {
    __dla__FPv(file->m_readBuffer);
    file->m_readBuffer = (void *)0x0;
  }
  uVar1 = (file->m_fileHandle2).mNextOffset;
  if (uVar1 != 0) {
    if (uVar1 != 0) {
      __dla__FPv((void *)(uVar1 - 0x10));
    }
    (file->m_fileHandle2).mNextOffset = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,file->m_stage);
  return;
}

