// Function: GetControllerMode__8GbaQueueFv
// Entry: 800c93e8
// Size: 140 bytes

uint GetControllerMode__8GbaQueueFv(GbaQueue *gbaQueue)

{
  char cVar1;
  int iVar2;
  GbaQueue *osSemaphore;
  
  iVar2 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar2 = iVar2 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar2 < 4);
  cVar1 = gbaQueue->field_0x2d57;
  iVar2 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar2 = iVar2 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar2 < 4);
  return (uint)(-(int)cVar1 | (int)cVar1) >> 0x1f;
}

