// Function: SetMapObjTransRate__7CMapMngFifff
// Entry: 8002f548
// Size: 28 bytes

void SetMapObjTransRate__7CMapMngFifff(float x,float y,float z,CMapMng *mapMng,int mapObjIndex)

{
  mapMng->mapObjArr[mapObjIndex].m_translationRate.x = x;
  mapMng->mapObjArr[mapObjIndex].m_translationRate.y = y;
  mapMng->mapObjArr[mapObjIndex].m_translationRate.z = z;
  return;
}

