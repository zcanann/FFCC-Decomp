// Function: pppMemFree__FPv
// Entry: 80056d20
// Size: 744 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int pppMemFree__FPv(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  pppPObjLink *ppVar4;
  uint uVar5;
  int iVar6;
  _pppMngSt *p_Var7;
  pppProg *ppVar8;
  short sVar9;
  byte bVar10;
  char *pcVar11;
  CPartMng *pCVar12;
  code *pcVar13;
  pppProgramSetDef *ppVar14;
  _pppPDataVal *p_Var15;
  pppProgramSetDef *ppVar16;
  pppPObjLink *ppVar17;
  pppPObjLink *ppVar18;
  pppPObjLink *ppVar19;
  uint unaff_r26;
  char local_1c8 [392];
  
  bVar2 = true;
  DAT_8032ed64 = 0;
  do {
    iVar6 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory,param_1,param_2,param_3,param_4,1);
    if (iVar6 != 0) {
      return iVar6;
    }
    if (bVar2) {
      bVar2 = false;
      memset(local_1c8,0,0x180);
      iVar6 = (int)&pppMngStPtr[0x5f2411].m_scale / 0x158 +
              ((int)&pppMngStPtr[0x5f2411].m_scale >> 0x1f);
      local_1c8[iVar6 - (iVar6 >> 0x1f)] = '\x01';
    }
    p_Var7 = (_pppMngSt *)0x0;
    pcVar11 = local_1c8;
    bVar10 = 1;
    iVar6 = 0xc0;
    pCVar12 = &PartMng;
    do {
      if ((((*pcVar11 == '\0') && (pCVar12->m_pppMngStArr[0].m_baseTime != -0x1000)) &&
          (pCVar12->m_pppMngStArr[0].m_kind != 0)) &&
         (bVar1 = pCVar12->m_pppMngStArr[0].m_prio, 1 < bVar1)) {
        if (bVar10 < bVar1) {
          p_Var7 = pCVar12->m_pppMngStArr;
          unaff_r26 = (uint)pCVar12->m_pppMngStArr[0].m_prioTime;
          bVar10 = bVar1;
        }
        else if ((bVar10 == bVar1) &&
                (uVar5 = (uint)pCVar12->m_pppMngStArr[0].m_prioTime, (int)unaff_r26 < (int)uVar5)) {
          p_Var7 = pCVar12->m_pppMngStArr;
          unaff_r26 = uVar5;
        }
      }
      if (((pcVar11[1] == '\0') && (pCVar12->m_pppMngStArr[1].m_baseTime != -0x1000)) &&
         ((pCVar12->m_pppMngStArr[1].m_kind != 0 &&
          (bVar1 = pCVar12->m_pppMngStArr[1].m_prio, 1 < bVar1)))) {
        if (bVar10 < bVar1) {
          p_Var7 = pCVar12->m_pppMngStArr + 1;
          unaff_r26 = (uint)pCVar12->m_pppMngStArr[1].m_prioTime;
          bVar10 = bVar1;
        }
        else if ((bVar10 == bVar1) &&
                (uVar5 = (uint)pCVar12->m_pppMngStArr[1].m_prioTime, (int)unaff_r26 < (int)uVar5)) {
          p_Var7 = pCVar12->m_pppMngStArr + 1;
          unaff_r26 = uVar5;
        }
      }
      pcVar11 = pcVar11 + 2;
      pCVar12 = (CPartMng *)(pCVar12->m_unk0x1d4_0x3d3 + 0x37);
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    if (p_Var7 == (_pppMngSt *)0x0) {
      bVar3 = false;
    }
    else {
      iVar6 = ((int)(p_Var7 + 0x5f2411) + 0x28) / 0x158 + ((int)(p_Var7 + 0x5f2411) + 0x28 >> 0x1f);
      local_1c8[iVar6 - (iVar6 >> 0x1f)] = '\x01';
      ppVar19 = (p_Var7->m_pppPObjLinkHead).m_next;
      ppVar4 = &p_Var7->m_pppPObjLinkHead;
      while (ppVar18 = ppVar4, ppVar17 = ppVar19, ppVar17 != (pppPObjLink *)0x0) {
        ppVar19 = ppVar17->m_next;
        bVar10 = ppVar17->m_owner->m_pppProgramSetDef->m_flags;
        ppVar4 = ppVar17;
        if (-1 < (int)((uint)bVar10 << 0x1e | (uint)(bVar10 >> 2))) {
          ppVar18->m_next = ppVar19;
          p_Var15 = ppVar17->m_owner;
          ppVar16 = p_Var15->m_pppProgramSetDef;
          ppVar14 = ppVar16;
          for (iVar6 = 0; iVar6 < ppVar16->m_numStages; iVar6 = iVar6 + 1) {
            ppVar8 = ppVar14->pppSubProgEntries[0].m_prog;
            if ((ppVar8 != (pppProg *)0x0) &&
               (pcVar13 = (code *)ppVar8->m_pppFunctionDestructor, pcVar13 != (code *)0x0)) {
              (*pcVar13)(ppVar17,ppVar14->pppSubProgEntries);
            }
            ppVar14 = (pppProgramSetDef *)&ppVar14->unk0x10;
          }
          sVar9 = p_Var15->m_activeCount + -1;
          p_Var15->m_activeCount = sVar9;
          if (sVar9 == 0) {
            p_Var15->m_pppPObjLink = (pppPObjLink *)0x0;
          }
          else if (p_Var15->m_pppPObjLink == ppVar17) {
            p_Var15->m_pppPObjLink = ppVar17->m_next;
          }
          ppVar4 = ppVar18;
          if (ppVar17 != (pppPObjLink *)0x0) {
            Free__7CMemoryFPv(&Memory,ppVar17);
          }
        }
      }
      bVar3 = true;
    }
  } while (bVar3);
  DAT_8032ed64 = 1;
  return 0;
}

