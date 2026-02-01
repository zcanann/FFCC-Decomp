// Function: pppGetNumFreePppMngSt__8CPartMngFv
// Entry: 8005e97c
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int pppGetNumFreePppMngSt__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0x30;
  do {
    if (partMng->m_pppMngStArr[0].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[1].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[2].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[3].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[4].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[5].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[6].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    if (partMng->m_pppMngStArr[7].m_baseTime == -0x1000) {
      iVar1 = iVar1 + 1;
    }
    partMng = (CPartMng *)(partMng->m_usbEdit + 0x2d0);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return iVar1;
}

