// Function: GetMemorys__8GbaQueueFi
// Entry: 800c8e00
// Size: 100 bytes

undefined2 GetMemorys__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  undefined2 uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  uVar1 = *(undefined2 *)(gbaQueue->compatibilityStr + param_2 * 0xdc + 0x10);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return uVar1;
}

