// Function: GXPokeDither
// Entry: 801a21a4
// Size: 28 bytes

void GXPokeDither(int param_1)

{
  *(ushort *)(DAT_8032f2f0 + 2) =
       *(ushort *)(DAT_8032f2f0 + 2) & 0xfffb | (ushort)(param_1 << 2) & 0x3fc;
  return;
}

