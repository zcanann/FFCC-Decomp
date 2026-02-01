// Function: pppReleasePdt__8CPartMngFi
// Entry: 8005ea20
// Size: 732 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppReleasePdt__8CPartMngFi(CPartMng *partMng,int pdtSlotIndex)

{
  short sVar1;
  int iVar2;
  CMapMesh *mapMesh;
  int *piVar3;
  int iVar4;
  int iVar5;
  _pppDataHead *p_Var6;
  pppPdtSlot *ppVar7;
  
  ppVar7 = partMng->m_pdtSlots + pdtSlotIndex;
  if (ppVar7->m_pppDataHead != (_pppDataHead *)0x0) {
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x158);
    ReleaseTag__12CMaterialSetFP11CTextureSetiP13CAmemCacheSet
              (partMng->m_materialSet,partMng->m_textureSet,pdtSlotIndex,
               (CAmemCacheSet *)CAMemCacheSet);
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x13a);
    pppEnvStPtr = (_pppEnvSt *)ppVar7->field1_0x4;
    iVar4 = 0;
    do {
      if ((pppPdtSlot *)partMng->m_pppMngStArr[0].m_pppResSet == ppVar7) {
        _pppAllFreePObject__FP9_pppMngSt(partMng->m_pppMngStArr);
      }
      iVar4 = iVar4 + 1;
      partMng = (CPartMng *)partMng->m_rgbaA;
    } while (iVar4 < 0x180);
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x149);
    p_Var6 = ppVar7->m_pppDataHead;
    if (p_Var6 != (_pppDataHead *)0x0) {
      iVar4 = 0;
      iVar5 = 0;
      while( true ) {
        if ((int)(uint)p_Var6->m_modelCount <= iVar4) break;
        mapMesh = *(CMapMesh **)(p_Var6->m_modelNames + iVar5);
        sVar1 = *(short *)&mapMesh[1].field11_0x20 + -1;
        *(short *)&mapMesh[1].field11_0x20 = sVar1;
        if (sVar1 < 1) {
          iVar2 = (int)*(short *)((int)&mapMesh[1].field11_0x20 + 2);
          if (iVar2 != -1) {
            DestroyCache__13CAmemCacheSetFi((CAmemCacheSet *)CAMemCacheSet,iVar2);
            mapMesh->field12_0x24 = 0;
            mapMesh->field13_0x28 = 0;
          }
          Destroy__8CMapMeshFv(mapMesh);
          *(undefined2 *)&mapMesh[1].field11_0x20 = 0;
          *(undefined *)&mapMesh[1].field12_0x24 = 0;
        }
        iVar5 = iVar5 + 4;
        iVar4 = iVar4 + 1;
      }
      if ((void *)p_Var6->m_modelNames != (void *)0x0) {
        __dla__FPv((void *)p_Var6->m_modelNames);
        p_Var6->m_modelNames = 0;
      }
      iVar4 = 0;
      iVar5 = 0;
      while( true ) {
        if ((int)(uint)p_Var6->m_shapeCount <= iVar4) break;
        piVar3 = *(int **)(p_Var6->m_shapeNames + iVar5);
        sVar1 = *(short *)(piVar3 + 10);
        *(short *)(piVar3 + 10) = sVar1 + -1;
        if ((short)(sVar1 + -1) < 1) {
          if (*piVar3 != 0) {
            __dl__FPv();
            *piVar3 = 0;
          }
          if (piVar3[1] != 0) {
            __dl__FPv();
            piVar3[1] = 0;
          }
          *(undefined2 *)(piVar3 + 10) = 0;
          *(undefined *)((int)piVar3 + 0x2a) = 0;
        }
        iVar5 = iVar5 + 4;
        iVar4 = iVar4 + 1;
      }
      if ((void *)p_Var6->m_shapeNames != (void *)0x0) {
        __dla__FPv((void *)p_Var6->m_shapeNames);
        p_Var6->m_shapeNames = 0;
      }
      iVar5 = 0;
      for (iVar4 = 0; iVar4 < (int)(uint)p_Var6->m_shapeGroupCount; iVar4 = iVar4 + 1) {
        iVar2 = p_Var6->m_shapeGroups + iVar5;
        if (*(int *)(iVar2 + 4) != 0) {
          __dl__FPv();
          *(undefined4 *)(iVar2 + 4) = 0;
        }
        iVar5 = iVar5 + 8;
      }
      if ((void *)p_Var6->m_shapeGroups != (void *)0x0) {
        __dla__FPv((void *)p_Var6->m_shapeGroups);
        p_Var6->m_shapeGroups = 0;
      }
      iVar5 = 0;
      for (iVar4 = 0; iVar4 < (int)(uint)p_Var6->m_cacheChunkCount; iVar4 = iVar4 + 1) {
        DestroyCache__13CAmemCacheSetFi
                  ((CAmemCacheSet *)CAMemCacheSet,(int)*(short *)(p_Var6->m_cacheChunks + iVar5));
        iVar5 = iVar5 + 8;
      }
      if (p_Var6->m_cacheChunks != 0) {
        __dl__FPv();
        p_Var6->m_cacheChunks = 0;
      }
      if (ppVar7->m_pppDataHead != (_pppDataHead *)0x0) {
        __dl__FPv();
        ppVar7->m_pppDataHead = (_pppDataHead *)0x0;
      }
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x182);
  }
  return;
}

