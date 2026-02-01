// Function: GetChgUseItemFlg__8GbaQueueFi
// Entry: 800ca4ec
// Size: 128 bytes

uint GetChgUseItemFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = (int)(char)gbaQueue->chgUseItemFlg & 1 << param_2;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (uint)((int)(-uVar1 | uVar1) >> 0x1f) >> 0x1f;
}

