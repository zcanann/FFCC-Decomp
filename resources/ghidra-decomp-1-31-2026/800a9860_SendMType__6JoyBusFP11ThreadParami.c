// Function: SendMType__6JoyBusFP11ThreadParami
// Entry: 800a9860
// Size: 940 bytes

void SendMType__6JoyBusFP11ThreadParami(JoyBus *joyBus,ThreadParam *threadParam,int modeType)

{
  int iVar1;
  uint32_t uVar2;
  int iVar3;
  uint32_t local_14;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  iVar3 = 8;
  iVar1 = 0;
  do {
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1) = 0;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 4) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 4) = 0;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 8) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 8) = 0;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0xc) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0xc) = 0;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x10) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x10) = 0
    ;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x14) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x14) = 0
    ;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x18) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x18) = 0
    ;
    *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x1c) = 0;
    *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x1c) = 0
    ;
    iVar3 = iVar3 + -1;
    iVar1 = iVar1 + 0x20;
  } while (iVar3 != 0);
  joyBus->m_cmdCount[threadParam->m_portIndex] = 0;
  joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
  OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  iVar1 = 0;
  if (joyBus->m_threadRunningMask != '\0') {
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    uVar2 = threadParam->m_portIndex;
    if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
      joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = 0x10000000;
      joyBus->m_cmdCount[threadParam->m_portIndex] =
           joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
      OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      iVar1 = 0;
    }
    else {
      OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
      iVar1 = -1;
    }
  }
  if (iVar1 == 0) {
    local_14 = CONCAT13(0x1b,(uint3)(byte)modeType << 0x10);
    if (joyBus->m_threadRunningMask == '\0') {
      iVar1 = 0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar2 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar2] < 0x40) {
        joyBus->m_cmdQueueData[uVar2][joyBus->m_cmdCount[uVar2]] = local_14;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        iVar1 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar2);
        iVar1 = -1;
      }
    }
    if (iVar1 == 0) {
      joyBus->m_modeXArr[threadParam->m_portIndex] =
           joyBus->m_nextModeTypeArr[threadParam->m_portIndex];
      joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = (byte)modeType;
      if ((modeType == 0) || (modeType == 4)) {
        joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\0';
      }
      else {
        joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\x01';
      }
    }
  }
  return;
}

