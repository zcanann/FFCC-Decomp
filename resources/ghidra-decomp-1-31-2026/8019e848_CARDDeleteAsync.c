// Function: CARDDeleteAsync
// Entry: 8019e848
// Size: 272 bytes

int CARDDeleteAsync(undefined4 param_1,undefined4 param_2,code *param_3)

{
  int iVar1;
  int local_1c;
  CARDControl *local_18 [3];
  
  iVar1 = __CARDGetControlBlock(param_1,local_18);
  if (-1 < iVar1) {
    iVar1 = __CARDGetFileNo(local_18[0],param_2,&local_1c);
    if (iVar1 < 0) {
      iVar1 = __CARDPutControlBlock(local_18[0],iVar1);
    }
    else {
      iVar1 = __CARDIsOpened(local_18[0],local_1c);
      if (iVar1 == 0) {
        iVar1 = __CARDGetDirBlock(local_18[0]);
        iVar1 = iVar1 + local_1c * 0x40;
        local_18[0]->startBlock = *(uint16_t *)(iVar1 + 0x36);
        memset(iVar1,0xff,0x40);
        if (param_3 == (code *)0x0) {
          param_3 = __CARDDefaultApiCallback;
        }
        local_18[0]->apiCallback = param_3;
        iVar1 = __CARDUpdateDir(param_1,DeleteCallback);
        if (iVar1 < 0) {
          __CARDPutControlBlock(local_18[0],iVar1);
        }
      }
      else {
        iVar1 = __CARDPutControlBlock(local_18[0],0xffffffff);
      }
    }
  }
  return iVar1;
}

