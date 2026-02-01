// Function: stateCoverClosed_CMD
// Entry: 80189928
// Size: 48 bytes

void stateCoverClosed_CMD(void)

{
  DVDLowReadDiskID(&DAT_8030ca40,cbForStateCoverClosed);
  return;
}

