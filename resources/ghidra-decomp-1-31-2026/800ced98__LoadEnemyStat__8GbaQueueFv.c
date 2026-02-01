// Function: ?LoadEnemyStat__8GbaQueueFv
// Entry: 800ced98
// Size: 472 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _LoadEnemyStat__8GbaQueueFv(GbaQueue *gbaQueue)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  GbaQueue *osSemaphore;
  undefined *puVar5;
  int iVar6;
  undefined auStack_528 [1280];
  longlong local_28;
  longlong local_20;
  
  memset(auStack_528,0,0x500);
  if (CFlat._66564_4_ != 0) {
    puVar5 = auStack_528;
    iVar6 = -0x7fde1140;
    iVar4 = 0;
    do {
      if (*(int *)(iVar6 + 0xc5d0) == 0) {
        puVar5[3] = 0;
      }
      else {
        sVar1 = *(short *)(Game.game.unkCFlatData0[1] +
                          *(int *)(*(int *)(iVar6 + 0xc6d0) + 0x10) * 0x1d0 + 0x10c);
        if (sVar1 == 10) {
          puVar5[1] = 1;
        }
        else if (sVar1 == 0xb) {
          puVar5[1] = 3;
        }
        else {
          puVar5[1] = 2;
        }
        iVar3 = *(int *)(iVar6 + 0xc6d0);
        iVar2 = *(int *)(iVar6 + 0xc5d0);
        puVar5[3] = (char)*(undefined4 *)(iVar3 + 0x10);
        *(undefined2 *)(puVar5 + 4) = *(undefined2 *)(iVar3 + 0x1c);
        *(undefined2 *)(puVar5 + 6) = *(undefined2 *)(iVar3 + 0x1a);
        iVar2 = (**(code **)(*(int *)(iVar2 + 0x48) + 0x2c))();
        iVar3 = *(int *)(iVar6 + 0xc5d0);
        puVar5[2] = (byte)((byte)((uint)-iVar2 >> 0x18) | (byte)((uint)iVar2 >> 0x18)) >> 7;
        *(undefined2 *)(puVar5 + 0xc) = *(undefined2 *)(iVar3 + 0x510);
        *(undefined2 *)(puVar5 + 0xe) = *(undefined2 *)(iVar3 + 0x512);
        *(undefined2 *)(puVar5 + 0x10) = *(undefined2 *)(iVar3 + 0x514);
        *(undefined2 *)(puVar5 + 0x12) = *(undefined2 *)(iVar3 + 0x516);
        iVar2 = (int)(*(float *)(iVar3 + 0x15c) / FLOAT_80330d54);
        local_20 = (longlong)iVar2;
        iVar3 = (int)(*(float *)(iVar3 + 0x164) / FLOAT_80330d54);
        local_28 = (longlong)iVar3;
        *(short *)(puVar5 + 8) = (short)iVar2;
        *(short *)(puVar5 + 10) = (short)iVar3;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 0x14;
      iVar6 = iVar6 + 4;
    } while (iVar4 < 0x40);
  }
  iVar4 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar4 = iVar4 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar4 < 4);
  memcpy(&gbaQueue->field_0xb34,auStack_528,0x500);
  iVar4 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar4 = iVar4 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar4 < 4);
  return;
}

