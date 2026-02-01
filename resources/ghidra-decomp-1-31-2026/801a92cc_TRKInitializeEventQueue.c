// Function: TRKInitializeEventQueue
// Entry: 801a92cc
// Size: 88 bytes

undefined4 TRKInitializeEventQueue(void)

{
  TRKInitializeMutex(&DAT_80328720);
  TRKAcquireMutex(&DAT_80328720);
  DAT_80328724 = 0;
  DAT_80328728 = 0;
  DAT_80328744 = 0x100;
  TRKReleaseMutex();
  return 0;
}

