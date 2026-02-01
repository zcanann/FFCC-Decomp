// Function: ShowMapObjChildID__7CMapMngFii
// Entry: 8002f5f0
// Size: 104 bytes

void ShowMapObjChildID__7CMapMngFii(CMapMng *mapMng,uint param_2,undefined4 param_3)

{
  int iVar1;
  CMapMng *pCVar2;
  
  pCVar2 = mapMng;
  for (iVar1 = 0; iVar1 < mapMng->field10_0xc; iVar1 = iVar1 + 1) {
    if (*(ushort *)&pCVar2->mapObjArr[0].field_0x2e == param_2) {
      SetShow__7CMapObjFi(pCVar2->mapObjArr,param_3);
    }
    pCVar2 = (CMapMng *)&pCVar2->octTreeArr[2].field51_0x3c.z;
  }
  return;
}

