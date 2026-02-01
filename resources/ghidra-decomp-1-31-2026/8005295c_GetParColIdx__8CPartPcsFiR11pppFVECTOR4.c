// Function: GetParColIdx__8CPartPcsFiR11pppFVECTOR4
// Entry: 8005295c
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetParColIdx__8CPartPcsFiR11pppFVECTOR4(CPartPcs *partPcs,int index,pppFVector4 *pppFVector4)

{
  pppFVector4->m_vector[0] = PartMng.m_pppMngStArr[index].m_userFloat0;
  pppFVector4->m_vector[1] = PartMng.m_pppMngStArr[index].m_userFloat1;
  pppFVector4->m_vector[2] = PartMng.m_pppMngStArr[index].m_scaleFactor;
  pppFVector4->m_vector[3] = PartMng.m_pppMngStArr[index].m_ownerScale;
  return;
}

