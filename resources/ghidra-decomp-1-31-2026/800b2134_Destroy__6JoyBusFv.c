// Function: Destroy__6JoyBusFv
// Entry: 800b2134
// Size: 448 bytes

void Destroy__6JoyBusFv(JoyBus *joyBus)

{
  int iVar1;
  JoyBus *pJVar2;
  JoyBus *pJVar3;
  JoyBus *pJVar4;
  int iVar5;
  
  joyBus->m_stageFlags[0] = 0;
  joyBus->m_stageFlags[1] = 0;
  joyBus->m_stageFlags[2] = 0;
  joyBus->m_stageFlags[3] = 0;
  joyBus->m_threadInitFlag = '\x01';
  do {
  } while (Joybus.m_threadRunningMask != '\0');
  if (joyBus->m_gbaBootParamA != (uint8_t *)0x0) {
    __dla__FPv(joyBus->m_gbaBootParamA);
    joyBus->m_gbaBootParamA = (uint8_t *)0x0;
  }
  if (joyBus->m_fileBaseA != (char *)0x0) {
    __dla__FPv(joyBus->m_fileBaseA);
    joyBus->m_fileBaseA = (char *)0x0;
  }
  if (joyBus->m_fileBaseB != (char *)0x0) {
    __dla__FPv(joyBus->m_fileBaseB);
    joyBus->m_fileBaseB = (char *)0x0;
  }
  iVar1 = 0;
  pJVar2 = joyBus;
  do {
    if (pJVar2->m_letterBuffer[0] != (char *)0x0) {
      __dla__FPv(pJVar2->m_letterBuffer[0]);
      pJVar2->m_letterBuffer[0] = (char *)0x0;
    }
    iVar1 = iVar1 + 1;
    pJVar2 = (JoyBus *)(pJVar2->m_pathBuf + 4);
  } while (iVar1 < 4);
  memset(joyBus->m_sendBuffer,0,0x4000);
  memset(joyBus->m_stageFlags,0,8);
  memset(joyBus->m_cmdQueueData,0,0x400);
  memset(joyBus->m_recvQueueEntriesArr,0,0x400);
  memset(joyBus->m_threadParams,0,0xf0);
  memset(joyBus->m_perThreadTemp,0,0x60);
  memset(joyBus->m_recvBuffer,0,0x1020);
  joyBus->m_mapId = 0xff;
  joyBus->m_stageId = 0xff;
  pJVar2 = joyBus;
  pJVar3 = joyBus;
  pJVar4 = joyBus;
  iVar1 = 0;
  do {
    pJVar4->m_threadParams[0].m_gbaStatus = 1;
    pJVar4->m_threadParams[0].m_padType = 0x40;
    pJVar3->m_cmdCount[0] = 0;
    pJVar3->m_secCmdCount[0] = 0;
    OSInitSemaphore(pJVar2->m_accessSemaphores,1);
    iVar5 = iVar1 + 1;
    joyBus->m_ctrlModeArr[iVar1] = '\0';
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0x3c);
    pJVar3 = (JoyBus *)(pJVar3->m_pathBuf + 4);
    joyBus->m_nextModeTypeArr[iVar1] = '\0';
    pJVar2 = (JoyBus *)(pJVar2->m_pathBuf + 0xc);
    joyBus->m_modeXArr[iVar1] = '\0';
    joyBus->m_stateCodeArr[iVar1] = 0xff;
    joyBus->m_stateFlagArr[iVar1] = '\0';
    iVar1 = iVar5;
  } while (iVar5 < 4);
  joyBus->m_fileBaseA_dup = 0;
  joyBus->m_fileBaseB_dup = 0;
  return;
}

