// Function: GetMoneyFlg__8GbaQueueFi
// Entry: 800ccbc0
// Size: 120 bytes

uint GetMoneyFlg__8GbaQueueFi(GbaQueue *gbaQueue,int portIndex)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + portIndex);
  uVar1 = (int)(char)gbaQueue->moneyFlg & 1 << portIndex;
  OSSignalSemaphore(gbaQueue->accessSemaphores + portIndex);
  return (-uVar1 | uVar1) >> 0x1f;
}

