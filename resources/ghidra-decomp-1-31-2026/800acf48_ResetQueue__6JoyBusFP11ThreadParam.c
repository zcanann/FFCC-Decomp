// Function: ResetQueue__6JoyBusFP11ThreadParam
// Entry: 800acf48
// Size: 468 bytes

void ResetQueue__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  int iVar1;
  int iVar2;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  iVar2 = 8;
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
    iVar2 = iVar2 + -1;
    iVar1 = iVar1 + 0x20;
  } while (iVar2 != 0);
  joyBus->m_cmdCount[threadParam->m_portIndex] = 0;
  joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
  OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  return;
}

