// Function: __CARDSetDiskID
// Entry: 801994a8
// Size: 56 bytes

void __CARDSetDiskID(DVDDiskId *dvdDiskId)

{
  DAT_8032764c = dvdDiskId;
  if (dvdDiskId == (DVDDiskId *)0x0) {
    DAT_8032764c = (DVDDiskId *)&DAT_80327760;
  }
  if (dvdDiskId == (DVDDiskId *)0x0) {
    dvdDiskId = (DVDDiskId *)&DAT_80327760;
  }
  DAT_8032775c = dvdDiskId;
  return;
}

