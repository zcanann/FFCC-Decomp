// Function: GXPokeAlphaUpdate
// Entry: 801a20d0
// Size: 28 bytes

void GXPokeAlphaUpdate(int param_1)

{
  *(ushort *)(DAT_8032f2f0 + 2) =
       *(ushort *)(DAT_8032f2f0 + 2) & 0xffef | (ushort)(param_1 << 4) & 0xff0;
  return;
}

