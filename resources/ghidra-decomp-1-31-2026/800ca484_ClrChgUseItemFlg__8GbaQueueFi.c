// Function: ClrChgUseItemFlg__8GbaQueueFi
// Entry: 800ca484
// Size: 104 bytes

void ClrChgUseItemFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->chgUseItemFlg = gbaQueue->chgUseItemFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

