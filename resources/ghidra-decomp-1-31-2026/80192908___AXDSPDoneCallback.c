// Function: __AXDSPDoneCallback
// Entry: 80192908
// Size: 44 bytes

void __AXDSPDoneCallback(void)

{
  DAT_8032f258 = 1;
  OSWakeupThread(&DAT_8032f260);
  return;
}

