// Function: GetMBasePos__8GbaQueueFiPsPs
// Entry: 800cf6ec
// Size: 120 bytes

void GetMBasePos__8GbaQueueFiPsPs
               (GbaQueue *gbaQueue,uint param_2,undefined2 *param_3,undefined2 *param_4)

{
  uint uVar1;
  
  uVar1 = param_2 & ~((-(int)(char)gbaQueue->field_0x2d56 | (int)(char)gbaQueue->field_0x2d56) >>
                     0x1f);
  OSWaitSemaphore(gbaQueue->accessSemaphores + uVar1);
  *param_3 = *(undefined2 *)(gbaQueue->compatibilityStr + uVar1 * 0xdc + 0x32);
  *param_4 = *(undefined2 *)(gbaQueue->compatibilityStr + uVar1 * 0xdc + 0x34);
  OSSignalSemaphore(gbaQueue->accessSemaphores + uVar1);
  return;
}

