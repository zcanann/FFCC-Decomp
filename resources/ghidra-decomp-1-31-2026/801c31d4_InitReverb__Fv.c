// Function: InitReverb__Fv
// Entry: 801c31d4
// Size: 68 bytes

void InitReverb__Fv(void)

{
  DAT_8032f4ac = RedNew__Fi(0x18);
  memset(DAT_8032f4ac,0,0x18);
  DAT_8032f4b0 = RedNew__Fi(4);
  return;
}

