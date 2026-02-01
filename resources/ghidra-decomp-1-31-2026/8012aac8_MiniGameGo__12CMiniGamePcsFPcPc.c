// Function: MiniGameGo__12CMiniGamePcsFPcPc
// Entry: 8012aac8
// Size: 1492 bytes

void MiniGameGo__12CMiniGamePcsFPcPc(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  undefined4 uVar5;
  CFileCHandle *pCVar6;
  int iVar7;
  char cVar8;
  char *pcVar9;
  char *pcVar10;
  void *pvVar11;
  int iVar12;
  undefined8 uVar13;
  undefined auStack_88 [8];
  OSAlarm OStack_80;
  undefined4 local_58;
  OSAlarm OStack_50;
  undefined4 local_28;
  
  if (*(int *)(param_1 + 0x1354) != 0) {
    *(undefined *)(param_1 + 0x649c) = 1;
    while (*(char *)(param_1 + 0x649c) != '\0') {
      uVar2 = DAT_800000f8 / 4000;
      OSCreateAlarm(&OStack_50);
      OSSetAlarmTag(&OStack_50,1);
      local_28 = OSGetCurrentThread();
      uVar13 = OSDisableInterrupts();
      OSSetAlarm(&OStack_50,(int)uVar13,0,uVar2 * 100,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
      OSSuspendThread(local_28);
      OSRestoreInterrupts((int)((ulonglong)uVar13 >> 0x20));
    }
    while (iVar4 = OSIsThreadTerminated(param_1 + 8), iVar4 == 0) {
      uVar2 = DAT_800000f8 / 4000;
      OSCreateAlarm(&OStack_80);
      OSSetAlarmTag(&OStack_80,1);
      local_58 = OSGetCurrentThread();
      uVar13 = OSDisableInterrupts();
      OSSetAlarm(&OStack_80,(int)uVar13,0,uVar2 * 100,GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
      OSSuspendThread(local_58);
      OSRestoreInterrupts((int)((ulonglong)uVar13 >> 0x20));
    }
    if (*(int *)(param_1 + 0x1354) != 0) {
      __dl__FPv();
      *(undefined4 *)(param_1 + 0x1354) = 0;
    }
    if (*(int *)(param_1 + 0x135c) != 0) {
      __dl__FPv();
      *(undefined4 *)(param_1 + 0x135c) = 0;
    }
  }
  *(undefined *)(param_1 + 0x6498) = 0xff;
  *(undefined *)(param_1 + 0x6499) = 0xff;
  *(undefined *)(param_1 + 0x649a) = 0xff;
  *(undefined *)(param_1 + 0x649b) = 0xff;
  *(undefined *)(param_1 + 0x6495) = 0;
  *(undefined *)(param_1 + 0x6496) = 0;
  *(undefined *)(param_1 + 0x6497) = 0;
  *(undefined2 *)(param_1 + 0x134e) = 0;
  *(undefined *)(param_1 + 0x6494) = 0;
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                    (0x40000,PartPcs.m_usbStreamData.m_stageLoad,s_p_minigame_cpp_801dd38c,0xf1);
  *(undefined4 *)(param_1 + 0x1354) = uVar5;
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                    (0x40000,PartPcs.m_usbStreamData.m_stageLoad,s_p_minigame_cpp_801dd38c,0xf2);
  *(undefined4 *)(param_1 + 0x135c) = uVar5;
  uVar5 = OSGetTick();
  *(undefined4 *)(param_1 + 0x1364) = uVar5;
  *(undefined4 *)(*(int *)(param_1 + 0x1354) + 200) = *(undefined4 *)(param_1 + 0x1364);
  *(undefined4 *)(*(int *)(param_1 + 0x135c) + 200) = *(undefined4 *)(param_1 + 0x1364);
  strncpy(param_1 + 0x1344,&DAT_80331bf0,4);
  pvVar11 = *(void **)(param_1 + 0x1354);
  pCVar6 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_2,0,0);
  if (pCVar6 != (CFileCHandle *)0x0) {
    uVar5 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    *(undefined4 *)(param_1 + 0x1358) = uVar5;
    Read__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    pvVar3 = File.m_readBuffer;
    Close__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    memcpy(pvVar11,pvVar3,*(undefined4 *)(param_1 + 0x1358));
  }
  iVar4 = 0xa0;
  iVar7 = *(int *)(param_1 + 0x1354);
  cVar8 = -0x19;
  *(undefined *)(iVar7 + 0xac) = *(undefined *)(param_1 + 0x1344);
  *(undefined *)(iVar7 + 0xad) = *(undefined *)(param_1 + 0x1345);
  *(undefined *)(iVar7 + 0xae) = *(undefined *)(param_1 + 0x1346);
  *(undefined *)(iVar7 + 0xaf) = *(undefined *)(param_1 + 0x1347);
  iVar12 = 2;
  do {
    pcVar9 = (char *)(iVar7 + iVar4);
    pcVar10 = (char *)(iVar7 + iVar4 + 7);
    cVar8 = (((((((((((((cVar8 - *pcVar9) - pcVar9[1]) - pcVar9[2]) - pcVar9[3]) - pcVar9[4]) -
                   pcVar9[5]) - pcVar9[6]) - *pcVar10) - pcVar10[1]) - pcVar10[2]) - pcVar10[3]) -
             pcVar10[4]) - pcVar10[5]) - pcVar10[6];
    iVar4 = iVar4 + 0xe;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  iVar12 = 0xbd - iVar4;
  pcVar9 = (char *)(iVar7 + iVar4);
  if (iVar4 < 0xbd) {
    do {
      cVar1 = *pcVar9;
      iVar4 = iVar4 + 1;
      pcVar9 = pcVar9 + 1;
      cVar8 = cVar8 - cVar1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  *(char *)(iVar7 + iVar4) = cVar8;
  pvVar11 = *(void **)(param_1 + 0x135c);
  pCVar6 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_3,0,0);
  if (pCVar6 != (CFileCHandle *)0x0) {
    uVar5 = GetLength__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    *(undefined4 *)(param_1 + 0x1360) = uVar5;
    Read__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    pvVar3 = File.m_readBuffer;
    Close__5CFileFPQ25CFile7CHandle(&File,pCVar6);
    memcpy(pvVar11,pvVar3,*(undefined4 *)(param_1 + 0x1360));
  }
  iVar4 = 0xa0;
  iVar7 = *(int *)(param_1 + 0x135c);
  cVar8 = -0x19;
  *(undefined *)(iVar7 + 0xac) = *(undefined *)(param_1 + 0x1344);
  *(undefined *)(iVar7 + 0xad) = *(undefined *)(param_1 + 0x1345);
  *(undefined *)(iVar7 + 0xae) = *(undefined *)(param_1 + 0x1346);
  *(undefined *)(iVar7 + 0xaf) = *(undefined *)(param_1 + 0x1347);
  iVar12 = 2;
  do {
    pcVar9 = (char *)(iVar7 + iVar4);
    pcVar10 = (char *)(iVar7 + iVar4 + 7);
    cVar8 = (((((((((((((cVar8 - *pcVar9) - pcVar9[1]) - pcVar9[2]) - pcVar9[3]) - pcVar9[4]) -
                   pcVar9[5]) - pcVar9[6]) - *pcVar10) - pcVar10[1]) - pcVar10[2]) - pcVar10[3]) -
             pcVar10[4]) - pcVar10[5]) - pcVar10[6];
    iVar4 = iVar4 + 0xe;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  iVar12 = 0xbd - iVar4;
  pcVar9 = (char *)(iVar7 + iVar4);
  if (iVar4 < 0xbd) {
    do {
      cVar1 = *pcVar9;
      iVar4 = iVar4 + 1;
      pcVar9 = pcVar9 + 1;
      cVar8 = cVar8 - cVar1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
  }
  *(char *)(iVar7 + iVar4) = cVar8;
  GBAReset(0,auStack_88);
  memset(param_1 + 8,0,0x318);
  memset(param_1 + 800,0,0x20);
  memset(param_1 + 0x340,0,4);
  OSInitMessageQueue(param_1 + 800,param_1 + 0x340,1);
  OSCreateThread(param_1 + 8,_MngThreadMain__FPv,0,param_1 + 0x1344,0x1000,8,1);
  OSResumeThread(param_1 + 8);
  return;
}

