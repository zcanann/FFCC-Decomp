// Function: __check_pad3
// Entry: 80003100
// Size: 64 bytes

void __check_pad3(void)

{
  if ((DAT_800030e4 & 0xeef) == 0xeef) {
    OSResetSystem(0,0,0);
  }
  return;
}

