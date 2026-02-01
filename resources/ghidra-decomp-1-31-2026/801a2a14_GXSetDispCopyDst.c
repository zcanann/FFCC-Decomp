// Function: GXSetDispCopyDst
// Entry: 801a2a14
// Size: 60 bytes

void GXSetDispCopyDst(uint param_1)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = DAT_80333828;
  *(undefined4 *)(DAT_80333828 + 0x1e8) = 0;
  puVar2 = (uint *)(iVar1 + 0x1e8);
  *puVar2 = *(uint *)(iVar1 + 0x1e8) & 0xfffffc00 | (int)((param_1 & 0x7fff) << 1) >> 5;
  *puVar2 = *puVar2 & 0xffffff | 0x4d000000;
  return;
}

