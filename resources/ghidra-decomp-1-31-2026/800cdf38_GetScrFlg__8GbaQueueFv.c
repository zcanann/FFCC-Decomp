// Function: GetScrFlg__8GbaQueueFv
// Entry: 800cdf38
// Size: 136 bytes

uint GetScrFlg__8GbaQueueFv(GbaQueue *gbaQueue)

{
  uint uVar1;
  int iVar2;
  GbaQueue *osSemaphore;
  
  iVar2 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar2 = iVar2 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar2 < 4);
  uVar1 = gbaQueue->scrInitEnd;
  iVar2 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar2 = iVar2 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar2 < 4);
  return (-uVar1 | uVar1) >> 0x1f;
}

