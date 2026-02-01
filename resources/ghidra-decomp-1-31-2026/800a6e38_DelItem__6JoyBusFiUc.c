// Function: DelItem__6JoyBusFiUc
// Entry: 800a6e38
// Size: 260 bytes

undefined4 DelItem__6JoyBusFiUc(JoyBus *joyBus,int portIndex,char param_3)

{
  undefined4 uVar1;
  uint32_t uVar2;
  uint local_14;
  
  local_14 = CONCAT22(CONCAT11(0x17,param_3),0xffff) & 0xff3fffff;
  if (joyBus->m_threadRunningMask == '\0') {
    uVar1 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar2 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = local_14;
      uVar2 = joyBus->m_threadParams[portIndex].m_portIndex;
      joyBus->m_cmdCount[uVar2] = joyBus->m_cmdCount[uVar2] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

