// Function: CARDFastOpen
// Entry: 8019d8e4
// Size: 352 bytes

int CARDFastOpen(int32_t param_1,int param_2,CARDFileInfo *fileInfo)

{
  CARDControl *pCVar1;
  int iVar2;
  char *pcVar3;
  CARDControl *local_1c [2];
  
  if ((param_2 < 0) || (0x7e < param_2)) {
    iVar2 = -0x80;
  }
  else {
    fileInfo->chan = -1;
    iVar2 = __CARDGetControlBlock(param_1,local_1c);
    if (-1 < iVar2) {
      iVar2 = __CARDGetDirBlock(local_1c[0]);
      pCVar1 = local_1c[0];
      pcVar3 = (char *)(iVar2 + param_2 * 0x40);
      if (*pcVar3 == -1) {
        iVar2 = -4;
      }
      else if ((local_1c[0]->diskId == (DVDDiskId *)&DAT_80327760) ||
              ((iVar2 = memcmp(pcVar3,local_1c[0]->diskId,4), iVar2 == 0 &&
               (iVar2 = memcmp(pcVar3 + 4,pCVar1->diskId->company,2), iVar2 == 0)))) {
        iVar2 = 0;
      }
      else {
        iVar2 = -10;
      }
      if (iVar2 == -10) {
        if (*pcVar3 == -1) {
          iVar2 = -4;
        }
        else if ((pcVar3[0x34] & 4U) == 0) {
          iVar2 = -10;
        }
        else {
          iVar2 = 0;
        }
      }
      if (-1 < iVar2) {
        if ((*(ushort *)(pcVar3 + 0x36) < 5) || (local_1c[0]->cBlock <= *(ushort *)(pcVar3 + 0x36)))
        {
          iVar2 = -6;
        }
        else {
          fileInfo->chan = param_1;
          fileInfo->fileNo = param_2;
          fileInfo->offset = 0;
          fileInfo->iBlock = *(uint16_t *)(pcVar3 + 0x36);
        }
      }
      iVar2 = __CARDPutControlBlock(local_1c[0],iVar2);
    }
  }
  return iVar2;
}

