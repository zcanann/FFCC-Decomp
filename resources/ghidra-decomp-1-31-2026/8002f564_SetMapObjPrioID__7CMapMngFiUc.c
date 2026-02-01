// Function: SetMapObjPrioID__7CMapMngFiUc
// Entry: 8002f564
// Size: 56 bytes

void SetMapObjPrioID__7CMapMngFiUc(CMapMng *mapMng,uint param_2,undefined param_3)

{
  CMapMng *pCVar1;
  int iVar2;
  
  pCVar1 = mapMng;
  for (iVar2 = 0; iVar2 < mapMng->field10_0xc; iVar2 = iVar2 + 1) {
    if (*(ushort *)&pCVar1->mapObjArr[0].field_0x2e == param_2) {
      pCVar1->mapObjArr[0].field_0x15 = param_3;
      pCVar1->mapObjArr[0].field_0x14 = param_3;
    }
    pCVar1 = (CMapMng *)&pCVar1->octTreeArr[2].field51_0x3c.z;
  }
  return;
}

