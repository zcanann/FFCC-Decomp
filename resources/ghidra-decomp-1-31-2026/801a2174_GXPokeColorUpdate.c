// Function: GXPokeColorUpdate
// Entry: 801a2174
// Size: 28 bytes

void GXPokeColorUpdate(int param_1)

{
  *(ushort *)(DAT_8032f2f0 + 2) =
       *(ushort *)(DAT_8032f2f0 + 2) & 0xfff7 | (ushort)(param_1 << 3) & 0x7f8;
  return;
}

