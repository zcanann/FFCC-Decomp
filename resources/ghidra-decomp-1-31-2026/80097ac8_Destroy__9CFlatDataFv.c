// Function: Destroy__9CFlatDataFv
// Entry: 80097ac8
// Size: 288 bytes

void Destroy__9CFlatDataFv(CFlatData *cflatData)

{
  int iVar1;
  CFlatData *pCVar2;
  
  pCVar2 = cflatData;
  for (iVar1 = 0; iVar1 < cflatData->m_dataCount; iVar1 = iVar1 + 1) {
    if (pCVar2->m_data[0].m_data != (void *)0x0) {
      __dl__FPv();
      pCVar2->m_data[0].m_data = (void *)0x0;
    }
    if (pCVar2->m_data[0].m_index != (int32_t *)0x0) {
      __dl__FPv();
      pCVar2->m_data[0].m_index = (int32_t *)0x0;
    }
    if (pCVar2->m_data[0].m_names != (char *)0x0) {
      __dl__FPv();
      pCVar2->m_data[0].m_names = (char *)0x0;
    }
    pCVar2 = (CFlatData *)&pCVar2->m_data[0].m_names;
  }
  cflatData->m_dataCount = 0;
  pCVar2 = cflatData;
  for (iVar1 = 0; iVar1 < cflatData->m_tableCount; iVar1 = iVar1 + 1) {
    if (pCVar2->m_table[0].index != (int32_t *)0x0) {
      __dl__FPv();
      pCVar2->m_table[0].index = (int32_t *)0x0;
    }
    if (pCVar2->m_table[0].data != (void *)0x0) {
      __dl__FPv();
      pCVar2->m_table[0].data = (void *)0x0;
    }
    pCVar2 = (CFlatData *)&pCVar2->m_data[0].m_count;
  }
  cflatData->m_tableCount = 0;
  if (cflatData->m_mesBuffer != (char *)0x0) {
    __dl__FPv();
    cflatData->m_mesBuffer = (char *)0x0;
  }
  cflatData->m_mesCount = 0;
  return;
}

