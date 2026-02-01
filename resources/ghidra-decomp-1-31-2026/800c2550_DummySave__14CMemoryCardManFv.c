// Function: DummySave__14CMemoryCardManFv
// Entry: 800c2550
// Size: 1824 bytes

int32_t DummySave__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  int iVar1;
  int32_t iVar2;
  uint8_t *puVar3;
  
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\x01';
  iVar1 = CARDMountAsync(0,memoryCardMan->mMountWorkArea,Detach__Fll,Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  do {
  } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag));
  if (memoryCardMan->mResult == -6) {
    memoryCardMan->m_opDoneFlag = '\0';
    memoryCardMan->mState = '\n';
    iVar1 = CARDFormatAsync(0,Attach__Fll);
    if (iVar1 < 0) {
      memoryCardMan->m_opDoneFlag = '\x01';
    }
    memoryCardMan->mResult = iVar1;
    do {
    } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag)
            );
    if (memoryCardMan->mResult != 0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McFormat__d__error__d__801daef8,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      return memoryCardMan->mResult;
    }
  }
  if (memoryCardMan->mResult != 0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_McMount__d__error__d__801dae78,0);
    }
    iVar2 = CARDUnmount(0);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x02';
    memoryCardMan->m_currentSlot = 0xff;
    return memoryCardMan->mResult;
  }
  iVar2 = CARDOpen(0,PTR_DAT_8032e854,&memoryCardMan->mFileInfo);
  memoryCardMan->mResult = iVar2;
  memoryCardMan->m_opDoneFlag = '\x01';
  memoryCardMan->mState = '\x03';
  if (memoryCardMan->mResult == -4) {
    memoryCardMan->m_opDoneFlag = '\0';
    memoryCardMan->mState = '\x05';
    iVar1 = CARDCreateAsync(0,PTR_DAT_8032e854,0x2c000,&memoryCardMan->mFileInfo,Attach__Fll);
    if (iVar1 < 0) {
      memoryCardMan->m_opDoneFlag = '\x01';
    }
    memoryCardMan->mResult = iVar1;
    do {
    } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag)
            );
    if (memoryCardMan->mResult != 0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McCreate__d__error__d__801daf10,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      return memoryCardMan->mResult;
    }
    iVar2 = CARDGetStatus(0,(memoryCardMan->mFileInfo).fileNo,&memoryCardMan->mcardStat);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x06';
    if (memoryCardMan->mResult != 0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McGetStat__d__error__d__801daf28,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      return memoryCardMan->mResult;
    }
    if (memoryCardMan->m_saveBuffer == (uint8_t *)0x0) {
      puVar3 = (uint8_t *)
               __nwa__FUlPQ27CMemory6CStagePci
                         (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x2ab);
      memoryCardMan->m_saveBuffer = puVar3;
      if ((memoryCardMan->m_saveBuffer == (uint8_t *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801daeb8,s_memorycard_cpp_801daea8,
                   0x2ad);
      }
    }
    memset(memoryCardMan->m_saveBuffer,0,0xa000);
    SetMcIconImage__14CMemoryCardManFv(memoryCardMan);
    memoryCardMan->m_opDoneFlag = '\0';
    memoryCardMan->mState = '\t';
    iVar1 = CARDWriteAsync(&memoryCardMan->mFileInfo,memoryCardMan->m_saveBuffer,0x4000,0,
                           Attach__Fll);
    if (iVar1 < 0) {
      memoryCardMan->m_opDoneFlag = '\x01';
    }
    memoryCardMan->mResult = iVar1;
    do {
    } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag)
            );
    if (memoryCardMan->mResult != 0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McWrite__d__error__d__801daf44,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
        __dla__FPv(memoryCardMan->m_saveBuffer);
        memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
      }
      return memoryCardMan->mResult;
    }
    iVar2 = CARDSetStatus(0,(memoryCardMan->mFileInfo).fileNo,&memoryCardMan->mcardStat);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\a';
    if (memoryCardMan->mResult != 0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McSetStat__d__error__d__801daf5c,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
        __dla__FPv(memoryCardMan->m_saveBuffer);
        memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
      }
      return memoryCardMan->mResult;
    }
  }
  else {
    if (memoryCardMan->m_saveBuffer == (uint8_t *)0x0) {
      puVar3 = (uint8_t *)
               __nwa__FUlPQ27CMemory6CStagePci
                         (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x2ab);
      memoryCardMan->m_saveBuffer = puVar3;
      if ((memoryCardMan->m_saveBuffer == (uint8_t *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801daeb8,s_memorycard_cpp_801daea8,
                   0x2ad);
      }
    }
    memset(memoryCardMan->m_saveBuffer,0,0xa000);
  }
  MakeSaveData__14CMemoryCardManFv(memoryCardMan);
  memoryCardMan->m_opDoneFlag = '\0';
  memoryCardMan->mState = '\t';
  iVar1 = CARDWriteAsync(&memoryCardMan->mFileInfo,memoryCardMan->m_saveBuffer,0xa000,0x4000,
                         Attach__Fll);
  if (iVar1 < 0) {
    memoryCardMan->m_opDoneFlag = '\x01';
  }
  memoryCardMan->mResult = iVar1;
  do {
  } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag));
  if (memoryCardMan->mResult == 0) {
    if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
      __dla__FPv(memoryCardMan->m_saveBuffer);
      memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
    }
    iVar1 = (memoryCardMan->mFileInfo).chan;
    if ((iVar1 < 0) || (1 < iVar1)) {
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x04';
      memoryCardMan->mResult = -3;
    }
    else {
      iVar2 = CARDClose(&memoryCardMan->mFileInfo);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x04';
    }
    iVar2 = CARDUnmount(0);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    iVar2 = 0;
    memoryCardMan->mState = '\x02';
    memoryCardMan->m_currentSlot = 0xff;
  }
  else {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_McWrite__d__error__d__801daf44,0);
    }
    iVar1 = (memoryCardMan->mFileInfo).chan;
    if ((iVar1 < 0) || (1 < iVar1)) {
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x04';
      memoryCardMan->mResult = -3;
    }
    else {
      iVar2 = CARDClose(&memoryCardMan->mFileInfo);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x04';
    }
    iVar2 = CARDUnmount(0);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x02';
    memoryCardMan->m_currentSlot = 0xff;
    if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
      __dla__FPv(memoryCardMan->m_saveBuffer);
      memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
    }
    iVar2 = memoryCardMan->mResult;
  }
  return iVar2;
}

