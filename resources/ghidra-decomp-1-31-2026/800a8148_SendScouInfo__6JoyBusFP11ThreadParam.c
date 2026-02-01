// Function: SendScouInfo__6JoyBusFP11ThreadParam
// Entry: 800a8148
// Size: 704 bytes

/* WARNING: Removing unreachable block (ram,0x800a8180) */

JoyBus * SendScouInfo__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  int iVar1;
  JoyBus *pJVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  undefined local_418;
  undefined auStack_417 [1035];
  
  if (threadParam->m_subState == '\x01') {
    uVar3 = threadParam->m_portIndex;
    uVar4 = *(uint32_t *)
             (joyBus->m_joyDataPacketBuffer[uVar3] + joyBus->m_txWordIndex[uVar3] * 4 + 2);
    if (joyBus->m_threadRunningMask == '\0') {
      pJVar2 = (JoyBus *)0x0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + uVar3);
      uVar3 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
        joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = uVar4;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        pJVar2 = (JoyBus *)0x0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
        pJVar2 = (JoyBus *)0xffffffff;
      }
    }
  }
  else {
    pJVar2 = joyBus;
    if (threadParam->m_subState == '\0') {
      joyBus->m_txWordIndex[threadParam->m_portIndex] = 0;
      memset(&local_418,0,0x400);
      memset(joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2,0,0x400);
      local_418 = 0xb;
      iVar1 = GetScouterInfo__8GbaQueueFiPUc(&GbaQue,threadParam->m_portIndex,auStack_417);
      pJVar2 = (JoyBus *)
               MakeJoyData__6JoyBusFPciPUi
                         (joyBus,&local_418,iVar1 + 1,
                          joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2);
      if ((int)pJVar2 < 0) {
        return pJVar2;
      }
      joyBus->m_txWordCount[threadParam->m_portIndex] = (int32_t)pJVar2;
      threadParam->m_subState = threadParam->m_subState + '\x01';
      uVar3 = threadParam->m_portIndex;
      uVar4 = *(uint32_t *)
               (joyBus->m_joyDataPacketBuffer[uVar3] + joyBus->m_txWordIndex[uVar3] * 4 + 2);
      if (joyBus->m_threadRunningMask == '\0') {
        pJVar2 = (JoyBus *)0x0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar3);
        uVar3 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
          joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = uVar4;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          pJVar2 = (JoyBus *)0x0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
          pJVar2 = (JoyBus *)0xffffffff;
        }
      }
    }
  }
  if ((pJVar2 == (JoyBus *)0x0) &&
     (joyBus->m_txWordIndex[threadParam->m_portIndex] =
           joyBus->m_txWordIndex[threadParam->m_portIndex] + 1,
     joyBus->m_txWordCount[threadParam->m_portIndex] <=
     joyBus->m_txWordIndex[threadParam->m_portIndex])) {
    pJVar2 = (JoyBus *)0x1;
  }
  return pJVar2;
}

