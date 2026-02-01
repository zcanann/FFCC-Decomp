// Function: SendMBase__6JoyBusFP11ThreadParam
// Entry: 800abb6c
// Size: 484 bytes

int SendMBase__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  uint32_t uVar1;
  int iVar2;
  uint uVar3;
  uint32_t uVar4;
  undefined local_18;
  undefined uStack_17;
  undefined local_16;
  undefined uStack_15;
  undefined4 local_14;
  
  GetMBasePos__8GbaQueueFiPsPs(&GbaQue,threadParam->m_portIndex,&local_16,&local_18);
  iVar2 = 0;
  local_14 = CONCAT22(0xf00,CONCAT11(uStack_15,local_16));
  uVar1 = local_14;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar4 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
      joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar1;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar2 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
      iVar2 = -1;
    }
  }
  if (iVar2 == 0) {
    uVar3 = 0;
    local_14 = CONCAT22(0x4f00,CONCAT11(uStack_17,local_18));
    uVar1 = local_14;
    if (joyBus->m_threadRunningMask != '\0') {
      OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar4 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
        joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar1;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar3 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
        uVar3 = 0xffffffff;
      }
    }
    iVar2 = (int)(-uVar3 | uVar3) >> 0x1f;
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}

