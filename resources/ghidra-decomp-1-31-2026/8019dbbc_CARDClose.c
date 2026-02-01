// Function: CARDClose
// Entry: 8019dbbc
// Size: 84 bytes

void CARDClose(undefined4 *param_1)

{
  int iVar1;
  CARDControl *local_c [2];
  
  iVar1 = __CARDGetControlBlock(*param_1,local_c);
  if (-1 < iVar1) {
    *param_1 = 0xffffffff;
    __CARDPutControlBlock(local_c[0],0);
  }
  return;
}

