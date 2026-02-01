// Function: SetStartBonusFlg__8GbaQueueFv
// Entry: 800c8b68
// Size: 128 bytes

void SetStartBonusFlg__8GbaQueueFv(GbaQueue *gbaQueue)

{
  int iVar1;
  GbaQueue *osSemaphore;
  
  iVar1 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar1 = iVar1 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar1 < 4);
  gbaQueue->startBonusFlg = 0xf;
  iVar1 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar1 = iVar1 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar1 < 4);
  return;
}

