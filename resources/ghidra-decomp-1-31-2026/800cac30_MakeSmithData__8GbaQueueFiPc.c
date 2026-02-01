// Function: MakeSmithData__8GbaQueueFiPc
// Entry: 800cac30
// Size: 1184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int MakeSmithData__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,char *param_3)

{
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  void *ptr;
  int iVar5;
  uint *puVar6;
  char cVar8;
  uint *puVar7;
  int iVar9;
  int iVar10;
  char *dstBuffer;
  char cVar11;
  uint32_t *puVar12;
  int iVar13;
  int iVar14;
  uint local_88;
  uint local_84;
  undefined2 local_80;
  undefined2 local_7e;
  undefined2 local_7c;
  undefined2 local_7a;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74 [22];
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x40,uRam8032edac,s_gbaque_cpp_801db370,0xe41);
  if (ptr == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0xe43);
    }
    iVar5 = -1;
  }
  else {
    memset(ptr,0xff,0x40);
    cVar11 = '\0';
    cVar8 = '\0';
    iVar5 = 0;
    iVar13 = 0x10;
    puVar12 = Game.game.m_scriptFoodBase + param_2;
    do {
      if (400 < *(short *)(*puVar12 + iVar5 + 0xb6)) {
        iVar3 = (int)cVar11;
        cVar11 = cVar11 + '\x01';
        *(char *)((int)ptr + iVar3) = cVar8;
      }
      if (400 < *(short *)(*puVar12 + iVar5 + 0xb8)) {
        iVar3 = (int)cVar11;
        cVar11 = cVar11 + '\x01';
        *(char *)((int)ptr + iVar3) = cVar8 + '\x01';
      }
      if (400 < *(short *)(*puVar12 + iVar5 + 0xba)) {
        iVar3 = (int)cVar11;
        cVar11 = cVar11 + '\x01';
        *(char *)((int)ptr + iVar3) = cVar8 + '\x02';
      }
      if (400 < *(short *)(*puVar12 + iVar5 + 0xbc)) {
        iVar3 = (int)cVar11;
        cVar11 = cVar11 + '\x01';
        *(char *)((int)ptr + iVar3) = cVar8 + '\x03';
      }
      iVar5 = iVar5 + 8;
      cVar8 = cVar8 + '\x04';
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    *param_3 = cVar11;
    memcpy(param_3 + 1,ptr,(int)cVar11);
    local_88 = (uint)cVar11;
    iVar5 = local_88 + 1;
    uVar1 = iVar5 >> 0x1f;
    if ((uVar1 * 4 | iVar5 * 0x40000000 + uVar1 >> 0x1e) != uVar1) {
      local_88 = ((iVar5 >> 2) + 1) * 4 - 1;
    }
    iVar13 = 0;
    iVar3 = 0;
    dstBuffer = param_3 + 1 + local_88;
    iVar5 = local_88 + 1;
    do {
      iVar4 = (int)*(short *)(*puVar12 + iVar3 + 0xb6);
      if (400 < iVar4) {
        iVar4 = iVar4 * 0x48;
        iVar10 = Game.game.unkCFlatData0[2] + iVar4;
        memset(&local_84,0,0x38);
        uStack_44 = (uint)*(ushort *)(iVar10 + 0x24);
        local_40 = 0x43300000;
        uStack_3c = (int)*(short *)(*puVar12 + 0xbe2) ^ 0x80000000;
        local_48 = 0x43300000;
        uVar1 = (uint)((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330d40) *
                      (float)(((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80330d48) /
                             DOUBLE_80330d38));
        local_38 = (longlong)(int)uVar1;
        local_84 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                   uVar1 >> 0x18;
        puVar6 = &local_84;
        local_80 = CONCAT11(*(undefined *)(iVar10 + 0x27),*(undefined *)(iVar10 + 0x26));
        local_7e = CONCAT11(*(undefined *)(iVar10 + 0x29),*(undefined *)(iVar10 + 0x28));
        local_7c = CONCAT11(*(undefined *)(iVar10 + 0x2b),*(undefined *)(iVar10 + 0x2a));
        local_7a = CONCAT11(*(undefined *)(iVar10 + 0x2d),*(undefined *)(iVar10 + 0x2c));
        local_78 = CONCAT11(*(undefined *)(iVar10 + 0x2f),*(undefined *)(iVar10 + 0x2e));
        local_76 = CONCAT11(*(undefined *)(iVar10 + 0x31),*(undefined *)(iVar10 + 0x30));
        iVar10 = 0;
        iVar14 = 2;
        puVar7 = puVar6;
        do {
          iVar9 = Game.game.unkCFlatData0[2] + iVar4 + iVar10;
          *(ushort *)(puVar7 + 4) =
               CONCAT11(*(undefined *)(iVar9 + 0x39),*(undefined *)(iVar9 + 0x38));
          if (*(ushort *)(iVar9 + 0x38) == 0) {
            *(undefined2 *)(puVar6 + 6) = 0;
            *(undefined2 *)((int)puVar6 + 0x1a) = 0;
            *(undefined2 *)(puVar6 + 7) = 0;
          }
          else {
            iVar9 = Game.game.unkCFlatData0[2] + (uint)*(ushort *)(iVar9 + 0x38) * 0x48;
            *(ushort *)(puVar6 + 6) = CONCAT11(*(undefined *)(iVar9 + 5),*(undefined *)(iVar9 + 4));
            *(ushort *)((int)puVar6 + 0x1a) =
                 CONCAT11(*(undefined *)(iVar9 + 7),*(undefined *)(iVar9 + 6));
            *(ushort *)(puVar6 + 7) = CONCAT11(*(undefined *)(iVar9 + 9),*(undefined *)(iVar9 + 8));
          }
          iVar9 = Game.game.unkCFlatData0[2] + iVar4 + iVar10 + 2;
          *(ushort *)((int)puVar7 + 0x12) =
               CONCAT11(*(undefined *)(iVar9 + 0x39),*(undefined *)(iVar9 + 0x38));
          if (*(ushort *)(iVar9 + 0x38) == 0) {
            *(undefined2 *)(puVar6 + 8) = 0;
            *(undefined2 *)((int)puVar6 + 0x22) = 0;
            *(undefined2 *)(puVar6 + 9) = 0;
          }
          else {
            iVar9 = Game.game.unkCFlatData0[2] + (uint)*(ushort *)(iVar9 + 0x38) * 0x48;
            *(ushort *)(puVar6 + 8) = CONCAT11(*(undefined *)(iVar9 + 5),*(undefined *)(iVar9 + 4));
            *(ushort *)((int)puVar6 + 0x22) =
                 CONCAT11(*(undefined *)(iVar9 + 7),*(undefined *)(iVar9 + 6));
            *(ushort *)(puVar6 + 9) = CONCAT11(*(undefined *)(iVar9 + 9),*(undefined *)(iVar9 + 8));
          }
          iVar10 = iVar10 + 4;
          puVar7 = puVar7 + 1;
          puVar6 = puVar6 + 4;
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        local_88 = 0x38;
        memcpy(dstBuffer,&local_84,0x38);
        dstBuffer = dstBuffer + local_88;
        iVar5 = iVar5 + local_88;
      }
      iVar13 = iVar13 + 1;
      iVar3 = iVar3 + 2;
    } while (iVar13 < 0x40);
    iVar3 = 0;
    iVar13 = 0;
    do {
      pbVar2 = (byte *)(*puVar12 + iVar13 + 0xc08);
      local_88 = (uint)pbVar2[3] << 0x18 | (uint)pbVar2[2] << 0x10 | (uint)pbVar2[1] << 8 |
                 (uint)*pbVar2;
      memcpy(dstBuffer,&local_88,4);
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 4;
      iVar13 = iVar13 + 4;
      dstBuffer = dstBuffer + 4;
    } while (iVar3 < 4);
    __dla__FPv(ptr);
    OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
    gbaQueue->mkSmithFlg = gbaQueue->mkSmithFlg | (byte)(1 << param_2);
    OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
    SetLetterSize__6JoyBusFii(&Joybus,param_2,iVar5);
  }
  return iVar5;
}

