// Function: ChkCMakeCharaType__8GbaQueueFiUi
// Entry: 800cc394
// Size: 560 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChkCMakeCharaType__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,undefined4 param_3)

{
  char cVar1;
  bool bVar2;
  ushort uVar3;
  GbaQueue *pGVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined uStack_27;
  byte bStack_26;
  
  bStack_26 = (byte)((uint)param_3 >> 8);
  if (bStack_26 == 0xff) {
    OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
    (&gbaQueue->field_0x2cca)[param_2 * 0x20] = 0xff;
    (&gbaQueue->field_0x2cd1)[param_2 * 0x20] = 0xff;
    OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  }
  else {
    bVar2 = false;
    iVar5 = 0;
    pGVar4 = gbaQueue;
    do {
      OSWaitSemaphore(pGVar4->accessSemaphores);
      iVar5 = iVar5 + 1;
      pGVar4 = (GbaQueue *)(pGVar4->accessSemaphores + 1);
    } while (iVar5 < 4);
    cVar1 = (&gbaQueue->field_0x2cb8)[param_2 * 0x20];
    iVar5 = 0;
    iVar6 = 4;
    pGVar4 = gbaQueue;
    do {
      uStack_27 = (undefined)((uint)param_3 >> 0x10);
      if (((param_2 != iVar5) && (pGVar4->cmakeInfo != '\0')) && (pGVar4->field_0x2cca == bStack_26)
         ) {
        SendResult__6JoyBusFiiii(&Joybus,param_2,1,uStack_27,0);
        bVar2 = true;
        break;
      }
      pGVar4 = (GbaQueue *)&pGVar4->accessSemaphores[2].queue.tail;
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar5 = 0;
    pGVar4 = gbaQueue;
    do {
      OSSignalSemaphore(pGVar4->accessSemaphores);
      iVar5 = iVar5 + 1;
      pGVar4 = (GbaQueue *)(pGVar4->accessSemaphores + 1);
    } while (iVar5 < 4);
    if (!bVar2) {
      iVar5 = -0x7fde1140;
      iVar6 = 0;
      iVar7 = 8;
      do {
        if (((iVar6 != cVar1) && (*(int *)(iVar5 + 0x1794) != 0)) &&
           (*(char *)(iVar5 + 0x1f96) == '\0')) {
          uVar3 = *(ushort *)(iVar5 + 0x17d0) & 0xff |
                  (ushort)(byte)((char)*(undefined2 *)(iVar5 + 0x17d4) << 2);
          if (*(short *)(iVar5 + 0x17d2) != 0) {
            uVar3 = uVar3 | 0x80;
          }
          if (uVar3 == bStack_26) {
            SendResult__6JoyBusFiiii(&Joybus,param_2,1,uStack_27,0);
            return;
          }
        }
        iVar5 = iVar5 + 0xc30;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      SendResult__6JoyBusFiiii(&Joybus,param_2,0,uStack_27,0);
      OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
      (&gbaQueue->field_0x2cca)[param_2 * 0x20] = bStack_26;
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
      ChgModel__8CMenuPcsFiiii
                (&MenuPcs,(int)cVar1,bStack_26 & 3,bStack_26 >> 2 & 3,(int)(uint)bStack_26 >> 7);
    }
  }
  return;
}

