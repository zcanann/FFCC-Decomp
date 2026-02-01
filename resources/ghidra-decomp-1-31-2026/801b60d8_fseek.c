// Function: fseek
// Entry: 801b60d8
// Size: 108 bytes

undefined4 fseek(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  __begin_critical_region(2);
  uVar1 = _fseek(param_1,param_2,param_3);
  __end_critical_region(2);
  return uVar1;
}

