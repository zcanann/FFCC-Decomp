// Function: SendGBA__6JoyBusFP11ThreadParam
// Entry: 800adba8
// Size: 504 bytes

undefined4 SendGBA__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint32_t uVar5;
  undefined4 local_18;
  
  OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  uVar5 = joyBus->m_cmdCount[threadParam->m_portIndex];
  local_18 = joyBus->m_cmdQueueData[threadParam->m_portIndex][0];
  OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  if ((int)uVar5 < 1) {
    uVar1 = 0;
  }
  else {
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar5 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar5;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    if (threadParam->m_gbaStatus == 0) {
      if ((threadParam->m_unk3 & 0x30) == 0) {
        if ((threadParam->m_unk3 & 2) == 0) {
          uVar5 = GBAWrite(threadParam->m_portIndex,&local_18,&threadParam->m_unk3);
          threadParam->m_gbaStatus = uVar5;
          if (threadParam->m_gbaStatus == 0) {
            if (((joyBus->m_stateCodeArr[threadParam->m_portIndex] == '\t') &&
                ((local_18._0_1_ & 0x3f) == 9)) && (local_18._1_1_ == '\x01')) {
              threadParam->m_state = '!';
              threadParam->m_subState = '\0';
              threadParam->m_skipProcessingFlag = '\x01';
            }
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            iVar4 = 1;
            iVar3 = 4;
            while( true ) {
              uVar5 = threadParam->m_portIndex;
              if ((int)joyBus->m_cmdCount[uVar5] <= iVar4) break;
              iVar4 = iVar4 + 1;
              *(undefined4 *)((int)joyBus->m_cmdQueueData[uVar5 - 1] + iVar3 + 0xfc) =
                   *(undefined4 *)((int)joyBus->m_cmdQueueData[uVar5] + iVar3);
              iVar3 = iVar3 + 4;
            }
            joyBus->m_cmdCount[uVar5] = joyBus->m_cmdCount[uVar5] - 1;
            OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar1 = 1;
          }
          else {
            uVar1 = 0xffffffff;
          }
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0xffffffff;
      }
    }
    else {
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

