// Function: CnvPlayTime__14CMemoryCardManFUiPiPi
// Entry: 800c2140
// Size: 96 bytes

void CnvPlayTime__14CMemoryCardManFUiPiPi
               (CMemoryCardMan *memoryCardMan,uint frames,uint *hours,uint *minutes)

{
  *minutes = (frames / 1500) % 60;
  *hours = (frames / 1500) / 60;
  if ((int)*hours < 999) {
    return;
  }
  *hours = 999;
  return;
}

