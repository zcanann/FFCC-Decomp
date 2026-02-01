// Function: GetMyEntryID__Fv
// Entry: 801bdcb8
// Size: 56 bytes

uint GetMyEntryID__Fv(void)

{
  DAT_8032f3bc = DAT_8032f3bc + 1 & 0x7fffffff;
  if (DAT_8032f3bc == 0) {
    DAT_8032f3bc = 1;
  }
  return DAT_8032f3bc;
}

