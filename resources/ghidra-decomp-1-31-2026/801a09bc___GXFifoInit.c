// Function: __GXFifoInit
// Entry: 801a09bc
// Size: 76 bytes

void __GXFifoInit(void)

{
  __OSSetInterruptHandler(0x11,GXCPInterruptHandler);
  __OSUnmaskInterrupts(0x4000);
  DAT_8032f318 = OSGetCurrentThread();
  DAT_8032f320 = 0;
  DAT_8032f310 = 0;
  DAT_8032f314 = 0;
  return;
}

