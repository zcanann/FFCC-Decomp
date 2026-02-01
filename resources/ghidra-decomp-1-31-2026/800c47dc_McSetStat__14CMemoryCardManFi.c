// Function: McSetStat__14CMemoryCardManFi
// Entry: 800c47dc
// Size: 80 bytes

int32_t McSetStat__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,undefined4 param_2)

{
  int32_t iVar1;
  
  iVar1 = CARDSetStatus(param_2,(memoryCardMan->mFileInfo).fileNo,&memoryCardMan->mcardStat);
  memoryCardMan->mResult = iVar1;
  memoryCardMan->m_opDoneFlag = '\x01';
  memoryCardMan->mState = '\a';
  return memoryCardMan->mResult;
}

