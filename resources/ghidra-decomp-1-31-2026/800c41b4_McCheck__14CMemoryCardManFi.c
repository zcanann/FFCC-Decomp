// Function: McCheck__14CMemoryCardManFi
// Entry: 800c41b4
// Size: 96 bytes

void McCheck__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,undefined4 param_2)

{
  int iVar1;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\v';
  iVar1 = CARDCheckAsync(param_2,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

