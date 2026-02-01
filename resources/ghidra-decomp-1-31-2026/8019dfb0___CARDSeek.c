// Function: __CARDSeek
// Entry: 8019dfb0
// Size: 440 bytes

int __CARDSeek(CARDFileInfo *cardFileInfo,int length,uint offset,CARDControl **pCardControl)

{
  int iVar1;
  int iVar2;
  CARDControl *local_18 [2];
  
  iVar1 = __CARDGetControlBlock(cardFileInfo->chan,local_18);
  if (-1 < iVar1) {
    if (((cardFileInfo->iBlock < 5) || ((uint)local_18[0]->cBlock <= (uint)cardFileInfo->iBlock)) ||
       ((int)((uint)local_18[0]->cBlock * local_18[0]->sectorSize) <= cardFileInfo->offset)) {
      iVar1 = __CARDPutControlBlock(local_18[0],0xffffff80);
    }
    else {
      iVar1 = __CARDGetDirBlock(local_18[0]);
      iVar1 = iVar1 + cardFileInfo->fileNo * 0x40;
      iVar2 = (uint)*(ushort *)(iVar1 + 0x38) * local_18[0]->sectorSize;
      if (((int)offset < iVar2) && ((int)(offset + length) <= iVar2)) {
        local_18[0]->fileInfo = cardFileInfo;
        cardFileInfo->length = length;
        if ((int)offset < cardFileInfo->offset) {
          cardFileInfo->offset = 0;
          cardFileInfo->iBlock = *(uint16_t *)(iVar1 + 0x36);
          if ((cardFileInfo->iBlock < 5) || (local_18[0]->cBlock <= cardFileInfo->iBlock)) {
            iVar1 = __CARDPutControlBlock(local_18[0],0xfffffffa);
            return iVar1;
          }
        }
        iVar1 = __CARDGetFatBlock(local_18[0]);
        do {
          if ((offset & ~(local_18[0]->sectorSize - 1U)) <= (uint)cardFileInfo->offset) {
            cardFileInfo->offset = offset;
            *pCardControl = local_18[0];
            return 0;
          }
          cardFileInfo->offset = cardFileInfo->offset + local_18[0]->sectorSize;
          cardFileInfo->iBlock = *(uint16_t *)(iVar1 + (uint)cardFileInfo->iBlock * 2);
        } while ((4 < cardFileInfo->iBlock) && (cardFileInfo->iBlock < local_18[0]->cBlock));
        iVar1 = __CARDPutControlBlock(local_18[0],0xfffffffa);
      }
      else {
        iVar1 = __CARDPutControlBlock(local_18[0],0xfffffff5);
      }
    }
  }
  return iVar1;
}

