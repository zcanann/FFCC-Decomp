// Function: __CARDSyncCallback
// Entry: 80198584
// Size: 52 bytes

void __CARDSyncCallback(int chan)

{
  OSWakeupThread(&DAT_803275cc + chan * 0x110);
  return;
}

