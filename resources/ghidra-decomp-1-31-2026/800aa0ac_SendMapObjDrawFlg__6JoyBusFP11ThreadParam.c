// Function: SendMapObjDrawFlg__6JoyBusFP11ThreadParam
// Entry: 800aa0ac
// Size: 612 bytes

int SendMapObjDrawFlg__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  byte bVar1;
  uint32_t uVar2;
  int iVar3;
  uint32_t uVar4;
  uint uVar5;
  byte *pbVar6;
  byte local_28 [4];
  undefined local_24;
  undefined local_23;
  undefined local_22;
  byte local_21;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar3 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_24);
  if (iVar3 < 0) {
    iVar3 = -1;
  }
  else {
    GetMapObjDrawFlg__8GbaQueueFPUi(&GbaQue,&local_24);
    pbVar6 = local_28;
    local_28[3] = local_24;
    uVar5 = 0xffff;
    iVar3 = 4;
    local_28[2] = local_23;
    local_28[1] = local_22;
    local_28[0] = local_21;
    while (iVar3 = iVar3 + -1, -1 < iVar3) {
      bVar1 = *pbVar6;
      pbVar6 = pbVar6 + 1;
      uVar5 = (uVar5 << 8 ^ (uint)JoyBusCrcTable[uVar5 >> 8 ^ (uint)bVar1]) & 0xffff;
    }
    iVar3 = 0;
    local_20 = CONCAT31(CONCAT21(CONCAT11(0x16,(char)~uVar5),(char)(~uVar5 >> 8)),local_21);
    uVar2 = local_20;
    local_1c = CONCAT31(CONCAT21(CONCAT11(0x56,local_22),local_23),local_24);
    if (joyBus->m_threadRunningMask != '\0') {
      OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      uVar4 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
        joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar2;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        iVar3 = 0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
        iVar3 = -1;
      }
    }
    uVar2 = local_1c;
    if (iVar3 == 0) {
      if (joyBus->m_threadRunningMask == '\0') {
        iVar3 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar4 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
          joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar2;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          iVar3 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
          iVar3 = -1;
        }
      }
    }
  }
  return iVar3;
}

