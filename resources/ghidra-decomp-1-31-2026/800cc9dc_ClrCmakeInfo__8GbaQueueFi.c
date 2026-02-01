// Function: ClrCmakeInfo__8GbaQueueFi
// Entry: 800cc9dc
// Size: 124 bytes

void ClrCmakeInfo__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  if ((&gbaQueue->cmakeInfo)[param_2 * 0x20] != '\0') {
    memset(&gbaQueue->cmakeInfo + param_2 * 0x20,0,0x20);
  }
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

