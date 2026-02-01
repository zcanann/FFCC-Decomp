// Function: SendPlayerHP__6JoyBusFP11ThreadParam
// Entry: 800aac60
// Size: 308 bytes

undefined4 SendPlayerHP__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint32_t uVar4;
  uint local_18 [3];
  
  iVar1 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_18);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    local_18[0] = 0;
    uVar3 = GetPlayerHP__8GbaQueueFiPUc(&GbaQue,threadParam->m_portIndex,local_18);
    if ((int)(-uVar3 | uVar3) < 0) {
      local_18[0] = local_18[0] | 0x800000;
      uVar3 = local_18[0];
      if (joyBus->m_threadRunningMask == '\0') {
        uVar2 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar4 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
          joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar3;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          uVar2 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
          uVar2 = 0xffffffff;
        }
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

