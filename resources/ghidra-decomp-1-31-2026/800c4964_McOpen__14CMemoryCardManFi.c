// Function: McOpen__14CMemoryCardManFi
// Entry: 800c4964
// Size: 80 bytes

int32_t McOpen__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,int chan)

{
  int32_t iVar1;
  
  iVar1 = CARDOpen(chan,PTR_DAT_8032e854,&memoryCardMan->mFileInfo);
  memoryCardMan->mResult = iVar1;
  memoryCardMan->m_opDoneFlag = '\x01';
  memoryCardMan->mState = '\x03';
  return memoryCardMan->mResult;
}

