// Function: InitializeUART
// Entry: 80183dd4
// Size: 112 bytes

undefined4 InitializeUART(void)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (DAT_8032effc == -0x5a00ffa6) {
    uVar1 = 0;
  }
  else {
    uVar2 = OSGetConsoleType();
    if ((uVar2 & 0x10000000) == 0) {
      DAT_8032eff8 = 0;
      uVar1 = 2;
    }
    else {
      DAT_8032eff8 = 0xa5ff005a;
      DAT_8032eff0 = 0;
      uVar1 = 0;
      DAT_8032eff4 = 1;
    }
  }
  return uVar1;
}

