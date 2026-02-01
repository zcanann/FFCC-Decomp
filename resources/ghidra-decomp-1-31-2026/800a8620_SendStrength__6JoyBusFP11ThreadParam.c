// Function: SendStrength__6JoyBusFP11ThreadParam
// Entry: 800a8620
// Size: 284 bytes

undefined4 SendStrength__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  undefined4 uVar1;
  uint32_t uVar2;
  undefined4 local_28;
  undefined local_24;
  undefined local_23;
  undefined local_22;
  
  GetStrengthData__8GbaQueueFiPUc(&GbaQue,threadParam->m_portIndex,&local_24);
  local_28 = CONCAT31(CONCAT21(CONCAT11(0x19,local_24),local_23),local_22);
  if (joyBus->m_threadRunningMask == '\0') {
    uVar1 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar2 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = local_28;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

