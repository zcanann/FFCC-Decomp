// Function: MakeArtiData__8GbaQueueFiPc
// Entry: 800ca030
// Size: 400 bytes

undefined4 MakeArtiData__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  void *ptr;
  undefined4 uVar1;
  void *ptr_00;
  uint local_28;
  uint local_24;
  uint local_20;
  
  ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uRam8032edac,s_gbaque_cpp_801db370,0x100f);
  if (ptr == (void *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x1011);
    }
    uVar1 = 0xffffffff;
  }
  else {
    memset(ptr,0,0x400);
    ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                               (0x400,uRam8032edac,s_gbaque_cpp_801db370,0x1017);
    if (ptr_00 == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x1019)
        ;
      }
      uVar1 = 0xffffffff;
    }
    else {
      memset(ptr_00,0,0x400);
      OSWaitSemaphore(gbaQueue->accessSemaphores + param_2);
      local_28 = (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x27] << 0x18 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x26] << 0x10 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x25] << 8 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x24];
      local_24 = (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2b] << 0x18 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2a] << 0x10 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x29] << 8 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x28];
      local_20 = (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2f] << 0x18 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2e] << 0x10 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2d] << 8 |
                 (uint)(byte)gbaQueue->compatibilityStr[param_2 * 0xdc + 0x2c];
      OSSignalSemaphore(gbaQueue->accessSemaphores + param_2);
      memcpy(param_3,&local_28,0xc);
      __dla__FPv(ptr_00);
      __dla__FPv(ptr);
      gbaQueue->artiDatFlg = gbaQueue->artiDatFlg | (byte)(1 << param_2);
      SetLetterSize__6JoyBusFii(&Joybus,param_2,0xc);
      uVar1 = 0xc;
    }
  }
  return uVar1;
}

