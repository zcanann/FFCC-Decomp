// Function: SIRegisterPollingHandler
// Entry: 80184794
// Size: 204 bytes

undefined4 SIRegisterPollingHandler(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = OSDisableInterrupts();
  piVar3 = &DAT_8030c8f0;
  iVar4 = 4;
  piVar2 = piVar3;
  do {
    if (*piVar2 == param_1) {
      OSRestoreInterrupts(uVar1);
      return 1;
    }
    piVar2 = piVar2 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar5 = 4;
  iVar4 = 0;
  do {
    if (*piVar3 == 0) {
      (&DAT_8030c8f0)[iVar4] = param_1;
      SIEnablePollingInterrupt(1);
      OSRestoreInterrupts(uVar1);
      return 1;
    }
    piVar3 = piVar3 + 1;
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  OSRestoreInterrupts(uVar1);
  return 0;
}

