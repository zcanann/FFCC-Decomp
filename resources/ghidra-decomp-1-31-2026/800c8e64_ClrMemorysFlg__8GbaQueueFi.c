// Function: ClrMemorysFlg__8GbaQueueFi
// Entry: 800c8e64
// Size: 104 bytes

void ClrMemorysFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->memorysFlg = gbaQueue->memorysFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

