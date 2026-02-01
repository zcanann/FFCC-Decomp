// Function: Add__Q29CCharaPcs7CHandleFv
// Entry: 80076cf4
// Size: 68 bytes

void Add__Q29CCharaPcs7CHandleFv(CCharaPcsCHandle *handle)

{
  CCharaPcsCHandle *pCVar1;
  
  if (handle->m_next != (CCharaPcsCHandle *)0x0) {
    return;
  }
  if (handle->m_previous != (CCharaPcsCHandle *)0x0) {
    return;
  }
  pCVar1 = *(CCharaPcsCHandle **)(CharaPcs._76_4_ + 0x15c);
  handle->m_previous = pCVar1;
  handle->m_next = pCVar1->m_next;
  pCVar1->m_next->m_previous = handle;
  pCVar1->m_next = handle;
  return;
}

