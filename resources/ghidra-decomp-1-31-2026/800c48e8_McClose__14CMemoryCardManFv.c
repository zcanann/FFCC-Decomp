// Function: McClose__14CMemoryCardManFv
// Entry: 800c48e8
// Size: 124 bytes

int32_t McClose__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  int iVar1;
  int32_t iVar2;
  
  iVar1 = (memoryCardMan->mFileInfo).chan;
  if ((iVar1 < 0) || (1 < iVar1)) {
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x04';
    memoryCardMan->mResult = -3;
    iVar2 = memoryCardMan->mResult;
  }
  else {
    iVar2 = CARDClose(&memoryCardMan->mFileInfo);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x04';
    iVar2 = memoryCardMan->mResult;
  }
  return iVar2;
}

