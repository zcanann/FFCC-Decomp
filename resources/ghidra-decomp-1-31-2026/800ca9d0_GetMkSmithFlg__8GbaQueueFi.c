// Function: GetMkSmithFlg__8GbaQueueFi
// Entry: 800ca9d0
// Size: 120 bytes

uint GetMkSmithFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = (int)(char)gbaQueue->mkSmithFlg & 1 << param_2;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (-uVar1 | uVar1) >> 0x1f;
}

