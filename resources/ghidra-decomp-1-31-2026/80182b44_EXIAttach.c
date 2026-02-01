// Function: EXIAttach
// Entry: 80182b44
// Size: 268 bytes

undefined4 EXIAttach(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined auStack_24 [16];
  
  iVar1 = __EXIProbe(param_1);
  if ((iVar1 != 0) && (FatalContext[param_1 * 0x10 + 0x29f] == 0)) {
    EXIGetID(param_1,0,auStack_24);
  }
  uVar2 = OSDisableInterrupts();
  if (FatalContext[param_1 * 0x10 + 0x29f] == 0) {
    OSRestoreInterrupts(uVar2);
    uVar3 = 0;
  }
  else {
    uVar3 = OSDisableInterrupts();
    if (((FatalContext[param_1 * 0x10 + 0x29a] & 8) == 0) &&
       (iVar1 = __EXIProbe(param_1), iVar1 != 0)) {
      EXIClearInterrupts(param_1,1,0,0);
      FatalContext[param_1 * 0x10 + 0x299] = param_2;
      __OSUnmaskInterrupts(0x100000 >> param_1 * 3);
      FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 8;
      OSRestoreInterrupts(uVar3);
      uVar3 = 1;
    }
    else {
      OSRestoreInterrupts(uVar3);
      uVar3 = 0;
    }
    OSRestoreInterrupts(uVar2);
  }
  return uVar3;
}

