// Function: RedDmaSearchID__Fi
// Entry: 801be234
// Size: 168 bytes

undefined4 RedDmaSearchID__Fi(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  
  uVar2 = 0;
  uVar1 = OSDisableInterrupts();
  if (param_1 != 0) {
    piVar3 = &DAT_8032b860;
    do {
      if ((*piVar3 != 0) && ((param_1 == 0 || (*piVar3 == param_1)))) {
        uVar2 = 1;
        break;
      }
      piVar3 = piVar3 + 7;
    } while (piVar3 < &DAT_8032d460);
  }
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

