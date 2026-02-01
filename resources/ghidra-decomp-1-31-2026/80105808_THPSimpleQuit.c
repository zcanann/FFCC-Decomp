// Function: THPSimpleQuit
// Entry: 80105808
// Size: 84 bytes

void THPSimpleQuit(void)

{
  undefined4 uVar1;
  
  LCDisable();
  uVar1 = OSDisableInterrupts();
  if (DAT_8032ee50 != 0) {
    AIRegisterDMACallback(DAT_8032ee50);
  }
  OSRestoreInterrupts(uVar1);
  DAT_8032ee48 = 0;
  return;
}

