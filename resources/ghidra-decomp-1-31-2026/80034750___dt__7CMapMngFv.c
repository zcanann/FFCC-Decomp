// Function: __dt__7CMapMngFv
// Entry: 80034750
// Size: 476 bytes

CMapMng * __dt__7CMapMngFv(CMapMng *mapMng,short param_2)

{
  void **ppvVar1;
  
  if (mapMng != (CMapMng *)0x0) {
    __destroy_arr(mapMng->mapLightHolderArr,__dt__29CPtrArray<P15CMapLightHolder>Fv,0x1c,2);
    if (mapMng != (CMapMng *)0xfffdebcc) {
      (mapMng->m_mapShadowArray).vtable = &PTR_PTR_s_CPtrArray<CMapShadow_*>_801e8978;
      ppvVar1 = (mapMng->m_mapShadowArray).items;
      if (ppvVar1 != (void **)0x0) {
        __dla__FPv(ppvVar1);
        (mapMng->m_mapShadowArray).items = (void **)0x0;
      }
      (mapMng->m_mapShadowArray).size = 0;
      (mapMng->m_mapShadowArray).numItems = 0;
    }
    if (mapMng != (CMapMng *)0xfffdebe8) {
      (mapMng->g_CMapAnimKeyDtArray).vtable = &PTR_PTR_s_CPtrArray<CMapAnimKeyDt_*>_801e8984;
      ppvVar1 = (mapMng->g_CMapAnimKeyDtArray).items;
      if (ppvVar1 != (void **)0x0) {
        __dla__FPv(ppvVar1);
        (mapMng->g_CMapAnimKeyDtArray).items = (void **)0x0;
      }
      (mapMng->g_CMapAnimKeyDtArray).size = 0;
      (mapMng->g_CMapAnimKeyDtArray).numItems = 0;
    }
    if (mapMng != (CMapMng *)0xfffdec04) {
      (mapMng->g_CMapAnimArray).vtable = &PTR_PTR_s_CPtrArray<CMapAnim_*>_801e8990;
      ppvVar1 = (mapMng->g_CMapAnimArray).items;
      if (ppvVar1 != (void **)0x0) {
        __dla__FPv(ppvVar1);
        (mapMng->g_CMapAnimArray).items = (void **)0x0;
      }
      (mapMng->g_CMapAnimArray).size = 0;
      (mapMng->g_CMapAnimArray).numItems = 0;
    }
    if (mapMng != (CMapMng *)0xfffdec20) {
      (mapMng->g_CMapAnimRunArray).vtable = &PTR_PTR_s_CPtrArray<CMapAnimRun_*>_801e899c;
      ppvVar1 = (mapMng->g_CMapAnimRunArray).items;
      if (ppvVar1 != (void **)0x0) {
        __dla__FPv(ppvVar1);
        (mapMng->g_CMapAnimRunArray).items = (void **)0x0;
      }
      (mapMng->g_CMapAnimRunArray).size = 0;
      (mapMng->g_CMapAnimRunArray).numItems = 0;
    }
    __destroy_arr(mapMng->mapMeshArr,__dt__8CMapMeshFv,0x44,0xa0);
    __destroy_arr(mapMng->mapObjArr,__dt__7CMapObjFv,0xf0,0x200);
    __destroy_arr(mapMng->mapHits,__dt__7CMapHitFv,0x24,0x20);
    __destroy_arr(mapMng->octTreeArr,__dt__8COctTreeFv,0x4c,0x10);
    if (0 < param_2) {
      __dl__FPv(mapMng);
    }
  }
  return mapMng;
}

