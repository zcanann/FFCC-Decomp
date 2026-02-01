// Function: pppPartDead__8CPartMngFv
// Entry: 80059cac
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppPartDead__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  _pppMngSt *pppMngSt;
  int iVar2;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0xb3d);
  iVar2 = 0;
  do {
    pppMngSt = partMng->m_pppMngStArr;
    iVar1 = partMng->m_pppMngStArr[0].m_baseTime;
    if (((iVar1 != -0x1000) && (iVar1 < 0)) &&
       ((partMng->m_pppMngStArr[0].field37_0xe6 != '\0' ||
        (partMng->m_pppMngStArr[0].m_endRequested != '\0')))) {
      pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
      pppMngStPtr = pppMngSt;
      _pppAllFreePObject__FP9_pppMngSt(pppMngSt);
    }
    iVar2 = iVar2 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar2 < 0x180);
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0xb5d);
  return;
}

