// Function: __sinit_joybus_cpp
// Entry: 800b2728
// Size: 456 bytes

void __sinit_joybus_cpp(void)

{
  JoyBus *pJVar1;
  JoyBus *pJVar2;
  JoyBus *pJVar3;
  JoyBus *pJVar4;
  int iVar5;
  
  Joybus.m_threadRunningMask = '\0';
  Joybus.m_binLoaded = false;
  Joybus.m_fileBaseA_dup = 0;
  Joybus.m_fileBaseB_dup = 0;
  Joybus.m_gbaBootParamA = (uint8_t *)0x0;
  Joybus.m_fileBaseA = (char *)0x0;
  Joybus.m_fileBaseB = (char *)0x0;
  Joybus.m_letterBuffer[0] = (char *)0x0;
  Joybus.m_letterSizeArr[0] = 0;
  Joybus.m_letterBuffer[1] = (char *)0x0;
  Joybus.m_letterSizeArr[1] = 0;
  Joybus.m_letterBuffer[2] = (char *)0x0;
  Joybus.m_letterSizeArr[2] = 0;
  Joybus.m_letterBuffer[3] = (char *)0x0;
  Joybus.m_letterSizeArr[3] = 0;
  strcpy(&Joybus,PTR_s_dvd_gba__8032e830);
  strcat(Joybus.m_pathBuf,PTR_s_ffcc_cli_bin_8032e834);
  memset(0x802ec7d0,0,0x4000);
  memset(0x802f08f0,0,8);
  memset(0x802f08f8,0,0x400);
  memset(0x802f0cf8,0,0x400);
  memset(0x802f07d0,0,0xf0);
  memset(0x802f1160,0,0x60);
  memset(0x802eab40,0,0x1020);
  iVar5 = 0;
  pJVar3 = &Joybus;
  Joybus.m_mapId = 0xff;
  Joybus.m_stageId = 0xff;
  pJVar1 = pJVar3;
  pJVar2 = pJVar3;
  pJVar4 = pJVar3;
  do {
    pJVar4->m_threadParams[0].m_gbaStatus = 1;
    pJVar4->m_threadParams[0].m_padType = 0x40;
    pJVar2->m_cmdCount[0] = 0;
    pJVar2->m_secCmdCount[0] = 0;
    OSInitSemaphore(pJVar1->m_accessSemaphores,1);
    pJVar3->m_ctrlModeArr[0] = '\0';
    iVar5 = iVar5 + 1;
    pJVar4 = (JoyBus *)(pJVar4->m_pathBuf + 0x3c);
    pJVar3->m_nextModeTypeArr[0] = '\0';
    pJVar2 = (JoyBus *)(pJVar2->m_pathBuf + 4);
    pJVar1 = (JoyBus *)(pJVar1->m_pathBuf + 0xc);
    pJVar3->m_modeXArr[0] = '\0';
    pJVar3->m_stateCodeArr[0] = 0xff;
    pJVar3->m_stateFlagArr[0] = '\0';
    pJVar3 = (JoyBus *)(pJVar3->m_pathBuf + 1);
  } while (iVar5 < 4);
  __register_global_object(&Joybus,__dt__6JoyBusFv,ARRAY_802eaab0);
  return;
}

