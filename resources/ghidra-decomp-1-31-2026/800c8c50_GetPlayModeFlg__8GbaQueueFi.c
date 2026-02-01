// Function: GetPlayModeFlg__8GbaQueueFi
// Entry: 800c8c50
// Size: 116 bytes

uint GetPlayModeFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  uint uVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = gbaQueue->playModeFlg;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar2 = (int)cVar1 & 1 << param_2;
  return (-uVar2 | uVar2) >> 0x1f;
}

