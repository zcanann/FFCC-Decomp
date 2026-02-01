// Function: SendAllStat__6JoyBusFi
// Entry: 800a72c4
// Size: 500 bytes

undefined4 SendAllStat__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  int iVar1;
  int iVar2;
  
  joyBus->m_threadParams[portIndex].m_state = '\0';
  joyBus->m_threadParams[portIndex].m_altState = '\0';
  OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
  iVar2 = 8;
  iVar1 = 0;
  do {
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1) = 0;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1) = 0
    ;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 4) = 0;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 4)
         = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 8) = 0;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 8)
         = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 0xc) = 0;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] +
     iVar1 + 0xc) = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 0x10) = 0
    ;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] +
     iVar1 + 0x10) = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 0x14) = 0
    ;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] +
     iVar1 + 0x14) = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 0x18) = 0
    ;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] +
     iVar1 + 0x18) = 0;
    *(undefined4 *)
     ((int)joyBus->m_cmdQueueData[joyBus->m_threadParams[portIndex].m_portIndex] + iVar1 + 0x1c) = 0
    ;
    *(undefined4 *)
     ((int)joyBus->m_recvQueueEntriesArr[joyBus->m_threadParams[portIndex].m_portIndex] +
     iVar1 + 0x1c) = 0;
    iVar2 = iVar2 + -1;
    iVar1 = iVar1 + 0x20;
  } while (iVar2 != 0);
  joyBus->m_cmdCount[joyBus->m_threadParams[portIndex].m_portIndex] = 0;
  joyBus->m_secCmdCount[joyBus->m_threadParams[portIndex].m_portIndex] = 0;
  OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
  return 0;
}

