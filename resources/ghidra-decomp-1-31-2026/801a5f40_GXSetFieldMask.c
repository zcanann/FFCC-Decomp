// Function: GXSetFieldMask
// Entry: 801a5f40
// Size: 56 bytes

void GXSetFieldMask(uint param_1,uint param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_2 & 0xfd | (param_1 & 0xff) << 1 | 0x44000000;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

