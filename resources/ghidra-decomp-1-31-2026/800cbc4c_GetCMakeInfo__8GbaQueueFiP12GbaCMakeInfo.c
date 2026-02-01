// Function: GetCMakeInfo__8GbaQueueFiP12GbaCMakeInfo
// Entry: 800cbc4c
// Size: 120 bytes

void GetCMakeInfo__8GbaQueueFiP12GbaCMakeInfo(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(param_3,&gbaQueue->cmakeInfo + param_2 * 0x20,0x20);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

