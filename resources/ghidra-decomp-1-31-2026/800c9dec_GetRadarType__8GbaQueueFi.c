// Function: GetRadarType__8GbaQueueFi
// Entry: 800c9dec
// Size: 100 bytes

int GetRadarType__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  char cVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  cVar1 = (&gbaQueue->field_0x2d32)[param_2];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return (int)cVar1;
}

