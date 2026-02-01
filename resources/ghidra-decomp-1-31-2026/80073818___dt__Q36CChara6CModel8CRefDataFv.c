// Function: __dt__Q36CChara6CModel8CRefDataFv
// Entry: 80073818
// Size: 276 bytes

CModelCRefData * __dt__Q36CChara6CModel8CRefDataFv(CModelCRefData *refData,short param_2)

{
  int iVar1;
  CMaterialSet *pCVar2;
  
  if (refData != (CModelCRefData *)0x0) {
    (refData->ref).vtable = &PTR_PTR_s_CChara_CModel_CRefData_801fcd0c;
    if (refData->m_dynParams != (void *)0x0) {
      __dla__FPv(refData->m_dynParams);
      refData->m_dynParams = (void *)0x0;
    }
    if (refData->m_nodeRef != (CNodeCRefData *)0x0) {
      __destroy_new_array(refData->m_nodeRef,__dt__Q36CChara5CNode8CRefDataFv);
      refData->m_nodeRef = (CNodeCRefData *)0x0;
    }
    if (refData->m_meshRef != (CMeshCRefData *)0x0) {
      __destroy_new_array(refData->m_meshRef,__dt__Q36CChara5CMesh8CRefDataFv);
      refData->m_meshRef = (CMeshCRefData *)0x0;
    }
    if (refData->m_bank != (uint16_t *)0x0) {
      __dla__FPv(refData->m_bank);
      refData->m_bank = (uint16_t *)0x0;
    }
    pCVar2 = refData->m_materialSet;
    if (pCVar2 != (CMaterialSet *)0x0) {
      iVar1 = *(int *)&pCVar2->field_0x4 + -1;
      *(int *)&pCVar2->field_0x4 = iVar1;
      if ((iVar1 == 0) && (pCVar2 != (CMaterialSet *)0x0)) {
        (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
      }
      refData->m_materialSet = (CMaterialSet *)0x0;
    }
    __dt__4CRefFv(&refData->ref,0);
    if (0 < param_2) {
      __dl__FPv(refData);
    }
  }
  return refData;
}

