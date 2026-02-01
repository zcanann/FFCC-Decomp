// Function: McFreeBlocks__14CMemoryCardManFiPiPi
// Entry: 800c413c
// Size: 120 bytes

int32_t McFreeBlocks__14CMemoryCardManFiPiPi
                  (CMemoryCardMan *memoryCardMan,int chan,undefined4 *bytesFree,
                  undefined4 *filesFree)

{
  int32_t iVar1;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  iVar1 = CARDFreeBlocks(chan,local_14,&local_18);
  memoryCardMan->mResult = iVar1;
  *bytesFree = local_14[0];
  *filesFree = local_18;
  memoryCardMan->mState = '\f';
  memoryCardMan->m_opDoneFlag = '\x01';
  return memoryCardMan->mResult;
}

