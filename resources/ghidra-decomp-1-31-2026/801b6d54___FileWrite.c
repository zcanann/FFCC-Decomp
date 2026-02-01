// Function: __FileWrite
// Entry: 801b6d54
// Size: 88 bytes

undefined4 __FileWrite(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = fwrite(param_2,1,param_3,param_1);
  if (param_3 != iVar1) {
    param_1 = 0;
  }
  return param_1;
}

