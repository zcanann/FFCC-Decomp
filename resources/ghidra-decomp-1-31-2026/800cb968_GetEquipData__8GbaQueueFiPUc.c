// Function: GetEquipData__8GbaQueueFiPUc
// Entry: 800cb968
// Size: 412 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetEquipData__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined *puVar4;
  char cVar5;
  uint uVar6;
  void *dstBuffer;
  int iVar7;
  int iVar8;
  undefined2 local_148;
  undefined2 local_146;
  undefined2 local_144;
  char local_140 [64];
  undefined auStack_100 [58];
  short local_c6 [85];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
  memcpy(auStack_100,gbaQueue->compatibilityStr + param_2 * 0xdc + -4,0xdc);
  memcpy(param_3,&gbaQueue->field_0x52b + param_2 * 0xdc,4);
  OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
  memset(local_140,0xff,0x40);
  iVar7 = 0;
  cVar5 = '\0';
  puVar4 = auStack_100;
  iVar1 = 0x40;
  pcVar2 = local_140;
  do {
    if ((-1 < *(short *)(puVar4 + 0x3a)) && (*(short *)(puVar4 + 0x3a) < 0x9f)) {
      *pcVar2 = cVar5;
      iVar7 = iVar7 + 1;
      pcVar2 = pcVar2 + 1;
    }
    puVar4 = puVar4 + 2;
    cVar5 = cVar5 + '\x01';
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  uVar6 = iVar7 + 1;
  if ((uVar6 & 3) != 0) {
    uVar6 = (((int)uVar6 >> 2) + 1) * 4;
  }
  *(char *)((int)param_3 + 4) = (char)iVar7;
  memcpy((void *)((int)param_3 + 5),local_140,uVar6 - 1);
  iVar1 = uVar6 + 4;
  pcVar2 = local_140;
  dstBuffer = (void *)((int)param_3 + 5 + (uVar6 - 1));
  for (iVar8 = 0; iVar8 < iVar7; iVar8 = iVar8 + 1) {
    iVar3 = Game.game.unkCFlatData0[2] + local_c6[*pcVar2] * 0x48;
    local_148 = CONCAT11(*(undefined *)(iVar3 + 5),*(undefined *)(iVar3 + 4));
    local_146 = CONCAT11(*(undefined *)(iVar3 + 7),*(undefined *)(iVar3 + 6));
    local_144 = CONCAT11(*(undefined *)(iVar3 + 9),*(undefined *)(iVar3 + 8));
    memcpy(dstBuffer,&local_148,8);
    dstBuffer = (void *)((int)dstBuffer + 8);
    iVar1 = iVar1 + 8;
    pcVar2 = pcVar2 + 1;
  }
  return iVar1;
}

