// Function: GXClearBoundingBox
// Entry: 801a34b8
// Size: 56 bytes

void GXClearBoundingBox(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x550003ff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x560003ff;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

