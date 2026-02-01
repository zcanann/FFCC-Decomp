// Function: SetSendQueue__6JoyBusFP11ThreadParamUi
// Entry: 800ace6c
// Size: 220 bytes

int SetSendQueue__6JoyBusFP11ThreadParamUi(JoyBus *joyBus,ThreadParam *threadParam,uint32_t command)

{
  int iVar1;
  uint32_t uVar2;
  
  if (joyBus->m_threadRunningMask == '\0') {
    iVar1 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar2 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = command;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      iVar1 = -1;
    }
  }
  return iVar1;
}

