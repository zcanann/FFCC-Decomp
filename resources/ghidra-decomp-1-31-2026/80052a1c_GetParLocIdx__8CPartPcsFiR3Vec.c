// Function: GetParLocIdx__8CPartPcsFiR3Vec
// Entry: 80052a1c
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetParLocIdx__8CPartPcsFiR3Vec(CPartPcs *param_1,int pppMngStIndex,Vec *location)

{
  location->x = PartMng.m_pppMngStArr[pppMngStIndex].m_position.x;
  location->y = PartMng.m_pppMngStArr[pppMngStIndex].m_position.y;
  location->z = PartMng.m_pppMngStArr[pppMngStIndex].m_position.z;
  return;
}

