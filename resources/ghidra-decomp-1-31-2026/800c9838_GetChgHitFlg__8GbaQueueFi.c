// Function: GetChgHitFlg__8GbaQueueFi
// Entry: 800c9838
// Size: 136 bytes

uint GetChgHitFlg__8GbaQueueFi(GbaQueue *gbaQueue,uint param_2)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = param_2 & ~((-(int)(char)gbaQueue->field_0x2d56 | (int)(char)gbaQueue->field_0x2d56) >>
                     0x1f);
  OSWaitSemaphore(gbaQueue->accessSemaphores + uVar2);
  cVar1 = gbaQueue->chgHitFlg;
  OSSignalSemaphore(gbaQueue->accessSemaphores + uVar2);
  uVar2 = (int)cVar1 & 1 << uVar2;
  return (-uVar2 | uVar2) >> 0x1f;
}

