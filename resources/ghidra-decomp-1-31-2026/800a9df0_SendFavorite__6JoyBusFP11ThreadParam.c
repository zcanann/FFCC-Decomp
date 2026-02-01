// Function: SendFavorite__6JoyBusFP11ThreadParam
// Entry: 800a9df0
// Size: 700 bytes

/* WARNING: Removing unreachable block (ram,0x800a9e28) */

JoyBus * SendFavorite__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  int iVar1;
  JoyBus *pJVar2;
  JoyBus *pJVar3;
  uint32_t uVar4;
  uint32_t uVar5;
  undefined local_58;
  undefined auStack_57 [75];
  
  if (threadParam->m_subState == '\x01') {
    uVar4 = threadParam->m_portIndex;
    uVar5 = *(uint32_t *)
             (joyBus->m_joyDataPacketBuffer[uVar4] + joyBus->m_txWordIndex[uVar4] * 4 + 2);
    if (joyBus->m_threadRunningMask == '\0') {
      pJVar3 = (JoyBus *)0x0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + uVar4);
      uVar4 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
        joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar5;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        pJVar3 = (JoyBus *)0x0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
        pJVar3 = (JoyBus *)0xffffffff;
      }
    }
  }
  else {
    pJVar3 = joyBus;
    if (threadParam->m_subState == '\0') {
      memset(&local_58,0,0x40);
      memset(joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2,0,0x400);
      local_58 = 4;
      iVar1 = GetFavorite__8GbaQueueFiPc(&GbaQue,threadParam->m_portIndex,auStack_57);
      pJVar2 = (JoyBus *)
               MakeJoyData__6JoyBusFPciPUi
                         (joyBus,&local_58,iVar1 + 1,
                          joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2);
      if ((int)pJVar2 < 0) {
        return pJVar2;
      }
      pJVar3 = (JoyBus *)0x0;
      joyBus->m_txWordCount[threadParam->m_portIndex] = (int32_t)pJVar2;
      joyBus->m_txWordIndex[threadParam->m_portIndex] = 0;
      uVar4 = threadParam->m_portIndex;
      uVar5 = *(uint32_t *)
               (joyBus->m_joyDataPacketBuffer[uVar4] + joyBus->m_txWordIndex[uVar4] * 4 + 2);
      if (joyBus->m_threadRunningMask != '\0') {
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar4);
        uVar4 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
          joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar5;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          pJVar3 = (JoyBus *)0x0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
          pJVar3 = (JoyBus *)0xffffffff;
        }
      }
      threadParam->m_subState = threadParam->m_subState + '\x01';
    }
  }
  if ((pJVar3 == (JoyBus *)0x0) &&
     (joyBus->m_txWordIndex[threadParam->m_portIndex] =
           joyBus->m_txWordIndex[threadParam->m_portIndex] + 1,
     joyBus->m_txWordCount[threadParam->m_portIndex] <=
     joyBus->m_txWordIndex[threadParam->m_portIndex])) {
    pJVar3 = (JoyBus *)0x1;
  }
  return pJVar3;
}

