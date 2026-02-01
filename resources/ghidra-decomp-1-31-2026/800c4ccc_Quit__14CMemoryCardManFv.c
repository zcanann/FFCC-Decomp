// Function: Quit__14CMemoryCardManFv
// Entry: 800c4ccc
// Size: 88 bytes

void Quit__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  memoryCardMan->m_currentSlot = 0xff;
  if (memoryCardMan->mMountWorkArea != (void *)0x0) {
    __dla__FPv(memoryCardMan->mMountWorkArea);
    memoryCardMan->mMountWorkArea = (void *)0x0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,memoryCardMan->mStage);
  return;
}

