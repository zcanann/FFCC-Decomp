// Function: pppHeapUseRate__FPQ27CMemory6CStage
// Entry: 80056cec
// Size: 52 bytes

void pppHeapUseRate__FPQ27CMemory6CStage(CStage *stage)

{
  if (stage != (CStage *)0x0) {
    Free__7CMemoryFPv(&Memory,stage);
  }
  return;
}

