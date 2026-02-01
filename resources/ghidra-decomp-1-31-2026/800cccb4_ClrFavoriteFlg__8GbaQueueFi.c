// Function: ClrFavoriteFlg__8GbaQueueFi
// Entry: 800cccb4
// Size: 104 bytes

void ClrFavoriteFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->favoriteFlag = gbaQueue->favoriteFlag & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

