// Function: SIUnregisterPollingHandler
// Entry: 80184860
// Size: 244 bytes

undefined4 SIUnregisterPollingHandler(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  uVar1 = OSDisableInterrupts();
  piVar3 = &DAT_8030c8f0;
  iVar4 = 4;
  iVar2 = 0;
  do {
    if (*piVar3 == param_1) {
      (&DAT_8030c8f0)[iVar2] = 0;
      iVar2 = 0;
      if ((((DAT_8030c8f0 == 0) && (iVar2 = 1, DAT_8030c8f4 == 0)) && (iVar2 = 2, DAT_8030c8f8 == 0)
          ) && (iVar2 = 3, DAT_8030c8fc == 0)) {
        iVar2 = 4;
      }
      if (iVar2 == 4) {
        SIEnablePollingInterrupt(0);
      }
      OSRestoreInterrupts(uVar1);
      return 1;
    }
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OSRestoreInterrupts(uVar1);
  return 0;
}

