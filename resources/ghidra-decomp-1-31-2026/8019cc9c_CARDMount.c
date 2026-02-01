// Function: CARDMount
// Entry: 8019cc9c
// Size: 72 bytes

void CARDMount(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = CARDMountAsync();
  if (-1 < iVar1) {
    __CARDSync(param_1);
  }
  return;
}

