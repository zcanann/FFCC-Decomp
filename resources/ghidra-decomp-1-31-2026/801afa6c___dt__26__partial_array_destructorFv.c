// Function: __dt__26__partial_array_destructorFv
// Entry: 801afa6c
// Size: 184 bytes

int * __dt__26__partial_array_destructorFv(int *param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    if (((uint)param_1[4] < (uint)param_1[2]) && (param_1[3] != 0)) {
      iVar1 = *param_1 + param_1[1] * param_1[4];
      while (param_1[4] != 0) {
        iVar1 = iVar1 - param_1[1];
        (*(code *)param_1[3])(iVar1,0xffffffff);
        param_1[4] = param_1[4] + -1;
      }
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

