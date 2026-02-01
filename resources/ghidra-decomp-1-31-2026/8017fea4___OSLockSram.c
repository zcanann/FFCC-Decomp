// Function: __OSLockSram
// Entry: 8017fea4
// Size: 92 bytes

undefined4 __OSLockSram(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = 0x8030bc40;
  uVar1 = OSDisableInterrupts();
  if (FatalContext[0x15] == 0) {
    FatalContext[0x15] = 1;
    FatalContext[0x14] = uVar1;
  }
  else {
    OSRestoreInterrupts();
    uVar2 = 0;
  }
  return uVar2;
}

