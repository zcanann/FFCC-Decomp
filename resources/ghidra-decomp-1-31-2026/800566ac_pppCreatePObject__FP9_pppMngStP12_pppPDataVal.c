// Function: pppCreatePObject__FP9_pppMngStP12_pppPDataVal
// Entry: 800566ac
// Size: 1120 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

pppPObjLink *
pppCreatePObject__FP9_pppMngStP12_pppPDataVal(_pppMngSt *pppMngSt,_pppPDataVal *pppPDataVal)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  pppPObjLink *ppVar7;
  _pppMngSt *p_Var8;
  short sVar10;
  pppProg *ppVar9;
  pppPObjLink *ppVar11;
  pppPObjLink *ppVar12;
  byte bVar14;
  pppPObjLink *ppVar13;
  char *pcVar15;
  uint32_t uVar16;
  CPartMng *pCVar17;
  code *pcVar18;
  uint32_t *puVar19;
  pppProgramSetDef *ppVar20;
  pppProgramSetDef *ppVar21;
  _pppPDataVal *p_Var22;
  pppPObjLink *ppVar23;
  uint unaff_r24;
  CStage *stage;
  char local_1d8 [384];
  pppProgramSetDef *local_58;
  
  bVar3 = true;
  local_58 = pppPDataVal->m_pppProgramSetDef;
  sVar2 = local_58->m_numStages;
  stage = pppEnvStPtr->m_stagePtr;
  uVar16 = local_58->m_objBaseSize;
  DAT_8032ed64 = 0;
  do {
    ppVar7 = (pppPObjLink *)
             _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,uVar16 + sVar2 * 4,stage,s_pppPart_cpp_801d81f8,0x305,1);
    if (ppVar7 != (pppPObjLink *)0x0) goto LAB_800569c8;
    if (bVar3) {
      bVar3 = false;
      memset(local_1d8,0,0x180);
      iVar5 = (int)&pppMngStPtr[0x5f2411].m_scale / 0x158 +
              ((int)&pppMngStPtr[0x5f2411].m_scale >> 0x1f);
      local_1d8[iVar5 - (iVar5 >> 0x1f)] = '\x01';
    }
    p_Var8 = (_pppMngSt *)0x0;
    pcVar15 = local_1d8;
    bVar14 = 1;
    iVar5 = 0xc0;
    pCVar17 = &PartMng;
    do {
      if ((((*pcVar15 == '\0') && (pCVar17->m_pppMngStArr[0].m_baseTime != -0x1000)) &&
          (pCVar17->m_pppMngStArr[0].m_kind != 0)) &&
         (bVar1 = pCVar17->m_pppMngStArr[0].m_prio, 1 < bVar1)) {
        if (bVar14 < bVar1) {
          p_Var8 = pCVar17->m_pppMngStArr;
          unaff_r24 = (uint)pCVar17->m_pppMngStArr[0].m_prioTime;
          bVar14 = bVar1;
        }
        else if ((bVar14 == bVar1) &&
                (uVar6 = (uint)pCVar17->m_pppMngStArr[0].m_prioTime, (int)unaff_r24 < (int)uVar6)) {
          p_Var8 = pCVar17->m_pppMngStArr;
          unaff_r24 = uVar6;
        }
      }
      if (((pcVar15[1] == '\0') && (pCVar17->m_pppMngStArr[1].m_baseTime != -0x1000)) &&
         ((pCVar17->m_pppMngStArr[1].m_kind != 0 &&
          (bVar1 = pCVar17->m_pppMngStArr[1].m_prio, 1 < bVar1)))) {
        if (bVar14 < bVar1) {
          p_Var8 = pCVar17->m_pppMngStArr + 1;
          unaff_r24 = (uint)pCVar17->m_pppMngStArr[1].m_prioTime;
          bVar14 = bVar1;
        }
        else if ((bVar14 == bVar1) &&
                (uVar6 = (uint)pCVar17->m_pppMngStArr[1].m_prioTime, (int)unaff_r24 < (int)uVar6)) {
          p_Var8 = pCVar17->m_pppMngStArr + 1;
          unaff_r24 = uVar6;
        }
      }
      pcVar15 = pcVar15 + 2;
      pCVar17 = (CPartMng *)(pCVar17->m_unk0x1d4_0x3d3 + 0x37);
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (p_Var8 == (_pppMngSt *)0x0) {
      bVar4 = false;
    }
    else {
      iVar5 = ((int)(p_Var8 + 0x5f2411) + 0x28) / 0x158 + ((int)(p_Var8 + 0x5f2411) + 0x28 >> 0x1f);
      local_1d8[iVar5 - (iVar5 >> 0x1f)] = '\x01';
      ppVar11 = (p_Var8->m_pppPObjLinkHead).m_next;
      ppVar13 = &p_Var8->m_pppPObjLinkHead;
      while (ppVar23 = ppVar13, ppVar12 = ppVar11, ppVar12 != (pppPObjLink *)0x0) {
        ppVar11 = ppVar12->m_next;
        bVar14 = ppVar12->m_owner->m_pppProgramSetDef->m_flags;
        ppVar13 = ppVar12;
        if (-1 < (int)((uint)bVar14 << 0x1e | (uint)(bVar14 >> 2))) {
          ppVar23->m_next = ppVar11;
          p_Var22 = ppVar12->m_owner;
          ppVar20 = p_Var22->m_pppProgramSetDef;
          ppVar21 = ppVar20;
          for (iVar5 = 0; iVar5 < ppVar20->m_numStages; iVar5 = iVar5 + 1) {
            ppVar9 = ppVar21->pppSubProgEntries[0].m_prog;
            if ((ppVar9 != (pppProg *)0x0) &&
               (pcVar18 = (code *)ppVar9->m_pppFunctionDestructor, pcVar18 != (code *)0x0)) {
              (*pcVar18)(ppVar12,ppVar21->pppSubProgEntries);
            }
            ppVar21 = (pppProgramSetDef *)&ppVar21->unk0x10;
          }
          sVar10 = p_Var22->m_activeCount + -1;
          p_Var22->m_activeCount = sVar10;
          if (sVar10 == 0) {
            p_Var22->m_pppPObjLink = (pppPObjLink *)0x0;
          }
          else if (p_Var22->m_pppPObjLink == ppVar12) {
            p_Var22->m_pppPObjLink = ppVar12->m_next;
          }
          ppVar13 = ppVar23;
          if (ppVar12 != (pppPObjLink *)0x0) {
            Free__7CMemoryFPv(&Memory,ppVar12);
          }
        }
      }
      bVar4 = true;
    }
  } while (bVar4);
  heapWalker__Q27CMemory6CStageFiPvUl(pppEnvStPtr->m_stagePtr,2,0,0xffffffff);
  pppDumpMngSt__8CPartMngFv(&PartMng);
  DAT_8032ed64 = 1;
