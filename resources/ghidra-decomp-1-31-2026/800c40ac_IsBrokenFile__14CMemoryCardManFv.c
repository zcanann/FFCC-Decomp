// Function: IsBrokenFile__14CMemoryCardManFv
// Entry: 800c40ac
// Size: 48 bytes

undefined4 IsBrokenFile__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  if (((memoryCardMan->mcardStat).iconAddr != 0xffffffff) &&
     ((memoryCardMan->mcardStat).commentAddr != 0xffffffff)) {
    return 0;
  }
  return 1;
}

