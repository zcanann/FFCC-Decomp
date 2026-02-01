// Function: GetMapObjDrawFlg__8GbaQueueFPUi
// Entry: 800ccdac
// Size: 140 bytes

void GetMapObjDrawFlg__8GbaQueueFPUi(GbaQueue *gbaQueue,undefined4 *param_2)

{
  int iVar1;
  GbaQueue *osSemaphore;
  
  iVar1 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar1 = iVar1 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar1 < 4);
  iVar1 = 0;
  *param_2 = *(undefined4 *)&gbaQueue->field_0x2b04;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar1 = iVar1 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar1 < 4);
  return;
}

