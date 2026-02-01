// Function: SetTmpArti__6JoyBusFiii
// Entry: 800a6524
// Size: 252 bytes

undefined4 SetTmpArti__6JoyBusFiii(JoyBus *joyBus,int portIndex,int param_3,int param_4)

{
  uint32_t uVar1;
  undefined4 uVar2;
  uint32_t local_18;
  
  uVar2 = 0;
  local_18 = CONCAT13(0x20,(uint3)(byte)param_3 << 0x10);
  local_18 = (uint)CONCAT21(local_18._0_2_,(char)param_4 + 'a') << 8;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_18;
      uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
      joyBus->m_cmdCount[uVar1] = joyBus->m_cmdCount[uVar1] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

