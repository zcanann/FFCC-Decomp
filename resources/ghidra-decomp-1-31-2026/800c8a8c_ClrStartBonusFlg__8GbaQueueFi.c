// Function: ClrStartBonusFlg__8GbaQueueFi
// Entry: 800c8a8c
// Size: 104 bytes

void ClrStartBonusFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->startBonusFlg = gbaQueue->startBonusFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

