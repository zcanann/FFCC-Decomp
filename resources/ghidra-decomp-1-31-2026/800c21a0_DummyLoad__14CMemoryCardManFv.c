// Function: DummyLoad__14CMemoryCardManFv
// Entry: 800c21a0
// Size: 944 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int32_t DummyLoad__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

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
  if (memoryCardMan->mResult == 0) {
    iVar2 = CARDOpen(0,PTR_DAT_8032e854,&memoryCardMan->mFileInfo);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x03';
    if (memoryCardMan->mResult == 0) {
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
      memoryCardMan->m_opDoneFlag = '\0';
      memoryCardMan->mState = '\b';
      iVar1 = CARDReadAsync(&memoryCardMan->mFileInfo,memoryCardMan->m_saveBuffer,0xa000,0x4000,
                            Attach__Fll);
      if (iVar1 < 0) {
        memoryCardMan->m_opDoneFlag = '\x01';
      }
      memoryCardMan->mResult = iVar1;
      do {
      } while (-1 < (-(int)(char)memoryCardMan->m_opDoneFlag |
                    (int)(char)memoryCardMan->m_opDoneFlag));
      if (memoryCardMan->mResult == 0) {
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
        LoadInit__5CGameFv(&Game.game);
        SetLoadData__14CMemoryCardManFv(memoryCardMan);
        LoadFinished__5CGameFv(&Game.game);
        if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
          __dla__FPv(memoryCardMan->m_saveBuffer);
          memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
        }
        iVar2 = 0;
      }
      else {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce(&System,s_McRead__d__error__d__801daee0,0);
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
    }
    else {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_McOpen__d__error__d__801dae90,0);
      }
      iVar2 = CARDUnmount(0);
      memoryCardMan->mResult = iVar2;
      memoryCardMan->m_opDoneFlag = '\x01';
      memoryCardMan->mState = '\x02';
      memoryCardMan->m_currentSlot = 0xff;
      iVar2 = memoryCardMan->mResult;
    }
  }
  else {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_McMount__d__error__d__801dae78,0);
    }
    iVar2 = CARDUnmount(0);
    memoryCardMan->mResult = iVar2;
    memoryCardMan->m_opDoneFlag = '\x01';
    memoryCardMan->mState = '\x02';
    memoryCardMan->m_currentSlot = 0xff;
    iVar2 = memoryCardMan->mResult;
  }
  return iVar2;
}

