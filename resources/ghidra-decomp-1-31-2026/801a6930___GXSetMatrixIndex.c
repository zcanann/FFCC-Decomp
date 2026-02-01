// Function: __GXSetMatrixIndex
// Entry: 801a6930
// Size: 132 bytes

void __GXSetMatrixIndex(int param_1)

{
  if (param_1 < 5) {
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x30;
    DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x80);
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1018;
    DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x80);
  }
  else {
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x40;
    DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x84);
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1019;
    DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x84);
  }
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

