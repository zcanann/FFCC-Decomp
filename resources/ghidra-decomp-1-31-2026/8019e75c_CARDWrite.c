// Function: CARDWrite
// Entry: 8019e75c
// Size: 72 bytes

void CARDWrite(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = CARDWriteAsync();
  if (-1 < iVar1) {
    __CARDSync(*param_1);
  }
  return;
}

