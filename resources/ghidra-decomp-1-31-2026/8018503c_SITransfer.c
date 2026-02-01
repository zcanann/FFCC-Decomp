// Function: SITransfer
// Entry: 8018503c
// Size: 364 bytes

undefined4
SITransfer(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6,int param_7,uint param_8)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined8 uVar7;
  
  uVar1 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 8 + 0x2c7] == -1) && (DAT_80217304 != param_1)) {
    uVar7 = __OSGetSystemTime();
    uVar2 = (uint)((ulonglong)uVar7 >> 0x20);
    uVar4 = (uint)uVar7;
    if (param_8 != 0 || param_7 != 0) {
      uVar7 = CONCAT44(param_7 + *(int *)(&DAT_8030c890 + param_1 * 8) +
                                 (uint)CARRY4(param_8,*(uint *)(&DAT_8030c894 + param_1 * 8)),
                       param_8 + *(uint *)(&DAT_8030c894 + param_1 * 8));
    }
    uVar6 = (uint)((ulonglong)uVar7 >> 0x20);
    uVar5 = (uint)uVar7;
    if ((uVar2 ^ 0x80000000) < (uint)(uVar4 < uVar5) + (uVar6 ^ 0x80000000)) {
      OSSetAlarm((OSAlarm *)(&DAT_8030c7d0 + param_1 * 0x28),0x80180000,
                 uVar6 - ((uVar5 < uVar4) + uVar2),uVar5 - uVar4,AlarmHandler);
    }
    else {
      iVar3 = __SITransfer(param_1,param_2,param_3,param_4,param_5,param_6);
      if (iVar3 != 0) {
        OSRestoreInterrupts(uVar1);
        return 1;
      }
    }
    FatalContext[param_1 * 8 + 0x2c7] = param_1;
    (&DAT_8030c754)[param_1 * 8] = param_2;
    (&DAT_8030c758)[param_1 * 8] = param_3;
    (&DAT_8030c75c)[param_1 * 8] = param_4;
    (&DAT_8030c760)[param_1 * 8] = param_5;
    (&DAT_8030c764)[param_1 * 8] = param_6;
    *(undefined8 *)(&DAT_8030c768 + param_1 * 8) = uVar7;
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  return uVar1;
}

