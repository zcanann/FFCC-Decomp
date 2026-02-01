// Function: GetUseItemFlg__8GbaQueueFi
// Entry: 800ca56c
// Size: 104 bytes

int GetUseItemFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = gbaQueue->compatibilityStr[param_2 * 0xdc + 0x1f];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (int)cVar1;
}

