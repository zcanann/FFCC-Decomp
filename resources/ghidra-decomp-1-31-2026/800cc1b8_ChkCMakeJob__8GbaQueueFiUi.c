// Function: ChkCMakeJob__8GbaQueueFiUi
// Entry: 800cc1b8
// Size: 476 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChkCMakeJob__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,undefined4 param_3)

{
  char cVar1;
  bool bVar2;
  GbaQueue *pGVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined uStack_27;
  byte bStack_26;
  
  bStack_26 = (byte)((uint)param_3 >> 8);
  if (bStack_26 == 0xff) {
    OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
    (&gbaQueue->field_0x2cd1)[param_2 * 0x20] = 0xff;
    OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  }
  else {
    bVar2 = false;
    iVar4 = 0;
    pGVar3 = gbaQueue;
    do {
      OSWaitSemaphore(pGVar3->accessSemaphores);
      iVar4 = iVar4 + 1;
      pGVar3 = (GbaQueue *)(pGVar3->accessSemaphores + 1);
    } while (iVar4 < 4);
    cVar1 = (&gbaQueue->field_0x2cb8)[param_2 * 0x20];
    iVar4 = 0;
    iVar5 = 4;
    pGVar3 = gbaQueue;
    do {
      uStack_27 = (undefined)((uint)param_3 >> 0x10);
      if (((param_2 != iVar4) && (pGVar3->cmakeInfo != '\0')) && (pGVar3->field_0x2cd1 == bStack_26)
         ) {
        SendResult__6JoyBusFiiii(&Joybus,param_2,1,uStack_27,0);
        bVar2 = true;
        break;
      }
      pGVar3 = (GbaQueue *)&pGVar3->accessSemaphores[2].queue.tail;
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar4 = 0;
    pGVar3 = gbaQueue;
    do {
      OSSignalSemaphore(pGVar3->accessSemaphores);
      iVar4 = iVar4 + 1;
      pGVar3 = (GbaQueue *)(pGVar3->accessSemaphores + 1);
    } while (iVar4 < 4);
    if (!bVar2) {
      iVar4 = -0x7fde1140;
      iVar5 = 0;
      iVar6 = 8;
      do {
        if (((iVar5 != cVar1) && (*(int *)(iVar4 + 0x1794) != 0)) &&
           ((*(char *)(iVar4 + 0x1f96) == '\0' &&
            ((*(uint *)(iVar4 + 0x179c) & 0xff) == (uint)bStack_26)))) {
          SendResult__6JoyBusFiiii(&Joybus,param_2,1,uStack_27,0);
          return;
        }
        iVar4 = iVar4 + 0xc30;
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      SendResult__6JoyBusFiiii(&Joybus,param_2,0,uStack_27,0);
      OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
      (&gbaQueue->field_0x2cd1)[param_2 * 0x20] = bStack_26;
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
    }
  }
  return;
}

