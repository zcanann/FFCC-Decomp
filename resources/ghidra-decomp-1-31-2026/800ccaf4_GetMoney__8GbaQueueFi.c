// Function: GetMoney__8GbaQueueFi
// Entry: 800ccaf4
// Size: 100 bytes

undefined4 GetMoney__8GbaQueueFi(GbaQueue *gbaQueue,int portIndex)

{
  undefined4 uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + portIndex);
  uVar1 = *(undefined4 *)(gbaQueue->compatibilityStr + portIndex * 0xdc + 0x20);
  OSSignalSemaphore(gbaQueue->accessSemaphores + portIndex);
  return uVar1;
}

