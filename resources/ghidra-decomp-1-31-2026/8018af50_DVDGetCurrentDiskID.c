// Function: DVDGetCurrentDiskID
// Entry: 8018af50
// Size: 8 bytes

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

DVDDiskId * DVDGetCurrentDiskID(void)

{
  return &DVDDiskId_80000000;
}

