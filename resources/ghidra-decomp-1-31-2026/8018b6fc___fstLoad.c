// Function: __fstLoad
// Entry: 8018b6fc
// Size: 360 bytes

void __fstLoad(void)

{
  int iVar1;
  undefined *puVar2;
  undefined auStack_40 [52];
  
  OSGetArenaHi();
  DAT_8032f0d8 = auStack_40;
  DAT_8032f0d4 = &DAT_8030cae0;
  DVDReset();
  DVDReadDiskID(&DAT_8030cb18,DAT_8032f0d8,cb);
  do {
    iVar1 = DVDGetDriveStatus();
  } while (iVar1 != 0);
  DAT_80000038 = *(undefined4 *)(DAT_8032f0d4 + 0x10);
  DAT_8000003c = *(undefined4 *)(DAT_8032f0d4 + 0xc);
  memcpy(&DVDDiskId_80000000,DAT_8032f0d8,0x20);
  OSReport(&DAT_8032eaf8);
  OSReport(s_Game_Name______c_c_c_c_80217770,(int)DVDDiskId_80000000.gameName[0],
           (int)DVDDiskId_80000000.gameName[1],(int)DVDDiskId_80000000.gameName[2],
           (int)DVDDiskId_80000000.gameName[3]);
  OSReport(s_Company________c_c_8021778c,(int)DVDDiskId_80000000.company[0],
           (int)DVDDiskId_80000000.company[1]);
  OSReport(s_Disk___________d_802177a4,DVDDiskId_80000000.diskNumber);
  OSReport(s_Game_ver_______d_802177b8,DVDDiskId_80000000.gameVersion);
  if (DVDDiskId_80000000.streaming == '\0') {
    puVar2 = &DAT_8032eafc;
  }
  else {
    puVar2 = &DAT_8032eb00;
  }
  OSReport(s_Streaming______s_802177cc,puVar2);
  OSReport(&DAT_8032eaf8);
  OSSetArenaHi(*(undefined4 *)(DAT_8032f0d4 + 0x10));
  return;
}

