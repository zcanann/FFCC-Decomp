// Function: GXSetScissorBoxOffset
// Entry: 801a68c8
// Size: 64 bytes

void GXSetScissorBoxOffset(int param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 + 0x156U >> 1 & 0x7ff003ff | (param_2 + 0x156) * 0x200 & 0xfffffc00U) &
                 0xffffff | 0x59000000;
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

