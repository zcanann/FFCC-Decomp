// Function: McWrite__14CMemoryCardManFPcii
// Entry: 800c4274
// Size: 104 bytes

void McWrite__14CMemoryCardManFPcii
               (CMemoryCardMan *memoryCardMan,uint8_t *param_2,undefined4 param_3,undefined4 param_4
               )

{
  int iVar1;
  
  if (param_2 == (uint8_t *)0x0) {
    param_2 = memoryCardMan->m_saveBuffer;
  }
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\t';
  iVar1 = CARDWriteAsync(&memoryCardMan->mFileInfo,param_2,param_3,param_4,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  return;
}

