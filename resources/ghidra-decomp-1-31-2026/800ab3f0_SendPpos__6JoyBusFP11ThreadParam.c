// Function: SendPpos__6JoyBusFP11ThreadParam
// Entry: 800ab3f0
// Size: 1620 bytes

/* WARNING: Removing unreachable block (ram,0x800ab43c) */

int SendPpos__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint32_t uVar4;
  uint32_t uVar5;
  int unaff_r27;
  uint8_t *puVar6;
  undefined4 local_28;
  
  uVar5 = threadParam->m_portIndex;
  bVar1 = threadParam->m_pposCounter;
  puVar6 = joyBus->m_playerPosPacketBuffer[uVar5] + 2;
  if (bVar1 == 3) {
LAB_800ab6a8:
    iVar3 = joyBus->m_pposWordIndex[threadParam->m_portIndex];
    puVar6 = puVar6 + iVar3 * 4;
    local_28 = iVar3;
    for (; iVar3 < (char)joyBus->m_cmdBuffer[threadParam->m_portIndex + 4]; iVar3 = iVar3 + 1) {
      uVar5 = *(uint32_t *)puVar6;
      if (joyBus->m_threadRunningMask == '\0') {
        unaff_r27 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar4 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
          joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar5;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          unaff_r27 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
          unaff_r27 = -1;
        }
      }
      if (unaff_r27 != 0) break;
      puVar6 = puVar6 + 4;
    }
    joyBus->m_pposWordIndex[threadParam->m_portIndex] =
         joyBus->m_pposWordIndex[threadParam->m_portIndex] + iVar3;
    if ((int)(char)joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] <=
        joyBus->m_pposWordIndex[threadParam->m_portIndex]) {
      threadParam->m_pposCounter = threadParam->m_pposCounter + '\x01';
      joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = '\0';
      joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
    }
  }
  else {
    if (2 < bVar1) {
      if (bVar1 != 5) {
        if (4 < bVar1) {
          if (1 < (uint)System.m_execParam) {
            Printf__7CSystemFPce
                      (&System,s___d__Error__m_PposCnt_error__d__801da32c,uVar5,
                       (int)(char)joyBus->m_cmdBuffer[uVar5]);
          }
          joyBus->m_cmdBuffer[threadParam->m_portIndex] = '\0';
          joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = '\0';
          joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
          return -1;
        }
        memset(puVar6,0,0x100);
        joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
        joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = '\0';
        GetTreasurePos__8GbaQueueFiPUiPi(&GbaQue,threadParam->m_portIndex,puVar6,&local_28);
        joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = (uint8_t)local_28;
        if (joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] == '\0') {
          threadParam->m_pposCounter = '\0';
          return unaff_r27;
        }
        threadParam->m_pposCounter = threadParam->m_pposCounter + '\x01';
      }
      iVar3 = joyBus->m_pposWordIndex[threadParam->m_portIndex];
      puVar6 = puVar6 + iVar3 * 4;
      local_28 = iVar3;
      for (; iVar3 < (char)joyBus->m_cmdBuffer[threadParam->m_portIndex + 4]; iVar3 = iVar3 + 1) {
        uVar5 = *(uint32_t *)puVar6;
        if (joyBus->m_threadRunningMask == '\0') {
          unaff_r27 = 0;
        }
        else {
          OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          uVar4 = threadParam->m_portIndex;
          if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
            joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar5;
            joyBus->m_cmdCount[threadParam->m_portIndex] =
                 joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
            OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            unaff_r27 = 0;
          }
          else {
            OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
            unaff_r27 = -1;
          }
        }
        if (unaff_r27 != 0) break;
        puVar6 = puVar6 + 4;
      }
      joyBus->m_pposWordIndex[threadParam->m_portIndex] =
           joyBus->m_pposWordIndex[threadParam->m_portIndex] + iVar3;
      if (joyBus->m_pposWordIndex[threadParam->m_portIndex] <
          (int)(char)joyBus->m_cmdBuffer[threadParam->m_portIndex + 4]) {
        return unaff_r27;
      }
      threadParam->m_pposCounter = '\0';
      joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = '\0';
      joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
      return unaff_r27;
    }
    if (bVar1 != 1) {
      if (bVar1 != 0) {
        memset(puVar6,0,0x100);
        joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
        joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = '\0';
        GetEnemyPos__8GbaQueueFiPUiPi(&GbaQue,threadParam->m_portIndex,puVar6,&local_28);
        joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] = (uint8_t)local_28;
        if (joyBus->m_cmdBuffer[threadParam->m_portIndex + 4] == '\0') {
          threadParam->m_pposCounter = threadParam->m_pposCounter + '\x02';
          return unaff_r27;
        }
        threadParam->m_pposCounter = threadParam->m_pposCounter + '\x01';
        goto LAB_800ab6a8;
      }
      uVar2 = (int)System.m_frameCounter >> 0x1f;
      if ((uVar2 * 4 | System.m_frameCounter * 0x40000000 + uVar2 >> 0x1e) != uVar2) {
        return 0;
      }
      memset(puVar6,0,0x100);
      GetPlayerPos__8GbaQueueFiPUi(&GbaQue,threadParam->m_portIndex,puVar6);
      joyBus->m_cmdBuffer[threadParam->m_portIndex] = '\x03';
      joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
      threadParam->m_pposCounter = threadParam->m_pposCounter + '\x01';
    }
    iVar3 = joyBus->m_pposWordIndex[threadParam->m_portIndex];
    puVar6 = puVar6 + iVar3 * 4;
    local_28 = iVar3;
    for (; iVar3 < (char)joyBus->m_cmdBuffer[threadParam->m_portIndex]; iVar3 = iVar3 + 1) {
      uVar5 = *(uint32_t *)puVar6;
      if (joyBus->m_threadRunningMask == '\0') {
        unaff_r27 = 0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar4 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar4] < 0x40) {
          joyBus->m_cmdQueueData[uVar4][joyBus->m_cmdCount[uVar4]] = uVar5;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          unaff_r27 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar4);
          unaff_r27 = -1;
        }
      }
      if (unaff_r27 != 0) break;
      puVar6 = puVar6 + 4;
    }
    joyBus->m_pposWordIndex[threadParam->m_portIndex] =
         joyBus->m_pposWordIndex[threadParam->m_portIndex] + iVar3;
    uVar5 = threadParam->m_portIndex;
    if ((int)(char)joyBus->m_cmdBuffer[uVar5] <= joyBus->m_pposWordIndex[uVar5]) {
      joyBus->m_cmdBuffer[uVar5] = '\0';
      joyBus->m_pposWordIndex[threadParam->m_portIndex] = 0;
      threadParam->m_pposCounter = threadParam->m_pposCounter + '\x01';
    }
  }
  return unaff_r27;
}

