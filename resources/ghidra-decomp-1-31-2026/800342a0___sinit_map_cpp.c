// Function: __sinit_map_cpp
// Entry: 800342a0
// Size: 320 bytes

void __sinit_map_cpp(void)

{
  __construct_array(MapMng.octTreeArr,__ct__8COctTreeFv,__dt__8COctTreeFv,0x4c,0x10);
  __construct_array(MapMng.mapHits,__ct__7CMapHitFv,__dt__7CMapHitFv,0x24,0x20);
  __construct_array(MapMng.mapObjArr,__ct__7CMapObjFv,__dt__7CMapObjFv,0xf0,0x200);
  __construct_array(MapMng.mapMeshArr,__ct__8CMapMeshFv,__dt__8CMapMeshFv,0x44,0xa0);
  __ct__25CPtrArray<P11CMapAnimRun>Fv(&MapMng.g_CMapAnimRunArray);
  __ct__21CPtrArray<P8CMapAnim>Fv(&MapMng.g_CMapAnimArray);
  __ct__27CPtrArray<P13CMapAnimKeyDt>Fv(&MapMng.g_CMapAnimKeyDtArray);
  __ct__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray);
  __construct_array(MapMng.mapLightHolderArr,__ct__29CPtrArray<P15CMapLightHolder>Fv,
                    __dt__29CPtrArray<P15CMapLightHolder>Fv,0x1c,2);
  __construct_array(MapMng.mapIdGrpArr,__ct__9CMapIdGrpFv,0,0x14,0x100);
  __register_global_object(&MapMng,__dt__7CMapMngFv,&Vec_80245758);
  return;
}

