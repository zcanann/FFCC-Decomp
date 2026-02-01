// Function: McFormat__14CMemoryCardManFi
// Entry: 800c4214
// Size: 96 bytes

void McFormat__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,undefined4 param_2)

{
  int iVar1;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\n';
  iVar1 = CARDFormatAsync(param_2,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

