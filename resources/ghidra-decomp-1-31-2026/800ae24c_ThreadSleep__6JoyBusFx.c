// Function: ThreadSleep__6JoyBusFx
// Entry: 800ae24c
// Size: 128 bytes

void ThreadSleep__6JoyBusFx(JoyBus *joyBus,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  OSAlarm OStack_38;
  undefined4 local_10;
  
  OSCreateAlarm(&OStack_38);
  OSSetAlarmTag(&OStack_38,1);
  local_10 = OSGetCurrentThread();
  uVar1 = OSDisableInterrupts();
  OSSetAlarm(&OStack_38,0x800b0000,param_3,param_4,ThreadAlarmHandler__FP7OSAlarmP9OSContext);
  OSSuspendThread(local_10);
  OSRestoreInterrupts(uVar1);
  return;
}

