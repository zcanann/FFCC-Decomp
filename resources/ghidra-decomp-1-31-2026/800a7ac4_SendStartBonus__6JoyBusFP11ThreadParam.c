// Function: SendStartBonus__6JoyBusFP11ThreadParam
// Entry: 800a7ac4
// Size: 240 bytes

undefined4 SendStartBonus__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  uint32_t uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar1 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = 0x14140000;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

