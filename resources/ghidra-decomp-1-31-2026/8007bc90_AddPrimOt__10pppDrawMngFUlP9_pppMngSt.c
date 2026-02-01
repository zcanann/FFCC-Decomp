// Function: AddPrimOt__10pppDrawMngFUlP9_pppMngSt
// Entry: 8007bc90
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void AddPrimOt__10pppDrawMngFUlP9_pppMngSt(pppDrawMng *pppDrawMng,int param_2,_pppMngSt *pppMngSt)

{
  pppDrawPrimitive *ppVar1;
  
  ppVar1 = pppDrawMng->m_nextFree;
  if (&pppDrawMng->m_nextFree <= ppVar1) {
    return;
  }
  pppDrawMng->m_nextFree = ppVar1 + 1;
  ppVar1->m_type = '\0';
  ppVar1->m_handle = pppMngSt;
  ppVar1->m_next = pppDrawMng->m_primitiveRefs[param_2];
  pppDrawMng->m_primitiveRefs[param_2] = ppVar1;
  return;
}

