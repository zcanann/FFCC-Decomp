// Function: IsGdev__7CSystemFv
// Entry: 800214b4
// Size: 36 bytes

uint IsGdev__7CSystemFv(void)

{
  uint uVar1;
  
  uVar1 = OSGetConsoleType();
  return uVar1 >> 0x1c & 1;
}

