// Function: Init__14CMemoryCardManFv
// Entry: 800c4d24
// Size: 148 bytes

void Init__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  CStage *pCVar1;
  void *pvVar2;
  
  CARDInit();
  memoryCardMan->mResult = 0;
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->m_currentSlot = 0xff;
  memoryCardMan->mState = '\0';
  memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x16000,s_CMemoryCardMan_801dae0c,0);
  memoryCardMan->mStage = pCVar1;
  pvVar2 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                             (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x88);
  memoryCardMan->mMountWorkArea = pvVar2;
  memoryCardMan->m_currentSlot = 0xff;
  return;
}

