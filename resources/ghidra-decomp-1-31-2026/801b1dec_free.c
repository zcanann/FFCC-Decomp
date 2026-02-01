// Function: free
// Entry: 801b1dec
// Size: 112 bytes

void free(undefined4 param_1)

{
  __begin_critical_region(1);
  if (DAT_8032f388 == '\0') {
    memset(&DAT_8032b510,0,0x34);
    DAT_8032f388 = '\x01';
  }
  __pool_free(&DAT_8032b510,param_1);
  __end_critical_region(1);
  return;
}

