// Function: ddh_cc_open
// Entry: 801aef94
// Size: 36 bytes

undefined4 ddh_cc_open(void)

{
  if (DAT_8032f360 != 0) {
    return 0xffffd8eb;
  }
  DAT_8032f360 = 1;
  return 0;
}

