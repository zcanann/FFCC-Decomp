// Function: GetMapObjEffectIdx__7CMapMngFUs
// Entry: 8002f910
// Size: 64 bytes

int GetMapObjEffectIdx__7CMapMngFUs(CMapMng *mapMng,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)mapMng->field10_0xc;
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      if (*(short *)&mapMng->mapObjArr[0].field_0x30 == param_2) {
        return iVar2;
      }
      mapMng = (CMapMng *)&mapMng->octTreeArr[2].field51_0x3c.z;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return -1;
}

