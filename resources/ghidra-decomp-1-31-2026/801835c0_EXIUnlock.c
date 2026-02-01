// Function: EXIUnlock
// Entry: 801835c0
// Size: 220 bytes

undefined4 EXIUnlock(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  iVar1 = param_1 * 0x40;
  uVar3 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) == 0) {
    OSRestoreInterrupts(uVar3);
    uVar3 = 0;
  }
  else {
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xffffffef;
    SetExiInterruptMask(param_1,iVar1 + -0x7fcf3970);
    if (0 < (int)FatalContext[param_1 * 0x10 + 0x2a0]) {
      pcVar4 = (code *)FatalContext[param_1 * 0x10 + 0x2a2];
      iVar2 = FatalContext[param_1 * 0x10 + 0x2a0] + -1;
      FatalContext[param_1 * 0x10 + 0x2a0] = iVar2;
      if (0 < iVar2) {
        memmove(iVar1 + -0x7fcf3948,iVar1 + -0x7fcf3940,FatalContext[param_1 * 0x10 + 0x2a0] << 3);
      }
      (*pcVar4)(param_1,0);
    }
    OSRestoreInterrupts(uVar3);
    uVar3 = 1;
  }
  return uVar3;
}

