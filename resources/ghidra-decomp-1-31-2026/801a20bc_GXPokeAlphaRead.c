// Function: GXPokeAlphaRead
// Entry: 801a20bc
// Size: 20 bytes

void GXPokeAlphaRead(ushort param_1)

{
  *(ushort *)(DAT_8032f2f0 + 8) = param_1 & 0xfffb | 4;
  return;
}

