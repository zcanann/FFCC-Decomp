// Function: ClrCompatibilityFlg__8GbaQueueFi
// Entry: 800cbea4
// Size: 96 bytes

void ClrCompatibilityFlg__8GbaQueueFi(GbaQueue *compatibilityFlg,int param_2)

{
  OSWaitSemaphore(compatibilityFlg->accessSemaphores + param_2);
  (&compatibilityFlg->compatibilityFlg)[param_2] = 0;
  OSSignalSemaphore(compatibilityFlg->accessSemaphores + param_2);
  return;
}

