// Function: SetCtrlMode__6JoyBusFii
// Entry: 800a7750
// Size: 348 bytes

int SetCtrlMode__6JoyBusFii(JoyBus *joyBus,int portIndex,int controlMode)

{
  char cVar2;
  int iVar1;
  uint32_t uVar3;
  byte bVar4;
  uint32_t local_18;
  
  cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,portIndex);
  if (cVar2 == '\0') {
    bVar4 = (byte)((byte)((uint)-controlMode >> 0x18) | (byte)((uint)controlMode >> 0x18)) >> 7;
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,joyBus->m_threadParams[portIndex].m_portIndex);
    if (cVar2 != '\0') {
      bVar4 = 0;
    }
    local_18 = CONCAT13(9,(uint3)bVar4 << 0x10);
    if (joyBus->m_threadRunningMask == '\0') {
      iVar1 = 0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[portIndex].m_portIndex);
      uVar3 = joyBus->m_threadParams[portIndex].m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
        joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_18;
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
      joyBus->m_ctrlModeArr[joyBus->m_threadParams[portIndex].m_portIndex] = bVar4;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

