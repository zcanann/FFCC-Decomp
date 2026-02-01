// Function: pppPartInit__8CPartMngFv
// Entry: 80059c44
// Size: 104 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppPartInit__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  partMng->m_unk0x8 = 0;
  do {
    iVar1 = partMng->m_pppMngStArr[0].m_baseTime;
    if ((iVar1 != -0x1000) && (iVar1 < 0)) {
      _pppInitPart__FP9_pppMngSt(partMng->m_pppMngStArr);
    }
    iVar2 = iVar2 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar2 < 0x180);
  return;
}

