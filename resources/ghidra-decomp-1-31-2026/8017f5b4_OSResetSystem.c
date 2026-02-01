// Function: OSResetSystem
// Entry: 8017f5b4
// Size: 648 bytes

void OSResetSystem(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 unaff_r31;
  
  OSDisableScheduler();
  __OSStopAudioSystem();
  if (param_1 == 2) {
    unaff_r31 = __PADDisableRecalibration(1);
  }
  do {
    puVar6 = DAT_8032efa8;
    for (uVar5 = 0; (puVar6 != (undefined4 *)0x0 && (uVar5 == 0)); uVar5 = uVar5 >> 5) {
      uVar3 = (*(code *)*puVar6)(0);
      uVar5 = countLeadingZeros(uVar3);
      puVar6 = (undefined4 *)puVar6[2];
    }
    uVar3 = __OSSyncSram();
    uVar2 = countLeadingZeros(uVar3);
  } while (uVar5 != 0 || uVar2 >> 5 != 0);
  if ((param_1 == 1) && (param_3 != 0)) {
    iVar4 = __OSLockSram();
    *(byte *)(iVar4 + 0x13) = *(byte *)(iVar4 + 0x13) | 0x40;
    __OSUnlockSram(1);
    do {
      iVar4 = __OSSyncSram();
    } while (iVar4 == 0);
  }
  OSDisableInterrupts();
  puVar6 = DAT_8032efa8;
  for (uVar5 = 0; (puVar6 != (undefined4 *)0x0 && (uVar5 == 0)); uVar5 = uVar5 >> 5) {
    uVar3 = (*(code *)*puVar6)(1);
    uVar5 = countLeadingZeros(uVar3);
    puVar6 = (undefined4 *)puVar6[2];
  }
  __OSSyncSram();
  LCDisable();
  if (param_1 == 1) {
    OSDisableInterrupts();
    DAT_cc002002 = 0;
    ICFlashInvalidate();
    Reset(param_2 << 3);
    iVar4 = DAT_800000dc;
  }
  else {
    iVar4 = DAT_800000dc;
    if (param_1 == 0) {
      while (iVar4 != 0) {
        uVar1 = *(ushort *)(iVar4 + 0x2c8);
        iVar4 = *(int *)(iVar4 + 0x2fc);
        if ((uVar1 == 4) || ((uVar1 < 4 && (uVar1 == 1)))) {
          OSCancelThread();
        }
      }
      OSEnableScheduler();
      __OSReboot(param_2,param_3);
      iVar4 = DAT_800000dc;
    }
  }
  while (iVar4 != 0) {
    uVar1 = *(ushort *)(iVar4 + 0x2c8);
    iVar4 = *(int *)(iVar4 + 0x2fc);
    if ((uVar1 == 4) || ((uVar1 < 4 && (uVar1 == 1)))) {
      OSCancelThread();
    }
  }
  memset(&DAT_80000040,0,0x8c);
  memset(&DAT_800000d4,0,0x14);
  memset(&DAT_800000f4,0,4);
  memset(&DAT_80003000,0,0xc0);
  memset(&DAT_800030c8,0,0xc);
  memset(&DAT_800030e2,0,1);
  __PADDisableRecalibration(unaff_r31);
  return;
}

