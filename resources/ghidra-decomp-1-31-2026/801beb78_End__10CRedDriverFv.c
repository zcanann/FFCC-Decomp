// Function: End__10CRedDriverFv
// Entry: 801beb78
// Size: 140 bytes

void End__10CRedDriverFv(void)

{
  AXRegisterCallback(0);
  DAT_8032f3c0 = 0;
  OSSignalSemaphore((OSSemaphore *)&DAT_8032d778);
  OSSignalSemaphore((OSSemaphore *)&DAT_8032daa0);
  OSSignalSemaphore((OSSemaphore *)&DAT_8032ddd8);
  OSSignalSemaphore((OSSemaphore *)&DAT_8032e120);
  while (DAT_8032f3c4 != 0) {
    RedSleep__Fi(0);
  }
  AXRegisterAuxACallback(0,0);
  AXRegisterAuxBCallback(0,0);
  return;
}

