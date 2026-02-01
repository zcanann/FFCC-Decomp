// Function: LoadBin__6JoyBusFv
// Entry: 800b1ec8
// Size: 620 bytes

undefined4 LoadBin__6JoyBusFv(JoyBus *joyBus)

{
  int iVar1;
  undefined4 uVar2;
  CFileCHandle *fileHandle;
  uint8_t *puVar3;
  int iVar4;
  uint8_t uVar5;
  
  if (joyBus->m_binLoaded == false) {
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,joyBus,0,0);
    if (fileHandle == (CFileCHandle *)0x0) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,s_Error___s_not_found_801da2a4,joyBus);
      }
      uVar2 = 0xffffffff;
    }
    else {
      Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      puVar3 = (uint8_t *)GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      joyBus->m_gbaBootParamB = puVar3;
      memcpy(joyBus->m_gbaBootParamA,File.m_readBuffer,joyBus->m_gbaBootParamB);
      Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
      puVar3 = (uint8_t *)GetCurrentDiskID__5CFileFv(&File);
      joyBus->m_diskId = puVar3;
      iVar4 = 0xbc;
      joyBus->m_gbaBootParamA[0xac] = *joyBus->m_diskId;
      joyBus->m_gbaBootParamA[0xad] = joyBus->m_diskId[1];
      joyBus->m_gbaBootParamA[0xae] = joyBus->m_diskId[2];
      joyBus->m_gbaBootParamA[0xaf] = joyBus->m_diskId[3];
      puVar3 = joyBus->m_gbaBootParamA;
      iVar1 = 1;
      uVar5 = (((((((((((((((((((((((((((-0x19 - puVar3[0xa0]) - puVar3[0xa1]) - puVar3[0xa2]) -
                                     puVar3[0xa3]) - puVar3[0xa4]) - puVar3[0xa5]) - puVar3[0xa6]) -
                                 puVar3[0xa7]) - puVar3[0xa8]) - puVar3[0xa9]) - puVar3[0xaa]) -
                             puVar3[0xab]) - puVar3[0xac]) - puVar3[0xad]) - puVar3[0xae]) -
                         puVar3[0xaf]) - puVar3[0xb0]) - puVar3[0xb1]) - puVar3[0xb2]) -
                     puVar3[0xb3]) - puVar3[0xb4]) - puVar3[0xb5]) - puVar3[0xb6]) - puVar3[0xb7]) -
                puVar3[0xb8]) - puVar3[0xb9]) - puVar3[0xba]) - puVar3[0xbb];
      do {
        puVar3 = joyBus->m_gbaBootParamA + iVar4;
        iVar4 = iVar4 + 1;
        uVar5 = uVar5 - *puVar3;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      joyBus->m_gbaBootParamA[iVar4] = uVar5;
      uVar2 = OSGetTick();
      *(undefined4 *)(joyBus->m_gbaBootParamA + 200) = uVar2;
      uVar2 = 0;
      joyBus->m_binLoaded = true;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

