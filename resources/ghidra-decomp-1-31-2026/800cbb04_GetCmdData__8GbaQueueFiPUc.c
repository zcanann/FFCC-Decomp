// Function: GetCmdData__8GbaQueueFiPUc
// Entry: 800cbb04
// Size: 328 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetCmdData__8GbaQueueFiPUc(GbaQueue *gbaQueue,int playerIndex,char *commandData)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int itemId;
  char *dstBuffer;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  undefined2 local_118;
  undefined2 local_116;
  undefined2 local_114;
  undefined auStack_110 [2];
  byte local_10e;
  short local_d6 [87];
  
  OSWaitSemaphore(gbaQueue->accessSemaphores + playerIndex);
  memcpy(auStack_110,gbaQueue->compatibilityStr + playerIndex * 0xdc + -4,0xdc);
  OSSignalSemaphore(gbaQueue->accessSemaphores + playerIndex);
  cVar4 = '\0';
  *commandData = '\0';
  commandData[1] = '\0';
  puVar7 = auStack_110;
  commandData[2] = '\0';
  dstBuffer = commandData + 4;
  commandData[3] = '\0';
  iVar5 = 4;
  for (iVar6 = 0; iVar6 < 0x40; iVar6 = iVar6 + 1) {
    itemId = (int)*(short *)(puVar7 + 0x3a);
    iVar2 = GetItemType__8CMenuPcsFii(&MenuPcs,itemId,1);
    if ((iVar2 == 1) &&
       (uVar1 = (uint)local_10e, uVar3 = GetItemIcon__8CMenuPcsFi(&MenuPcs,itemId),
       uVar3 == (uVar1 & 3))) {
      iVar2 = Game.game.unkCFlatData0[2] + itemId * 0x48;
      local_118 = CONCAT11(*(undefined *)(iVar2 + 5),*(undefined *)(iVar2 + 4));
      local_116 = CONCAT11(*(undefined *)(iVar2 + 7),*(undefined *)(iVar2 + 6));
      local_114 = CONCAT11(*(undefined *)(iVar2 + 9),*(undefined *)(iVar2 + 8));
      memcpy(dstBuffer,&local_118,8);
      dstBuffer = dstBuffer + 8;
      iVar5 = iVar5 + 8;
      cVar4 = cVar4 + '\x01';
    }
    puVar7 = puVar7 + 2;
  }
  *commandData = cVar4;
  return iVar5;
}

