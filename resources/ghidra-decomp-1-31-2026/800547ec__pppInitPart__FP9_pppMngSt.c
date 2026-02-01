// Function: _pppInitPart__FP9_pppMngSt
// Entry: 800547ec
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _pppInitPart__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  pppPObjLink *ppVar1;
  
  if (DAT_8032ed70 != 0) {
    return;
  }
  for (ppVar1 = (pppMngSt->m_pppPObjLinkHead).m_next; ppVar1 != (pppPObjLink *)0x0;
      ppVar1 = ppVar1->m_next) {
    *(undefined *)&ppVar1[10].m_previous = 0;
  }
  return;
}

