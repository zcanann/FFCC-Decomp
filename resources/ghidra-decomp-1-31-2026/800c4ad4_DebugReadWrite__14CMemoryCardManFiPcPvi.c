// Function: DebugReadWrite__14CMemoryCardManFiPcPvi
// Entry: 800c4ad4
// Size: 504 bytes

void DebugReadWrite__14CMemoryCardManFiPcPvi
               (CMemoryCardMan *memoryCardMan,int isWrite,char *filename,void *buffer,int length)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined auStack_a8 [4];
  CARDFileInfo CStack_a4;
  CARDStat CStack_90;
  
  bVar1 = false;
  iVar2 = CARDMount(1,memoryCardMan->mMountWorkArea,0);
  if (((iVar2 != 0) && (iVar2 != -6)) || (iVar2 = CARDCheckAsync(1,0), -1 < iVar2)) {
    while (iVar2 = CARDGetResultCode(1), iVar2 != 0) {
      if (((iVar2 != -6) && (iVar2 != -0xd)) || (isWrite != 0)) goto LAB_800c4c90;
      Printf__7CSystemFPce(&System,&DAT_801db044);
      iVar2 = CARDFormat(1);
      if (iVar2 < 0) goto LAB_800c4c90;
    }
    iVar2 = CARDGetSectorSize(1,auStack_a8);
    if (-1 < iVar2) {
      if (isWrite != 0) {
        iVar2 = CARDOpen(1,filename,&CStack_a4);
        if (-1 < iVar2) goto LAB_800c4c20;
        iVar2 = 0;
        goto LAB_800c4bc0;
      }
      CARDDelete(1,filename);
      iVar2 = CARDCreate(1,filename,length,&CStack_a4);
      if (-1 < iVar2) {
        iVar2 = CARDWrite(&CStack_a4,buffer,length,0);
        if (iVar2 < 0) goto LAB_800c4c88;
        goto LAB_800c4c84;
      }
    }
  }
  goto LAB_800c4c90;
  while (iVar2 = iVar2 + 1, iVar2 < 0x7f) {
LAB_800c4bc0:
    iVar3 = CARDGetStatus(1,iVar2,&CStack_90);
    if ((-1 < iVar3) && (iVar3 = strcmp(filename,&CStack_90), iVar3 == 0)) goto LAB_800c4c00;
  }
  iVar2 = -1;
LAB_800c4c00:
  if ((-1 < iVar2) && (iVar2 = CARDFastOpen(1,iVar2,&CStack_a4), -1 < iVar2)) {
LAB_800c4c20:
    iVar2 = CARDRead(&CStack_a4,buffer,length,0);
    if (-1 < iVar2) {
LAB_800c4c84:
      bVar1 = true;
    }
LAB_800c4c88:
    CARDClose(&CStack_a4);
  }
LAB_800c4c90:
  CARDUnmount(1);
  if (!bVar1) {
    Printf__7CSystemFPce(&System,&DAT_801db07c);
  }
  return;
}

