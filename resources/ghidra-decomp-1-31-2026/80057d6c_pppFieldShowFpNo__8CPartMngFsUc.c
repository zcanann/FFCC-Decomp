// Function: pppFieldShowFpNo__8CPartMngFsUc
// Entry: 80057d6c
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFieldShowFpNo__8CPartMngFsUc(CPartMng *partMng,short param_2,uint8_t param_3)

{
  int iVar1;
  
  iVar1 = 0x60;
  do {
    if (((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
        (partMng->m_pppMngStArr[0].m_kind == 0)) &&
       (partMng->m_pppMngStArr[0].m_nodeIndex == param_2)) {
      partMng->m_pppMngStArr[0].m_isVisible = param_3;
    }
    if (((partMng->m_pppMngStArr[1].m_baseTime != -0x1000) &&
        (partMng->m_pppMngStArr[1].m_kind == 0)) &&
       (partMng->m_pppMngStArr[1].m_nodeIndex == param_2)) {
      partMng->m_pppMngStArr[1].m_isVisible = param_3;
    }
    if (((partMng->m_pppMngStArr[2].m_baseTime != -0x1000) &&
        (partMng->m_pppMngStArr[2].m_kind == 0)) &&
       (partMng->m_pppMngStArr[2].m_nodeIndex == param_2)) {
      partMng->m_pppMngStArr[2].m_isVisible = param_3;
    }
    if (((partMng->m_pppMngStArr[3].m_baseTime != -0x1000) &&
        (partMng->m_pppMngStArr[3].m_kind == 0)) &&
       (partMng->m_pppMngStArr[3].m_nodeIndex == param_2)) {
      partMng->m_pppMngStArr[3].m_isVisible = param_3;
    }
    partMng = (CPartMng *)(partMng->m_streamTextRaw + 0x62);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

