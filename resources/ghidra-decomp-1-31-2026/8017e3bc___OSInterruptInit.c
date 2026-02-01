// Function: __OSInterruptInit
// Entry: 8017e3bc
// Size: 116 bytes

void __OSInterruptInit(void)

{
  OSAlarm_8032ef60.start._0_4_ = &DAT_80003040;
  memset(&DAT_80003040,0,0x80);
  DAT_800000c4 = 0;
  DAT_800000c8 = 0;
  DAT_cc003004 = 0xf0;
  __OSMaskInterrupts(0xffffffe0);
  __OSSetExceptionHandler(4,ExternalInterruptHandler);
  return;
}

