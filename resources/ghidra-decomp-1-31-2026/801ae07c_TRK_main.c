// Function: TRK_main
// Entry: 801ae07c
// Size: 88 bytes

void TRK_main(void)

{
  MWTRACE(1,s_TRK_Main_801e6b90);
  DAT_8032a6a8 = TRKInitializeNub();
  if (DAT_8032a6a8 == 0) {
    TRKNubWelcome();
    TRKNubMainLoop();
  }
  DAT_8032a6a8 = TRKTerminateNub();
  return;
}

