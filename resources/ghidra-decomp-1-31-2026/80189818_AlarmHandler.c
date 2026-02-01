// Function: AlarmHandler
// Entry: 80189818
// Size: 68 bytes

void AlarmHandler(void)

{
  DVDReset();
  DCInvalidateRange(&DAT_8030ca40,0x20);
  DAT_8032f0c4 = stateCoverClosed_CMD;
  stateCoverClosed_CMD(DAT_8032f080);
  return;
}

