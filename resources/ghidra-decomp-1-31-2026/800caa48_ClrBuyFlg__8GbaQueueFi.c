// Function: ClrBuyFlg__8GbaQueueFi
// Entry: 800caa48
// Size: 124 bytes

void ClrBuyFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->buyFlg = gbaQueue->buyFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
  return;
}

