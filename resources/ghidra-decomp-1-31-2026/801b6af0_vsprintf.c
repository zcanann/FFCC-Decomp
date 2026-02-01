// Function: vsprintf
// Entry: 801b6af0
// Size: 120 bytes

void vsprintf(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int local_18 [5];
  
  local_18[1] = 0xffffffff;
  local_18[2] = 0;
  local_18[0] = param_1;
  iVar1 = __pformatter(__StringWrite,local_18,param_2,param_3);
  if (param_1 != 0) {
    iVar2 = -2;
    if (iVar1 != -1) {
      iVar2 = iVar1;
    }
    *(undefined *)(param_1 + iVar2) = 0;
  }
  return;
}

