// Function: ChkCMakeName__8GbaQueueFiUi
// Entry: 800cc5c4
// Size: 1048 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChkCMakeName__8GbaQueueFiUi(GbaQueue *gbaQueue,int param_2,uint param_3)

{
  int iVar1;
  short sVar3;
  int iVar2;
  int iVar4;
  int iVar5;
  GbaQueue *pGVar6;
  OSSemaphore *osSemaphore;
  undefined local_58;
  undefined uStack_57;
  undefined uStack_56;
  undefined uStack_55;
  undefined2 local_54 [2];
  undefined local_50;
  undefined local_4f;
  undefined2 local_4e;
  short local_4c;
  char local_4a;
  undefined auStack_49 [17];
  undefined local_38;
  undefined auStack_37 [2];
  undefined auStack_35 [4];
  undefined local_31;
  
  uStack_55 = (undefined)param_3;
  uStack_56 = (undefined)(param_3 >> 8);
  uStack_57 = (undefined)(param_3 >> 0x10);
  if ((int)(param_3 >> 0x18) >> 6 == 0) {
    OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
    iVar5 = param_2 * 0x20;
    local_58 = (undefined)(param_3 >> 0x18);
    (&gbaQueue->field_0x2cb3)[iVar5] = local_58;
    *(undefined2 *)(&gbaQueue->field_0x2cb4 + iVar5) = 1;
    *(short *)(&gbaQueue->field_0x2cb6 + iVar5) = (short)(param_3 >> 8);
    memset(&gbaQueue->field_0x2cb9 + iVar5,0,0x11);
    (&gbaQueue->field_0x2cb9)[iVar5] = uStack_55;
    OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  }
  else {
    osSemaphore = gbaQueue->accessSemaphores + param_2;
    OSWaitSemaphore(osSemaphore);
    iVar5 = param_2 * 0x20;
    iVar1 = iVar5 + 0x2cb9;
    iVar4 = *(short *)(&gbaQueue->field_0x2cb4 + iVar5) * 3;
    *(short *)(&gbaQueue->field_0x2cb4 + iVar5) = *(short *)(&gbaQueue->field_0x2cb4 + iVar5) + 1;
    (&gbaQueue->field_0x2cb7)[iVar4 + iVar1 + -0x2cb9] = uStack_57;
    (&gbaQueue->field_0x2cb8)[iVar4 + iVar1 + -0x2cb9] = uStack_56;
    (&gbaQueue->field_0x2cb9)[iVar4 + iVar1 + -0x2cb9] = uStack_55;
    if (5 < *(short *)(&gbaQueue->field_0x2cb4 + iVar5)) {
      local_50 = (&gbaQueue->cmakeInfo)[iVar5];
      local_4f = (&gbaQueue->field_0x2cb3)[iVar5];
      local_4e = *(undefined2 *)(&gbaQueue->field_0x2cb4 + iVar5);
      local_4c = *(short *)(&gbaQueue->field_0x2cb6 + iVar5);
      local_4a = (&gbaQueue->field_0x2cb8)[iVar5];
      __copy(auStack_49,&gbaQueue->field_0x2cb9 + iVar5,0x11);
      local_38 = (&gbaQueue->field_0x2cca)[iVar5];
      __copy(auStack_37,&gbaQueue->field_0x2ccb + iVar5,2);
      __copy(auStack_35,&gbaQueue->field_0x2ccd + iVar5,4);
      local_31 = (&gbaQueue->field_0x2cd1)[iVar5];
    }
    OSSignalSemaphore(osSemaphore);
    if (5 < *(short *)(&gbaQueue->field_0x2cb4 + iVar5)) {
      iVar1 = strlen(&gbaQueue->field_0x2cb9 + iVar5);
      if (iVar1 == 0) {
        (&gbaQueue->field_0x2cca)[iVar5] = 0xff;
        (&gbaQueue->field_0x2cd1)[iVar5] = 0xff;
      }
      else {
        local_54[0] = 0xffff;
        sVar3 = Crc16__6JoyBusFiPUcPUs(&Joybus,0x10,auStack_49,local_54);
        if (sVar3 == local_4c) {
          iVar1 = 0;
          pGVar6 = gbaQueue;
          do {
            OSWaitSemaphore(pGVar6->accessSemaphores);
            iVar1 = iVar1 + 1;
            pGVar6 = (GbaQueue *)(pGVar6->accessSemaphores + 1);
          } while (iVar1 < 4);
          iVar1 = 0;
          pGVar6 = gbaQueue;
          do {
            if (((param_2 != iVar1) && (pGVar6->cmakeInfo != '\0')) &&
               (iVar4 = strcmp(&pGVar6->field_0x2cb9,auStack_49), iVar4 == 0)) {
              memset(&gbaQueue->field_0x2cb9 + iVar5,0,0x11);
              iVar5 = 0;
              do {
                OSSignalSemaphore(gbaQueue->accessSemaphores);
                iVar5 = iVar5 + 1;
                gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
              } while (iVar5 < 4);
              SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_4f,0);
              return;
            }
            iVar1 = iVar1 + 1;
            pGVar6 = (GbaQueue *)&pGVar6->accessSemaphores[2].queue.tail;
          } while (iVar1 < 4);
          iVar1 = 0;
          pGVar6 = gbaQueue;
          do {
            OSSignalSemaphore(pGVar6->accessSemaphores);
            iVar1 = iVar1 + 1;
            pGVar6 = (GbaQueue *)(pGVar6->accessSemaphores + 1);
          } while (iVar1 < 4);
          iVar1 = 0;
          iVar4 = 0;
          do {
            iVar2 = strcmp(*(undefined4 *)
                            ((int)Game.game.m_cFlatDataArr[1].m_table[2].index + iVar4),auStack_49);
            if (iVar2 == 0) {
              SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_4f,0);
              return;
            }
            iVar1 = iVar1 + 1;
            iVar4 = iVar4 + 4;
          } while (iVar1 < 0x100);
          iVar4 = 0;
          iVar1 = -0x7fde1140;
          do {
            if (((iVar4 != local_4a) && (*(int *)(iVar1 + 0x1794) != 0)) &&
               ((*(char *)(iVar1 + 0x1f96) == '\0' &&
                (iVar2 = strcmp(iVar1 + 0x17ba,auStack_49), iVar2 == 0)))) {
              SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_4f,0);
              return;
            }
            iVar4 = iVar4 + 1;
            iVar1 = iVar1 + 0xc30;
          } while (iVar4 < 8);
          SendResult__6JoyBusFiiii(&Joybus,param_2,0,local_4f,0);
          OSWaitSemaphore(osSemaphore);
          (&gbaQueue->field_0x2cb3)[iVar5] = 0;
          *(undefined2 *)(&gbaQueue->field_0x2cb4 + iVar5) = 0;
          *(undefined2 *)(&gbaQueue->field_0x2cb6 + iVar5) = 0;
          OSSignalSemaphore(osSemaphore);
        }
        else {
          if (System.m_execParam != 0) {
            Printf__7CSystemFPce
                      (&System,s__s__d___Error_ChkCMakeName___crc_801db3ec,s_gbaque_cpp_801db370,
                       0xad3);
          }
          SendResult__6JoyBusFiiii(&Joybus,param_2,1,local_4f,0);
        }
      }
    }
  }
  return;
}

