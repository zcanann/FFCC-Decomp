// Function: pppSetLocSlot__8CPartMngFiP3Vec
// Entry: 80057b2c
// Size: 220 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetLocSlot__8CPartMngFiP3Vec(CPartMng *partMng,int param_2,Vec *position)

{
  int iVar1;
  
  iVar1 = 0x60;
  do {
    if ((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[0].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[0].m_position.x = position->x;
      partMng->m_pppMngStArr[0].m_position.y = position->y;
      partMng->m_pppMngStArr[0].m_position.z = position->z;
    }
    if ((partMng->m_pppMngStArr[1].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[1].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[1].m_position.x = position->x;
      partMng->m_pppMngStArr[1].m_position.y = position->y;
      partMng->m_pppMngStArr[1].m_position.z = position->z;
    }
    if ((partMng->m_pppMngStArr[2].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[2].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[2].m_position.x = position->x;
      partMng->m_pppMngStArr[2].m_position.y = position->y;
      partMng->m_pppMngStArr[2].m_position.z = position->z;
    }
    if ((partMng->m_pppMngStArr[3].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[3].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[3].m_position.x = position->x;
      partMng->m_pppMngStArr[3].m_position.y = position->y;
      partMng->m_pppMngStArr[3].m_position.z = position->z;
    }
    partMng = (CPartMng *)(partMng->m_streamTextRaw + 0x62);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

