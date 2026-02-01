// Function: GetHitEInfo__8GbaQueueFi
// Entry: 800c95bc
// Size: 132 bytes

int GetHitEInfo__8GbaQueueFi(GbaQueue *gbaQueue,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_2 & ~((-(int)(char)gbaQueue->field_0x2d56 | (int)(char)gbaQueue->field_0x2d56) >>
                     0x1f);
  OSWaitSemaphore(gbaQueue->accessSemaphores + uVar2);
  iVar1 = (&gbaQueue->hitEInfo)[uVar2];
  OSSignalSemaphore(gbaQueue->accessSemaphores + uVar2);
  return iVar1;
}

