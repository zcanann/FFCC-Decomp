// Function: SetParLocIdx__8CPartPcsFiR3Vec
// Entry: 80052a48
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetParLocIdx__8CPartPcsFiR3Vec(CPartPcs *partPcs,int index,Vec *location)

{
  PartMng.m_pppMngStArr[index].m_position.x = location->x;
  PartMng.m_pppMngStArr[index].m_position.y = location->y;
  PartMng.m_pppMngStArr[index].m_position.z = location->z;
  return;
}

