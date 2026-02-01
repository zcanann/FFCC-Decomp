// Function: CARDRead
// Entry: 8019e3e0
// Size: 72 bytes

void CARDRead(CARDFileInfo *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = CARDReadAsync(param_1,param_2,param_3,param_4,__CARDSyncCallback);
  if (-1 < iVar1) {
    __CARDSync(param_1->chan);
  }
  return;
}

