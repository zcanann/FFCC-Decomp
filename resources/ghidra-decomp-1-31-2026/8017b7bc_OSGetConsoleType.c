// Function: OSGetConsoleType
// Entry: 8017b7bc
// Size: 40 bytes

int OSGetConsoleType(void)

{
  int iVar1;
  
  if ((DAT_8032ef20 == 0) || (iVar1 = *(int *)(DAT_8032ef20 + 0x2c), iVar1 == 0)) {
    iVar1 = 0x10000002;
  }
  return iVar1;
}

