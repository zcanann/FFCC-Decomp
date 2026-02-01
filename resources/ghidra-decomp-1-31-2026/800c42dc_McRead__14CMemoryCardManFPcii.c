// Function: McRead__14CMemoryCardManFPcii
// Entry: 800c42dc
// Size: 104 bytes

void McRead__14CMemoryCardManFPcii
               (CMemoryCardMan *memoryCardMan,uint8_t *buffer,int length,int offset)

{
  int iVar1;
  
  if (buffer == (uint8_t *)0x0) {
    buffer = memoryCardMan->m_saveBuffer;
  }
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\b';
  iVar1 = CARDReadAsync(&memoryCardMan->mFileInfo,buffer,length,offset,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

