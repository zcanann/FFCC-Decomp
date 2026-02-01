// Function: DestroyMap__7CMapMngFv
// Entry: 80033254
// Size: 892 bytes

void DestroyMap__7CMapMngFv(CMapMng *mapMng)

{
  int *piVar1;
  uint uVar2;
  CMapAnim *pCVar3;
  int iVar4;
  uint uVar5;
  uint32_t index;
  CMapMng *pCVar6;
  CPtrArray *ptrArray;
  int iVar7;
  
  pCVar6 = mapMng;
  for (iVar7 = 0; iVar7 < mapMng->field8_0x8; iVar7 = iVar7 + 1) {
    __dt__8COctTreeFv(pCVar6->octTreeArr,0xffff);
    pCVar6 = (CMapMng *)&pCVar6->octTreeArr[0].field_0x38;
  }
  mapMng->field8_0x8 = 0;
  pCVar6 = mapMng;
  for (iVar7 = 0; iVar7 < mapMng->field9_0xa; iVar7 = iVar7 + 1) {
    __dt__7CMapHitFv(pCVar6->mapHits,0xffff);
    pCVar6 = (CMapMng *)&pCVar6->octTreeArr[0].field_0x10;
  }
  mapMng->field9_0xa = 0;
  pCVar6 = mapMng;
  for (iVar7 = 0; iVar7 < mapMng->field10_0xc; iVar7 = iVar7 + 1) {
    __dt__7CMapObjFv(pCVar6->mapObjArr,0xffffffff);
    pCVar6 = (CMapMng *)&pCVar6->octTreeArr[2].field51_0x3c.z;
  }
  mapMng->field10_0xc = 0;
  pCVar6 = mapMng;
  for (iVar7 = 0; iVar7 < *(short *)&mapMng->field_0xe; iVar7 = iVar7 + 1) {
    __dt__8CMapMeshFv(pCVar6->mapMeshArr,0xffff);
    pCVar6 = (CMapMng *)&pCVar6->octTreeArr[0].field_0x30;
  }
  *(undefined2 *)&mapMng->field_0xe = 0;
  piVar1 = *(int **)&mapMng->field_0x213d4;
  if (piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&mapMng->field_0x213d4 = 0;
  }
  piVar1 = *(int **)&mapMng->field_0x213d8;
  if (piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&mapMng->field_0x213d8 = 0;
  }
  piVar1 = *(int **)&mapMng->field_0x213dc;
  if (piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&mapMng->field_0x213dc = 0;
  }
  for (uVar5 = 0; uVar2 = GetSize__21CPtrArray<P8CMapAnim>Fv(&mapMng->g_CMapAnimArray),
      uVar5 < uVar2; uVar5 = uVar5 + 1) {
    iVar7 = __vc__21CPtrArray<P8CMapAnim>FUl(&mapMng->g_CMapAnimArray,uVar5);
    if (iVar7 != 0) {
      pCVar3 = (CMapAnim *)__vc__21CPtrArray<P8CMapAnim>FUl(&mapMng->g_CMapAnimArray,uVar5);
      __dt__8CMapAnimFv(pCVar3,1);
    }
  }
  RemoveAll__21CPtrArray<P8CMapAnim>Fv(&mapMng->g_CMapAnimArray);
  for (uVar5 = 0; uVar2 = GetSize__27CPtrArray<P13CMapAnimKeyDt>Fv(&mapMng->g_CMapAnimKeyDtArray),
      uVar5 < uVar2; uVar5 = uVar5 + 1) {
    iVar7 = __vc__27CPtrArray<P13CMapAnimKeyDt>FUl(&mapMng->g_CMapAnimKeyDtArray,uVar5);
    if (iVar7 != 0) {
      pCVar3 = (CMapAnim *)
               __vc__27CPtrArray<P13CMapAnimKeyDt>FUl(&mapMng->g_CMapAnimKeyDtArray,uVar5);
      __dt__13CMapAnimKeyDtFv(pCVar3,1);
    }
  }
  RemoveAll__27CPtrArray<P13CMapAnimKeyDt>Fv(&mapMng->g_CMapAnimKeyDtArray);
  for (index = 0; uVar5 = GetSize__25CPtrArray<P11CMapAnimRun>Fv(&mapMng->g_CMapAnimRunArray),
      index < uVar5; index = index + 1) {
    iVar7 = __vc__25CPtrArray<P11CMapAnimRun>FUl(&mapMng->g_CMapAnimRunArray,index);
    if (iVar7 != 0) {
      __vc__25CPtrArray<P11CMapAnimRun>FUl(&mapMng->g_CMapAnimRunArray,index);
      __dl__FPv();
    }
  }
  RemoveAll__25CPtrArray<P11CMapAnimRun>Fv(&mapMng->g_CMapAnimRunArray);
  for (uVar5 = 0; uVar2 = GetSize__24CPtrArray<P10CMapShadow>Fv(&mapMng->m_mapShadowArray),
      uVar5 < uVar2; uVar5 = uVar5 + 1) {
    iVar7 = __vc__24CPtrArray<P10CMapShadow>FUl(&mapMng->m_mapShadowArray,uVar5);
    if (iVar7 != 0) {
      __vc__24CPtrArray<P10CMapShadow>FUl(&mapMng->m_mapShadowArray,uVar5);
      __dl__FPv();
    }
  }
  RemoveAll__24CPtrArray<P10CMapShadow>Fv(&mapMng->m_mapShadowArray);
  iVar7 = 0;
  pCVar6 = mapMng;
  do {
    ptrArray = pCVar6->mapLightHolderArr;
    for (uVar5 = 0; uVar2 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(ptrArray), uVar5 < uVar2;
        uVar5 = uVar5 + 1) {
      iVar4 = __vc__29CPtrArray<P15CMapLightHolder>FUl(ptrArray,uVar5);
      if (iVar4 != 0) {
        __vc__29CPtrArray<P15CMapLightHolder>FUl(ptrArray,uVar5);
        __dl__FPv();
      }
    }
    RemoveAll__29CPtrArray<P15CMapLightHolder>Fv(pCVar6->mapLightHolderArr);
    iVar7 = iVar7 + 1;
    pCVar6 = (CMapMng *)&pCVar6->octTreeArr[0].field2_0x8;
  } while (iVar7 < 2);
  DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs,1);
  *(undefined4 *)&mapMng->field_0x228e8 = 0;
  return;
}

