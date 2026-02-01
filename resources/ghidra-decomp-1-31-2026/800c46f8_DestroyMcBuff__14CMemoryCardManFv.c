// Function: DestroyMcBuff__14CMemoryCardManFv
// Entry: 800c46f8
// Size: 64 bytes

void DestroyMcBuff__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  if (memoryCardMan->m_saveBuffer != (uint8_t *)0x0) {
    __dla__FPv(memoryCardMan->m_saveBuffer);
    memoryCardMan->m_saveBuffer = (uint8_t *)0x0;
  }
  return;
}

