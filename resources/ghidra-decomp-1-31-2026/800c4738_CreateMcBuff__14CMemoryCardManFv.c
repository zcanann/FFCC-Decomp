// Function: CreateMcBuff__14CMemoryCardManFv
// Entry: 800c4738
// Size: 164 bytes

void CreateMcBuff__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  uint8_t *puVar1;
  
  if (memoryCardMan->m_saveBuffer == (uint8_t *)0x0) {
    puVar1 = (uint8_t *)
             __nwa__FUlPQ27CMemory6CStagePci
                       (0xa000,memoryCardMan->mStage,s_memorycard_cpp_801daea8,0x2ab);
    memoryCardMan->m_saveBuffer = puVar1;
    if ((memoryCardMan->m_saveBuffer == (uint8_t *)0x0) && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801daeb8,s_memorycard_cpp_801daea8,0x2ad
                );
    }
  }
  memset(memoryCardMan->m_saveBuffer,0,0xa000);
  return;
}

