// Function: pppDestroyHeap__FP9_pppEnvSt
// Entry: 80057314
// Size: 48 bytes

void pppDestroyHeap__FP9_pppEnvSt(_pppEnvSt *pppEnvSt)

{
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,pppEnvSt->m_stagePtr);
  return;
}

