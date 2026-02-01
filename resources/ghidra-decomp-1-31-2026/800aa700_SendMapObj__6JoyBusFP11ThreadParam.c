// Function: SendMapObj__6JoyBusFP11ThreadParam
// Entry: 800aa700
// Size: 672 bytes

/* WARNING: Removing unreachable block (ram,0x800aa738) */

JoyBus * SendMapObj__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  int iVar1;
  JoyBus *pJVar2;
  uint32_t uVar3;
  uint32_t uVar4;
  undefined local_218;
  char acStack_217 [523];
  
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
      memset(&local_218,0,0x200);
      local_218 = 3;
      iVar1 = GetMapObj__8GbaQueueFPUc(&GbaQue,acStack_217);
      pJVar2 = (JoyBus *)
               MakeJoyData__6JoyBusFPciPUi
                         (joyBus,&local_218,iVar1 + 1,
                          joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2);
      if ((int)pJVar2 < 0) {
        return pJVar2;
      }
      joyBus->m_txWordCount[threadParam->m_portIndex] = (int32_t)pJVar2;
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
      threadParam->m_subState = threadParam->m_subState + '\x01';
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

