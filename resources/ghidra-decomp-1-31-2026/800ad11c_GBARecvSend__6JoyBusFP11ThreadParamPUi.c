// Function: GBARecvSend__6JoyBusFP11ThreadParamPUi
// Entry: 800ad11c
// Size: 2700 bytes

uint GBARecvSend__6JoyBusFP11ThreadParamPUi
               (JoyBus *joyBus,ThreadParam *threadParam,uint32_t *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar7;
  uint32_t uVar5;
  uint uVar6;
  int iVar8;
  int iVar9;
  int iVar10;
  uint8_t *puVar11;
  int iVar12;
  uint32_t uVar13;
  uint32_t uVar14;
  JoyBusRecvBuffer *pJVar15;
  byte local_34;
  uint8_t uStack_33;
  uint8_t uStack_32;
  uint8_t uStack_31;
  
  uVar4 = RecvGBA__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,param_3);
  if (-1 < (int)uVar4) {
    if (uVar4 == 2) {
      bVar7 = *(byte *)param_3 & 0x3f;
      if (((((bVar7 == 0x14) || (bVar7 == 0x17)) || (bVar7 == 0x1a)) ||
          (((bVar7 == 0x1c || (bVar7 == 0x1d)) || ((bVar7 == 0x1e || (bVar7 == 0x1f)))))) ||
         ((bVar7 == 6 && (*(char *)((int)param_3 + 1) == '\x18')))) {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar5 = threadParam->m_portIndex;
        uVar13 = joyBus->m_recvQueueEntriesArr[uVar5 - 1][joyBus->m_secCmdCount[uVar5] + 0x3f];
        joyBus->m_secCmdCount[uVar5] = joyBus->m_secCmdCount[uVar5] - 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
        uVar4 = 0;
        *param_3 = 0;
      }
      else if (bVar7 == 0xc) {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar5 = threadParam->m_portIndex;
        uVar13 = joyBus->m_recvQueueEntriesArr[uVar5 - 1][joyBus->m_secCmdCount[uVar5] + 0x3f];
        joyBus->m_secCmdCount[uVar5] = joyBus->m_secCmdCount[uVar5] - 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        cVar1 = *(char *)((int)param_3 + 1);
        if (cVar1 == '\x03') {
          ClrLetterLstFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = '!';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
        else if (cVar1 == '\x02') {
          ClrLetterDatFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = '%';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
        else if (cVar1 == '\x06') {
          ClrSellFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = '5';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
        else if (cVar1 == '\a') {
          ClrBuyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = '7';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
        else if (cVar1 == '\b') {
          ClrMkSmithFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = '9';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
        else if (cVar1 == '\t') {
          ClrArtiDatFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          SetQueue__8GbaQueueFiUi(&GbaQue,threadParam->m_portIndex,uVar13);
          threadParam->m_state = 'A';
          threadParam->m_subState = '\0';
          threadParam->m_skipProcessingFlag = '\x01';
        }
      }
      else if (bVar7 == 0x15) {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar5 = threadParam->m_portIndex;
        uVar13 = joyBus->m_recvQueueEntriesArr[uVar5 - 1][joyBus->m_secCmdCount[uVar5] + 0x3f];
        joyBus->m_secCmdCount[uVar5] = joyBus->m_secCmdCount[uVar5] - 1;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        if ((int)(uint)*(byte *)param_3 >> 6 == 0) {
          uVar5 = threadParam->m_portIndex;
          OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
          memset(joyBus->m_recvBuffer + uVar5,0,0x408);
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar5);
        }
        uVar5 = *param_3;
        pJVar15 = joyBus->m_recvBuffer + threadParam->m_portIndex;
        if ((*(byte *)&pJVar15->m_cmdFlags != 0) &&
           (local_34 = (byte)(uVar5 >> 0x18), *(byte *)&pJVar15->m_cmdFlags != (local_34 & 0x3f))) {
          if (1 < (uint)System.m_execParam) {
            Printf__7CSystemFPce
                      (&System,s___d___s__d___Warning__Recv_data_t_801da2f0,threadParam->m_portIndex
                       ,s_joybus_cpp_801da320,0x1079);
          }
          uVar14 = threadParam->m_portIndex;
          OSWaitSemaphore(joyBus->m_accessSemaphores + uVar14);
          memset(joyBus->m_recvBuffer + uVar14,0,0x408);
          OSSignalSemaphore(joyBus->m_accessSemaphores + uVar14);
        }
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar14 = pJVar15->m_length;
        uStack_31 = (uint8_t)uVar5;
        uStack_32 = (uint8_t)(uVar5 >> 8);
        uStack_33 = (uint8_t)(uVar5 >> 0x10);
        if (uVar14 == 0) {
          pJVar15->m_crc = (uint16_t)(uVar5 >> 8);
          uVar5 = pJVar15->m_length;
          pJVar15->m_length = uVar5 + 1;
          pJVar15->m_payload[uVar5] = uStack_31;
        }
        else {
          pJVar15->m_length = uVar14 + 1;
          pJVar15->m_payload[uVar14] = uStack_33;
          uVar5 = pJVar15->m_length;
          pJVar15->m_length = uVar5 + 1;
          pJVar15->m_payload[uVar5] = uStack_32;
          uVar5 = pJVar15->m_length;
          pJVar15->m_length = uVar5 + 1;
          pJVar15->m_payload[uVar5] = uStack_31;
        }
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        if ((int)(uint)*(byte *)param_3 >> 6 == 2) {
          uVar5 = threadParam->m_portIndex;
          uVar6 = 0xffff;
          uVar14 = joyBus->m_recvBuffer[uVar5].m_length;
          puVar11 = joyBus->m_recvBuffer[uVar5].m_payload;
          while (uVar14 = uVar14 - 1, -1 < (int)uVar14) {
            bVar7 = *puVar11;
            puVar11 = puVar11 + 1;
            uVar6 = (uVar6 << 8 ^ (uint)JoyBusCrcTable[uVar6 >> 8 ^ (uint)bVar7]) & 0xffff;
          }
          if ((~uVar6 & 0xffff) == (uint)joyBus->m_recvBuffer[uVar5].m_crc) {
            SetQueue__8GbaQueueFiUi(&GbaQue,uVar5,uVar13);
          }
          else {
            if (joyBus->m_threadRunningMask != '\0') {
              OSWaitSemaphore(joyBus->m_accessSemaphores + joyBus->m_threadParams[uVar5].m_portIndex
                             );
              uVar13 = joyBus->m_threadParams[uVar5].m_portIndex;
              if ((int)joyBus->m_cmdCount[uVar13] < 0x40) {
                joyBus->m_cmdQueueData[uVar13][joyBus->m_cmdCount[uVar13]] = 0x7150000;
                uVar13 = joyBus->m_threadParams[uVar5].m_portIndex;
                joyBus->m_cmdCount[uVar13] = joyBus->m_cmdCount[uVar13] + 1;
                OSSignalSemaphore(joyBus->m_accessSemaphores +
                                  joyBus->m_threadParams[uVar5].m_portIndex);
              }
              else {
                OSSignalSemaphore(joyBus->m_accessSemaphores + uVar13);
              }
            }
            uVar5 = threadParam->m_portIndex;
            OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
            memset(joyBus->m_recvBuffer + uVar5,0,0x408);
            OSSignalSemaphore(joyBus->m_accessSemaphores + uVar5);
          }
        }
      }
    }
    uVar6 = SendGBA__6JoyBusFP11ThreadParam(joyBus,threadParam);
    if ((int)uVar6 < 0) {
      threadParam->m_state = '\x02';
      threadParam->m_subState = '\0';
      threadParam->m_skipProcessingFlag = '\x01';
    }
    else {
      if (threadParam->m_skipProcessingFlag != '\0') {
        OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        uVar2 = DAT_80330b28;
        uVar5 = 0;
        iVar12 = 0;
        iVar9 = 0;
        for (iVar8 = 0; uVar13 = threadParam->m_portIndex, iVar8 < (int)joyBus->m_cmdCount[uVar13];
            iVar8 = iVar8 + 1) {
          uVar3 = *(byte *)((int)joyBus->m_cmdQueueData[uVar13] + iVar12) & uVar2;
          if (((((uVar3 == 10) || (uVar3 == 0x10)) || (uVar3 == 0x14)) ||
              ((uVar3 == 0x1b || (uVar3 == 0x13)))) || (iVar10 = iVar9, uVar3 == 9)) {
            uVar5 = uVar5 + 1;
            iVar10 = iVar9 + 4;
            *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[uVar13] + iVar9) =
                 *(undefined4 *)((int)joyBus->m_cmdQueueData[uVar13] + iVar12);
          }
          iVar12 = iVar12 + 4;
          iVar9 = iVar10;
        }
        iVar8 = 0;
        iVar9 = 0;
        iVar12 = 0x20;
        do {
          if (iVar8 < (int)uVar5) {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar9) =
                 *(undefined4 *)
                  ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar9);
          }
          else {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar9) = 0;
          }
          iVar10 = iVar9 + 4;
          *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar9) = 0;
          if (iVar8 + 1 < (int)uVar5) {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar10) =
                 *(undefined4 *)
                  ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar10);
          }
          else {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar10) = 0;
          }
          iVar8 = iVar8 + 2;
          iVar9 = iVar9 + 8;
          *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar10) = 0
          ;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
        joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
        joyBus->m_cmdCount[threadParam->m_portIndex] = uVar5;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
      }
      uVar5 = threadParam->m_portIndex;
      bVar7 = threadParam->m_state;
      if (((joyBus->m_stateFlagArr[uVar5] != '\0') && (joyBus->m_stateCodeArr[uVar5] != '\t')) &&
         ((bVar7 != 5 && ((0x20 < bVar7 && (bVar7 < 0x29)))))) {
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar5);
        uVar2 = DAT_80330b28;
        uVar5 = 0;
        iVar12 = 0;
        iVar9 = 0;
        for (iVar8 = 0; uVar13 = threadParam->m_portIndex, iVar8 < (int)joyBus->m_cmdCount[uVar13];
            iVar8 = iVar8 + 1) {
          uVar3 = *(byte *)((int)joyBus->m_cmdQueueData[uVar13] + iVar12) & uVar2;
          if ((((uVar3 == 10) || (uVar3 == 0x10)) || (uVar3 == 0x14)) ||
             (((uVar3 == 0x1b || (uVar3 == 0x13)) || (iVar10 = iVar9, uVar3 == 9)))) {
            uVar5 = uVar5 + 1;
            iVar10 = iVar9 + 4;
            *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[uVar13] + iVar9) =
                 *(undefined4 *)((int)joyBus->m_cmdQueueData[uVar13] + iVar12);
          }
          iVar12 = iVar12 + 4;
          iVar9 = iVar10;
        }
        iVar8 = 0;
        iVar9 = 0;
        iVar12 = 0x20;
        do {
          if (iVar8 < (int)uVar5) {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar9) =
                 *(undefined4 *)
                  ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar9);
          }
          else {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar9) = 0;
          }
          iVar10 = iVar9 + 4;
          *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar9) = 0;
          if (iVar8 + 1 < (int)uVar5) {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar10) =
                 *(undefined4 *)
                  ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar10);
          }
          else {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar10) = 0;
          }
          iVar8 = iVar8 + 2;
          iVar9 = iVar9 + 8;
          *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar10) = 0
          ;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
        joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
        joyBus->m_cmdCount[threadParam->m_portIndex] = uVar5;
        OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
        threadParam->m_state = '\x05';
        threadParam->m_subState = '\0';
        threadParam->m_skipProcessingFlag = '\x01';
      }
      uVar4 = countLeadingZeros(2 - uVar4);
      uVar6 = uVar4 >> 5 | (int)(-uVar6 | uVar6) >> 0x1f & 2U;
    }
    return uVar6;
  }
  threadParam->m_state = '\x02';
  threadParam->m_subState = '\0';
  return uVar4;
}

