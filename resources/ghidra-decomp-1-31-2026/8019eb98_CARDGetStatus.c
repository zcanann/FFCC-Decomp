// Function: CARDGetStatus
// Entry: 8019eb98
// Size: 300 bytes

int CARDGetStatus(int chan,int fileNo,CARDStat *cardStat)

{
  int iVar1;
  CARDDir *cardDir;
  CARDControl *local_14 [2];
  
  if ((fileNo < 0) || (0x7e < fileNo)) {
    iVar1 = -0x80;
  }
  else {
    iVar1 = __CARDGetControlBlock(chan,local_14);
    if (-1 < iVar1) {
      iVar1 = __CARDGetDirBlock(local_14[0]);
      cardDir = (CARDDir *)(iVar1 + fileNo * 0x40);
      iVar1 = __CARDAccess(local_14[0],cardDir);
      if (iVar1 == -10) {
        iVar1 = __CARDIsPublic(cardDir);
      }
      if (-1 < iVar1) {
        memcpy(cardStat->gameName,cardDir,4);
        memcpy(cardStat->company,cardDir->company,2);
        cardStat->length = (uint)cardDir->length * local_14[0]->sectorSize;
        memcpy(cardStat,cardDir->fileName,0x20);
        cardStat->time = cardDir->time;
        cardStat->bannerFormat = cardDir->bannerFormat;
        cardStat->iconAddr = cardDir->iconAddr;
        cardStat->iconFormat = cardDir->iconFormat;
        cardStat->iconSpeed = cardDir->iconSpeed;
        cardStat->commentAddr = cardDir->commentAddr;
        UpdateIconOffsets(cardDir,cardStat);
      }
      iVar1 = __CARDPutControlBlock(local_14[0],iVar1);
    }
  }
  return iVar1;
}

