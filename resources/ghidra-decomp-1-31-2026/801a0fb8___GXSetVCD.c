// Function: __GXSetVCD
// Entry: 801a0fb8
// Size: 84 bytes

void __GXSetVCD(void)

{
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = 0x50;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x14);
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = 0x60;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x18);
  __GXXfVtxSpecs();
  return;
}

