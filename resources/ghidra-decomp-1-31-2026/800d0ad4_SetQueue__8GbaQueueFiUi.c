// Function: SetQueue__8GbaQueueFiUi
// Entry: 800d0ad4
// Size: 196 bytes

undefined4 SetQueue__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  if (gbaQueue->compatibilityStr[param_2 + -0x18] == '\0') {
    if (*(int *)(gbaQueue->compatibilityStr + param_2 * 4 + -0x28) < 0x40) {
      uVar1 = 0;
      *(undefined4 *)
       ((int)gbaQueue->accessSemaphores +
       *(int *)(gbaQueue->compatibilityStr + param_2 * 4 + -0x28) * 4 + param_2 * 0x100 + 0x30) =
           param_3;
      *(int *)(gbaQueue->compatibilityStr + param_2 * 4 + -0x28) =
           *(int *)(gbaQueue->compatibilityStr + param_2 * 4 + -0x28) + 1;
    }
    else {
      uVar1 = 0xffffffff;
      gbaQueue->compatibilityStr[param_2 + -0x18] = '\x01';
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return uVar1;
}

