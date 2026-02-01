// Function: Calc__7CMapMngFv
// Entry: 800311e8
// Size: 552 bytes

void Calc__7CMapMngFv(CMapMng *mapMng)

{
  int iVar1;
  CMapAnimRun *mapAnimRun;
  CMapShadow *mapShadow;
  uint uVar2;
  uint uVar3;
  uint32_t index;
  CMapMng *pCVar4;
  CMapMng *pCVar5;
  Mtx MStack_48;
  
  *(int *)&mapMng->field_0x4 = *(int *)&mapMng->field_0x4 + 1;
  if (mapMng->field10_0xc != 0) {
    iVar1 = GetSize__25CPtrArray<P11CMapAnimRun>Fv(&mapMng->g_CMapAnimRunArray);
    for (index = 0; (int)index < iVar1; index = index + 1) {
      mapAnimRun = (CMapAnimRun *)
                   __vc__25CPtrArray<P11CMapAnimRun>FUl(&mapMng->g_CMapAnimRunArray,index);
      Calc__11CMapAnimRunFl(mapAnimRun,*(undefined4 *)&mapMng->field_0x22a6c);
    }
    PSMTXIdentity(&MStack_48);
    if (*(CMapObj **)&mapMng->field_0x228e8 != (CMapObj *)0x0) {
      CalcMtx__7CMapObjFPA4_fUc(*(CMapObj **)&mapMng->field_0x228e8,&MStack_48,0);
    }
    *(int *)&mapMng->field_0x22a6c = *(int *)&mapMng->field_0x22a6c + 1;
    uVar3 = *(int *)&mapMng->field_0x22a6c + 1;
    *(uint *)&mapMng->field_0x22a6c = uVar3;
    if ((((int)uVar3 >> 0x1f) + (uint)(1 < uVar3) & 0xff) != 0x1e) {
      *(undefined4 *)&mapMng->field_0x22a6c = 0x1c;
    }
    SetLightSource__7CMapMngFv(mapMng);
    for (uVar3 = 0; uVar2 = GetSize__24CPtrArray<P10CMapShadow>Fv(&mapMng->m_mapShadowArray),
        uVar3 < uVar2; uVar3 = uVar3 + 1) {
      mapShadow = (CMapShadow *)__vc__24CPtrArray<P10CMapShadow>FUl(&mapMng->m_mapShadowArray,uVar3)
      ;
      Calc__10CMapShadowFv(mapShadow);
    }
    pCVar4 = &MapMng;
    pCVar5 = pCVar4;
    for (iVar1 = 0; iVar1 < mapMng->field10_0xc; iVar1 = iVar1 + 1) {
      Calc__7CMapObjFv(pCVar5->mapObjArr);
      pCVar5 = (CMapMng *)&pCVar5->octTreeArr[2].field51_0x3c.z;
    }
    if (*(int *)&mapMng->field_0x213dc != 0) {
      Calc__14CMapTexAnimSetFv();
    }
    Calc__12CMaterialSetFv(*(CMaterialSet **)&mapMng->field_0x213d4);
    pCVar5 = mapMng;
    for (iVar1 = 0; iVar1 < mapMng->field8_0x8; iVar1 = iVar1 + 1) {
      InsertOctTree__9CLightPcsFQ29CLightPcs6TARGETR8COctTree(&LightPcs,1,pCVar5->octTreeArr);
      pCVar5 = (CMapMng *)&pCVar5->octTreeArr[0].field_0x38;
    }
    pCVar5 = mapMng;
    for (iVar1 = 0; iVar1 < mapMng->field8_0x8; iVar1 = iVar1 + 1) {
      CMapShadowInsertOctTree__FQ210CMapShadow6TARGETR8COctTree
                ((CMapShadow *)0x1,pCVar5->octTreeArr);
      pCVar5 = (CMapMng *)&pCVar5->octTreeArr[0].field_0x38;
    }
    pCVar5 = mapMng;
    for (iVar1 = 0; iVar1 < mapMng->field8_0x8; iVar1 = iVar1 + 1) {
      SetDrawFlag__8COctTreeFv(pCVar5->octTreeArr);
      pCVar5 = (CMapMng *)&pCVar5->octTreeArr[0].field_0x38;
    }
    for (iVar1 = 0; iVar1 < mapMng->field10_0xc; iVar1 = iVar1 + 1) {
      SetDrawFlag__7CMapObjFv(pCVar4->mapObjArr);
      pCVar4 = (CMapMng *)&pCVar4->octTreeArr[2].field51_0x3c.z;
    }
  }
  return;
}

