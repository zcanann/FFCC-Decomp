// Function: EXIDeselect
// Entry: 80182e38
// Size: 272 bytes

undefined4 EXIDeselect(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 0x10 + 0x29a] & 4) == 0) {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  else {
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xfffffffb;
    uVar3 = (&DAT_cc006800)[param_1 * 5];
    (&DAT_cc006800)[param_1 * 5] = uVar3 & 0x405;
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 8) != 0) {
      if (param_1 == 1) {
        __OSUnmaskInterrupts(0x20000);
      }
      else if ((param_1 < 1) && (-1 < param_1)) {
        __OSUnmaskInterrupts(0x100000);
      }
    }
    OSRestoreInterrupts(uVar1);
    if ((param_1 == 2) || ((uVar3 & 0x80) == 0)) {
      uVar1 = 1;
    }
    else {
      iVar2 = __EXIProbe(param_1);
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

