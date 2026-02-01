// Function: __ptmf_test
// Entry: 801afeec
// Size: 48 bytes

undefined4 __ptmf_test(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (*param_1 != 0) {
    return uVar1;
  }
  if (param_1[1] != 0) {
    return uVar1;
  }
  if (param_1[2] != 0) {
    return uVar1;
  }
  return 0;
}

