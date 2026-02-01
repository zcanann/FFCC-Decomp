// Function: __AXGetCurrentProfile
// Entry: 80193e28
// Size: 72 bytes

int __AXGetCurrentProfile(void)

{
  int iVar1;
  
  if (DAT_8032f2ac != 0) {
    iVar1 = DAT_8032f2a8 * 0x38;
    DAT_8032f2a8 = (DAT_8032f2a8 + 1U) - ((DAT_8032f2a8 + 1U) / DAT_8032f2a4) * DAT_8032f2a4;
    return DAT_8032f2a0 + iVar1;
  }
  return 0;
}

