// Function: __destroy_arr
// Entry: 801af8f8
// Size: 120 bytes

void __destroy_arr(int param_1,code *param_2,int param_3,int param_4)

{
  param_1 = param_1 + param_3 * param_4;
  for (; param_4 != 0; param_4 = param_4 + -1) {
    param_1 = param_1 - param_3;
    (*param_2)(param_1,0xffffffff);
  }
  return;
}

