// Function: RedSleep__Fi
// Entry: 801bdd1c
// Size: 160 bytes

void RedSleep__Fi(int param_1)

{
  undefined4 uVar1;
  OSAlarm OStack_38;
  undefined4 local_10;
  
  if (param_1 < 0xfa) {
    param_1 = 0xfa;
  }
  uVar1 = OSDisableInterrupts();
  local_10 = OSGetCurrentThread();
  OSCreateAlarm(&OStack_38);
  OSSetAlarm(&OStack_38,0x431bde83,0,param_1 * (DAT_800000f8 / 500000) >> 3,
             _MyAlarmHandler__FP7OSAlarmP9OSContext);
  OSSuspendThread(local_10);
  OSRestoreInterrupts(uVar1);
  return;
}

