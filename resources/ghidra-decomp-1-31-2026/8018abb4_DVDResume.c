// Function: DVDResume
// Entry: 8018abb4
// Size: 80 bytes

void DVDResume(void)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_8032f08c = 0;
  if (DAT_8032f090 != 0) {
    DAT_8032f090 = 0;
    stateReady();
  }
  OSRestoreInterrupts(uVar1);
  return;
}

