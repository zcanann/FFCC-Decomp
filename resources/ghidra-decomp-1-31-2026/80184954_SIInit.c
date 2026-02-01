// Function: SIInit
// Entry: 80184954
// Size: 180 bytes

void SIInit(void)

{
  uint uVar1;
  
  OSRegisterVersion(DAT_8032eac0);
  DAT_8030c7b0 = 0xffffffff;
  DAT_8030c790 = 0xffffffff;
  DAT_8030c770 = 0xffffffff;
  FatalContext[0x2c7] = 0xffffffff;
  DAT_80217308 = 0;
  SISetSamplingRate(0);
  do {
    uVar1 = DAT_cc006434;
  } while ((uVar1 & 1) != 0);
  DAT_cc006434 = 0x80000000;
  __OSSetInterruptHandler(0x14,SIInterruptHandler);
  __OSUnmaskInterrupts(0x800);
  SIGetType(0);
  SIGetType(1);
  SIGetType(2);
  SIGetType(3);
  return;
}

