// Function: __GXSetVAT
// Entry: 801a1838
// Size: 156 bytes

void __GXSetVAT(void)

{
  int iVar1;
  byte bVar2;
  
  bVar2 = 0;
  iVar1 = 0;
  while( true ) {
    if (7 < bVar2) break;
    if (((uint)*(byte *)(DAT_80333828 + 0x4f3) & 1 << (uint)bVar2) != 0) {
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x70;
      DAT_cc008000 = *(undefined4 *)(DAT_80333828 + iVar1 + 0x1c);
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x80;
      DAT_cc008000 = *(undefined4 *)(DAT_80333828 + iVar1 + 0x3c);
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x90;
      DAT_cc008000 = *(undefined4 *)(DAT_80333828 + iVar1 + 0x5c);
    }
    iVar1 = iVar1 + 4;
    bVar2 = bVar2 + 1;
  }
  *(undefined *)(DAT_80333828 + 0x4f3) = 0;
  return;
}

