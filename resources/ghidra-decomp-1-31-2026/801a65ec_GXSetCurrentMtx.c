// Function: GXSetCurrentMtx
// Entry: 801a65ec
// Size: 56 bytes

void GXSetCurrentMtx(uint param_1)

{
  *(uint *)(DAT_80333828 + 0x80) = *(uint *)(DAT_80333828 + 0x80) & 0xffffffc0 | param_1;
  __GXSetMatrixIndex(0);
  return;
}

