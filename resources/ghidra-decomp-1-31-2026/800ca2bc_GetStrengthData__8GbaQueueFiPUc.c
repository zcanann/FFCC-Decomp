// Function: GetStrengthData__8GbaQueueFiPUc
// Entry: 800ca2bc
// Size: 128 bytes

void GetStrengthData__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,char *param_3)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  *param_3 = gbaQueue->compatibilityStr[param_2 * 0xdc + 0x1c];
  param_3[1] = gbaQueue->compatibilityStr[param_2 * 0xdc + 0x1d];
  param_3[2] = gbaQueue->compatibilityStr[param_2 * 0xdc + 0x1e];
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

