// Function: OSCancelAlarm
// Entry: 8017c494
// Size: 284 bytes

void OSCancelAlarm(int *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  void *pvVar4;
  undefined8 uVar5;
  
  uVar1 = OSDisableInterrupts();
  if (*param_1 == 0) {
    OSRestoreInterrupts(uVar1);
  }
  else {
    pvVar4 = (void *)param_1[5];
    if (pvVar4 == (void *)0x0) {
      OSAlarm_8032ef60.tag = param_1[4];
    }
    else {
      *(int *)((int)pvVar4 + 0x10) = param_1[4];
    }
    if (param_1[4] == 0) {
      OSAlarm_8032ef60.handler = pvVar4;
      if (pvVar4 != (void *)0x0) {
        uVar5 = __OSGetSystemTime();
        uVar3 = *(uint *)((int)pvVar4 + 0xc) - (uint)uVar5;
        uVar2 = *(int *)((int)pvVar4 + 8) -
                ((uint)(*(uint *)((int)pvVar4 + 0xc) < (uint)uVar5) +
                (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000;
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
    }
    else {
      *(void **)(param_1[4] + 0x14) = pvVar4;
    }
    *param_1 = 0;
    OSRestoreInterrupts(uVar1);
  }
  return;
}

