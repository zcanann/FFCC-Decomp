// Function: __OSInitMemoryProtection
// Entry: 8017ef94
// Size: 280 bytes

void __OSInitMemoryProtection(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = DAT_800000f0;
  uVar2 = OSDisableInterrupts();
  DAT_cc004020 = 0;
  DAT_cc004010 = 0xff;
  __OSMaskInterrupts(0xf0000000);
  __OSSetInterruptHandler(0,MEMIntrruptHandler);
  __OSSetInterruptHandler(1,MEMIntrruptHandler);
  __OSSetInterruptHandler(2,MEMIntrruptHandler);
  __OSSetInterruptHandler(3,MEMIntrruptHandler);
  __OSSetInterruptHandler(4,MEMIntrruptHandler);
  OSRegisterResetFunction(&PTR_OnReset_80217140);
  if ((DAT_800000f0 < DAT_80000028) && (DAT_800000f0 == 0x1800000)) {
    DCInvalidateRange(0x81800000,0x1800000);
    DAT_cc004028 = 2;
  }
  if (uVar1 < 0x1800001) {
    RealMode(Config24MB);
  }
  else if (uVar1 < 0x3000001) {
    RealMode(Config48MB);
  }
  __OSUnmaskInterrupts(0x8000000);
  OSRestoreInterrupts(uVar2);
  return;
}

