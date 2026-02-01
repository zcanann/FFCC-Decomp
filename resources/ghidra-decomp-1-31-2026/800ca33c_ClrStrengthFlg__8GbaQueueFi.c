// Function: ClrStrengthFlg__8GbaQueueFi
// Entry: 800ca33c
// Size: 104 bytes

void ClrStrengthFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->strengthFlg = gbaQueue->strengthFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

