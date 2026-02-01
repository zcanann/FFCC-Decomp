// Function: EXIDetach
// Entry: 80182c50
// Size: 188 bytes

undefined4 EXIDetach(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 0x10 + 0x29a] & 8) == 0) {
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else if (((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) == 0) ||
          (FatalContext[param_1 * 0x10 + 0x29d] != 0)) {
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xfffffff7;
    __OSMaskInterrupts(0x500000 >> param_1 * 3);
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  return uVar1;
}

