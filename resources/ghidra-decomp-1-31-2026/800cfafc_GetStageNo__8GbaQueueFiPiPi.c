// Function: GetStageNo__8GbaQueueFiPiPi
// Entry: 800cfafc
// Size: 112 bytes

void GetStageNo__8GbaQueueFiPiPi
               (GbaQueue *gbaQueue,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  *param_3 = *(undefined4 *)&gbaQueue->field_0x444;
  *param_4 = *(undefined4 *)&gbaQueue->field_0x448;
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  return;
}

