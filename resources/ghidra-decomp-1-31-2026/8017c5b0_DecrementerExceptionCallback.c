// Function: DecrementerExceptionCallback
// Entry: 8017c5b0
// Size: 560 bytes

void DecrementerExceptionCallback(undefined4 param_1,undefined4 param_2)

{
  void *osAlarm;
  void *pvVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  undefined8 uVar5;
  undefined auStack_2d8 [712];
  
  uVar5 = __OSGetSystemTime();
  osAlarm = OSAlarm_8032ef60.handler;
  if (OSAlarm_8032ef60.handler == (void *)0x0) {
    OSLoadContext(param_2);
  }
  if (((uint)((ulonglong)uVar5 >> 0x20) ^ 0x80000000) <
      (uint)((uint)uVar5 < *(uint *)((int)osAlarm + 0xc)) +
      (*(uint *)((int)osAlarm + 8) ^ 0x80000000)) {
    uVar5 = __OSGetSystemTime();
    uVar3 = *(uint *)((int)osAlarm + 0xc) - (uint)uVar5;
    uVar2 = *(int *)((int)osAlarm + 8) -
            ((uint)(*(uint *)((int)osAlarm + 0xc) < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20))
            ^ 0x80000000;
    if (uVar2 < 0x80000000) {
      PPCMtdec(0);
    }
    else if (uVar2 < (uVar3 < 0x80000000) + 0x80000000) {
      PPCMtdec(uVar3);
    }
    else {
      PPCMtdec(0x7fffffff);
    }
    OSLoadContext(param_2);
  }
  OSAlarm_8032ef60.handler = *(void **)((int)osAlarm + 0x14);
  if (OSAlarm_8032ef60.handler == (void *)0x0) {
    OSAlarm_8032ef60.tag = 0;
  }
  else {
    *(undefined4 *)((int)OSAlarm_8032ef60.handler + 0x10) = 0;
  }
                    /* WARNING: Load size is inaccurate */
  pcVar4 = *osAlarm;
  *(undefined4 *)osAlarm = 0;
  if (0x80000000 <
      (uint)(*(int *)((int)osAlarm + 0x1c) != 0) + (*(uint *)((int)osAlarm + 0x18) ^ 0x80000000)) {
    InsertAlarm((OSAlarm *)osAlarm,0x80000000,0,0,pcVar4);
  }
  pvVar1 = OSAlarm_8032ef60.handler;
  if (OSAlarm_8032ef60.handler != (void *)0x0) {
    uVar5 = __OSGetSystemTime();
    uVar2 = *(uint *)((int)pvVar1 + 0xc);
    uVar3 = uVar2 - (uint)uVar5;
    uVar2 = *(int *)((int)pvVar1 + 8) -
            ((uint)(uVar2 < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000;
    if (uVar2 < 0x80000000) {
      PPCMtdec(0);
    }
    else if (uVar2 < (uVar3 < 0x80000000) + 0x80000000) {
      PPCMtdec(uVar3);
    }
    else {
      PPCMtdec(0x7fffffff);
    }
  }
  OSDisableScheduler();
  OSClearContext(auStack_2d8);
  OSSetCurrentContext(auStack_2d8);
  (*pcVar4)(osAlarm,param_2);
  OSClearContext(auStack_2d8);
  OSSetCurrentContext(param_2);
  OSEnableScheduler();
  __OSReschedule();
  OSLoadContext(param_2);
  return;
}

