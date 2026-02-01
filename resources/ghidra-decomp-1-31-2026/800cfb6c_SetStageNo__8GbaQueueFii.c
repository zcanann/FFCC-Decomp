// Function: SetStageNo__8GbaQueueFii
// Entry: 800cfb6c
// Size: 332 bytes

void SetStageNo__8GbaQueueFii(GbaQueue *gbaQueue,int param_2,int param_3)

{
  int iVar1;
  GbaQueue *pGVar2;
  
  iVar1 = 0;
  pGVar2 = gbaQueue;
  do {
    OSWaitSemaphore(pGVar2->accessSemaphores);
    iVar1 = iVar1 + 1;
    pGVar2 = (GbaQueue *)(pGVar2->accessSemaphores + 1);
  } while (iVar1 < 4);
  gbaQueue->shopFlg = 0;
  gbaQueue->field_0x2d39 = 0;
  gbaQueue->startBonusFlg = 0;
  gbaQueue->scrInitEnd = 0;
  gbaQueue->field_0x2c88 = 0;
  memset(&gbaQueue->field_0x2b00,0,0x188);
  if ((*(int *)&gbaQueue->field_0x444 != param_2) || (*(int *)&gbaQueue->field_0x448 != param_3)) {
    gbaQueue->field_0x44c = 0xf;
    gbaQueue->chgUseItemFlg = 0xf;
  }
  *(int *)&gbaQueue->field_0x444 = param_2;
  iVar1 = 0;
  *(int *)&gbaQueue->field_0x448 = param_3;
  gbaQueue->chgScouFlg = 0xf;
  pGVar2 = gbaQueue;
  do {
    OSSignalSemaphore(pGVar2->accessSemaphores);
    iVar1 = iVar1 + 1;
    pGVar2 = (GbaQueue *)(pGVar2->accessSemaphores + 1);
  } while (iVar1 < 4);
  iVar1 = LoadMap__6JoyBusFii(&Joybus,param_2,param_3);
  if (iVar1 == 0) {
    iVar1 = 0;
    pGVar2 = gbaQueue;
    do {
      OSWaitSemaphore(pGVar2->accessSemaphores);
      iVar1 = iVar1 + 1;
      pGVar2 = (GbaQueue *)(pGVar2->accessSemaphores + 1);
    } while (iVar1 < 4);
    gbaQueue->field_0x44c = 0xf;
    iVar1 = 0;
    gbaQueue->chgUseItemFlg = 0xf;
    pGVar2 = gbaQueue;
    do {
      OSSignalSemaphore(pGVar2->accessSemaphores);
      iVar1 = iVar1 + 1;
      pGVar2 = (GbaQueue *)(pGVar2->accessSemaphores + 1);
    } while (iVar1 < 4);
  }
  memset(&gbaQueue->hitEInfo,0xff,0x10);
  gbaQueue->chgHitFlg = 0;
  return;
}

