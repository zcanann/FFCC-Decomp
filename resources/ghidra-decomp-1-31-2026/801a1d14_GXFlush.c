// Function: GXFlush
// Entry: 801a1d14
// Size: 92 bytes

void GXFlush(void)

{
  if (*(int *)(DAT_80333828 + 0x4f4) != 0) {
    __GXSetDirtyState();
  }
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  PPCSync();
  return;
}

