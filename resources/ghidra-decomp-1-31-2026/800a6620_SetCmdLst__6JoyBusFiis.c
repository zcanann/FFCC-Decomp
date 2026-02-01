// Function: SetCmdLst__6JoyBusFiis
// Entry: 800a6620
// Size: 260 bytes

undefined4 SetCmdLst__6JoyBusFiis(JoyBus *joyBus,int portIndex,int param_3,short param_4)

{
  uint32_t uVar1;
  undefined4 uVar2;
  undefined local_18;
  undefined uStack_17;
  undefined4 local_14;
  
  uVar2 = 0;
  uStack_17 = (undefined)param_4;
  local_18 = (undefined)((ushort)param_4 >> 8);
  local_14 = CONCAT22(CONCAT11(0x1f,(char)param_3),CONCAT11(uStack_17,local_18));
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
    uVar1 = joyBus->m_threadParams[portIndex].m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar1] < 0x40) {
      joyBus->m_cmdQueueData[uVar1][joyBus->m_cmdCount[uVar1]] = local_14;
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

