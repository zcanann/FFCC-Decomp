// Function: GetMapObjWMtx__7CMapMngFiPA4_f
// Entry: 8002f880
// Size: 52 bytes

void GetMapObjWMtx__7CMapMngFiPA4_f(CMapMng *mapMng,int mapObjIndex,Mtx *destination)

{
  PSMTXCopy((Mtx *)&mapMng->mapObjArr[mapObjIndex].field_0xb8,destination);
  return;
}

