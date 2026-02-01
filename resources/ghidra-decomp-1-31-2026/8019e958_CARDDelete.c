// Function: CARDDelete
// Entry: 8019e958
// Size: 72 bytes

void CARDDelete(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = CARDDeleteAsync(param_1,param_2,__CARDSyncCallback);
  if (-1 < iVar1) {
    __CARDSync(param_1);
  }
  return;
}

