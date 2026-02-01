// Function: GXSetDispCopyGamma
// Entry: 801a31c4
// Size: 28 bytes

void GXSetDispCopyGamma(int param_1)

{
  *(uint *)(DAT_80333828 + 0x1ec) = *(uint *)(DAT_80333828 + 0x1ec) & 0xfffffe7f | param_1 << 7;
  return;
}

