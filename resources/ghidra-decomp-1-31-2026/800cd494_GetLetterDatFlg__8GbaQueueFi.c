// Function: GetLetterDatFlg__8GbaQueueFi
// Entry: 800cd494
// Size: 120 bytes

uint GetLetterDatFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = (int)gbaQueue->letterDatFlg & 0x10 << param_2;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (-uVar1 | uVar1) >> 0x1f;
}

