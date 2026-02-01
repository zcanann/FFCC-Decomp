// Function: SetParColIdx__8CPartPcsFiR11pppFVECTOR4
// Entry: 80052990
// Size: 140 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetParColIdx__8CPartPcsFiR11pppFVECTOR4(CPartPcs *partPcs,int index,pppFVector4 *pppFVector4)

{
  float fVar1;
  
  fVar1 = FLOAT_8032fdc8;
  PartMng.m_pppMngStArr[index].m_userFloat0 = pppFVector4->m_vector[0];
  PartMng.m_pppMngStArr[index].m_userFloat1 = pppFVector4->m_vector[1];
  PartMng.m_pppMngStArr[index].m_scaleFactor = pppFVector4->m_vector[2];
  PartMng.m_pppMngStArr[index].m_ownerScale = pppFVector4->m_vector[3];
  if ((((fVar1 == pppFVector4->m_vector[0]) && (fVar1 == pppFVector4->m_vector[1])) &&
      (fVar1 == pppFVector4->m_vector[2])) && (fVar1 == pppFVector4->m_vector[3])) {
    PartMng.m_pppMngStArr[index].m_ownerScaleMode = '\0';
    return;
  }
  PartMng.m_pppMngStArr[index].m_ownerScaleMode = '\x01';
  PartMng.m_pppMngStArr[index].m_lockScaleFromOwner = '\x01';
  return;
}

