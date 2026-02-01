// Function: __dt__9CFlatDataFv
// Entry: 800980b4
// Size: 292 bytes

CFlatData * __dt__9CFlatDataFv(CFlatData *cflatData,short param_2)

{
  CFlatData *pCVar1;
  int iVar2;
  
  if (cflatData != (CFlatData *)0x0) {
    pCVar1 = cflatData;
    for (iVar2 = 0; iVar2 < cflatData->m_dataCount; iVar2 = iVar2 + 1) {
      if (pCVar1->m_data[0].m_data != (void *)0x0) {
        __dl__FPv();
        pCVar1->m_data[0].m_data = (void *)0x0;
      }
      if (pCVar1->m_data[0].m_index != (int32_t *)0x0) {
        __dl__FPv();
        pCVar1->m_data[0].m_index = (int32_t *)0x0;
      }
      if (pCVar1->m_data[0].m_names != (char *)0x0) {
        __dl__FPv();
        pCVar1->m_data[0].m_names = (char *)0x0;
      }
      pCVar1 = (CFlatData *)&pCVar1->m_data[0].m_names;
    }
    cflatData->m_dataCount = 0;
    pCVar1 = cflatData;
    for (iVar2 = 0; iVar2 < cflatData->m_tableCount; iVar2 = iVar2 + 1) {
      if (pCVar1->m_table[0].index != (int32_t *)0x0) {
        __dl__FPv();
        pCVar1->m_table[0].index = (int32_t *)0x0;
      }
      if (pCVar1->m_table[0].data != (void *)0x0) {
        __dl__FPv();
        pCVar1->m_table[0].data = (void *)0x0;
      }
      pCVar1 = (CFlatData *)&pCVar1->m_data[0].m_count;
    }
    cflatData->m_tableCount = 0;
    if (cflatData->m_mesBuffer != (char *)0x0) {
      __dl__FPv();
      cflatData->m_mesBuffer = (char *)0x0;
    }
    cflatData->m_mesCount = 0;
    if (0 < param_2) {
      __dl__FPv(cflatData);
    }
  }
  return cflatData;
}

