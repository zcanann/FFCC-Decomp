// Function: GetSPMode__8GbaQueueFi
// Entry: 800c8f40
// Size: 116 bytes

uint GetSPMode__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  uint uVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = gbaQueue->field_0x2d5c;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar2 = (int)cVar1 & 1 << param_2;
  return (-uVar2 | uVar2) >> 0x1f;
}

