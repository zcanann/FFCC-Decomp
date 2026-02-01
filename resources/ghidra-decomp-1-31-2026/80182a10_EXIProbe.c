// Function: EXIProbe
// Entry: 80182a10
// Size: 128 bytes

int EXIProbe(int param_1)

{
  int iVar1;
  undefined auStack_c [4];
  
  iVar1 = __EXIProbe(param_1);
  if ((iVar1 != 0) && (FatalContext[param_1 * 0x10 + 0x29f] == 0)) {
    iVar1 = EXIGetID(param_1,0,auStack_c);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}

