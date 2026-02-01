// Function: __ct__7CMapHitFv
// Entry: 80026dec
// Size: 56 bytes

void __ct__7CMapHitFv(CMapHit *mapHit)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8032f8f0;
  fVar1 = FLOAT_8032f8ec;
  (mapHit->m_positionMin).z = FLOAT_8032f8ec;
  (mapHit->m_positionMin).y = fVar1;
  (mapHit->m_positionMin).x = fVar1;
  (mapHit->m_positionMax).z = fVar2;
  (mapHit->m_positionMax).y = fVar2;
  (mapHit->m_positionMax).x = fVar2;
  mapHit->m_vertexCount = 0;
  mapHit->m_faceCount = 0;
  mapHit->m_vertices = (float *)0x0;
  mapHit->m_faces = (CMapHitFace *)0x0;
  return;
}

