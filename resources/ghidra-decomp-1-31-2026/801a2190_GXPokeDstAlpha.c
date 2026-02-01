// Function: GXPokeDstAlpha
// Entry: 801a2190
// Size: 20 bytes

void GXPokeDstAlpha(int param_1,ushort param_2)

{
  *(ushort *)(DAT_8032f2f0 + 4) = param_2 & 0xff | (ushort)(param_1 << 8);
  return;
}

