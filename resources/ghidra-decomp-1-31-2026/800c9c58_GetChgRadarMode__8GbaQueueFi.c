// Function: GetChgRadarMode__8GbaQueueFi
// Entry: 800c9c58
// Size: 116 bytes

uint GetChgRadarMode__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  uint uVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = gbaQueue->chgRadarMode;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar2 = (int)cVar1 & 1 << param_2;
  return (-uVar2 | uVar2) >> 0x1f;
}

