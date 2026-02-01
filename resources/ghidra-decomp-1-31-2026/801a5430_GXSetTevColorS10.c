// Function: GXSetTevColorS10
// Entry: 801a5430
// Size: 116 bytes

void GXSetTevColorS10(int param_1,short *param_2)

{
  uint uVar1;
  
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (int)*param_2 & 0x7ffU | ((int)param_2[3] & 0x7ffU) << 0xc |
                 (param_1 * 2 + 0xe0) * 0x1000000;
  DAT_cc008000._0_1_ = 0x61;
  uVar1 = (int)param_2[2] & 0x7ffU | ((int)param_2[1] & 0x7ffU) << 0xc |
          (param_1 * 2 + 0xe1) * 0x1000000;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

