// Function: SendItemUse__6JoyBusFP11ThreadParam
// Entry: 800a7efc
// Size: 300 bytes

undefined4 SendItemUse__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  char cVar2;
  undefined4 uVar1;
  undefined uVar3;
  uint32_t uVar4;
  uint32_t local_18;
  
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
  if (cVar2 == '\0') {
    uVar3 = GetItemUse__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    local_18 = (uint)CONCAT21(0x1410,uVar3) << 8;
    if (joyBus->m_threadRunningMask == '\0') {
      uVar1 = 0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar4 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
        joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = local_18;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar1 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
        uVar1 = 0xffffffff;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

