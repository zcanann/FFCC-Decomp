// Function: ClrSPModeFlg__8GbaQueueFi
// Entry: 800c8fb4
// Size: 104 bytes

void ClrSPModeFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->spModeFlg = gbaQueue->spModeFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

