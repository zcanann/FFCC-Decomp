// Function: calc__9CCharaPcsFv
// Entry: 80079938
// Size: 100 bytes

void calc__9CCharaPcsFv(int param_1)

{
  CCharaPcsCHandle *handle;
  CCharaPcsCHandle *pCVar1;
  
  handle = *(CCharaPcsCHandle **)(*(int *)(param_1 + 0x4c) + 0x160);
  while (*(CCharaPcsCHandle **)(param_1 + 0x4c) != handle) {
    pCVar1 = handle->m_next;
    handle->m_shadowTexturePtr = (void *)0x0;
    loadModelASyncFrame__Q29CCharaPcs7CHandleFv(handle);
    handle = pCVar1;
  }
  return;
}

