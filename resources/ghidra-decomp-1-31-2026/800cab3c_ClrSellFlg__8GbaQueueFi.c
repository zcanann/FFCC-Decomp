// Function: ClrSellFlg__8GbaQueueFi
// Entry: 800cab3c
// Size: 124 bytes

void ClrSellFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->sellFlg = gbaQueue->sellFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
  return;
}

