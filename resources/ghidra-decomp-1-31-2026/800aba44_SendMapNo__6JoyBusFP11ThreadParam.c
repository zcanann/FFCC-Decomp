// Function: SendMapNo__6JoyBusFP11ThreadParam
// Entry: 800aba44
// Size: 296 bytes

int SendMapNo__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  uint32_t uVar1;
  uint32_t uVar2;
  uint uVar3;
  undefined local_28 [3];
  undefined uStack_25;
  undefined local_24 [3];
  undefined uStack_21;
  undefined4 local_20;
  
  GetStageNo__8GbaQueueFiPiPi(&GbaQue,threadParam->m_portIndex,local_24,local_28);
  uVar3 = 0;
  local_20 = CONCAT31(CONCAT21(0xe01,uStack_21),uStack_25);
  uVar1 = local_20;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar2 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = uVar1;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar3 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      uVar3 = 0xffffffff;
    }
  }
  return (int)(-uVar3 | uVar3) >> 0x1f;
}

