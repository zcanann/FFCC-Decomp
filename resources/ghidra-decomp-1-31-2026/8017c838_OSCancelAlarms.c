// Function: OSCancelAlarms
// Entry: 8017c838
// Size: 176 bytes

void OSCancelAlarms(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  void *pvVar3;
  
  if (param_1 != 0) {
    uVar1 = OSDisableInterrupts();
    pvVar2 = OSAlarm_8032ef60.handler;
    if (OSAlarm_8032ef60.handler == (void *)0x0) {
      pvVar3 = (void *)0x0;
    }
    else {
      pvVar3 = *(void **)((int)OSAlarm_8032ef60.handler + 0x14);
    }
    while (pvVar2 != (void *)0x0) {
      if (*(int *)((int)pvVar2 + 4) == param_1) {
        OSCancelAlarm();
      }
      pvVar2 = pvVar3;
      if (pvVar3 == (void *)0x0) {
        pvVar3 = (void *)0x0;
      }
      else {
        pvVar3 = *(void **)((int)pvVar3 + 0x14);
      }
    }
    OSRestoreInterrupts(uVar1);
  }
  return;
}