LAB_800569c8:
  if (ppVar7 == (pppPObjLink *)0x0) {
    ppVar7 = (pppPObjLink *)0x0;
  }
  else {
    ppVar7[1].m_next = (pppPObjLink *)0x0;
    ppVar7[9].m_previous = (pppPObjLink *)0x0;
    ppVar7[9].m_owner = (_pppPDataVal *)0x0;
    ppVar7->m_owner = pppPDataVal;
    *(undefined *)&ppVar7[10].m_previous = 1;
    ppVar11 = (pppMngSt->m_pppPObjLinkHead).m_next;
    if (ppVar11 == (pppPObjLink *)0x0) {
      pppPDataVal->m_pppPObjLink = ppVar7;
      (pppMngSt->m_pppPObjLinkHead).m_next = ppVar7;
      ppVar7->m_next = (pppPObjLink *)0x0;
    }
    else if (pppPDataVal->m_pppPObjLink == (pppPObjLink *)0x0) {
      ppVar13 = &pppMngSt->m_pppPObjLinkHead;
      do {
        ppVar12 = ppVar11;
        if (local_58->m_sortKey <= ppVar12->m_owner->m_pppProgramSetDef->m_sortKey) {
          pppPDataVal->m_pppPObjLink = ppVar7;
          ppVar13->m_next = ppVar7;
          ppVar7->m_next = ppVar12;
          goto LAB_80056a84;
        }
        ppVar11 = ppVar12->m_next;
        ppVar13 = ppVar12;
      } while (ppVar12->m_next != (pppPObjLink *)0x0);
      pppPDataVal->m_pppPObjLink = ppVar7;
      ppVar12->m_next = ppVar7;
      ppVar7->m_next = (pppPObjLink *)0x0;
    }
    else {
      ppVar7->m_next = pppPDataVal->m_pppPObjLink->m_next;
      pppPDataVal->m_pppPObjLink->m_next = ppVar7;
    }
LAB_80056a84:
    pppPDataVal->m_activeCount = pppPDataVal->m_activeCount + 1;
    ppVar20 = ppVar7->m_owner->m_pppProgramSetDef;
    puVar19 = (uint32_t *)((int)&ppVar7->m_next + ppVar20->m_objBaseSize);
    ppVar21 = ppVar20;
    for (iVar5 = 0; iVar5 < ppVar20->m_numStages; iVar5 = iVar5 + 1) {
      ppVar9 = ppVar21->pppSubProgEntries[0].m_prog;
      *puVar19 = ppVar21->pppSubProgEntries[0].m_initWork;
      puVar19 = puVar19 + 1;
      if ((ppVar9 != (pppProg *)0x0) &&
         (pcVar18 = (code *)ppVar9->m_pppFunctionConstructor, pcVar18 != (code *)0x0)) {
        (*pcVar18)(ppVar7,ppVar21->pppSubProgEntries);
      }
      ppVar21 = (pppProgramSetDef *)&ppVar21->unk0x10;
    }
  }
  return ppVar7;
}

