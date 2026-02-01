// Function: LCEnable
// Entry: 8017d0c8
// Size: 56 bytes

void LCEnable(void)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  __LCEnable();
  OSRestoreInterrupts(uVar1);
  return;
}

