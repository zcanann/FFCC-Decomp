// Function: vprintf
// Entry: 801b6b68
// Size: 152 bytes

undefined4 vprintf(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = fwide(&DAT_8021d1a8,0xffffffff);
  if (iVar1 < 0) {
    __begin_critical_region(2);
    uVar2 = __pformatter(__FileWrite,&DAT_8021d1a8,param_1,param_2);
    __end_critical_region(2);
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

