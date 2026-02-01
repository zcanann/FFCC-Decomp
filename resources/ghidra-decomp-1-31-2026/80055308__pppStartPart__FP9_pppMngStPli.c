// Function: _pppStartPart__FP9_pppMngStPli
// Entry: 80055308
// Size: 1376 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _pppStartPart__FP9_pppMngStPli(_pppMngSt *pppMngSt,long *param_2,int param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  pppPObjLink *ppVar4;
  uint uVar5;
  int iVar6;
  _pppPDataVal *p_Var7;
  _pppMngSt *p_Var8;
  pppProg *ppVar9;
  short sVar10;
  uint8_t uVar11;
  int iVar12;
  short *psVar13;
  byte bVar15;
  pppProgramSetDef *ppVar14;
  int iVar16;
  char *pcVar17;
  CPartMng *pCVar18;
  code *pcVar19;
  pppProgramSetDef *ppVar20;
  int iVar21;
  short sVar23;
  _pppPDataVal *p_Var22;
  pppProgramSetDef *ppVar24;
  pppPObjLink *ppVar25;
  pppPObjLink *ppVar26;
  short *psVar27;
  pppPObjLink *ppVar28;
  uint unaff_r23;
  CStage *stage;
  CMapMesh *mapMesh;
  char local_1d4 [396];
  
  ppVar14 = (pppProgramSetDef *)(param_2 + 6);
  pppMngStPtr = pppMngSt;
  pppMngSt->m_lifeEnd = *param_2;
  pppMngSt->m_stopAtLifeEnd = (uint8_t)param_2[1];
  iVar16 = param_2[2];
  iVar12 = param_2[3];
  psVar27 = (short *)((int)param_2 + param_2[5]);
  psVar13 = (short *)((int)param_2 + param_2[4]);
  if (Game.game.m_currentSceneId != 7) {
    sVar10 = *psVar13;
                    /* WARNING: Load size is inaccurate */
    iVar21 = *pppMngSt->m_pppResSet;
    for (sVar23 = 0; psVar13 = psVar13 + 1, sVar23 < sVar10; sVar23 = sVar23 + 1) {
      mapMesh = *(CMapMesh **)(*(int *)(iVar21 + 0x14) + *psVar13 * 4);
      iVar6 = IsEnable__13CAmemCacheSetFs
                        ((CAmemCacheSet *)CAMemCacheSet,
                         *(undefined2 *)((int)&mapMesh[1].field11_0x20 + 2));
      if (iVar6 == 0) {
        Ptr2Off__8CMapMeshFv(mapMesh);
        iVar6 = GetData__13CAmemCacheSetFsPci
                          ((CAmemCacheSet *)CAMemCacheSet,
                           *(undefined2 *)((int)&mapMesh[1].field11_0x20 + 2),s_pppPart_cpp_801d81f8
                           ,0x4e5);
        mapMesh->field12_0x24 = iVar6;
        Off2Ptr__8CMapMeshFv(mapMesh);
      }
      AddRef__13CAmemCacheSetFs
                ((CAmemCacheSet *)CAMemCacheSet,*(undefined2 *)((int)&mapMesh[1].field11_0x20 + 2));
      pppCacheLoadModelTexture__8CMapMeshFP12CMaterialSetP13CAmemCacheSet
                (mapMesh,PartMng.m_materialSet,(CAmemCacheSet *)CAMemCacheSet);
    }
    sVar10 = *psVar27;
                    /* WARNING: Load size is inaccurate */
    iVar21 = *pppMngSt->m_pppResSet;
    for (sVar23 = 0; psVar27 = psVar27 + 1, sVar23 < sVar10; sVar23 = sVar23 + 1) {
      pppCacheLoadShapeTexture__FP10pppShapeStP12CMaterialSet
                (*(pppShapeSt **)(*(int *)(iVar21 + 0x18) + *psVar27 * 4),PartMng.m_materialSet);
    }
    pppMngSt->m_mapTexLoaded = '\x01';
  }
  pppMngSt->field37_0xe6 = '\0';
  pppMngSt->m_numControlPrograms = *(int32_t *)((int)param_2 + iVar16);
  (pppMngSt->m_pppPObjLinkHead).m_owner = (_pppPDataVal *)((int32_t *)((int)param_2 + iVar16) + 1);
  pppMngSt->m_numPrograms = *(int32_t *)((int)param_2 + iVar12);
  pppMngSt->field32_0xd0 = (int32_t *)((int)param_2 + iVar12) + 1;
  iVar12 = pppMngSt->m_numPrograms;
  if (iVar12 == 0) {
    pppMngSt->m_pppPDataVals = (_pppPDataVal *)0x0;
  }
  else {
    stage = pppEnvStPtr->m_stagePtr;
    DAT_8032ed64 = 0;
    bVar2 = true;
    do {
      p_Var7 = (_pppPDataVal *)
               _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                         (&Memory,iVar12 << 4,stage,s_pppPart_cpp_801d81f8,0x585,1);
      if (p_Var7 != (_pppPDataVal *)0x0) goto LAB_80055780;
      if (bVar2) {
        bVar2 = false;
        memset(local_1d4,0,0x180);
        iVar16 = (int)&pppMngStPtr[0x5f2411].m_scale / 0x158 +
                 ((int)&pppMngStPtr[0x5f2411].m_scale >> 0x1f);
        local_1d4[iVar16 - (iVar16 >> 0x1f)] = '\x01';
      }
      p_Var8 = (_pppMngSt *)0x0;
      pcVar17 = local_1d4;
      bVar15 = 1;
      iVar16 = 0xc0;
      pCVar18 = &PartMng;
      do {
        if ((((*pcVar17 == '\0') && (pCVar18->m_pppMngStArr[0].m_baseTime != -0x1000)) &&
            (pCVar18->m_pppMngStArr[0].m_kind != 0)) &&
           (bVar1 = pCVar18->m_pppMngStArr[0].m_prio, 1 < bVar1)) {
          if (bVar15 < bVar1) {
            p_Var8 = pCVar18->m_pppMngStArr;
            unaff_r23 = (uint)pCVar18->m_pppMngStArr[0].m_prioTime;
            bVar15 = bVar1;
          }
          else if ((bVar15 == bVar1) &&
                  (uVar5 = (uint)pCVar18->m_pppMngStArr[0].m_prioTime, (int)unaff_r23 < (int)uVar5))
          {
            p_Var8 = pCVar18->m_pppMngStArr;
            unaff_r23 = uVar5;
          }
        }
        if (((pcVar17[1] == '\0') && (pCVar18->m_pppMngStArr[1].m_baseTime != -0x1000)) &&
           ((pCVar18->m_pppMngStArr[1].m_kind != 0 &&
            (bVar1 = pCVar18->m_pppMngStArr[1].m_prio, 1 < bVar1)))) {
          if (bVar15 < bVar1) {
            p_Var8 = pCVar18->m_pppMngStArr + 1;
            unaff_r23 = (uint)pCVar18->m_pppMngStArr[1].m_prioTime;
            bVar15 = bVar1;
          }
          else if ((bVar15 == bVar1) &&
                  (uVar5 = (uint)pCVar18->m_pppMngStArr[1].m_prioTime, (int)unaff_r23 < (int)uVar5))
          {
            p_Var8 = pCVar18->m_pppMngStArr + 1;
            unaff_r23 = uVar5;
          }
        }
        pcVar17 = pcVar17 + 2;
        pCVar18 = (CPartMng *)(pCVar18->m_unk0x1d4_0x3d3 + 0x37);
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
      if (p_Var8 == (_pppMngSt *)0x0) {
        bVar3 = false;
      }
      else {
        iVar16 = ((int)(p_Var8 + 0x5f2411) + 0x28) / 0x158 +
                 ((int)(p_Var8 + 0x5f2411) + 0x28 >> 0x1f);
        local_1d4[iVar16 - (iVar16 >> 0x1f)] = '\x01';
        ppVar28 = (p_Var8->m_pppPObjLinkHead).m_next;
        ppVar4 = &p_Var8->m_pppPObjLinkHead;
        while (ppVar26 = ppVar4, ppVar25 = ppVar28, ppVar25 != (pppPObjLink *)0x0) {
          ppVar28 = ppVar25->m_next;
          bVar15 = ppVar25->m_owner->m_pppProgramSetDef->m_flags;
          ppVar4 = ppVar25;
          if (-1 < (int)((uint)bVar15 << 0x1e | (uint)(bVar15 >> 2))) {
            ppVar26->m_next = ppVar28;
            p_Var22 = ppVar25->m_owner;
            ppVar24 = p_Var22->m_pppProgramSetDef;
            ppVar20 = ppVar24;
            for (iVar16 = 0; iVar16 < ppVar24->m_numStages; iVar16 = iVar16 + 1) {
              ppVar9 = ppVar20->pppSubProgEntries[0].m_prog;
              if ((ppVar9 != (pppProg *)0x0) &&
                 (pcVar19 = (code *)ppVar9->m_pppFunctionDestructor, pcVar19 != (code *)0x0)) {
                (*pcVar19)(ppVar25,ppVar20->pppSubProgEntries);
              }
              ppVar20 = (pppProgramSetDef *)&ppVar20->unk0x10;
            }
            sVar10 = p_Var22->m_activeCount + -1;
            p_Var22->m_activeCount = sVar10;
            if (sVar10 == 0) {
              p_Var22->m_pppPObjLink = (pppPObjLink *)0x0;
            }
            else if (p_Var22->m_pppPObjLink == ppVar25) {
              p_Var22->m_pppPObjLink = ppVar25->m_next;
            }
            ppVar4 = ppVar26;
            if (ppVar25 != (pppPObjLink *)0x0) {
              Free__7CMemoryFPv(&Memory,ppVar25);
            }
          }
        }
        bVar3 = true;
      }
    } while (bVar3);
    heapWalker__Q27CMemory6CStageFiPvUl(pppEnvStPtr->m_stagePtr,2,0,0xffffffff);
    pppDumpMngSt__8CPartMngFv(&PartMng);
    DAT_8032ed64 = 1;
LAB_80055780:
    pppMngSt->m_pppPDataVals = p_Var7;
  }
  if (ppVar14->m_next != (pppProgramSetDef *)0x0) {
    (pppMngSt->m_pppPObjLinkHead).m_previous = (pppPObjLink *)0x0;
  }
  pppMngSt->m_currentFrame = 0;
  if (pppMngSt->m_numPrograms == 0) {
    (pppMngSt->m_pppPObjLinkHead).m_previous = (pppPObjLink *)0x0;
  }
  else {
    (pppMngSt->m_pppPObjLinkHead).m_previous = (pppPObjLink *)ppVar14;
  }
  uVar11 = '\0';
  (pppMngSt->m_pppPObjLinkHead).m_next = (pppPObjLink *)0x0;
  pppMngSt->m_spawnedCount = 0;
  p_Var7 = pppMngSt->m_pppPDataVals;
  for (; ppVar14 != (pppProgramSetDef *)0x0; ppVar14 = ppVar14->m_next) {
    p_Var7->m_pppProgramSetDef = ppVar14;
    p_Var7->m_nextSpawnTime = ppVar14->unk0x10;
    p_Var7->m_pppPObjLink = (pppPObjLink *)0x0;
    p_Var7->m_activeCount = 0;
    p_Var7->field4_0xe = uVar11;
    uVar11 = uVar11 + '\x01';
    p_Var7 = p_Var7 + 1;
  }
  if (param_3 != 0) {
    iVar16 = 0;
    for (iVar12 = 0; iVar12 < pppMngSt->m_numControlPrograms; iVar12 = iVar12 + 1) {
      pcVar19 = *(code **)(*(int *)((int)&((pppMngSt->m_pppPObjLinkHead).m_owner)->
                                          m_pppProgramSetDef + iVar16) + 0x10);
      if (pcVar19 != (code *)0x0) {
        (*pcVar19)(pppMngSt);
      }
      iVar16 = iVar16 + 4;
    }
  }
  return;
}

