// Function: SIEnablePollingInterrupt
// Entry: 801846fc
// Size: 152 bytes

bool SIEnablePollingInterrupt(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  OSDisableInterrupts();
  uVar1 = DAT_cc006434;
  if (param_1 == 0) {
    uVar2 = uVar1 & 0xf7ffffff;
  }
  else {
    DAT_8030c930 = 0;
    uVar2 = uVar1 | 0x8000000;
    DAT_8030c934 = 0;
    DAT_8030c938 = 0;
    DAT_8030c93c = 0;
  }
  DAT_cc006434 = uVar2 & 0x7ffffffe;
  OSRestoreInterrupts();
  return (uVar1 & 0x8000000) != 0;
}

