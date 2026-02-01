// Function: ClrChgRadarMode__8GbaQueueFi
// Entry: 800c9bf0
// Size: 104 bytes

void ClrChgRadarMode__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->chgRadarMode = gbaQueue->chgRadarMode & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

