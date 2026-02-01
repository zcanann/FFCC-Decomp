// Function: DBInitInterrupts
// Entry: 801bc81c
// Size: 84 bytes

void DBInitInterrupts(void)

{
  __OSMaskInterrupts(0x18000);
  __OSMaskInterrupts(0x40);
  DAT_8032f3a4 = MWCallback;
  __OSSetInterruptHandler(0x19,DBGHandler);
  __OSUnmaskInterrupts(0x40);
  return;
}

