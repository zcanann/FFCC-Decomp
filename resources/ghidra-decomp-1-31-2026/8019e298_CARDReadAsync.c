// Function: CARDReadAsync
// Entry: 8019e298
// Size: 328 bytes

int CARDReadAsync(CARDFileInfo *cardFileInfo,void *buffer,uint length,uint offset,code *callback)

{
  int iVar1;
  uint length_00;
  uint uVar2;
  CARDDir *cardDir;
  CARDControl *local_1c [2];
  
  if (((offset & 0x1ff) == 0) && ((length & 0x1ff) == 0)) {
    iVar1 = __CARDSeek(cardFileInfo,length,offset,local_1c);
    if (-1 < iVar1) {
      iVar1 = __CARDGetDirBlock(local_1c[0]);
      cardDir = (CARDDir *)(iVar1 + cardFileInfo->fileNo * 0x40);
      iVar1 = __CARDAccess(local_1c[0],cardDir);
      if (iVar1 == -10) {
        iVar1 = __CARDIsPublic(cardDir);
      }
      if (iVar1 < 0) {
        iVar1 = __CARDPutControlBlock(local_1c[0],iVar1);
      }
      else {
        DCInvalidateRange(buffer,length);
        if (callback == (code *)0x0) {
          callback = __CARDDefaultApiCallback;
        }
        local_1c[0]->apiCallback = callback;
        iVar1 = local_1c[0]->sectorSize;
        uVar2 = cardFileInfo->offset & iVar1 - 1U;
        length_00 = iVar1 - uVar2;
        if ((int)length < (int)length_00) {
          length_00 = length;
        }
        iVar1 = __CARDRead(cardFileInfo->chan,uVar2 + iVar1 * (uint)cardFileInfo->iBlock,length_00,
                           buffer,ReadCallback);
        if (iVar1 < 0) {
          __CARDPutControlBlock(local_1c[0],iVar1);
        }
      }
    }
  }
  else {
    iVar1 = -0x80;
  }
  return iVar1;
}

