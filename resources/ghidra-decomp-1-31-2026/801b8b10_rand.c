// Function: rand
// Entry: 801b8b10
// Size: 32 bytes

uint rand(void)

{
  DAT_8032ec10 = DAT_8032ec10 * 0x41c64e6d + 0x3039;
  return DAT_8032ec10 >> 0x10 & 0x7fff;
}

