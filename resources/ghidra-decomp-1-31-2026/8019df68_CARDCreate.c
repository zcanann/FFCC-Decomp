// Function: CARDCreate
// Entry: 8019df68
// Size: 72 bytes

void CARDCreate(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = CARDCreateAsync();
  if (-1 < iVar1) {
    __CARDSync(param_1);
  }
  return;
}

