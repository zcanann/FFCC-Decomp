// Function: ClrPlayModeFlg__8GbaQueueFi
// Entry: 800c8be8
// Size: 104 bytes

void ClrPlayModeFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->playModeFlg = gbaQueue->playModeFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

