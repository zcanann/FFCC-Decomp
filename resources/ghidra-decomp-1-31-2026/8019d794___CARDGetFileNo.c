// Function: __CARDGetFileNo
// Entry: 8019d794
// Size: 336 bytes

undefined4 __CARDGetFileNo(CARDControl *cardControl,char *fileName,int *pfileNo)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  
  if (cardControl->attached == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    pcVar6 = (char *)__CARDGetDirBlock(cardControl);
    iVar9 = 0;
    do {
      if (*pcVar6 == -1) {
        iVar4 = -4;
      }
      else if ((cardControl->diskId == (DVDDiskId *)&DAT_80327760) ||
              ((iVar4 = memcmp(pcVar6,cardControl->diskId,4), iVar4 == 0 &&
               (iVar4 = memcmp(pcVar6 + 4,cardControl->diskId->company,2), iVar4 == 0)))) {
        iVar4 = 0;
      }
      else {
        iVar4 = -10;
      }
      if (-1 < iVar4) {
        pcVar7 = pcVar6 + 8;
        iVar4 = 0x20;
        pcVar8 = fileName;
        do {
          iVar4 = iVar4 + -1;
          if (iVar4 < 0) {
            if (*pcVar8 == '\0') {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            goto LAB_8019d8a8;
          }
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          cVar2 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          if (cVar1 != cVar2) {
            bVar3 = false;
            goto LAB_8019d8a8;
          }
        } while (cVar2 != '\0');
        bVar3 = true;
LAB_8019d8a8:
        if (bVar3) {
          *pfileNo = iVar9;
          return 0;
        }
      }
      iVar9 = iVar9 + 1;
      pcVar6 = pcVar6 + 0x40;
    } while (iVar9 < 0x7f);
    uVar5 = 0xfffffffc;
  }
  return uVar5;
}

