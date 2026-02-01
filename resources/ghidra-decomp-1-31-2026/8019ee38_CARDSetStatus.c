// Function: CARDSetStatus
// Entry: 8019ee38
// Size: 72 bytes

void CARDSetStatus(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = CARDSetStatusAsync();
  if (-1 < iVar1) {
    __CARDSync(param_1);
  }
  return;
}

