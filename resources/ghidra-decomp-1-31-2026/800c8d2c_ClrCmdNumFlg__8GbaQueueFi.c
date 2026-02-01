// Function: ClrCmdNumFlg__8GbaQueueFi
// Entry: 800c8d2c
// Size: 108 bytes

void ClrCmdNumFlg__8GbaQueueFi(GbaQueue *cmdNumFlg,int param_2)

{
  OSWaitSemaphore(cmdNumFlg->accessSemaphores + param_2);
  cmdNumFlg->cmdNumFlag = cmdNumFlg->cmdNumFlag & ~(byte)(3 << (param_2 << 1));
  OSSignalSemaphore(cmdNumFlg->accessSemaphores + param_2);
  return;
}

