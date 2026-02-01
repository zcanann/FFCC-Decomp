// Function: Create__7CMapMngFv
// Entry: 8003368c
// Size: 304 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Create__7CMapMngFv(CMapMng *mapMng)

{
  CStage *pCVar1;
  int iVar2;
  CMapMng *pCVar3;
  
  *(undefined4 *)&mapMng->field_0x4 = 0;
  *(undefined2 *)&mapMng->field_0x10 = 0;
  *(undefined2 *)&mapMng->field_0xe = 0;
  mapMng->field10_0xc = 0;
  mapMng->field8_0x8 = 0;
  mapMng->field_0x2298c = 0xff;
  mapMng->field_0x2298d = 0xff;
  mapMng->field_0x2298e = 0xff;
  mapMng->field_0x2298f = 0xff;
  if (Game.game.m_currentSceneId == 3) {
    mapMng->field_0x22988 = 0;
  }
  else {
    mapMng->field_0x22988 = 1;
  }
  *(undefined4 *)&mapMng->field_0x22a6c = 0;
  *(undefined4 *)&mapMng->field_0x228e8 = 0;
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x540000,s_CMapMng_mapmng_801d75f4,0);
  *(CStage **)mapMng = pCVar1;
  SetStage__25CPtrArray<P11CMapAnimRun>FPQ27CMemory6CStage
            (&mapMng->g_CMapAnimRunArray,*(undefined4 *)mapMng);
  SetStage__21CPtrArray<P8CMapAnim>FPQ27CMemory6CStage
            (&mapMng->g_CMapAnimArray,*(undefined4 *)mapMng);
  SetStage__27CPtrArray<P13CMapAnimKeyDt>FPQ27CMemory6CStage
            (&mapMng->g_CMapAnimKeyDtArray,*(undefined4 *)mapMng);
  SetStage__24CPtrArray<P10CMapShadow>FPQ27CMemory6CStage
            (&mapMng->m_mapShadowArray,*(undefined4 *)mapMng);
  iVar2 = 0;
  pCVar3 = mapMng;
  do {
    SetStage__29CPtrArray<P15CMapLightHolder>FPQ27CMemory6CStage
              (pCVar3->mapLightHolderArr,*(undefined4 *)mapMng);
    iVar2 = iVar2 + 1;
    pCVar3 = (CMapMng *)&pCVar3->octTreeArr[0].field2_0x8;
  } while (iVar2 < 2);
  DAT_8032ecb9 = 0;
  return;
}

