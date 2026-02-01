// Function: GXInvalidateTexAll
// Entry: 801a4660
// Size: 72 bytes

void GXInvalidateTexAll(void)

{
  __GXFlushTextureState();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x66001000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x66001100;
  __GXFlushTextureState();
  return;
}

