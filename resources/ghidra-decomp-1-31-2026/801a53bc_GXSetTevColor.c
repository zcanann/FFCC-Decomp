// Function: GXSetTevColor
// Entry: 801a53bc
// Size: 116 bytes

void GXSetTevColor(int param_1,byte *param_2)

{
  uint uVar1;
  
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (uint)*param_2 | (uint)param_2[3] << 0xc | (param_1 * 2 + 0xe0) * 0x1000000;
  DAT_cc008000._0_1_ = 0x61;
  uVar1 = (uint)param_2[2] | (uint)param_2[1] << 0xc | (param_1 * 2 + 0xe1) * 0x1000000;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

