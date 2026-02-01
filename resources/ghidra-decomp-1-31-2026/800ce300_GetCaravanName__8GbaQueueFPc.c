// Function: GetCaravanName__8GbaQueueFPc
// Entry: 800ce300
// Size: 148 bytes

void GetCaravanName__8GbaQueueFPc(GbaQueue *gbaQueue,char *outName)

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
  memcpy(outName,gbaQueue->caravanName,0x80);
  iVar1 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar1 = iVar1 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar1 < 4);
  return;
}

