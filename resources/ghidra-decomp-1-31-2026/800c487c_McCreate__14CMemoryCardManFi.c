// Function: McCreate__14CMemoryCardManFi
// Entry: 800c487c
// Size: 108 bytes

void McCreate__14CMemoryCardManFi(CMemoryCardMan *memoryCardMan,undefined4 param_2)

{
  int iVar1;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\x05';
  iVar1 = CARDCreateAsync(param_2,PTR_DAT_8032e854,0x2c000,&memoryCardMan->mFileInfo,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

