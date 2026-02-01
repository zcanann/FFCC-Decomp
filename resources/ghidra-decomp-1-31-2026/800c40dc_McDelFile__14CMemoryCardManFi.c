// Function: McDelFile__14CMemoryCardManFi
// Entry: 800c40dc
// Size: 96 bytes

void McDelFile__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,undefined4 param_2)

{
  int iVar1;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\r';
  iVar1 = CARDDeleteAsync(param_2,PTR_DAT_8032e854,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

