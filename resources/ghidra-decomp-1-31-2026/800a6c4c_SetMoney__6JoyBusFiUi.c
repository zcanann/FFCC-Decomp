// Function: SetMoney__6JoyBusFiUi
// Entry: 800a6c4c
// Size: 484 bytes

int SetMoney__6JoyBusFiUi(JoyBus *joyBus,int portIndex,uint32_t money)

{
  uint32_t uVar1;
  int iVar2;
  undefined4 local_28;
  
  iVar2 = 0;
  if ((int)joyBus->m_cmdCount[portIndex] < 0x3e) {
    local_28 = CONCAT31(CONCAT21(0x1a00,(char)(money >> 0x18)),(char)(money >> 0x10));
    if (joyBus->m_threadRunningMask != '\0') {
      OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
        joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_28;
        uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
        joyBus->m_cmdCount[uVar1] = joyBus->m_cmdCount[uVar1] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex
                         );
        iVar2 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
        iVar2 = -1;
      }
    }
    if (iVar2 == 0) {
      iVar2 = 0;
      local_28 = CONCAT13(0x5a,(uint3)(byte)(money >> 8) << 0x10);
      local_28 = (uint)CONCAT21(local_28._0_2_,(char)money) << 8;
      if (joyBus->m_threadRunningMask != '\0') {
        OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
        uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
          joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_28;
          uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
          joyBus->m_cmdCount[uVar1] = joyBus->m_cmdCount[uVar1] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores +
                            joyBus->m_threadParams[portIndex].m_portIndex);
          iVar2 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar1);
          iVar2 = -1;
        }
      }
    }
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}

