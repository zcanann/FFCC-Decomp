// Function: GXPixModeSync
// Entry: 801a2084
// Size: 36 bytes

void GXPixModeSync(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1dc);
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

