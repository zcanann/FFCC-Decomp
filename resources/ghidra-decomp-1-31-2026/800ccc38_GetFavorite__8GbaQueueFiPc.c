// Function: GetFavorite__8GbaQueueFiPc
// Entry: 800ccc38
// Size: 124 bytes

undefined4 GetFavorite__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(param_3,gbaQueue->compatibilityStr + param_2 * 0xdc + 0x14,8);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return 8;
}

