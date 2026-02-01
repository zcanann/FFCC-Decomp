// Function: ClrLetterLstFlg__8GbaQueueFi
// Entry: 800cd50c
// Size: 124 bytes

void ClrLetterLstFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->letterDatFlg = gbaQueue->letterDatFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
  return;
}

