// Function: ClrMoneyFlg__8GbaQueueFi
// Entry: 800ccb58
// Size: 104 bytes

void ClrMoneyFlg__8GbaQueueFi(GbaQueue *gbaQueue,int portIndex)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + portIndex);
  gbaQueue->moneyFlg = gbaQueue->moneyFlg & ~(byte)(1 << portIndex);
  OSSignalSemaphore(gbaQueue->accessSemaphores + portIndex);
  return;
}

