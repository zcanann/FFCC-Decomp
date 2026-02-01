// Function: __GXSetGenMode
// Entry: 801a27b0
// Size: 36 bytes

void __GXSetGenMode(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x204);
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

