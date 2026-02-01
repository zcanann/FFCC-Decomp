// Function: SetControllerMode__8GbaQueueFi
// Entry: 800c9474
// Size: 232 bytes

void SetControllerMode__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  GbaQueue *osSemaphore;
  
  iVar3 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar3 = iVar3 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar3 < 4);
  gbaQueue->field_0x2d57 = (byte)param_2 & 1;
  iVar3 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar3 = iVar3 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar3 < 4);
  iVar3 = 0;
  do {
    iVar2 = 0;
    do {
      if (param_2 == 0) {
        iVar1 = SetMType__6JoyBusFii(&Joybus,iVar3,0);
      }
      else {
        iVar1 = SetMType__6JoyBusFii(&Joybus,iVar3,4);
      }
    } while ((iVar1 != 0) && (iVar2 = iVar2 + 1, iVar2 < 10));
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  return;
}

