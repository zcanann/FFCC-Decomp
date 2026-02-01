// Function: SetShopFlg__8GbaQueueFi
// Entry: 800cb8c0
// Size: 168 bytes

void SetShopFlg__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  byte bVar1;
  int iVar2;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  bVar1 = (byte)(1 << param_2);
  gbaQueue->shopFlg = gbaQueue->shopFlg | bVar1;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  iVar2 = SetMType__6JoyBusFii(&Joybus,param_2,2);
  if (iVar2 == 0) {
    gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 & ~bVar1;
  }
  else {
    gbaQueue->field_0x2d39 = gbaQueue->field_0x2d39 | bVar1;
  }
  return;
}

