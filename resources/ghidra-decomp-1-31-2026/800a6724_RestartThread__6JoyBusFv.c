// Function: RestartThread__6JoyBusFv
// Entry: 800a6724
// Size: 892 bytes

void RestartThread__6JoyBusFv(JoyBus *joyBus)

{
  uint8_t uVar1;
  CFileCHandle *fileHandle;
  undefined4 uVar2;
  int iVar3;
  uint8_t uVar4;
  int iVar5;
  uint8_t *puVar6;
  JoyBus *pJVar7;
  uint32_t uVar8;
  JoyBus *pJVar9;
  
  joyBus->m_threadInitFlag = '\0';
  CreateInit__6JoyBusFv(&Joybus);
  if (Joybus.m_binLoaded == false) {
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,&Joybus,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,s_Error___s_not_found_801da2a4,&Joybus);
      }
      iVar3 = -1;
    }
    else {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      Joybus.m_gbaBootParamB = (uint8_t *)GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      memcpy(Joybus.m_gbaBootParamA,File.m_readBuffer,Joybus.m_gbaBootParamB);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      Joybus.m_diskId = (uint8_t *)GetCurrentDiskID__5CFileFv(&File);
      iVar5 = 0xbc;
      Joybus.m_gbaBootParamA[0xac] = *Joybus.m_diskId;
      Joybus.m_gbaBootParamA[0xad] = Joybus.m_diskId[1];
      Joybus.m_gbaBootParamA[0xae] = Joybus.m_diskId[2];
      Joybus.m_gbaBootParamA[0xaf] = Joybus.m_diskId[3];
      puVar6 = Joybus.m_gbaBootParamA + 0xbc;
      iVar3 = 1;
      uVar4 = (((((((((((((((((((((((((((-0x19 - Joybus.m_gbaBootParamA[0xa0]) -
                                       Joybus.m_gbaBootParamA[0xa1]) - Joybus.m_gbaBootParamA[0xa2])
                                     - Joybus.m_gbaBootParamA[0xa3]) - Joybus.m_gbaBootParamA[0xa4])
                                   - Joybus.m_gbaBootParamA[0xa5]) - Joybus.m_gbaBootParamA[0xa6]) -
                                 Joybus.m_gbaBootParamA[0xa7]) - Joybus.m_gbaBootParamA[0xa8]) -
                               Joybus.m_gbaBootParamA[0xa9]) - Joybus.m_gbaBootParamA[0xaa]) -
                             Joybus.m_gbaBootParamA[0xab]) - Joybus.m_gbaBootParamA[0xac]) -
                           Joybus.m_gbaBootParamA[0xad]) - Joybus.m_gbaBootParamA[0xae]) -
                         Joybus.m_gbaBootParamA[0xaf]) - Joybus.m_gbaBootParamA[0xb0]) -
                       Joybus.m_gbaBootParamA[0xb1]) - Joybus.m_gbaBootParamA[0xb2]) -
                     Joybus.m_gbaBootParamA[0xb3]) - Joybus.m_gbaBootParamA[0xb4]) -
                   Joybus.m_gbaBootParamA[0xb5]) - Joybus.m_gbaBootParamA[0xb6]) -
                 Joybus.m_gbaBootParamA[0xb7]) - Joybus.m_gbaBootParamA[0xb8]) -
               Joybus.m_gbaBootParamA[0xb9]) - Joybus.m_gbaBootParamA[0xba]) -
              Joybus.m_gbaBootParamA[0xbb];
      do {
        uVar1 = *puVar6;
        puVar6 = puVar6 + 1;
        iVar5 = iVar5 + 1;
        uVar4 = uVar4 - uVar1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      Joybus.m_gbaBootParamA[iVar5] = uVar4;
      uVar2 = OSGetTick();
      iVar3 = 0;
      *(undefined4 *)(Joybus.m_gbaBootParamA + 200) = uVar2;
      Joybus.m_binLoaded = true;
    }
  }
  else {
    iVar3 = 0;
  }
  if ((iVar3 != 0) && (1 < (uint)System.m_execParam)) {
    Printf__7CSystemFPce(&System,s_JoyBus__LoadBin___error_801da2bc);
  }
  memset(0x802f07d0,0,0xf0);
  uVar8 = 0;
  pJVar9 = &Joybus;
  Joybus.m_threadInitFlag = '\0';
  Joybus.m_threadRunningMask = '\0';
  pJVar7 = pJVar9;
  do {
    pJVar7->m_threadParams[0].m_portIndex = uVar8;
    pJVar7->m_threadParams[0].m_gbaStatus = 1;
    OSCreateThread(pJVar9->m_threads,_ThreadMain__6JoyBusFPv,pJVar7->m_threadParams,
                   (uVar8 + 1) * 0x1000 + -0x7fd13830,0x1000,8,1);
    OSResumeThread(pJVar9->m_threads);
    iVar3 = 1 << uVar8;
    uVar8 = uVar8 + 1;
    Joybus.m_threadRunningMask = Joybus.m_threadRunningMask | (byte)iVar3;
    pJVar9 = (JoyBus *)(pJVar9->m_recvBuffer[0].m_payload + 0x290);
    pJVar7 = (JoyBus *)(pJVar7->m_pathBuf + 0x3c);
  } while ((int)uVar8 < 4);
  if (1 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_JoyBus__ThreadInit_end_801da2d8);
  }
  return;
}

