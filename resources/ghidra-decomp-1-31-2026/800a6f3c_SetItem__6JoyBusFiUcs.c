// Function: SetItem__6JoyBusFiUcs
// Entry: 800a6f3c
// Size: 256 bytes

undefined4 SetItem__6JoyBusFiUcs(JoyBus *joyBus,int portIndex,int itemId,uint16_t amount)

{
  undefined4 uVar1;
  uint32_t uVar2;
  undefined local_18;
  undefined uStack_17;
  uint local_14;
  
  uStack_17 = (undefined)amount;
  local_18 = (undefined)(amount >> 8);
  local_14 = CONCAT22(CONCAT11(0x17,(char)itemId),CONCAT11(uStack_17,local_18)) & 0xff3fffff;
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

