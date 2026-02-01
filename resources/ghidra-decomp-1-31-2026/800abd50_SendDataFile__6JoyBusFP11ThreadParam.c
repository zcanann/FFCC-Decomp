// Function: SendDataFile__6JoyBusFP11ThreadParam
// Entry: 800abd50
// Size: 3364 bytes

int SendDataFile__6JoyBusFP11ThreadParam(JoyBus *joyBus,ThreadParam *threadParam)

{
  byte bVar1;
  undefined uVar2;
  undefined uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint8_t uVar9;
  short sVar8;
  undefined *puVar7;
  uint32_t uVar10;
  byte *pbVar11;
  uint8_t (*pauVar12) [24];
  uint32_t uVar13;
  int iVar14;
  undefined2 local_28;
  undefined local_26;
  undefined uStack_25;
  undefined4 local_1c;
  
  pauVar12 = joyBus->m_perThreadTemp + threadParam->m_portIndex;
  uVar5 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_1c);
  if (threadParam->m_skipProcessingFlag == '\0') {
    if ((int)uVar5 < 0) {
      iVar6 = -1;
    }
    else if ((threadParam->m_unk3 & 2) == 0) {
      if ((uVar5 & 1) == 0) {
        if (((*pauVar12)[1] == '\x02') &&
           (*(ushort *)(*pauVar12 + 0x10) <= *(ushort *)(*pauVar12 + 0xe))) {
          return -1;
        }
      }
      else {
        uVar13 = threadParam->m_portIndex;
        OSWaitSemaphore(joyBus->m_accessSemaphores + uVar13);
        joyBus->m_recvQueueEntriesArr[uVar13][joyBus->m_secCmdCount[uVar13]] = 0;
        joyBus->m_secCmdCount[uVar13] = joyBus->m_secCmdCount[uVar13] - 1;
        local_1c._0_2_ = (short)(local_1c >> 0x18);
        OSSignalSemaphore(joyBus->m_accessSemaphores + uVar13);
        if ((local_1c._0_1_ & 0x3f) == 7) {
          *(uint8_t *)((int)pauVar12 + 0xe) = '\0';
          *(uint8_t *)((int)pauVar12 + 0xf) = '\0';
          (*pauVar12)[0xd] = '\0';
          (*pauVar12)[1] = '\0';
          local_1c = 0;
          OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          iVar14 = 8;
          iVar6 = 0;
          do {
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6) = 0;
            *(undefined4 *)((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6) =
                 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 4) = 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 4) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 8) = 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 8) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 0xc) = 0
            ;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 0xc) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 0x10) =
                 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 0x10) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 0x14) =
                 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 0x14) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 0x18) =
                 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 0x18) = 0;
            *(undefined4 *)((int)joyBus->m_cmdQueueData[threadParam->m_portIndex] + iVar6 + 0x1c) =
                 0;
            *(undefined4 *)
             ((int)joyBus->m_recvQueueEntriesArr[threadParam->m_portIndex] + iVar6 + 0x1c) = 0;
            iVar14 = iVar14 + -1;
            iVar6 = iVar6 + 0x20;
          } while (iVar14 != 0);
          joyBus->m_cmdCount[threadParam->m_portIndex] = 0;
          joyBus->m_secCmdCount[threadParam->m_portIndex] = 0;
          OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          iVar6 = 0;
          if (joyBus->m_threadRunningMask != '\0') {
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar13 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar13] < 0x40) {
              joyBus->m_cmdQueueData[uVar13][joyBus->m_cmdCount[uVar13]] = 0x10000000;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar13);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -2 - ((int)((int)(char)(*pauVar12)[0] - (uint)local_1c._1_1_ |
                              (uint)local_1c._1_1_ - (int)(char)(*pauVar12)[0]) >> 0x1f);
          }
          return ((int)((uint)local_1c._1_1_ - (int)(char)(*pauVar12)[0] |
                       (int)(char)(*pauVar12)[0] - (uint)local_1c._1_1_) >> 0x1f) + -1;
        }
        if ((uint)local_1c._1_1_ == (int)(char)(*pauVar12)[0]) {
          *(uint8_t *)((int)pauVar12 + 0xe) = '\0';
          *(uint8_t *)((int)pauVar12 + 0xf) = '\0';
          (*pauVar12)[1] = '\x01';
          (*pauVar12)[0xd] = (*pauVar12)[0xd] + '\x01';
          *(uint *)(*pauVar12 + 4) = *(int *)(*pauVar12 + 4) + (uint)*(ushort *)(*pauVar12 + 0x14);
          if ((*pauVar12)[0xc] <= (*pauVar12)[0xd]) {
            return 1;
          }
        }
      }
      iVar6 = 0;
      local_1c = 0xb000000;
      if ((*pauVar12)[1] == '\0') {
        if (*(short *)(*pauVar12 + 0xe) == 0) {
          uVar9 = (*pauVar12)[0];
          if ((((uVar9 != '\x03') && (uVar9 != '\x02')) && (uVar9 != '\x06')) &&
             (((uVar9 != '\a' && (uVar9 != '\b')) && (uVar9 != '\t')))) {
            IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            if (joyBus->m_threadRunningMask == '\0') {
              iVar6 = 0;
            }
            else {
              OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              uVar13 = threadParam->m_portIndex;
              if ((int)joyBus->m_cmdCount[uVar13] < 0x40) {
                joyBus->m_cmdQueueData[uVar13][joyBus->m_cmdCount[uVar13]] = 0x9000000;
                joyBus->m_cmdCount[threadParam->m_portIndex] =
                     joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
                OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
                iVar6 = 0;
              }
              else {
                OSSignalSemaphore(joyBus->m_accessSemaphores + uVar13);
                iVar6 = -1;
              }
            }
            if (iVar6 != 0) {
              return -1;
            }
            joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\0';
          }
          uVar9 = (*pauVar12)[0];
          if (uVar9 == '\0') {
            pcVar4 = joyBus->m_fileBaseA;
            *(char **)(*pauVar12 + 4) = pcVar4;
            *(char **)(*pauVar12 + 8) = pcVar4;
            *(short *)(*pauVar12 + 0x12) = (short)joyBus->m_fileBaseA_dup;
          }
          else if (uVar9 == '\x01') {
            pcVar4 = joyBus->m_fileBaseB;
            *(char **)(*pauVar12 + 4) = pcVar4;
            *(char **)(*pauVar12 + 8) = pcVar4;
            *(short *)(*pauVar12 + 0x12) = (short)joyBus->m_fileBaseB_dup;
          }
          else {
            if (((uVar9 != '\x03') && (uVar9 != '\x02')) &&
               ((uVar9 != '\x06' && (((uVar9 != '\a' && (uVar9 != '\b')) && (uVar9 != '\t')))))) {
              if (System.m_execParam != 0) {
                Printf__7CSystemFPce
                          (&System,s___d___Error_send_type_error__02x_801da350,
                           threadParam->m_portIndex);
              }
              return -1;
            }
            pcVar4 = joyBus->m_letterBuffer[threadParam->m_portIndex];
            *(char **)(*pauVar12 + 4) = pcVar4;
            *(char **)(*pauVar12 + 8) = pcVar4;
            *(short *)(*pauVar12 + 0x12) = (short)joyBus->m_letterSizeArr[threadParam->m_portIndex];
          }
          uVar5 = *(ushort *)(*pauVar12 + 0x12) / 0x2fd;
          uVar9 = (uint8_t)uVar5;
          if ((uint)*(ushort *)(*pauVar12 + 0x12) != uVar5 * 0x2fd) {
            uVar9 = uVar9 + '\x01';
          }
          (*pauVar12)[0xc] = uVar9;
          local_28 = 0xffff;
          pbVar11 = *(byte **)(*pauVar12 + 8);
          uVar5 = (uint)*(ushort *)(*pauVar12 + 0x12);
          while (uVar5 = uVar5 - 1, -1 < (int)uVar5) {
            bVar1 = *pbVar11;
            pbVar11 = pbVar11 + 1;
            local_28 = local_28 << 8 ^ JoyBusCrcTable[(int)(uint)local_28 >> 8 ^ (uint)bVar1];
          }
          *(ushort *)(*pauVar12 + 2) = ~local_28;
          uVar13 = (uint)CONCAT21(CONCAT11(local_1c._0_1_,(*pauVar12)[0]),(*pauVar12)[0xc]) << 8;
          if (joyBus->m_threadRunningMask == '\0') {
            iVar6 = 0;
          }
          else {
            local_1c = uVar13;
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar10 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
              joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -1;
          }
          *(short *)(*pauVar12 + 0xe) = *(short *)(*pauVar12 + 0xe) + 1;
        }
        else if (*(short *)(*pauVar12 + 0xe) == 1) {
          local_28._1_1_ = (undefined)*(undefined2 *)(*pauVar12 + 0x12);
          local_28._0_1_ = (undefined)((ushort)*(undefined2 *)(*pauVar12 + 0x12) >> 8);
          uVar13 = CONCAT22(0xb00,CONCAT11((undefined)local_28,local_28._0_1_));
          if (joyBus->m_threadRunningMask != '\0') {
            local_1c = uVar13;
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar10 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
              joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -1;
          }
          *(short *)(*pauVar12 + 0xe) = *(short *)(*pauVar12 + 0xe) + 1;
        }
        else {
          uStack_25 = (undefined)*(undefined2 *)(*pauVar12 + 2);
          local_26 = (undefined)((ushort)*(undefined2 *)(*pauVar12 + 2) >> 8);
          uVar13 = CONCAT22(0xb00,CONCAT11(uStack_25,local_26));
          if (joyBus->m_threadRunningMask != '\0') {
            local_1c = uVar13;
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar10 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
              joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -1;
          }
          (*pauVar12)[1] = '\x01';
          *(uint8_t *)((int)pauVar12 + 0xe) = '\0';
          *(uint8_t *)((int)pauVar12 + 0xf) = '\0';
        }
      }
      else if ((*pauVar12)[1] == '\x01') {
        if (*(short *)(*pauVar12 + 0xe) == 0) {
          if ((int)(uint)(*pauVar12)[0xd] < (int)((*pauVar12)[0xc] - 1)) {
            *(uint8_t *)((int)pauVar12 + 0x10) = '\0';
            *(uint8_t *)((int)pauVar12 + 0x11) = 0xff;
            *(uint8_t *)((int)pauVar12 + 0x14) = '\x02';
            *(uint8_t *)((int)pauVar12 + 0x15) = 0xfd;
          }
          else {
            uVar5 = (uint)*(ushort *)(*pauVar12 + 0x12) % 0x2fd;
            if ((*(ushort *)(*pauVar12 + 0x12) != 0) && (uVar5 == 0)) {
              uVar5 = 0x2fd;
            }
            sVar8 = (short)(uVar5 / 3);
            if (uVar5 != (uVar5 / 3) * 3) {
              sVar8 = sVar8 + 1;
            }
            *(short *)(*pauVar12 + 0x10) = sVar8;
            *(short *)(*pauVar12 + 0x14) = (short)uVar5;
          }
          local_28._1_1_ = (undefined)*(undefined2 *)(*pauVar12 + 0x14);
          local_28._0_1_ = (undefined)((ushort)*(undefined2 *)(*pauVar12 + 0x14) >> 8);
          uVar13 = CONCAT22(CONCAT11(0x4b,(char)*(undefined2 *)(*pauVar12 + 0x10)),
                            CONCAT11((undefined)local_28,local_28._0_1_));
          if (joyBus->m_threadRunningMask == '\0') {
            iVar6 = 0;
          }
          else {
            local_1c = uVar13;
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar10 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
              joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -1;
          }
          *(short *)(*pauVar12 + 0xe) = *(short *)(*pauVar12 + 0xe) + 1;
        }
        else {
          local_28 = 0xffff;
          pbVar11 = *(byte **)(*pauVar12 + 4);
          uVar5 = (uint)*(ushort *)(*pauVar12 + 0x14);
          while (uVar5 = uVar5 - 1, -1 < (int)uVar5) {
            bVar1 = *pbVar11;
            pbVar11 = pbVar11 + 1;
            local_28 = local_28 << 8 ^ JoyBusCrcTable[(int)(uint)local_28 >> 8 ^ (uint)bVar1];
          }
          uStack_25 = (undefined)~local_28;
          local_26 = (undefined)((ushort)~local_28 >> 8);
          uVar13 = CONCAT22(CONCAT11(0x4b,(*pauVar12)[0xd]),CONCAT11(uStack_25,local_26));
          if (joyBus->m_threadRunningMask == '\0') {
            iVar6 = 0;
          }
          else {
            local_1c = uVar13;
            OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            uVar10 = threadParam->m_portIndex;
            if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
              joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
              joyBus->m_cmdCount[threadParam->m_portIndex] =
                   joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
              OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
              iVar6 = 0;
            }
            else {
              OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
              iVar6 = -1;
            }
          }
          if (iVar6 != 0) {
            return -1;
          }
          (*pauVar12)[1] = '\x02';
          *(uint8_t *)((int)pauVar12 + 0xe) = '\0';
          *(uint8_t *)((int)pauVar12 + 0xf) = '\0';
        }
      }
      else {
        puVar7 = *(undefined **)(*pauVar12 + 8);
        *(undefined **)(*pauVar12 + 8) = puVar7 + 1;
        uVar2 = *puVar7;
        puVar7 = *(undefined **)(*pauVar12 + 8);
        *(undefined **)(*pauVar12 + 8) = puVar7 + 1;
        uVar3 = *puVar7;
        puVar7 = *(undefined **)(*pauVar12 + 8);
        *(undefined **)(*pauVar12 + 8) = puVar7 + 1;
        uVar13 = CONCAT31(CONCAT21(CONCAT11(0x8b,uVar2),uVar3),*puVar7);
        if (joyBus->m_threadRunningMask != '\0') {
          local_1c = uVar13;
          OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
          uVar10 = threadParam->m_portIndex;
          if ((int)joyBus->m_cmdCount[uVar10] < 0x40) {
            joyBus->m_cmdQueueData[uVar10][joyBus->m_cmdCount[uVar10]] = uVar13;
            joyBus->m_cmdCount[threadParam->m_portIndex] =
                 joyBus->m_cmdCount[threadParam->m_portIndex] + 1;
            OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
            iVar6 = 0;
          }
          else {
            OSSignalSemaphore(joyBus->m_accessSemaphores + uVar10);
            iVar6 = -1;
          }
        }
        if (iVar6 != 0) {
          return -1;
        }
        *(short *)(*pauVar12 + 0xe) = *(short *)(*pauVar12 + 0xe) + 1;
      }
      iVar6 = 0;
    }
    else {
      iVar6 = 0;
    }
  }
  else {
    iVar6 = 0;
  }
  return iVar6;
}

