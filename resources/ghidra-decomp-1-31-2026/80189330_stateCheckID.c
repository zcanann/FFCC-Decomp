// Function: stateCheckID
// Entry: 80189330
// Size: 224 bytes

void stateCheckID(void)

{
  int iVar1;
  
  if (DAT_8032f09c == 3) {
    iVar1 = DVDCompareDiskID(&DAT_8030ca40,*(undefined4 *)(DAT_8032f080 + 0x24));
    if (iVar1 == 0) {
      DVDLowStopMotor(cbForStateCheckID1);
    }
    else {
      memcpy(DAT_8032f084,&DAT_8030ca40,0x20);
      *(undefined4 *)(DAT_8032f080 + 0xc) = 1;
      DCInvalidateRange(&DAT_8030ca20,0x20);
      DAT_8032f0c4 = stateCheckID2a;
      stateCheckID2a(DAT_8032f080);
    }
  }
  else {
    iVar1 = memcmp(&DAT_8030ca40,DAT_8032f084,0x20);
    if (iVar1 == 0) {
      DAT_8032f0c4 = stateCheckID3;
      stateCheckID3(DAT_8032f080);
    }
    else {
      DVDLowStopMotor(cbForStateCheckID1);
    }
  }
  return;
}

