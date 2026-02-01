// Function: GXSetCopyClear
// Entry: 801a2f34
// Size: 104 bytes

void GXSetCopyClear(undefined *param_1,uint param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = CONCAT11(param_1[3],*param_1) | 0x4f000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(ushort *)(param_1 + 1) | 0x50000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_2 & 0xffffff | 0x51000000;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

