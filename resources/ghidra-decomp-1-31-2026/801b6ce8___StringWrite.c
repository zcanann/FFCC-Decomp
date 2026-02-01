// Function: __StringWrite
// Entry: 801b6ce8
// Size: 108 bytes

undefined4 __StringWrite(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int count;
  
  iVar1 = param_1[2];
  count = param_1[1] - iVar1;
  if ((uint)(iVar1 + param_3) <= (uint)param_1[1]) {
    count = param_3;
  }
  memcpy((void *)(*param_1 + iVar1),param_2,count);
  param_1[2] = param_1[2] + count;
  return 1;
}

