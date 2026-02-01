// Function: GXSetAlphaCompare
// Entry: 801a56dc
// Size: 84 bytes

void GXSetAlphaCompare(uint param_1,uint param_2,int param_3,int param_4,uint param_5)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = ((param_5 & 0xff) << 8 | param_2 & 0xff | 0xf3000000 | (param_1 & 0xffc7) << 0x10 |
                 param_4 << 0x13) & 0xff3fffff | param_3 << 0x16;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

