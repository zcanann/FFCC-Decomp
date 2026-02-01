// Function: SendAddLetter__6JoyBusFi
// Entry: 800a703c
// Size: 248 bytes

int SendAddLetter__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  uint32_t uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = 0x14010000;
      uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
      joyBus->m_cmdCount[uVar1] = joyBus->m_cmdCount[uVar1] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      iVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      iVar2 = -1;
    }
  }
  return iVar2;
}

