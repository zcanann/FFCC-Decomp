// Function: CreateInit__6JoyBusFv
// Entry: 800b22f4
// Size: 936 bytes

void CreateInit__6JoyBusFv(JoyBus *joyBus)

{
  uint8_t *puVar1;
  CFileCHandle *fileHandle;
  uint32_t uVar2;
  char *pcVar3;
  JoyBus *pJVar4;
  JoyBus *pJVar5;
  JoyBus *pJVar6;
  int iVar7;
  int iVar8;
  char acStack_b8 [140];
  
  memset(joyBus->m_sendBuffer,0,0x4000);
  memset(joyBus->m_stageFlags,0,8);
  memset(joyBus->m_cmdQueueData,0,0x400);
  memset(joyBus->m_recvQueueEntriesArr,0,0x400);
  memset(joyBus->m_threadParams,0,0xf0);
  memset(joyBus->m_perThreadTemp,0,0x60);
  memset(joyBus->m_recvBuffer,0,0x1020);
  joyBus->m_mapId = 0xff;
  joyBus->m_stageId = 0xff;
  pJVar4 = joyBus;
  pJVar5 = joyBus;
  pJVar6 = joyBus;
  iVar7 = 0;
  do {
    pJVar6->m_threadParams[0].m_gbaStatus = 1;
    pJVar6->m_threadParams[0].m_padType = 0x40;
    pJVar5->m_cmdCount[0] = 0;
    pJVar5->m_secCmdCount[0] = 0;
    OSInitSemaphore(pJVar4->m_accessSemaphores,1);
    iVar8 = iVar7 + 1;
    joyBus->m_ctrlModeArr[iVar7] = '\0';
    pJVar6 = (JoyBus *)(pJVar6->m_pathBuf + 0x3c);
    pJVar5 = (JoyBus *)(pJVar5->m_pathBuf + 4);
    joyBus->m_nextModeTypeArr[iVar7] = '\0';
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0xc);
    joyBus->m_modeXArr[iVar7] = '\0';
    joyBus->m_stateCodeArr[iVar7] = 0xff;
    joyBus->m_stateFlagArr[iVar7] = '\0';
    iVar7 = iVar8;
  } while (iVar8 < 4);
  if (joyBus->m_gbaBootParamA == (uint8_t *)0x0) {
    puVar1 = (uint8_t *)
             __nwa__FUlPQ27CMemory6CStagePci(0x38000,uRam8032edac,s_joybus_cpp_801da320,0x122);
    joyBus->m_gbaBootParamA = puVar1;
    if (joyBus->m_gbaBootParamA == (uint8_t *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801da384,s_joybus_cpp_801da320,0x126);
      }
    }
  }
  strcpy(acStack_b8,PTR_s_dvd_gba__8032e830);
  strcat(acStack_b8,PTR_s_objdat_spt_8032e838);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_b8,0,0);
  if ((fileHandle == (CFileCHandle *)0x0) && (1 < (uint)System.m_execParam)) {
    Printf__7CSystemFPce(&System,s_Error___s_not_found_801da2a4,acStack_b8);
  }
  Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  uVar2 = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  joyBus->m_fileBaseA_dup = uVar2;
  if (joyBus->m_fileBaseA == (char *)0x0) {
    pcVar3 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                               (joyBus->m_fileBaseA_dup + 0x20,uRam8032edac,s_joybus_cpp_801da320,
                                0x137);
    joyBus->m_fileBaseA = pcVar3;
    if ((joyBus->m_fileBaseA == (char *)0x0) && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801da384,s_joybus_cpp_801da320,0x13a);
    }
  }
  memset(joyBus->m_fileBaseA,0,joyBus->m_fileBaseA_dup);
  memcpy(joyBus->m_fileBaseA,File.m_readBuffer,joyBus->m_fileBaseA_dup);
  Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  if (joyBus->m_fileBaseB == (char *)0x0) {
    pcVar3 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                               (0x5000,uRam8032edac,s_joybus_cpp_801da320,0x143);
    joyBus->m_fileBaseB = pcVar3;
    if ((joyBus->m_fileBaseB == (char *)0x0) && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801da384,s_joybus_cpp_801da320,0x146);
    }
  }
  joyBus->m_fileBaseB_dup = 0;
  iVar7 = 0;
  joyBus->m_cmdBuffer[0] = '\0';
  joyBus->m_cmdBuffer[4] = '\0';
  joyBus->m_cmdBuffer[1] = '\0';
  joyBus->m_cmdBuffer[5] = '\0';
  joyBus->m_cmdBuffer[2] = '\0';
  joyBus->m_cmdBuffer[6] = '\0';
  joyBus->m_cmdBuffer[3] = '\0';
  joyBus->m_cmdBuffer[7] = '\0';
  do {
    if (joyBus->m_letterBuffer[0] == (char *)0x0) {
      pcVar3 = (char *)__nwa__FUlPQ27CMemory6CStagePci
                                 (0x2800,uRam8032edac,s_joybus_cpp_801da320,0x152);
      joyBus->m_letterBuffer[0] = pcVar3;
      if ((joyBus->m_letterBuffer[0] == (char *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801da384,s_joybus_cpp_801da320,0x155);
      }
      joyBus->m_letterSizeArr[0] = 0;
    }
    iVar7 = iVar7 + 1;
    joyBus = (JoyBus *)(joyBus->m_pathBuf + 4);
  } while (iVar7 < 4);
  return;
}

