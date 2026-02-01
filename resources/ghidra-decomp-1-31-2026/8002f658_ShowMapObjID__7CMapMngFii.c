// Function: ShowMapObjID__7CMapMngFii
// Entry: 8002f658
// Size: 84 bytes

void ShowMapObjID__7CMapMngFii(CMapMng *mapMng,uint param_2,int param_3)

{
  CMapMng *pCVar1;
  int iVar2;
  
  pCVar1 = mapMng;
  for (iVar2 = 0; iVar2 < mapMng->field10_0xc; iVar2 = iVar2 + 1) {
    if (*(ushort *)&pCVar1->mapObjArr[0].field_0x2e == param_2) {
      if (param_3 == 0) {
        pCVar1->mapObjArr[0].field_0x18 = pCVar1->mapObjArr[0].field_0x18 & 0xfe;
      }
      else {
        pCVar1->mapObjArr[0].field_0x18 = pCVar1->mapObjArr[0].field_0x18 | 1;
      }
    }
    pCVar1 = (CMapMng *)&pCVar1->octTreeArr[2].field51_0x3c.z;
  }
  return;
}

