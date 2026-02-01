// Function: GetCmdNumFlg__8GbaQueueFi
// Entry: 800c8d98
// Size: 104 bytes

uint GetCmdNumFlg__8GbaQueueFi(GbaQueue *gbaQueue,uint param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = gbaQueue->cmdNumFlag;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (int)cVar1 >> ((param_2 & 0x1f) << 1) & 3;
}

