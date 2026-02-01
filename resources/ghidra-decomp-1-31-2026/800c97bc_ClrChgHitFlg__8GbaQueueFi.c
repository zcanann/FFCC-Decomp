// Function: ClrChgHitFlg__8GbaQueueFi
// Entry: 800c97bc
// Size: 124 bytes

void ClrChgHitFlg__8GbaQueueFi(GbaQueue *gbaQueue,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_2 & ~((-(int)(char)gbaQueue->field_0x2d56 | (int)(char)gbaQueue->field_0x2d56) >>
                     0x1f);
  OSWaitSemaphore(gbaQueue->accessSemaphores + uVar1);
  gbaQueue->chgHitFlg = gbaQueue->chgHitFlg & ~(byte)(1 << uVar1);
  OSSignalSemaphore(gbaQueue->accessSemaphores + uVar1);
  return;
}

