// Function: GetRadarMode__8GbaQueueFi
// Entry: 800c9d6c
// Size: 116 bytes

uint GetRadarMode__8GbaQueueFi(GbaQueue *gbaQueue,int portIndex)

{
  char cVar1;
  uint uVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + portIndex);
  cVar1 = gbaQueue->field_0x2d41;
  OSSignalSemaphore(gbaQueue->accessSemaphores + portIndex);
  uVar2 = (int)cVar1 & 1 << portIndex;
  return (-uVar2 | uVar2) >> 0x1f;
}

