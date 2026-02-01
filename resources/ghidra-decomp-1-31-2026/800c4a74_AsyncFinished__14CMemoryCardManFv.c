// Function: AsyncFinished__14CMemoryCardManFv
// Entry: 800c4a74
// Size: 24 bytes

uint AsyncFinished__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  return (uint)(-(int)(char)memoryCardMan->m_opDoneFlag | (int)(char)memoryCardMan->m_opDoneFlag) >>
         0x1f;
}

