// Function: GetPlayerStat__8GbaQueueFiP8GbaPInfo
// Entry: 800ce394
// Size: 100 bytes

void GetPlayerStat__8GbaQueueFiP8GbaPInfo(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(param_3,&gbaQueue->field_0x454,0x370);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

