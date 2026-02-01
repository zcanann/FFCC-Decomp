// Function: fwrite
// Entry: 801b55d0
// Size: 124 bytes

undefined4 fwrite(void *param_1,undefined4 param_2,undefined4 param_3,FILE *param_4)

{
  undefined4 uVar1;
  
  __begin_critical_region(2);
  uVar1 = __fwrite(param_1,param_2,param_3,param_4);
  __end_critical_region(2);
  return uVar1;
}

