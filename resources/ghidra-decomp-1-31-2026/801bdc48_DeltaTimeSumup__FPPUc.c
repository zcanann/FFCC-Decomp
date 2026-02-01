// Function: DeltaTimeSumup__FPPUc
// Entry: 801bdc48
// Size: 112 bytes

uint DeltaTimeSumup__FPPUc(int *param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != (int *)0x0) {
    uVar1 = *(byte *)*param_1 & 0x7f;
    while ((*(byte *)*param_1 & 0x80) != 0) {
      *param_1 = *param_1 + 1;
      uVar1 = uVar1 << 7 | *(byte *)*param_1 & 0x7f;
    }
    *param_1 = *param_1 + 1;
  }
  return uVar1;
}

