// Function: GetBuyFlg__8GbaQueueFi
// Entry: 800caac4
// Size: 120 bytes

uint GetBuyFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = (int)(char)gbaQueue->buyFlg & 1 << param_2;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (-uVar1 | uVar1) >> 0x1f;
}

