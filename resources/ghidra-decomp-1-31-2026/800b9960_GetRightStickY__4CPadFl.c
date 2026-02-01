// Function: GetRightStickY__4CPadFl
// Entry: 800b9960
// Size: 96 bytes

double GetRightStickY__4CPadFl(int param_1,uint param_2)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(int *)(param_1 + 0x1c4) == 0) {
    if (param_2 != 0) goto LAB_800b9988;
    if (*(int *)(param_1 + 0x1c0) == -1) goto LAB_800b9988;
  }
  bVar1 = true;
LAB_800b9988:
  if (bVar1) {
    return (double)FLOAT_80330b30;
  }
  return (double)*(float *)(param_1 + (param_2 &
                                      ~((int)~(*(int *)(param_1 + 0x1c0) - param_2 |
                                              param_2 - *(int *)(param_1 + 0x1c0)) >> 0x1f)) * 0x54
                           + 0x30);
}

