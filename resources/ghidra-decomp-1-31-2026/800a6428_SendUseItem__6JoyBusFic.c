// Function: SendUseItem__6JoyBusFic
// Entry: 800a6428
// Size: 252 bytes

undefined4 SendUseItem__6JoyBusFic(JoyBus *joyBus,int portIndex,char _itemId)

{
  uint32_t uVar1;
  undefined4 uVar2;
  uint32_t local_18;
  
  uVar2 = 0;
  local_18 = (uint)CONCAT21(0x140c,_itemId) << 8;
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

