// Function: __construct_new_array
// Entry: 801afb24
// Size: 260 bytes

int * __construct_new_array(int *param_1,code *param_2,code *param_3,int param_4,uint param_5)

{
  int *piVar1;
  uint local_28;
  
  if (param_1 != (int *)0x0) {
    *param_1 = param_4;
    param_1[1] = param_5;
    param_1 = param_1 + 4;
    if (param_2 != (code *)0x0) {
      piVar1 = param_1;
      for (local_28 = 0; local_28 < param_5; local_28 = local_28 + 1) {
        (*param_2)(piVar1,1);
        piVar1 = (int *)((int)piVar1 + param_4);
      }
      if ((local_28 < param_5) && (param_3 != (code *)0x0)) {
        piVar1 = (int *)((int)param_1 + param_4 * local_28);
        for (; local_28 != 0; local_28 = local_28 - 1) {
          piVar1 = (int *)((int)piVar1 - param_4);
          (*param_3)(piVar1,0xffffffff);
        }
      }
    }
  }
  return param_1;
}

