// Function: McMount__14CMemoryCardManFi
// Entry: 800c4a04
// Size: 104 bytes

void McMount__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,int chan)

{
  int iVar1;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\x01';
  iVar1 = CARDMountAsync(chan,memoryCardMan->mMountWorkArea,Detach__Fll,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

