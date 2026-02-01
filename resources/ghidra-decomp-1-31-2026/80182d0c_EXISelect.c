// Function: EXISelect
// Entry: 80182d0c
// Size: 300 bytes

undefined4 EXISelect(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = OSDisableInterrupts();
  if (((FatalContext[param_1 * 0x10 + 0x29a] & 4) == 0) &&
     ((param_1 == 2 ||
      ((((param_2 != 0 || ((FatalContext[param_1 * 0x10 + 0x29a] & 8) != 0)) ||
        (iVar2 = __EXIProbe(param_1), iVar2 != 0)) &&
       (((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) != 0 &&
        (FatalContext[param_1 * 0x10 + 0x29d] == param_2)))))))) {
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 4;
    (&DAT_cc006800)[param_1 * 5] =
         (&DAT_cc006800)[param_1 * 5] & 0x405 | (1 << param_2) << 7 | param_3 << 4;
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 8) != 0) {
      if (param_1 == 1) {
        __OSMaskInterrupts(0x20000);
      }
      else if ((param_1 < 1) && (-1 < param_1)) {
        __OSMaskInterrupts(0x100000);
      }
    }
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  return uVar1;
}

