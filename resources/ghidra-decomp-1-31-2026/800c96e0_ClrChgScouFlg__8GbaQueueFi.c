// Function: ClrChgScouFlg__8GbaQueueFi
// Entry: 800c96e0
// Size: 104 bytes

void ClrChgScouFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->chgScouFlg = gbaQueue->chgScouFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

