// Function: GetItemUse__8GbaQueueFi
// Entry: 800c9090
// Size: 104 bytes

int GetItemUse__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = (&gbaQueue->itemUse)[param_2 * 0xdc];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (int)cVar1;
}

