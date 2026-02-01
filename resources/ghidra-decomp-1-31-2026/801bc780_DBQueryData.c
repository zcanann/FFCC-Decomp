// Function: DBQueryData
// Entry: 801bc780
// Size: 156 bytes

uint DBQueryData(void)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_10 [3];
  
  DAT_8032f3b4 = 0;
  if (DAT_8032f3ac == 0) {
    uVar2 = OSDisableInterrupts();
    DBGReadStatus(local_10);
    uVar1 = local_10[0];
    if ((local_10[0] & 1) != 0) {
      DBGReadMailbox(local_10);
      uVar1 = local_10[0] & 0x1fffffff;
      if ((local_10[0] & 0x1f000000) == 0x1f000000) {
        DAT_8032f3ac = local_10[0] & 0x7fff;
        DAT_8032f3b4 = 1;
        DAT_8032f3a8 = uVar1;
      }
    }
    local_10[0] = uVar1;
    OSRestoreInterrupts(uVar2);
  }
  return DAT_8032f3ac;
}

