// Function: __GXFlushTextureState
// Entry: 801a51b4
// Size: 36 bytes

void __GXFlushTextureState(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x124);
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

