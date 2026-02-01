// Function: SendBonusStr__6JoyBusFP11ThreadParam
// Entry: 800a8f7c
// Size: 868 bytes

/* WARNING: Removing unreachable block (ram,0x800a8fac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

JoyBus * SendBonusStr__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  char cVar4;
  int iVar1;
  int iVar2;
  JoyBus *pJVar3;
  uint32_t uVar5;
  uint32_t uVar6;
  undefined local_118;
  undefined local_117;
  undefined local_116 [258];
  
  if (threadParam->m_subState == '\x01') {
    uVar5 = threadParam->m_portIndex;
    uVar6 = *(uint32_t *)
             (joyBus->m_joyDataPacketBuffer[uVar5] + joyBus->m_txWordIndex[uVar5] * 4 + 2);
    if (joyBus->m_threadRunningMask == '\0') {
      pJVar3 = (JoyBus *)0x0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
      uVar5 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar5] < 0x40) {
        joyBus->m_cmdQueueData[uVar5][joyBus->m_cmdCount[uVar5]] = uVar6;
        joyBus->m_cmdCount[threadParam->m_portIndex] =
             joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        pJVar3 = (JoyBus *)0x0;
      }
      else {
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar5);
        pJVar3 = (JoyBus *)0xffffffff;
      }
    }
  }
  else {
    pJVar3 = joyBus;
    if (threadParam->m_subState == '\0') {
      joyBus->m_txWordIndex[threadParam->m_portIndex] = 0;
      memset(&local_118,0,0x100);
      memset(joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2,0,0x400);
      local_118 = 7;
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xe) {
        cVar4 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
        if ((cVar4 == '\0') || (threadParam->m_portIndex != 1)) {
          uVar5 = threadParam->m_portIndex;
        }
        else {
          uVar5 = 0;
        }
        iVar1 = GetBonus__8GbaQueueFi(&GbaQue,uVar5);
        strcpy(&local_117,Game.game.m_cFlatDataArr[1].m_table[7].index[iVar1 * 2]);
        iVar2 = strlen(&local_117);
        strcpy(local_116 + iVar2,Game.game.m_cFlatDataArr[1].m_table[7].index[iVar1 * 2 + 1]);
        iVar1 = strlen(local_116 + iVar2);
        iVar1 = iVar1 + iVar2 + 3;
      }
      else {
        iVar1 = 3;
        local_117 = 0;
        local_116[0] = 0;
      }
      pJVar3 = (JoyBus *)
               MakeJoyData__6JoyBusFPciPUi
                         (joyBus,&local_118,iVar1,
                          joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2);
      if ((int)pJVar3 < 0) {
        return pJVar3;
      }
      joyBus->m_txWordCount[threadParam->m_portIndex] = (int32_t)pJVar3;
      threadParam->m_subState = threadParam->m_subState + '\x01';
      uVar5 = threadParam->m_portIndex;
      uVar6 = *(uint32_t *)
               (joyBus->m_joyDataPacketBuffer[uVar5] + joyBus->m_txWordIndex[uVar5] * 4 + 2);
      if (joyBus->m_threadRunningMask == '\0') {
        pJVar3 = (JoyBus *)0x0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
        uVar5 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar5] < 0x40) {
          joyBus->m_cmdQueueData[uVar5][joyBus->m_cmdCount[uVar5]] = uVar6;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          pJVar3 = (JoyBus *)0x0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar5);
          pJVar3 = (JoyBus *)0xffffffff;
        }
      }
    }
  }
  if ((pJVar3 == (JoyBus *)0x0) &&
     (joyBus->m_txWordIndex[threadParam->m_portIndex] =
           joyBus->m_txWordIndex[threadParam->m_portIndex] + 1,
     joyBus->m_txWordCount[threadParam->m_portIndex] <=
     joyBus->m_txWordIndex[threadParam->m_portIndex])) {
    pJVar3 = (JoyBus *)0x1;
  }
  return pJVar3;
}

