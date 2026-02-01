// Function: SIDisablePolling
// Entry: 80184dac
// Size: 108 bytes

uint SIDisablePolling(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_80217308;
  if (param_1 != 0) {
    OSDisableInterrupts();
    uVar1 = DAT_80217308 & ~(param_1 >> 0x18 & 0xf0);
    DAT_cc006430 = uVar1;
    DAT_80217308 = uVar1;
    OSRestoreInterrupts();
  }
  return uVar1;
}

