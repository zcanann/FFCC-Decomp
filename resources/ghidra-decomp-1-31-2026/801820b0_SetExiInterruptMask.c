// Function: SetExiInterruptMask
// Entry: 801820b0
// Size: 244 bytes

void SetExiInterruptMask(int param_1,int *param_2)

{
  int iVar1;
  
  if (param_1 == 1) {
    if ((*param_2 == 0) || ((param_2[3] & 0x10U) != 0)) {
      __OSMaskInterrupts(0x80000);
    }
    else {
      __OSUnmaskInterrupts(0x80000);
    }
  }
  else if (param_1 < 1) {
    if (-1 < param_1) {
      if (((*param_2 == 0) && (FatalContext[0x2b7] == 0)) || ((param_2[3] & 0x10U) != 0)) {
        __OSMaskInterrupts(0x410000);
      }
      else {
        __OSUnmaskInterrupts(0x410000);
      }
    }
  }
  else if (param_1 < 3) {
    iVar1 = __OSGetInterruptHandler(0x19);
    if ((iVar1 == 0) || ((param_2[3] & 0x10U) != 0)) {
      __OSMaskInterrupts(0x40);
    }
    else {
      __OSUnmaskInterrupts(0x40);
    }
  }
  return;
}

