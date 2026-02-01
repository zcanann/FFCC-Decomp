// Function: SetPauseMode__8GbaQueueFi
// Entry: 800c9184
// Size: 136 bytes

void SetPauseMode__8GbaQueueFi(GbaQueue *gbaQueue,undefined param_2)

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
  gbaQueue->field_0x2d5b = param_2;
  iVar1 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar1 = iVar1 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar1 < 4);
  return;
}

