// Function: ReverbAreaAlloc__FUl
// Entry: 801c3154
// Size: 88 bytes

void ReverbAreaAlloc__FUl(int param_1)

{
  *DAT_8032f4b0 = *DAT_8032f4b0 + param_1;
  DAT_8032f4b0[1] = DAT_8032f4b0[1] + (param_1 + 0x1fU & 0xffffffe0);
  RedNew__Fi();
  return;
}

