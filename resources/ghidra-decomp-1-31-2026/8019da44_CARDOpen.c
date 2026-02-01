// Function: CARDOpen
// Entry: 8019da44
// Size: 376 bytes

void CARDOpen(int32_t param_1,undefined4 param_2,CARDFileInfo *cardFileInfo)

{
  ushort uVar1;
  CARDControl *pCVar2;
  int iVar3;
  CARDDir *cardDir;
  DVDDiskId *pDVar4;
  int iVar5;
  int unaff_r30;
  CARDControl *local_2c [2];
  
  cardFileInfo->chan = -1;
  iVar3 = __CARDGetControlBlock(param_1,local_2c);
  pCVar2 = local_2c[0];
  if (-1 < iVar3) {
    if (local_2c[0]->attached == 0) {
      iVar5 = -3;
    }
    else {
      cardDir = (CARDDir *)__CARDGetDirBlock(local_2c[0]);
      iVar3 = 0;
      do {
        if (cardDir->gameName[0] == 0xff) {
          iVar5 = -4;
        }
        else {
          pDVar4 = pCVar2->diskId;
          if ((pDVar4 == (DVDDiskId *)&DAT_80327760) ||
             ((iVar5 = memcmp(cardDir,pDVar4,4), iVar5 == 0 &&
              (iVar5 = memcmp(cardDir->company,pCVar2->diskId->company,2), iVar5 == 0)))) {
            iVar5 = 0;
          }
          else {
            iVar5 = -10;
          }
        }
        if ((-1 < iVar5) && (iVar5 = __CARDCompareFileName(cardDir,param_2), iVar5 != 0)) {
          iVar5 = 0;
          unaff_r30 = iVar3;
          goto LAB_8019db48;
        }
        iVar3 = iVar3 + 1;
        cardDir = cardDir + 1;
      } while (iVar3 < 0x7f);
      iVar5 = -4;
    }
LAB_8019db48:
    if (-1 < iVar5) {
      iVar3 = __CARDGetDirBlock(local_2c[0]);
      iVar3 = iVar3 + unaff_r30 * 0x40;
      uVar1 = *(ushort *)(iVar3 + 0x36);
      if ((uVar1 < 5) || (local_2c[0]->cBlock <= uVar1)) {
        iVar5 = -6;
      }
      else {
        cardFileInfo->chan = param_1;
        cardFileInfo->fileNo = unaff_r30;
        cardFileInfo->offset = 0;
        cardFileInfo->iBlock = *(uint16_t *)(iVar3 + 0x36);
      }
    }
    __CARDPutControlBlock(local_2c[0],iVar5);
  }
  return;
}

