// Function: DrawMapShadow__7CMapMngFv
// Entry: 80031178
// Size: 112 bytes

void DrawMapShadow__7CMapMngFv(CMapMng *mapMng)

{
  CMapShadow *mapShadow;
  uint uVar1;
  uint uVar2;
  
  if (mapMng->field10_0xc != 0) {
    for (uVar2 = 0; uVar1 = GetSize__24CPtrArray<P10CMapShadow>Fv(&mapMng->m_mapShadowArray),
        uVar2 < uVar1; uVar2 = uVar2 + 1) {
      mapShadow = (CMapShadow *)__vc__24CPtrArray<P10CMapShadow>FUl(&mapMng->m_mapShadowArray,uVar2)
      ;
      Draw__10CMapShadowFv(mapShadow);
    }
  }
  return;
}

