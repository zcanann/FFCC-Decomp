// Function: LoadMap__6JoyBusFii
// Entry: 800b1d54
// Size: 372 bytes

undefined4 LoadMap__6JoyBusFii(JoyBus *joyBus,int stageId,int mapId)

{
  CFileCHandle *fileHandle;
  undefined4 uVar1;
  uint32_t uVar2;
  int iVar3;
  JoyBus *pJVar4;
  char acStack_a8 [16];
  char acStack_98 [132];
  
  iVar3 = 0;
  pJVar4 = joyBus;
  do {
    OSWaitSemaphore(pJVar4->m_accessSemaphores);
    iVar3 = iVar3 + 1;
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0xc);
  } while (iVar3 < 4);
  joyBus->m_stageId = (uint8_t)stageId;
  iVar3 = 0;
  joyBus->m_mapId = (uint8_t)mapId;
  pJVar4 = joyBus;
  do {
    OSSignalSemaphore(pJVar4->m_accessSemaphores);
    iVar3 = iVar3 + 1;
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0xc);
  } while (iVar3 < 4);
  joyBus->m_fileBaseB_dup = 0;
  strcpy(acStack_98,PTR_s_dvd_gba__8032e830);
  sprintf(acStack_a8,s_m_02d__d_mcd_801da374,stageId,mapId);
  strcat(acStack_98,acStack_a8);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,acStack_98,0,0);
  if (fileHandle == (CFileCHandle *)0x0) {
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s_Error___s_not_found_801da2a4,acStack_98);
    }
    uVar1 = 0xffffffff;
  }
  else {
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    uVar2 = GetLength__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    joyBus->m_fileBaseB_dup = uVar2;
    memset(joyBus->m_fileBaseB,0,0x5000);
    memcpy(joyBus->m_fileBaseB,File.m_readBuffer,joyBus->m_fileBaseB_dup);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    uVar1 = 0;
  }
  return uVar1;
}

