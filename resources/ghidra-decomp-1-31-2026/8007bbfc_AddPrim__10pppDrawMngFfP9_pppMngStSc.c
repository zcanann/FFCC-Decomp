// Function: AddPrim__10pppDrawMngFfP9_pppMngStSc
// Entry: 8007bbfc
// Size: 148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void AddPrim__10pppDrawMngFfP9_pppMngStSc
               (float param_1,pppDrawMng *pppDrawMng,_pppMngSt *pppMngSt,char param_4)

{
  pppDrawPrimitive *ppVar1;
  int iVar2;
  
  iVar2 = 0x100 - (int)(param_1 * pppDrawMng->m_depthScale);
  if ((-1 < iVar2) && (iVar2 < 0x400)) {
    if (param_4 != '\0') {
      iVar2 = iVar2 + param_4;
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      else if (0x3ff < iVar2) {
        iVar2 = 0x3ff;
      }
    }
    ppVar1 = pppDrawMng->m_nextFree;
    if (ppVar1 < &pppDrawMng->m_nextFree) {
      pppDrawMng->m_nextFree = ppVar1 + 1;
      ppVar1->m_type = '\0';
      ppVar1->m_handle = pppMngSt;
      ppVar1->m_next = pppDrawMng->m_primitiveRefs[iVar2];
      pppDrawMng->m_primitiveRefs[iVar2] = ppVar1;
    }
  }
  return;
}

