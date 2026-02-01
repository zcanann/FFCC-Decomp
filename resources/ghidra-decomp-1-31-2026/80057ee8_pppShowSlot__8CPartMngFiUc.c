// Function: pppShowSlot__8CPartMngFiUc
// Entry: 80057ee8
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppShowSlot__8CPartMngFiUc(CPartMng *partMng,int param_2,uint8_t isVisible)

{
  int iVar1;
  
  iVar1 = 0x40;
  do {
    if ((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[0].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[0].m_isVisible = isVisible;
    }
    if ((partMng->m_pppMngStArr[1].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[1].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[1].m_isVisible = isVisible;
    }
    if ((partMng->m_pppMngStArr[2].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[2].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[2].m_isVisible = isVisible;
    }
    if ((partMng->m_pppMngStArr[3].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[3].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[3].m_isVisible = isVisible;
    }
    if ((partMng->m_pppMngStArr[4].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[4].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[4].m_isVisible = isVisible;
    }
    if ((partMng->m_pppMngStArr[5].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[5].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[5].m_isVisible = isVisible;
    }
    partMng = (CPartMng *)(partMng->m_usbEdit + 0x20);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

