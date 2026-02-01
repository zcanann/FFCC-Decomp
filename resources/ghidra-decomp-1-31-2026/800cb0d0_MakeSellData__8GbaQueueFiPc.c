// Function: MakeSellData__8GbaQueueFiPc
// Entry: 800cb0d0
// Size: 972 bytes

/* WARNING: Removing unreachable block (ram,0x800cb480) */
/* WARNING: Removing unreachable block (ram,0x800cb0e0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int MakeSellData__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,undefined *param_3)

{
  void *ptr;
  int iVar1;
  void *ptr_00;
  int iVar2;
  uint32_t *puVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  uint local_58;
  uint local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined4 local_48;
  uint uStack_44;
  longlong local_40;
  
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0xdd5);
  if (ptr == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0xdd7);
    }
    iVar1 = -1;
  }
  else {
    memset(ptr,0,0x400);
    ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0xdde)
    ;
    if (ptr_00 == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0xde0);
      }
      iVar1 = -1;
    }
    else {
      memset(ptr_00,0,0x400);
      iVar1 = 0;
      iVar4 = 0;
      puVar3 = Game.game.m_scriptFoodBase + param_2;
      do {
        local_54 = (uint)*(short *)(*puVar3 + iVar4 + 0xb6);
        if (((int)local_54 < 1) || (0x9e < (int)local_54)) {
          memset(&local_50,0,8);
        }
        else {
          iVar5 = Game.game.unkCFlatData0[2] + local_54 * 0x48;
          local_50 = CONCAT11(*(undefined *)(iVar5 + 5),*(undefined *)(iVar5 + 4));
          local_4e = CONCAT11(*(undefined *)(iVar5 + 7),*(undefined *)(iVar5 + 6));
          local_4c = CONCAT11(*(undefined *)(iVar5 + 9),*(undefined *)(iVar5 + 8));
        }
        memcpy(param_3,&local_50,8);
        iVar1 = iVar1 + 1;
        iVar4 = iVar4 + 2;
        param_3 = param_3 + 8;
      } while (iVar1 < 0x40);
      iVar4 = 0;
      local_48 = 0x43300000;
      iVar5 = 0;
      iVar1 = 0x200;
      uStack_44 = (int)*(short *)(Game.game.m_scriptFoodBase[param_2] + 0xbe2) ^ 0x80000000;
      dVar6 = (double)((float)(((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330d48) /
                              DOUBLE_80330d38) * FLOAT_80330d50);
      do {
        local_54 = (uint)*(short *)(*puVar3 + iVar5 + 0xb6);
        if ((int)local_54 < 1) {
          local_58 = 0;
        }
        else {
          local_48 = 0x43300000;
          uStack_44 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + local_54 * 0x48 + 0x20);
          local_54 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330d40
                                           ) * dVar6);
          local_40 = (longlong)(int)local_54;
          if ((int)local_54 < 1) {
            local_54 = 1;
          }
          local_58 = local_54 << 0x18 | (local_54 >> 8 & 0xff) << 0x10 |
                     (local_54 >> 0x10 & 0xff) << 8 | local_54 >> 0x18;
        }
        memcpy(param_3,&local_58,4);
        iVar4 = iVar4 + 1;
        iVar1 = iVar1 + 4;
        iVar5 = iVar5 + 2;
        param_3 = param_3 + 4;
      } while (iVar4 < 0x40);
      iVar5 = 0;
      iVar4 = 0;
      do {
        memset(ptr,0,0x400);
        memset(ptr_00,0,0x400);
        local_54 = (uint)*(short *)(*puVar3 + iVar4 + 0xb6);
        if ((int)local_54 < 1) {
          iVar1 = iVar1 + 1;
          *param_3 = 0;
          param_3 = param_3 + 1;
        }
        else {
          strcpy(ptr,Game.game.m_cFlatDataArr[1].m_table[6].index[local_54]);
          MakeAgbString__4CMesFPcPcii(ptr_00,ptr,0,0);
          iVar2 = strlen(ptr_00);
          local_58 = iVar2 + 1;
          memcpy(param_3,ptr_00,local_58);
          param_3 = param_3 + local_58;
          iVar1 = iVar1 + local_58;
        }
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 2;
      } while (iVar5 < 0x40);
      __dla__FPv(ptr_00);
      __dla__FPv(ptr);
      OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
      gbaQueue->sellFlg = gbaQueue->sellFlg | (byte)(1 << param_2);
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
      SetLetterSize__6JoyBusFii(&Joybus,param_2,iVar1);
    }
  }
  return iVar1;
}

