// Function: MakeLetterData__8GbaQueueFiPci
// Entry: 800cd600
// Size: 592 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int MakeLetterData__8GbaQueueFiPci(GbaQueue *gbaQueue,int param_2,void *param_3,int param_4)

{
  uint32_t *puVar1;
  void *ptr;
  int iVar2;
  void *ptr_00;
  int iVar3;
  
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0x859);
  if (ptr == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x85b);
    }
    iVar2 = -1;
  }
  else {
    memset(ptr,0,0x400);
    ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0x862)
    ;
    if (ptr_00 == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x864);
      }
      iVar2 = -1;
    }
    else {
      memset(ptr_00,0,0x400);
      puVar1 = Game.game.m_scriptFoodBase + param_2;
      iVar3 = *puVar1 + param_4 * 0xc;
      m_tempVar__4CMes._0_4_ = ZEXT24(*(ushort *)(iVar3 + 0x3f0));
      m_tempVar__4CMes._4_4_ = ZEXT24(*(ushort *)(iVar3 + 0x3f2));
      m_tempVar__4CMes._8_4_ = ZEXT24(*(ushort *)(iVar3 + 0x3f4));
      m_tempVar__4CMes._12_4_ = ZEXT24(*(ushort *)(iVar3 + 0x3f6));
      iVar3 = (*(ushort *)(*puVar1 + param_4 * 0xc + 0x3ec) & 0x7fc) * 2;
      strcpy(ptr,*(undefined4 *)((int)Game.game.m_cFlatDataArr[1].m_mesPtr + iVar3 + 0x40));
      MakeAgbString__4CMesFPcPcii(ptr_00,ptr,*(undefined2 *)(*puVar1 + 0x3e2),0);
      iVar2 = strlen(ptr_00);
      iVar2 = iVar2 + 1;
      memcpy(param_3,ptr_00,iVar2);
      memset(ptr,0,0x400);
      memset(ptr_00,0,0x400);
      strcpy(ptr,*(undefined4 *)((int)Game.game.m_cFlatDataArr[1].m_mesPtr + iVar3 + 0x44));
      MakeAgbString__4CMesFPcPcii(ptr_00,ptr,*(undefined2 *)(*puVar1 + 0x3e2),0);
      iVar3 = strlen(ptr_00);
      memcpy((void *)((int)param_3 + iVar2),ptr_00,iVar3 + 1);
      iVar2 = iVar2 + iVar3 + 1;
      __dla__FPv(ptr_00);
      __dla__FPv(ptr);
      gbaQueue->letterDatFlg = gbaQueue->letterDatFlg | (byte)(0x10 << param_2);
      SetLetterSize__6JoyBusFii(&Joybus,param_2,iVar2);
    }
  }
  return iVar2;
}

