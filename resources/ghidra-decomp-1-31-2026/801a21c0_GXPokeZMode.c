// Function: GXPokeZMode
// Entry: 801a21c0
// Size: 40 bytes

void GXPokeZMode(ushort param_1,int param_2,int param_3)

{
  *DAT_8032f2f0 =
       (param_1 & 0xf1 | (ushort)(param_2 << 1)) & 0xffef | (ushort)(param_3 << 4) & 0xff0;
  return;
}

