// Function: __OSLockSramEx
// Entry: 8017ff00
// Size: 92 bytes

undefined4 __OSLockSramEx(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  if (FatalContext[0x15] == 0) {
    uVar2 = 0x8030bc54;
    FatalContext[0x15] = 1;
    FatalContext[0x14] = uVar1;
  }
  else {
    OSRestoreInterrupts();
    uVar2 = 0;
  }
  return uVar2;
}

