// Function: McUnmount__14CMemoryCardManFi
// Entry: 800c49b4
// Size: 80 bytes

int32_t McUnmount__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,int chan)

{
  int32_t iVar1;
  
  iVar1 = CARDUnmount(chan);
  memoryCardMan->mResult = iVar1;
  memoryCardMan->m_opDoneFlag = '\x01';
  memoryCardMan->mState = '\x02';
  memoryCardMan->m_currentSlot = 0xff;
  return memoryCardMan->mResult;
}

