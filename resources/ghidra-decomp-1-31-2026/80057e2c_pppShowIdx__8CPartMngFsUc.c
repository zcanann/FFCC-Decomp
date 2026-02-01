// Function: pppShowIdx__8CPartMngFsUc
// Entry: 80057e2c
// Size: 20 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppShowIdx__8CPartMngFsUc(CPartMng *partMng,short index,uint8_t param_3)

{
  partMng->m_pppMngStArr[index].m_isVisible = param_3;
  return;
}

