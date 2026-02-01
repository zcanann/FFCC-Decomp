// Function: gdev_cc_open
// Entry: 801af548
// Size: 20 bytes

undefined4 gdev_cc_open(void)

{
  if (DAT_8032f368 != 0) {
    return 0xffffd8eb;
  }
  DAT_8032f368 = 1;
  return 0;
}

