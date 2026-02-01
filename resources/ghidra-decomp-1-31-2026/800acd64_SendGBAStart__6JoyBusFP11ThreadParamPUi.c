// Function: SendGBAStart__6JoyBusFP11ThreadParamPUi
// Entry: 800acd64
// Size: 264 bytes

int SendGBAStart__6JoyBusFP11ThreadParamPUi
              (JoyBus *joyBus,ThreadParam *threadParam,uint32_t *param_3)

{
  uint32_t uVar1;
  int iVar2;
  
  iVar2 = 0;
  *param_3 = 0xa010000;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar1 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = 0xa010000;
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
    threadParam->m_sentStartFlag = '\x01';
  }
  return iVar2;
}

