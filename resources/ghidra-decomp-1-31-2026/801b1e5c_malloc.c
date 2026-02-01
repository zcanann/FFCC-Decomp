// Function: malloc
// Entry: 801b1e5c
// Size: 124 bytes

undefined4 malloc(undefined4 param_1)

{
  undefined4 uVar1;
  
  __begin_critical_region(1);
  if (DAT_8032f388 == '\0') {
    memset(&DAT_8032b510,0,0x34);
    DAT_8032f388 = '\x01';
  }
  uVar1 = __pool_alloc(&DAT_8032b510,param_1);
  __end_critical_region(1);
  return uVar1;
}

