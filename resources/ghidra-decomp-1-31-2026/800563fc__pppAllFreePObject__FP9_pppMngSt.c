// Function: _pppAllFreePObject__FP9_pppMngSt
// Entry: 800563fc
// Size: 688 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _pppAllFreePObject__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  bool bVar1;
  _pppMngSt *p_Var2;
  pppProg *ppVar3;
  short sVar4;
  int iVar5;
  code *pcVar6;
  pppProgramSetDef *ppVar7;
  short *psVar8;
  short sVar9;
  _pppPDataVal *p_Var10;
  CMapMesh *mapMesh;
  int iVar11;
  pppProgramSetDef *ppVar12;
  pppPObjLink *ppVar13;
  short *psVar14;
  pppPObjLink *ppVar15;
  
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppPart_cpp_801d81f8,0x362);
  p_Var2 = pppMngStPtr;
  pppMngStPtr = pppMngSt;
  if ((-1 < (pppMngSt->m_soundEffectData).m_soundEffectSlot) &&
     (iVar5 = (pppMngSt->m_soundEffectData).m_soundEffectHandle, -1 < iVar5)) {
    FadeOutSe3D__6CSoundFii(&Sound,iVar5,(pppMngSt->m_soundEffectData).m_soundEffectFadeFrames);
    (pppMngSt->m_soundEffectData).m_soundEffectHandle = -1;
  }
  ppVar13 = (pppMngSt->m_pppPObjLinkHead).m_next;
  while (ppVar15 = ppVar13, ppVar15 != (pppPObjLink *)0x0) {
    p_Var10 = ppVar15->m_owner;
    ppVar13 = ppVar15->m_next;
    ppVar12 = p_Var10->m_pppProgramSetDef;
    ppVar7 = ppVar12;
    for (iVar5 = 0; iVar5 < ppVar12->m_numStages; iVar5 = iVar5 + 1) {
      ppVar3 = ppVar7->pppSubProgEntries[0].m_prog;
      if ((ppVar3 != (pppProg *)0x0) &&
         (pcVar6 = (code *)ppVar3->m_pppFunctionDestructor, pcVar6 != (code *)0x0)) {
        (*pcVar6)(ppVar15,ppVar7->pppSubProgEntries);
      }
      ppVar7 = (pppProgramSetDef *)&ppVar7->unk0x10;
    }
    sVar4 = p_Var10->m_activeCount + -1;
    p_Var10->m_activeCount = sVar4;
    if (sVar4 == 0) {
      p_Var10->m_pppPObjLink = (pppPObjLink *)0x0;
    }
    else if (p_Var10->m_pppPObjLink == ppVar15) {
      p_Var10->m_pppPObjLink = ppVar15->m_next;
    }
    if (ppVar15 != (pppPObjLink *)0x0) {
      Free__7CMemoryFPv(&Memory,ppVar15);
    }
  }
  (pppMngSt->m_pppPObjLinkHead).m_next = (pppPObjLink *)0x0;
  bVar1 = pppMngSt->m_pppPDataVals != (_pppPDataVal *)0x0;
  if (bVar1) {
    if (bVar1) {
      Free__7CMemoryFPv(&Memory);
    }
    pppMngSt->m_pppPDataVals = (_pppPDataVal *)0x0;
  }
  DAT_8032ed7c = 0;
  pppMngSt->m_baseTime = -0x1000;
  if (Game.game.m_currentSceneId != 7) {
    if (pppMngSt->m_hasMapRef != '\0') {
                    /* WARNING: Load size is inaccurate */
      psVar8 = (short *)(*(int *)(*pppMngSt->m_pppResSet + 0x10) + pppMngSt->m_partIndex * 8);
      sVar4 = *psVar8;
      if (sVar4 != -1) {
        Release__13CAmemCacheSetFs((CAmemCacheSet *)CAMemCacheSet,sVar4);
      }
      if (pppMngSt->m_mapTexLoaded != '\0') {
        iVar5 = *(int *)(psVar8 + 2);
        psVar8 = (short *)(iVar5 + *(int *)(iVar5 + 0x10));
                    /* WARNING: Load size is inaccurate */
        iVar11 = *pppMngSt->m_pppResSet;
        sVar4 = *psVar8;
        psVar14 = (short *)(iVar5 + *(int *)(iVar5 + 0x14));
        for (sVar9 = 0; psVar8 = psVar8 + 1, sVar9 < sVar4; sVar9 = sVar9 + 1) {
          mapMesh = *(CMapMesh **)(*(int *)(iVar11 + 0x14) + *psVar8 * 4);
          Release__13CAmemCacheSetFs
                    ((CAmemCacheSet *)CAMemCacheSet,
                     *(undefined2 *)((int)&mapMesh[1].field11_0x20 + 2));
          pppCacheDumpModelTexture__8CMapMeshFP12CMaterialSetP13CAmemCacheSet
                    (mapMesh,PartMng.m_materialSet,(CAmemCacheSet *)CAMemCacheSet);
        }
        sVar4 = *psVar14;
                    /* WARNING: Load size is inaccurate */
        iVar5 = *pppMngSt->m_pppResSet;
        for (sVar9 = 0; psVar14 = psVar14 + 1, sVar9 < sVar4; sVar9 = sVar9 + 1) {
          pppCacheDumpShapeTexture__FP10pppShapeStP12CMaterialSet
                    (*(pppShapeSt **)(*(int *)(iVar5 + 0x18) + *psVar14 * 4),PartMng.m_materialSet);
        }
      }
    }
    pppMngSt->m_mapTexLoaded = '\0';
    pppMngSt->m_hasMapRef = '\0';
  }
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppPart_cpp_801d81f8,0x3a1);
  pppMngStPtr = p_Var2;
  return;
}

