// Function: GetCmdNum__8GbaQueueFi
// Entry: 800c8cc4
// Size: 104 bytes

int GetCmdNum__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = (&gbaQueue->field_0x527)[param_2 * 0xdc];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (int)cVar1;
}

