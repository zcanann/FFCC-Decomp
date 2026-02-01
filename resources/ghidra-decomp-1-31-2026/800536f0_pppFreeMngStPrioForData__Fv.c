// Function: pppFreeMngStPrioForData__Fv
// Entry: 800536f0
// Size: 528 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 pppFreeMngStPrioForData__Fv(void)

{
  byte bVar1;
  uint uVar2;
  CPartMng *pCVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  uint in_r7;
  _pppMngSt *p_Var7;
  _pppMngSt *pppMngSt;
  int iVar8;
  
  pCVar3 = &PartMng;
  bVar6 = 1;
  iVar5 = 0;
  pppMngSt = (_pppMngSt *)0x0;
  iVar8 = 0xc0;
  do {
    p_Var7 = pCVar3->m_pppMngStArr;
    if ((((p_Var7 != pppMngStPtr) && (pCVar3->m_pppMngStArr[0].m_baseTime != -0x1000)) &&
        (pCVar3->m_pppMngStArr[0].m_kind != 0)) &&
       (bVar1 = pCVar3->m_pppMngStArr[0].m_prio, 1 < bVar1)) {
      if (bVar6 < bVar1) {
        in_r7 = (uint)pCVar3->m_pppMngStArr[0].m_prioTime;
        pppMngSt = p_Var7;
        bVar6 = bVar1;
      }
      else if ((bVar6 == bVar1) &&
              (uVar2 = (uint)pCVar3->m_pppMngStArr[0].m_prioTime, (int)in_r7 < (int)uVar2)) {
        in_r7 = uVar2;
        pppMngSt = p_Var7;
      }
    }
    p_Var7 = pCVar3->m_pppMngStArr + 1;
    if (((p_Var7 != pppMngStPtr) && (pCVar3->m_pppMngStArr[1].m_baseTime != -0x1000)) &&
       ((pCVar3->m_pppMngStArr[1].m_kind != 0 &&
        (bVar1 = pCVar3->m_pppMngStArr[1].m_prio, 1 < bVar1)))) {
      if (bVar6 < bVar1) {
        in_r7 = (uint)pCVar3->m_pppMngStArr[1].m_prioTime;
        pppMngSt = p_Var7;
        bVar6 = bVar1;
      }
      else if ((bVar6 == bVar1) &&
              (uVar2 = (uint)pCVar3->m_pppMngStArr[1].m_prioTime, (int)in_r7 < (int)uVar2)) {
        in_r7 = uVar2;
        pppMngSt = p_Var7;
      }
    }
    pCVar3 = (CPartMng *)(pCVar3->m_unk0x1d4_0x3d3 + 0x37);
    iVar5 = iVar5 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  if (pppMngSt == (_pppMngSt *)0x0) {
    uVar4 = 0;
  }
  else {
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c,iVar5);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce
                (&System,s_prioTime__d_prio__d_pdtID__2d_fp_801d81a0,pppMngSt->m_prioTime,
                 pppMngSt->m_prio,(int)pppMngSt->m_kind,(int)pppMngSt->m_nodeIndex,
                 pppMngSt->m_kind * 0x38 + -0x7fd672e8);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d81d4);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_tina_cpp_801d8008,0xfc);
    _pppAllFreePObject__FP9_pppMngSt(pppMngSt);
    uVar4 = 1;
  }
  return uVar4;
}

