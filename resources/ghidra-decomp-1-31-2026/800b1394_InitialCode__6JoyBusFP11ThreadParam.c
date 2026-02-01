// Function: InitialCode__6JoyBusFP11ThreadParam
// Entry: 800b1394
// Size: 2392 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

JoyBus * InitialCode__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  char cVar2;
  int iVar1;
  uint32_t uVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  uint32_t local_38;
  undefined4 local_34;
  undefined local_30 [3];
  undefined uStack_2d;
  undefined local_2c [3];
  undefined uStack_29;
  undefined local_28;
  int3 iStack_27;
  uint32_t local_24;
  char local_20;
  byte local_1f;
  uint32_t local_1c [4];
  
  switch(threadParam->m_subState) {
  case '\0':
    joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
    OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    iVar6 = 8;
    iVar1 = 0;
    do {
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1) = 0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 4) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 4) = 0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 8) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 8) = 0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0xc) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0xc) =
           0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x10) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x10) =
           0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x14) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x14) =
           0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x18) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x18) =
           0;
      *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar1 + 0x1c) = 0;
      *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar1 + 0x1c) =
           0;
      iVar6 = iVar6 + -1;
      iVar1 = iVar1 + 0x20;
    } while (iVar6 != 0);
    joyBus->m_cmdCount[threadParam->m_portIndex] = 0;
    joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
    OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    if ((threadParam->m_gbaStatus == 0) && (threadParam->m_unk3 == '(')) {
      uVar3 = GBARead(threadParam->m_portIndex,local_1c,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
      if (threadParam->m_gbaStatus == 0) {
        threadParam->m_recvReadIdx = local_1c[0];
        threadParam->m_deviceType = '\0';
        threadParam->m_padding[0] = '\0';
        threadParam->m_padding[1] = '\0';
        threadParam->m_padding[2] = '\x01';
      }
    }
    joyBus = (JoyBus *)0x0;
    threadParam->m_subState = '\x01';
    break;
  case '\x01':
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    uVar3 = threadParam->m_gbaStatus;
    if (uVar3 == 0) {
      if (threadParam->m_unk3 == ' ') {
        uVar3 = GBAWrite(threadParam->m_portIndex,joyBus->m_diskId,&threadParam->m_unk3);
        threadParam->m_gbaStatus = uVar3;
        uVar3 = threadParam->m_gbaStatus;
        if (uVar3 == 0) {
          cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
            uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
            threadParam->m_gbaStatus = uVar3;
          }
          else {
            threadParam->m_gbaStatus = 0;
          }
          uVar3 = threadParam->m_gbaStatus;
          if (uVar3 == 0) {
            if ((threadParam->m_unk3 & 0x30) == 0x20) {
              uVar3 = 0;
            }
            else {
              uVar3 = 1;
            }
          }
        }
      }
      else {
        uVar3 = 1;
      }
    }
    if (uVar3 == 0) {
      joyBus = (JoyBus *)0x0;
      threadParam->m_subState = '\x02';
    }
    else {
      joyBus = (JoyBus *)0x1;
    }
    break;
  case '\x02':
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    uVar3 = threadParam->m_gbaStatus;
    if (uVar3 == 0) {
      if (threadParam->m_unk3 == '(') {
        uVar3 = GBARead(threadParam->m_portIndex,&local_20,&threadParam->m_unk3);
        threadParam->m_gbaStatus = uVar3;
        uVar3 = threadParam->m_gbaStatus;
        if (uVar3 == 0) {
          if (local_20 == '\x01') {
            uVar3 = 0;
            threadParam->m_gbaBootFlag = (uint8_t)((int)(uint)local_1f >> 6);
            threadParam->m_unk2 = local_1f >> 4 & 3;
            threadParam->m_bootRetryCount = local_1f & 0xf;
          }
          else {
            uVar3 = 1;
          }
        }
      }
      else {
        uVar3 = 1;
      }
    }
    if (uVar3 == 0) {
      joyBus = (JoyBus *)0x0;
      threadParam->m_subState = '\x03';
    }
    else {
      joyBus = (JoyBus *)0x1;
    }
    break;
  case '\x03':
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    uVar3 = threadParam->m_gbaStatus;
    if (uVar3 == 0) {
      if (threadParam->m_unk3 == '(') {
        uVar3 = GBARead(threadParam->m_portIndex,&local_24,&threadParam->m_unk3);
        threadParam->m_gbaStatus = uVar3;
        uVar3 = threadParam->m_gbaStatus;
        if (uVar3 == 0) {
          uVar3 = 0;
          threadParam->m_timeChangedFlag =
               (byte)((byte)(local_24 - threadParam->m_timestamp >> 0x18) |
                     (byte)(threadParam->m_timestamp - local_24 >> 0x18)) >> 7;
          threadParam->m_timestamp = local_24;
        }
      }
      else {
        uVar3 = 1;
      }
    }
    if (uVar3 == 0) {
      threadParam->m_subState = '\x04';
    }
  case '\x04':
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    uVar3 = threadParam->m_gbaStatus;
    if (uVar3 == 0) {
      if (threadParam->m_unk3 == ' ') {
        if ((threadParam->m_timeChangedFlag != '\0') ||
           ((threadParam->m_gbaBootFlag == '\0' && (threadParam->m_timestamp == 0)))) {
          uVar3 = OSGetTick();
          threadParam->m_timestamp = uVar3;
        }
        uVar3 = GBAWrite(threadParam->m_portIndex,&threadParam->m_timestamp,&threadParam->m_unk3);
        threadParam->m_gbaStatus = uVar3;
        uVar3 = threadParam->m_gbaStatus;
        if (uVar3 == 0) {
          uVar3 = 0;
        }
      }
      else {
        uVar3 = 1;
      }
    }
    if (uVar3 == 0) {
      joyBus = (JoyBus *)0x0;
      threadParam->m_subState = '\x05';
    }
    else {
      joyBus = (JoyBus *)0x1;
    }
    break;
  case '\x05':
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    uVar3 = threadParam->m_gbaStatus;
    if (uVar3 == 0) {
      if (threadParam->m_unk3 == ' ') {
        cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
        if (cVar2 == '\0') {
          bVar4 = (byte)threadParam->m_portIndex;
        }
        else {
          bVar4 = 0;
        }
        _local_28 = CONCAT13(1,(uint3)(byte)(bVar4 | threadParam->m_gbaBootFlag << 6 |
                                                     threadParam->m_unk2 << 4) << 0x10);
        uVar3 = GBAWrite(threadParam->m_portIndex,&local_28,&threadParam->m_unk3);
        threadParam->m_gbaStatus = uVar3;
        uVar3 = threadParam->m_gbaStatus;
        if (uVar3 == 0) {
          uVar3 = 0;
        }
      }
      else {
        uVar3 = 1;
      }
    }
    if (uVar3 == 0) {
      joyBus = (JoyBus *)0x0;
      threadParam->m_subState = '\x06';
    }
    else {
      joyBus = (JoyBus *)0x1;
    }
    break;
  case '\x06':
    iVar1 = SendMType__6JoyBusFP11ThreadParami
                      (joyBus,threadParam,(uint)joyBus->m_nextModeTypeArr[threadParam->m_portIndex])
    ;
    if (iVar1 < 0) {
      joyBus = (JoyBus *)0x1;
    }
    else {
      GetStageNo__8GbaQueueFiPiPi(&GbaQue,threadParam->m_portIndex,local_30,local_2c);
      uVar5 = 0;
      local_34 = CONCAT31(CONCAT21(0xe01,uStack_2d),uStack_29);
      if (joyBus->m_threadRunningMask != '\0') {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar3 = threadParam->m_portIndex;
        if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
          joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_34;
          joyBus->m_cmdCount[threadParam->m_portIndex] =
               joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          uVar5 = 0;
        }
        else {
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
          uVar5 = 0xffffffff;
        }
      }
      if ((int)(-uVar5 | uVar5) >> 0x1f < 0) {
        joyBus = (JoyBus *)0x1;
      }
      else {
        iVar1 = 0;
        local_38 = (uint)CONCAT21(0x1416,Game.game.m_gameWork.m_languageId - 1 | (byte)DAT_80330b24)
                   << 8;
        if (joyBus->m_threadRunningMask != '\0') {
          OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          uVar3 = threadParam->m_portIndex;
          if ((int)joyBus->m_cmdCount[uVar3] < 0x40) {
            joyBus->m_cmdQueueData[uVar3][joyBus->m_cmdCount[uVar3]] = local_38;
            joyBus->m_cmdCount[threadParam->m_portIndex] =
                 joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
            OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            iVar1 = 0;
          }
          else {
            OSSignalSemaphore(joyBus->m_accessSemaphores + uVar3);
            iVar1 = -1;
          }
        }
        if (iVar1 < 0) {
          joyBus = (JoyBus *)0x1;
        }
        else {
          threadParam->m_subState = '\0';
          threadParam->m_state = '\x14';
          threadParam->m_flags[0] = '\x01';
          ClrPlayModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          joyBus = (JoyBus *)0x0;
        }
      }
    }
  }
  return joyBus;
}

