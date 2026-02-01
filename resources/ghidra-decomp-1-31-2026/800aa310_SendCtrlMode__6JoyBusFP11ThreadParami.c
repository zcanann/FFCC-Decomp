// Function: SendCtrlMode__6JoyBusFP11ThreadParami
// Entry: 800aa310
// Size: 304 bytes

void SendCtrlMode__6JoyBusFP11ThreadParami(JoyBus *joyBus,ThreadParam *threadParam,int controlMode)

{
  char cVar2;
  int iVar1;
  uint32_t uVar3;
  byte bVar4;
  uint32_t local_18;
  
  bVar4 = (byte)controlMode;
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
  if (cVar2 != '\0') {
    bVar4 = 0;
  }
  local_18 = CONCAT13(9,(uint3)bVar4 << 0x10);
  if (joyBus->m_threadRunningMask == '\0') {
    iVar1 = 0;
  }
  else {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar3 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
      joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_18;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
      iVar1 = -1;
    }
  }
  if (iVar1 == 0) {
    joyBus->m_ctrlModeArr[threadParam->m_portIndex] = bVar4;
  }
  return;
}

