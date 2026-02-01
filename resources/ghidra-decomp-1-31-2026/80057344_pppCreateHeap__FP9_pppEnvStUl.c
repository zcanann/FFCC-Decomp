// Function: pppCreateHeap__FP9_pppEnvStUl
// Entry: 80057344
// Size: 68 bytes

void pppCreateHeap__FP9_pppEnvStUl(_pppEnvSt *pppEnvSt,undefined4 param_2)

{
  CStage *pCVar1;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,param_2,s_CPartPcs_heap_801d821c,0);
  pppEnvSt->m_stagePtr = pCVar1;
  return;
}

