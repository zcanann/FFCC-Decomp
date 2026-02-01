// Function: EXILock
// Entry: 801834cc
// Size: 244 bytes

undefined4 EXILock(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1 * 0x40 + -0x7fcf3970;
  uVar1 = OSDisableInterrupts();
  if ((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) == 0) {
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 0x10;
    FatalContext[param_1 * 0x10 + 0x29d] = param_2;
    SetExiInterruptMask(param_1,iVar4);
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else {
    if (param_3 != 0) {
      iVar3 = FatalContext[param_1 * 0x10 + 0x2a0];
      iVar2 = iVar4;
      iVar5 = iVar3;
      if (0 < iVar3) {
        do {
          if (*(int *)(iVar2 + 0x28) == param_2) {
            OSRestoreInterrupts(uVar1);
            return 0;
          }
          iVar2 = iVar2 + 8;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      *(int *)(iVar4 + iVar3 * 8 + 0x2c) = param_3;
      *(int *)(iVar4 + FatalContext[param_1 * 0x10 + 0x2a0] * 8 + 0x28) = param_2;
      FatalContext[param_1 * 0x10 + 0x2a0] = FatalContext[param_1 * 0x10 + 0x2a0] + 1;
    }
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  return uVar1;
}

