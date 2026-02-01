// Function: McGetStat__14CMemoryCardManFi
// Entry: 800c482c
// Size: 80 bytes

int32_t McGetStat__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,int param_2)

{
  int32_t iVar1;
  
  iVar1 = CARDGetStatus(param_2,(memoryCardMan->mFileInfo).fileNo,&memoryCardMan->mcardStat);
  memoryCardMan->mResult = iVar1;
  memoryCardMan->m_opDoneFlag = '\x01';
  memoryCardMan->mState = '\x06';
  return memoryCardMan->mResult;
}

