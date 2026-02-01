// Function: pppGetIfDt__8CPartMngFs
// Entry: 80057e40
// Size: 24 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

PPPIFPARAM * pppGetIfDt__8CPartMngFs(CPartMng *partMng,short index)

{
  return &partMng->m_pppMngStArr[index].m_hitParams;
}

