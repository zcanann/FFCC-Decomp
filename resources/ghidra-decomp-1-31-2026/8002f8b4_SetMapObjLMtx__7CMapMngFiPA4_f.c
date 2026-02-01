// Function: SetMapObjLMtx__7CMapMngFiPA4_f
// Entry: 8002f8b4
// Size: 92 bytes

void SetMapObjLMtx__7CMapMngFiPA4_f(CMapMng *mapMng,int mapObjIndex,Mtx *source)

{
  PSMTXCopy(source,&mapMng->mapObjArr[mapObjIndex].localMtx);
  mapMng->mapObjArr[mapObjIndex].field_0x1c = 1;
  mapMng->mapObjArr[mapObjIndex].field_0x1b = 1;
  mapMng->mapObjArr[mapObjIndex].field_0x1c = 0;
  return;
}

