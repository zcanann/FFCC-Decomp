// Function: __AXGetCommandListAddress
// Entry: 80191f84
// Size: 60 bytes

undefined * __AXGetCommandListAddress(void)

{
  int iVar1;
  
  iVar1 = DAT_8032f228 * 0x300;
  DAT_8032f228 = DAT_8032f228 + 1 & 1;
  DAT_8032f22c = &DAT_8030fae0 + DAT_8032f228 * 0x300;
  return &DAT_8030fae0 + iVar1;
}

