// Function: OSSetAlarm
// Entry: 8017c42c
// Size: 104 bytes

void OSSetAlarm(OSAlarm *osAlarm,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  longlong lVar1;
  undefined4 uVar2;
  longlong lVar3;
  
  uVar2 = OSDisableInterrupts();
  *(undefined4 *)((int)&osAlarm->period + 4) = 0;
  *(undefined4 *)&osAlarm->period = 0;
  lVar3 = __OSGetSystemTime();
  lVar1 = lVar3 + CONCAT44(param_3,param_4);
  InsertAlarm(osAlarm,(int)lVar3,(int)((ulonglong)lVar1 >> 0x20),(int)lVar1,param_5);
  OSRestoreInterrupts(uVar2);
  return;
}

