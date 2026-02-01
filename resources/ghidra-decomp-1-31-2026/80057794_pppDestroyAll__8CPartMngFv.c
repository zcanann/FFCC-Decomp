// Function: pppDestroyAll__8CPartMngFv
// Entry: 80057794
// Size: 148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestroyAll__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x116f);
  iVar1 = 0;
  do {
    if ((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
       (partMng->m_pppMngStArr[0].m_pppResSet != (void *)0x0)) {
      _pppAllFreePObject__FP9_pppMngSt(partMng->m_pppMngStArr);
    }
    iVar1 = iVar1 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar1 < 0x180);
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x117b);
  return;
}

