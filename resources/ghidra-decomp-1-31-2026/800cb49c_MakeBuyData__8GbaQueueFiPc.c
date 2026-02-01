// Function: MakeBuyData__8GbaQueueFiPc
// Entry: 800cb49c
// Size: 892 bytes

/* WARNING: Removing unreachable block (ram,0x800cb7fc) */
/* WARNING: Removing unreachable block (ram,0x800cb7f4) */
/* WARNING: Removing unreachable block (ram,0x800cb4b4) */
/* WARNING: Removing unreachable block (ram,0x800cb4ac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int MakeBuyData__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,undefined *param_3)

{
  uint32_t *puVar1;
  short sVar2;
  undefined2 uVar3;
  void *ptr;
  int letterSize;
  void *ptr_00;
  int iVar4;
  undefined *dstBuffer;
  uint uVar5;
  uint32_t *puVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  undefined2 local_78;
  undefined2 local_76;
  uint local_74;
  uint local_70;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0xd79);
  if (ptr == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0xd7b);
    }
    letterSize = -1;
  }
  else {
    memset(ptr,0,0x400);
    ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0xd82)
    ;
    if (ptr_00 == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0xd84);
      }
      letterSize = -1;
    }
    else {
      memset(ptr_00,0,0x400);
      dstBuffer = param_3 + 4;
      puVar1 = Game.game.m_scriptFoodBase + param_2;
      iVar7 = 0;
      sVar2 = *(short *)(*puVar1 + 0xbe4);
      uVar5 = (uint)sVar2;
      letterSize = 4;
      puVar6 = Game.game.m_scriptFoodBase + param_2;
      *param_3 = (char)sVar2;
      for (iVar8 = 0; iVar8 < (int)uVar5; iVar8 = iVar8 + 1) {
        uVar3 = *(undefined2 *)(*puVar6 + iVar7 + 0xbe6);
        local_76._1_1_ = (undefined)uVar3;
        local_76._0_1_ = (undefined)((ushort)uVar3 >> 8);
        local_78 = CONCAT11((undefined)local_76,local_76._0_1_);
        local_76 = uVar3;
        memcpy(dstBuffer,&local_78,2);
        dstBuffer = dstBuffer + 2;
        letterSize = letterSize + 2;
        iVar7 = iVar7 + 2;
      }
      if ((uVar5 & 1) != 0) {
        dstBuffer = dstBuffer + 2;
        letterSize = letterSize + 2;
      }
      local_68 = 0x43300000;
      iVar8 = 0;
      uStack_64 = (int)*(short *)(*puVar1 + 0xbe2) ^ 0x80000000;
      dVar9 = (double)(float)(((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330d48) /
                             DOUBLE_80330d38);
      dVar10 = DOUBLE_80330d40;
      for (iVar7 = 0; iVar7 < (int)uVar5; iVar7 = iVar7 + 1) {
        local_68 = 0x43300000;
        uStack_64 = (uint)*(ushort *)
                           (Game.game.unkCFlatData0[2] +
                           *(short *)(*puVar6 + iVar8 + 0xbe6) * 0x48 + 0x20);
        local_70 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_64) - dVar10) * dVar9);
        local_60 = (longlong)(int)local_70;
        if ((int)local_70 < 1) {
          local_70 = 1;
        }
        local_74 = local_70 << 0x18 | (local_70 >> 8 & 0xff) << 0x10 |
                   (local_70 >> 0x10 & 0xff) << 8 | local_70 >> 0x18;
        memcpy(dstBuffer,&local_74,4);
        dstBuffer = dstBuffer + 4;
        letterSize = letterSize + 4;
        iVar8 = iVar8 + 2;
      }
      iVar7 = 0;
      for (iVar8 = 0; iVar8 < (int)uVar5; iVar8 = iVar8 + 1) {
        memset(ptr,0,0x400);
        memset(ptr_00,0,0x400);
        strcpy(ptr,Game.game.m_cFlatDataArr[1].m_table[6].index[*(short *)(*puVar6 + iVar7 + 0xbe6)]
              );
        MakeAgbString__4CMesFPcPcii(ptr_00,ptr,0,0);
        iVar4 = strlen(ptr_00);
        iVar4 = iVar4 + 1;
        memcpy(dstBuffer,ptr_00,iVar4);
        dstBuffer = dstBuffer + iVar4;
        letterSize = letterSize + iVar4;
        iVar7 = iVar7 + 2;
      }
      __dla__FPv(ptr_00);
      __dla__FPv(ptr);
      OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
      gbaQueue->buyFlg = gbaQueue->buyFlg | (byte)(1 << param_2);
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
      SetLetterSize__6JoyBusFii(&Joybus,param_2,letterSize);
    }
  }
  return letterSize;
}

