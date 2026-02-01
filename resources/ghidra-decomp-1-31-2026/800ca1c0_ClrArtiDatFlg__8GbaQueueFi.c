// Function: ClrArtiDatFlg__8GbaQueueFi
// Entry: 800ca1c0
// Size: 124 bytes

void ClrArtiDatFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  gbaQueue->artiDatFlg = gbaQueue->artiDatFlg & ~(byte)(1 << param_2);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
  return;
}

