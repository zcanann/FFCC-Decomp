// Function: __GXPEInit
// Entry: 801a23a4
// Size: 128 bytes

void __GXPEInit(void)

{
  __OSSetInterruptHandler(0x12,GXTokenInterruptHandler);
  __OSSetInterruptHandler(0x13,GXFinishInterruptHandler);
  OSInitThreadQueue(&DAT_8032f33c);
  __OSUnmaskInterrupts(0x2000);
  __OSUnmaskInterrupts(0x1000);
  *(ushort *)(DAT_8032f2f0 + 10) = *(ushort *)(DAT_8032f2f0 + 10) & 0xfff0 | 0xf;
  return;
}

