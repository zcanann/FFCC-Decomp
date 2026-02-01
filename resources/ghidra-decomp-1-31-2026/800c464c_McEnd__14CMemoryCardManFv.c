// Function: McEnd__14CMemoryCardManFv
// Entry: 800c464c
// Size: 172 bytes

void McEnd__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  int32_t iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar2 = 0;
    do {
      iVar1 = CARDUnmount(iVar3);
      memoryCardMan->mResult = iVar1;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      if (memoryCardMan->mResult != -1) break;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 10);
    iVar3 = iVar3 + 1;
    if (1 < iVar3) {
      if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
        __dla__FPv(memoryCardMan->m_saveBuffer);
        memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
      }
      memoryCardMan->mResult = 0;
      memoryCardMan->m_opDoneFlag = '\0';
      memoryCardMan->m_currentSlot = 0xff;
      memoryCardMan->mState = '\0';
      memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
      return;
    }
  } while( true );
}

