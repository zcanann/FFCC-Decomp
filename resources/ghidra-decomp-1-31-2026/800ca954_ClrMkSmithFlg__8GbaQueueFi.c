// Function: ClrMkSmithFlg__8GbaQueueFi
// Entry: 800ca954
// Size: 124 bytes

void ClrMkSmithFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->mkSmithFlg = gbaQueue->mkSmithFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
  return;
}

