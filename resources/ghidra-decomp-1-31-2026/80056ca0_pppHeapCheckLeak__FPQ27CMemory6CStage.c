// Function: pppHeapCheckLeak__FPQ27CMemory6CStage
// Entry: 80056ca0
// Size: 76 bytes

uint pppHeapCheckLeak__FPQ27CMemory6CStage(CStage *stage)

{
  undefined auStack_18 [4];
  int local_14;
  uint local_10 [4];
  
  heapInfo__Q27CMemory6CStageFRUlRUlRUl(stage,local_10,&local_14,auStack_18);
  if (local_10[0] == 0) {
    local_10[0] = 10000;
  }
  else {
    local_10[0] = (uint)(local_14 * 10000) / local_10[0];
  }
  return local_10[0];
}

