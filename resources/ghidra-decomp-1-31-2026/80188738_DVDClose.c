// Function: DVDClose
// Entry: 80188738
// Size: 36 bytes

undefined4 DVDClose(DVDFileInfo *fileInfo)

{
  DVDCancel();
  return 1;
}

