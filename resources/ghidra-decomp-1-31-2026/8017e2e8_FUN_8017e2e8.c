// Function: FUN_8017e2e8
// Entry: 8017e2e8
// Size: 88 bytes

ushort FUN_8017e2e8(void)

{
  ushort uVar1;
  
  if (DAT_8032eaa8 < 2) {
    return DAT_8032eaa8;
  }
  if (DAT_800000cc == 0) {
    uVar1 = DAT_cc00206e;
    DAT_8032eaa8 = (ushort)((uVar1 & 2) != 0);
  }
  else {
    DAT_8032eaa8 = 0;
  }
  return DAT_8032eaa8;
}

