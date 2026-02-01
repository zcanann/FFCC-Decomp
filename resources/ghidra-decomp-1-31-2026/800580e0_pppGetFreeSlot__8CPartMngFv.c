// Function: pppGetFreeSlot__8CPartMngFv
// Entry: 800580e0
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppGetFreeSlot__8CPartMngFv(CPartMng *partMng)

{
  uint32_t uVar1;
  
  uVar1 = (partMng->m_pppEnvSt).m_mngStCount + 1;
  (partMng->m_pppEnvSt).m_mngStCount = uVar1;
  if ((int)uVar1 < 0x7fffffff) {
    return;
  }
  (partMng->m_pppEnvSt).m_mngStCount = 0x10;
  return;
}

