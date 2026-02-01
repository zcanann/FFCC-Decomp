// Function: SendRaderType__6JoyBusFP11ThreadParam
// Entry: 800a8514
// Size: 268 bytes

undefined4 SendRaderType__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  undefined uVar2;
  undefined4 uVar1;
  uint32_t uVar3;
  uint32_t local_18;
  
  uVar2 = GetRadarType__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
  local_18 = (uint)CONCAT21(0x140d,uVar2) << 8;
  if (joyBus->m_threadRunningMask == '\0') {
    uVar1 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar3 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
      joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_18;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

