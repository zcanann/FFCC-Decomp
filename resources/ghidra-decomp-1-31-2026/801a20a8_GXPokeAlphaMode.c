// Function: GXPokeAlphaMode
// Entry: 801a20a8
// Size: 20 bytes

void GXPokeAlphaMode(int param_1,ushort param_2)

{
  *(ushort *)(DAT_8032f2f0 + 6) = (ushort)(param_1 << 8) | param_2 & 0xff;
  return;
}

