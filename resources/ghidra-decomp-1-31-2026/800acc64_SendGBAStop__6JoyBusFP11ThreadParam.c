// Function: SendGBAStop__6JoyBusFP11ThreadParam
// Entry: 800acc64
// Size: 256 bytes

int SendGBAStop__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  uint32_t uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar1 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = 0xa000000;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      iVar2 = -1;
    }
  }
  if (iVar2 == 0) {
    threadParam->m_sentStartFlag = '\0';
  }
  return iVar2;
}

