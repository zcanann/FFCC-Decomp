// Function: SendPlayerStat__6JoyBusFP11ThreadParam
// Entry: 800aad94
// Size: 1208 bytes

/* WARNING: Removing unreachable block (ram,0x800aadd0) */

JoyBus * SendPlayerStat__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  byte bVar1;
  int iVar2;
  JoyBus *pJVar3;
  char *pcVar4;
  uint32_t uVar5;
  byte bVar6;
  byte bVar7;
  uint32_t uVar8;
  int iVar9;
  byte abStack_6d0 [48];
  undefined2 local_698 [2];
  uint local_694;
  byte abStack_690 [4];
  undefined local_68c;
  char acStack_68b [128];
  undefined auStack_60b [4];
  undefined local_607;
  undefined local_606;
  undefined local_605;
  undefined local_604;
  undefined local_603;
  undefined local_602;
  undefined local_601;
  undefined local_600;
  undefined local_5ff;
  undefined auStack_5fe [3];
  undefined auStack_5fb [2];
  char acStack_5f9 [8];
  undefined auStack_5f1 [613];
  char local_38c [2];
  undefined auStack_38a [18];
  undefined auStack_378 [12];
  undefined auStack_36c [4];
  byte abStack_368 [206];
  undefined local_29a;
  undefined local_299;
  undefined local_1be;
  undefined local_1bd;
  undefined local_e2;
  undefined local_e1;
  
  if (threadParam->m_subState == '\x01') {
    uVar5 = threadParam->m_portIndex;
    uVar8 = *(uint32_t *)
             (joyBus->m_joyDataPacketBuffer[uVar5] + joyBus->m_txWordIndex[uVar5] * 4 + 2);
    if (joyBus->m_threadRunningMask == '\0') {
      pJVar3 = (JoyBus *)0x0;
    }
    else {
      OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
      uVar5 = threadParam->m_portIndex;
      if ((int)joyBus->m_cmdCount[uVar5] < 0x40) {
        joyBus->m_cmdQueueData[uVar5][joyBus->m_cmdCount[uVar5]] = uVar8;
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
      GetPlayerStat__8GbaQueueFiP8GbaPInfo(&GbaQue,threadParam->m_portIndex,local_38c);
      joyBus->m_txWordIndex[threadParam->m_portIndex] = 0;
      memset(abStack_690,0xff,4);
      memset(&local_68c,0,0x300);
      memset(joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2,0,0x400);
      local_68c = 1;
      GetCaravanName__8GbaQueueFPc(&GbaQue,acStack_68b);
      pcVar4 = local_38c;
      bVar7 = 0;
      bVar6 = 0;
      iVar9 = 2;
      do {
        if (pcVar4[0x16] != '\0') {
          iVar2 = (int)*pcVar4 >> 1;
          bVar1 = abStack_690[iVar2] & 0xf | bVar6;
          if (((int)*pcVar4 & 1U) != 0) {
            bVar1 = abStack_690[iVar2] & 0xf0 | bVar7;
          }
          abStack_690[iVar2] = bVar1;
        }
        if (pcVar4[0xf2] != '\0') {
          iVar2 = (int)pcVar4[0xdc] >> 1;
          bVar1 = abStack_690[iVar2] & 0xf | bVar6 + 0x10;
          if (((int)pcVar4[0xdc] & 1U) != 0) {
            bVar1 = abStack_690[iVar2] & 0xf0 | bVar7 + 1;
          }
          abStack_690[iVar2] = bVar1;
        }
        pcVar4 = pcVar4 + 0x1b8;
        bVar6 = bVar6 + 0x20;
        bVar7 = bVar7 + 2;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      memcpy(auStack_60b,abStack_690,4);
      local_607 = auStack_378[2];
      local_606 = auStack_378[3];
      local_605 = local_29a;
      local_604 = local_299;
      local_603 = local_1be;
      local_602 = local_1bd;
      local_601 = local_e2;
      local_600 = local_e1;
      iVar9 = threadParam->m_portIndex * 0xdc;
      local_5ff = auStack_38a[iVar9];
      memcpy(auStack_5fe,auStack_36c + iVar9,3);
      iVar9 = threadParam->m_portIndex * 0xdc;
      local_698[0] = CONCAT11(auStack_378[iVar9 + 1],auStack_378[iVar9]);
      memcpy(auStack_5fb,local_698,2);
      iVar9 = GetCompatibility__8GbaQueueFiPUc(&GbaQue,threadParam->m_portIndex,acStack_5f9);
      memcpy(acStack_5f9 + iVar9,auStack_378 + threadParam->m_portIndex * 0xdc + 4,8);
      iVar2 = threadParam->m_portIndex * 0xdc;
      local_694 = (uint)abStack_368[iVar2 + 3] << 0x18 | (uint)abStack_368[iVar2 + 2] << 0x10 |
                  (uint)abStack_368[iVar2 + 1] << 8 | (uint)abStack_368[iVar2];
      memcpy(auStack_5f1 + iVar9,&local_694,4);
      pJVar3 = (JoyBus *)
               MakeJoyData__6JoyBusFPciPUi
                         (joyBus,&local_68c,iVar9 + 0xa3,
                          joyBus->m_joyDataPacketBuffer[threadParam->m_portIndex] + 2);
      if ((int)pJVar3 < 0) {
        return pJVar3;
      }
      joyBus->m_txWordCount[threadParam->m_portIndex] = (int32_t)pJVar3;
      threadParam->m_subState = threadParam->m_subState + '\x01';
      uVar5 = threadParam->m_portIndex;
      uVar8 = *(uint32_t *)
               (joyBus->m_joyDataPacketBuffer[uVar5] + joyBus->m_txWordIndex[uVar5] * 4 + 2);
      if (joyBus->m_threadRunningMask == '\0') {
        pJVar3 = (JoyBus *)0x0;
      }
      else {
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
        uVar5 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar5] < 0x40) {
          joyBus->m_cmdQueueData[uVar5][joyBus->m_cmdCount[uVar5]] = uVar8;
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
  if (pJVar3 == (JoyBus *)0x0) {
    joyBus->m_txWordIndex[threadParam->m_portIndex] =
         joyBus->m_txWordIndex[threadParam->m_portIndex] + 1;
    uVar5 = threadParam->m_portIndex;
    if (joyBus->m_txWordCount[uVar5] <= joyBus->m_txWordIndex[uVar5]) {
      ClrCompatibilityFlg__8GbaQueueFi(&GbaQue,uVar5);
      pJVar3 = (JoyBus *)0x1;
    }
  }
  return pJVar3;
}

