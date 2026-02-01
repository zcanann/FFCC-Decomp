// Function: LoadMapItemStat__8GbaQueueFv
// Entry: 800cebe4
// Size: 436 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadMapItemStat__8GbaQueueFv(GbaQueue *gbaQueue)

{
  int iVar1;
  CGObject *gObject;
  GbaQueue *osSemaphore;
  int iVar2;
  char cVar3;
  undefined *puVar4;
  undefined auStack_178 [320];
  longlong local_38;
  longlong local_30;
  
  memset(auStack_178,0,0x140);
  cVar3 = '\0';
  if (CFlat._66564_4_ != 0) {
    gObject = (CGObject *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
    puVar4 = auStack_178;
    cVar3 = '\0';
    while( true ) {
      if (gObject == (CGObject *)0x0) break;
      if ((gObject->m_objectFlags & 0x100) != 0) {
        if (((int)(short)gObject->m_dropItemCodes[0] & 0xc000U) == 0x4000) {
          puVar4[1] = 4;
        }
        else if ((int)(uint)*(ushort *)
                             (Game.game.unkCFlatData0[2] + (short)gObject->m_dropItemCodes[0] * 0x48
                             + 0xc) <
                 Game.game.m_gameWork.m_bossArtifactStageTable
                 [Game.game.m_gameWork.m_bossArtifactStageIndex] + 2) {
          puVar4[1] = 4;
        }
        else {
          puVar4[1] = 5;
        }
        iVar2 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0x2c))(gObject);
        cVar3 = cVar3 + '\x01';
        puVar4[2] = (byte)((byte)((uint)-iVar2 >> 0x18) | (byte)((uint)iVar2 >> 0x18)) >> 7;
        iVar2 = (int)((gObject->m_worldPosition).x / FLOAT_80330d54);
        local_30 = (longlong)iVar2;
        iVar1 = (int)((gObject->m_worldPosition).z / FLOAT_80330d54);
        local_38 = (longlong)iVar1;
        *(short *)(puVar4 + 8) = (short)iVar2;
        *(short *)(puVar4 + 10) = (short)iVar1;
        puVar4 = puVar4 + 0x14;
      }
      gObject = (CGObject *)
                FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject);
    }
  }
  gbaQueue->field_0x2af4 = cVar3;
  iVar2 = 0;
  osSemaphore = gbaQueue;
  do {
    OSWaitSemaphore(osSemaphore->accessSemaphores);
    iVar2 = iVar2 + 1;
    osSemaphore = (GbaQueue *)(osSemaphore->accessSemaphores + 1);
  } while (iVar2 < 4);
  memcpy(&gbaQueue->field_0x2434,auStack_178,0x140);
  iVar2 = 0;
  do {
    OSSignalSemaphore(gbaQueue->accessSemaphores);
    iVar2 = iVar2 + 1;
    gbaQueue = (GbaQueue *)(gbaQueue->accessSemaphores + 1);
  } while (iVar2 < 4);
  return;
}

