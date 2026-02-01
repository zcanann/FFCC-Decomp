// Function: pppDumpMngSt__8CPartMngFv
// Entry: 8005ecfc
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDumpMngSt__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  CPartMng *pCVar5;
  uint local_40;
  uint local_3c;
  uint local_38 [5];
  
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,s__________________________________801d8358);
  }
  iVar3 = 0;
  pCVar5 = partMng;
  do {
    if ((pCVar5->m_pppMngStArr[0].m_baseTime != -0x1000) && (System.m_execParam != 0)) {
      iVar4 = (int)pCVar5->m_pppMngStArr[0].m_kind;
      iVar1 = (int)(pCVar5[0x38d6].m_unk0x1d4_0x3d3 + 0x2d) / 0x158 +
              ((int)(pCVar5[0x38d6].m_unk0x1d4_0x3d3 + 0x2d) >> 0x1f);
      iVar1 = iVar1 - (iVar1 >> 0x1f);
      uVar2 = heapWalker__Q27CMemory6CStageFiPvUl(pppEnvStPtr->m_stagePtr,0,0,iVar1);
      Printf__7CSystemFPce
                (&System,s_prioTime__d_prio__d_heapSize__d_p_801d8454,
                 pCVar5->m_pppMngStArr[0].m_prioTime,pCVar5->m_pppMngStArr[0].m_prio,uVar2,iVar4,
                 (int)pCVar5->m_pppMngStArr[0].m_nodeIndex,iVar1,partMng->m_pdtSlots[iVar4].m_name);
    }
    iVar3 = iVar3 + 1;
    pCVar5 = (CPartMng *)pCVar5->m_rgbaA;
  } while (iVar3 < 0x180);
  heapInfo__Q27CMemory6CStageFRUlRUlRUl(pppEnvStPtr->m_stagePtr,local_38,&local_3c,&local_40);
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce
              (&System,s_HEAP_TOTAL__dKbyte_USE__dKbyte_F_801d84a0,local_38[0] >> 10,local_3c >> 10,
               local_40 >> 10);
  }
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,&DAT_8032fe88);
  }
  return;
}

