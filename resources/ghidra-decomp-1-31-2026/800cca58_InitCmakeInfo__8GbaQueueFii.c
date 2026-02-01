// Function: InitCmakeInfo__8GbaQueueFii
// Entry: 800cca58
// Size: 144 bytes

void InitCmakeInfo__8GbaQueueFii(GbaQueue *gbaQueue,int param_2,undefined param_3)

{
  int iVar1;
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  iVar1 = param_2 * 0x20;
  memset(&gbaQueue->cmakeInfo + iVar1,0,0x20);
  (&gbaQueue->cmakeInfo)[iVar1] = 1;
  (&gbaQueue->field_0x2cca)[iVar1] = 0xff;
  (&gbaQueue->field_0x2cd1)[iVar1] = 0xff;
  (&gbaQueue->field_0x2cb8)[iVar1] = param_3;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  SetMType__6JoyBusFii(&Joybus,param_2,1);
  return;
}

