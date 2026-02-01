// Function: CARDWriteAsync
// Entry: 8019e648
// Size: 276 bytes

int CARDWriteAsync(undefined4 *param_1,void *param_2,uint param_3,uint param_4,code *param_5)

{
  int iVar1;
  uint uVar2;
  CARDControl *local_1c [2];
  
  iVar1 = __CARDSeek(param_1,param_3,param_4,local_1c);
  if (-1 < iVar1) {
    uVar2 = local_1c[0]->sectorSize - 1;
    if (((param_4 & uVar2) == 0) && ((param_3 & uVar2) == 0)) {
      iVar1 = __CARDGetDirBlock(local_1c[0]);
      iVar1 = __CARDAccess(local_1c[0],iVar1 + param_1[1] * 0x40);
      if (iVar1 < 0) {
        iVar1 = __CARDPutControlBlock(local_1c[0],iVar1);
      }
      else {
        DCStoreRange(param_2,param_3);
        if (param_5 == (code *)0x0) {
          param_5 = __CARDDefaultApiCallback;
        }
        local_1c[0]->apiCallback = param_5;
        local_1c[0]->buffer = param_2;
        iVar1 = __CARDEraseSector(*param_1,local_1c[0]->sectorSize * (uint)*(ushort *)(param_1 + 4),
                                  EraseCallback);
        if (iVar1 < 0) {
          __CARDPutControlBlock(local_1c[0],iVar1);
        }
      }
    }
    else {
      iVar1 = __CARDPutControlBlock(local_1c[0],0xffffff80);
    }
  }
  return iVar1;
}

