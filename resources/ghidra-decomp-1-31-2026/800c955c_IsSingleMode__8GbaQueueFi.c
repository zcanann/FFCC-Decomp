// Function: IsSingleMode__8GbaQueueFi
// Entry: 800c955c
// Size: 96 bytes

uint IsSingleMode__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = countLeadingZeros(1 - (char)gbaQueue->field_0x2d56);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return uVar1 >> 5;
}

