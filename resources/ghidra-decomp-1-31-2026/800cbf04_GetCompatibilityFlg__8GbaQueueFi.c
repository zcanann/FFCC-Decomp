// Function: GetCompatibilityFlg__8GbaQueueFi
// Entry: 800cbf04
// Size: 112 bytes

uint GetCompatibilityFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = (&gbaQueue->compatibilityFlg)[param_2];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (uint)(-(int)cVar1 | (int)cVar1) >> 0x1f;
}

