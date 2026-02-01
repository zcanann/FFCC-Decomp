// Function: GXClearVtxDesc
// Entry: 801a1130
// Size: 56 bytes

void GXClearVtxDesc(void)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(undefined4 *)(DAT_80333828 + 0x14) = 0;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xfffff9ff | 0x200;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  *(undefined *)(iVar1 + 0x41c) = 0;
  *(undefined *)(iVar1 + 0x41d) = 0;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 8;
  return;
}

