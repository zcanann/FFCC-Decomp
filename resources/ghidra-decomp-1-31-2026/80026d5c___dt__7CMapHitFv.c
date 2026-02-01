// Function: __dt__7CMapHitFv
// Entry: 80026d5c
// Size: 144 bytes

CMapHit * __dt__7CMapHitFv(CMapHit *mapHit,short param_2)

{
  CMapHitFace *pCVar1;
  
  if (mapHit != (CMapHit *)0x0) {
    if (mapHit->m_vertices != (float *)0x0) {
      __dl__FPv();
      mapHit->m_vertices = (float *)0x0;
    }
    pCVar1 = mapHit->m_faces;
    if (pCVar1 != (CMapHitFace *)0x0) {
      if (pCVar1 != (CMapHitFace *)0x0) {
        __dla__FPv(&pCVar1[-1].field16_0x10.z);
      }
      mapHit->m_faces = (CMapHitFace *)0x0;
    }
    mapHit->m_vertexCount = 0;
    mapHit->m_faceCount = 0;
    if (0 < param_2) {
      __dl__FPv(mapHit);
    }
  }
  return mapHit;
}

