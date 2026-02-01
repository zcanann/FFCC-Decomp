// Function: GetBonus__8GbaQueueFi
// Entry: 800ca888
// Size: 100 bytes

undefined GetBonus__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  undefined uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = (&gbaQueue->bonus)[param_2 * 0xdc];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return uVar1;
}

