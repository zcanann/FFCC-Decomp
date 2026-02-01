// Function: RecvGBA__6JoyBusFP11ThreadParamPUi
// Entry: 800adda0
// Size: 640 bytes

int RecvGBA__6JoyBusFP11ThreadParamPUi(JoyBus *joyBus,ThreadParam *threadParam,uint32_t *recvBuffer)

{
  int iVar1;
  char cVar2;
  uint32_t uVar3;
  undefined4 local_18;
  
  *recvBuffer = 0;
  OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  uVar3 = joyBus->m_secCmdCount[threadParam->m_portIndex];
  OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  if ((int)uVar3 < 0x40) {
    cVar2 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar2 == '\0') || (threadParam->m_portIndex == 1)) {
      uVar3 = GBAGetStatus(threadParam->m_portIndex,&threadParam->m_unk3);
      threadParam->m_gbaStatus = uVar3;
    }
    else {
      threadParam->m_gbaStatus = 0;
    }
    if (threadParam->m_gbaStatus == 0) {
      if ((threadParam->m_unk3 & 0x30) == 0) {
        if ((threadParam->m_unk3 & 8) == 0) {
          iVar1 = 0;
        }
        else {
          uVar3 = GBARead(threadParam->m_portIndex,&local_18,&threadParam->m_unk3);
          threadParam->m_gbaStatus = uVar3;
          if (threadParam->m_gbaStatus == 0) {
            *recvBuffer = local_18;
            if ((local_18._0_1_ & 0x3f) == 4) {
              SetPadData__6JoyBusFP11ThreadParamPUc(joyBus,threadParam,(char *)&local_18);
              iVar1 = 1;
            }
            else if ((local_18._0_1_ & 0x3f) == 0xe) {
              if (local_18._1_1_ == '\0') {
                joyBus->m_stateCodeArr[threadParam->m_portIndex] = local_18._2_1_;
                joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\x01';
                iVar1 = 1;
              }
              else {
                OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
                joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex]
                [joyBus->m_secCmdCount[threadParam->m_portIndex]] = local_18;
                joyBus->m_secCmdCount[threadParam->m_portIndex] =
                     joyBus->m_secCmdCount[threadParam->m_portIndex] + 1;
                OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
                iVar1 = 2;
              }
            }
            else {
              OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex]
              [joyBus->m_secCmdCount[threadParam->m_portIndex]] = local_18;
              joyBus->m_secCmdCount[threadParam->m_portIndex] =
                   joyBus->m_secCmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar1 = 2;
            }
          }
          else {
            iVar1 = -1;
          }
        }
      }
      else {
        iVar1 = -1;
      }
    }
    else {
      iVar1 = -1;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

