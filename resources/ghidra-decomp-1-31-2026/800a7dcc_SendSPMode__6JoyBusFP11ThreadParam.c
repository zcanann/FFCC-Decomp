// Function: SendSPMode__6JoyBusFP11ThreadParam
// Entry: 800a7dcc
// Size: 304 bytes

void SendSPMode__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint32_t uVar4;
  uint32_t local_18;
  
  uVar2 = GetSPMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
  bVar1 = (byte)(-(uVar2 & 0xff) >> 0x1f);
  local_18 = (uint)CONCAT21(0x1411,bVar1) << 8;
  if (joyBus->m_threadRunningMask == '\0') {
    iVar3 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar4 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
      joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = local_18;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar3 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
      iVar3 = -1;
    }
  }
  if (iVar3 == 0) {
    threadParam->m_flags[6] = bVar1;
  }
  return;
}

