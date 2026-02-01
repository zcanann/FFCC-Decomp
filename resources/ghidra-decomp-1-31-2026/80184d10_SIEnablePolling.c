// Function: SIEnablePolling
// Entry: 80184d10
// Size: 156 bytes

uint SIEnablePolling(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_80217308;
  if (param_1 != 0) {
    OSDisableInterrupts();
    uVar1 = DAT_80217308 & ~(param_1 >> 0x1c) | param_1 >> 0x18 & (param_1 >> 0x1c | 0x3fffff0);
    DAT_cc006438 = 0x80000000;
    DAT_cc006430 = uVar1;
    DAT_80217308 = uVar1;
    OSRestoreInterrupts();
  }
  return uVar1;
}

