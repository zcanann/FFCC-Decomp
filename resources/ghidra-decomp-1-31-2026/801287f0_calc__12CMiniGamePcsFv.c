// Function: calc__12CMiniGamePcsFv
// Entry: 801287f0
// Size: 1244 bytes

/* WARNING: Removing unreachable block (ram,0x80128828) */

void calc__12CMiniGamePcsFv(int param_1)

{
  byte bVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  OSAlarm OStack_280;
  undefined4 local_258;
  OSAlarm OStack_250;
  undefined4 local_228;
  undefined auStack_220 [256];
  undefined auStack_120 [260];
  
  bVar1 = *(byte *)(param_1 + 0x1348);
  if (bVar1 != 2) {
    if (1 < bVar1) {
      if (3 < bVar1) {
        return;
      }
      if (*(char *)(param_1 + 0x6496) != '\0') {
        Printf__7CSystemFPce(&System,s__________________________________801dd1e8);
        iVar4 = 0;
        do {
          Printf__7CSystemFPce
                    (&System,s_P_d____d_801dd230,iVar4 + 1,(int)*(char *)(param_1 + iVar4 + 0x6498))
          ;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 4);
        Printf__7CSystemFPce(&System,s__________________________________801dd240);
        local_290 = 0x3000;
        local_28c = 0;
        local_288 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,8,3,&local_290,(CStack *)0x0);
        *(undefined *)(param_1 + 0x6496) = 0;
      }
      if (*(char *)(param_1 + 0x6497) != '\0') {
        *(undefined *)(param_1 + 0x6498) = 0xff;
        *(undefined *)(param_1 + 0x6499) = 0xff;
        *(undefined *)(param_1 + 0x649a) = 0xff;
        *(undefined *)(param_1 + 0x649b) = 0xff;
        if (2 < (uint)System.m_execParam) {
          Printf__7CSystemFPce(&System,s_MINI_GAME_CONTINUE_801dd278);
        }
        local_29c = 0x3002;
        local_298 = 0;
        local_294 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,8,3,&local_29c,(CStack *)0x0);
        *(undefined *)(param_1 + 0x6497) = 0;
      }
      if (*(char *)(param_1 + 0x6495) == '\0') {
        return;
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_CallMiniGameParam_MGR_CALL_MGR_E_801dd290);
      }
      local_2a8 = 0x3001;
      local_2a4 = 0;
      local_2a0 = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,8,3,&local_2a8,(CStack *)0x0);
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_CallMiniGameParam_MGR_CALL_MGR_E_801dd2b8);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_MiniGameEnd_0000_801dd0d4);
      }
      if (*(int *)(param_1 + 0x1354) != 0) {
        *(undefined *)(param_1 + 0x649c) = 1;
        while (*(char *)(param_1 + 0x649c) != '\0') {
          uVar2 = DAT_800000f8 / 4000;
          OSCreateAlarm(&OStack_250);
          OSSetAlarmTag(&OStack_250,1);
          local_228 = OSGetCurrentThread();
          uVar5 = OSDisableInterrupts();
          OSSetAlarm(&OStack_250,(int)uVar5,0,uVar2 * 100,
                     GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
          OSSuspendThread(local_228);
          OSRestoreInterrupts((int)((ulonglong)uVar5 >> 0x20));
        }
        while (iVar4 = OSIsThreadTerminated(param_1 + 8), iVar4 == 0) {
          uVar2 = DAT_800000f8 / 4000;
          OSCreateAlarm(&OStack_280);
          OSSetAlarmTag(&OStack_280,1);
          local_258 = OSGetCurrentThread();
          uVar5 = OSDisableInterrupts();
          OSSetAlarm(&OStack_280,(int)uVar5,0,uVar2 * 100,
                     GbaThreadAlarmHandler__FP7OSAlarmP9OSContext);
          OSSuspendThread(local_258);
          OSRestoreInterrupts((int)((ulonglong)uVar5 >> 0x20));
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
      *(undefined *)(param_1 + 0x134b) = 0xf;
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_MiniGameEnd_1111_801dd0e8);
      }
      RestartThread__6JoyBusFv(&Joybus);
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,s_MiniGameEnd_2222_801dd0fc);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801dd2e4);
      }
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      *(undefined *)(param_1 + 0x6495) = 0;
      *(undefined *)(param_1 + 0x1348) = 0;
      return;
    }
    if (bVar1 == 0) {
      return;
    }
    ExitThread__6JoyBusFv(&Joybus);
    *(undefined *)(param_1 + 0x1348) = 2;
  }
  cVar3 = IsThreadRunning__6JoyBusFv(&Joybus);
  if (cVar3 == '\0') {
    sprintf(auStack_120,s__s_mgr_02d_bin_801dd18c,s_dvd_minigame_mgr_801dd19c,
            *(undefined *)(param_1 + 0x1350));
    sprintf(auStack_220,s__s_mgrsp_02d_bin_801dd1b0,s_dvd_minigame_mgr_801dd19c,
            *(undefined *)(param_1 + 0x1350));
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s_MINIGAME_FILE__s_SPFILE__s_801dd1c4,auStack_120,auStack_220);
    }
    MiniGameGo__12CMiniGamePcsFPcPc(param_1,auStack_120,auStack_220);
    *(undefined *)(param_1 + 0x1348) = 3;
  }
  return;
}

