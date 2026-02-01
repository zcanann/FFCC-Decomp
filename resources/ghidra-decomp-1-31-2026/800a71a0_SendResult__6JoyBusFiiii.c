// Function: SendResult__6JoyBusFiiii
// Entry: 800a71a0
// Size: 260 bytes

undefined4
SendResult__6JoyBusFiiii
          (JoyBus *joyBus,int portIndex,undefined4 param_3,undefined param_4,undefined param_5)

{
  uint uVar1;
  uint32_t uVar2;
  undefined4 uVar3;
  uint32_t local_18;
  
  uVar1 = countLeadingZeros(param_3);
  uVar3 = 0;
  local_18 = (uint)CONCAT21(CONCAT11('\a' - ((byte)(uVar1 >> 5) & 1),param_4),param_5) << 8;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar2 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = local_18;
      uVar2 = joyBus->m_threadParams[portIndex].m_portIndex;
      joyBus->m_cmdCount[uVar2] = joyBus->m_cmdCount[uVar2] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar3 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

