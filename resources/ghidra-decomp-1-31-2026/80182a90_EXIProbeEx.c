// Function: EXIProbeEx
// Entry: 80182a90
// Size: 180 bytes

undefined4 EXIProbeEx(int param_1)

{
  int iVar1;
  undefined4 uVar2;
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
  if (iVar1 == 0) {
    if ((&DAT_800030c0)[param_1] == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

