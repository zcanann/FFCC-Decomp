// Function: ChgCtrlMode__6JoyBusFi
// Entry: 800a78ac
// Size: 292 bytes

int ChgCtrlMode__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  char cVar2;
  int iVar1;
  byte bVar4;
  uint32_t uVar3;
  uint32_t local_28;
  
  bVar4 = joyBus->m_ctrlModeArr[portIndex];
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,portIndex);
  if (cVar2 == '\0') {
    bVar4 = bVar4 ^ (byte)DAT_80330b20;
    local_28 = CONCAT13(9,(uint3)bVar4 << 0x10);
    if (joyBus->m_threadRunningMask == '\0') {
      iVar1 = 0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar3 = joyBus->m_threadParams[portIndex].m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
        joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_28;
        uVar3 = joyBus->m_threadParams[portIndex].m_portIndex;
        joyBus->m_cmdCount[uVar3] = joyBus->m_cmdCount[uVar3] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex
                         );
        iVar1 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
        iVar1 = -1;
      }
    }
    if (iVar1 == 0) {
      joyBus->m_ctrlModeArr[portIndex] = bVar4;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

