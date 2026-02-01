// Function: DrawBefore__7CMapMngFv
// Entry: 80031084
// Size: 244 bytes

void DrawBefore__7CMapMngFv(CMapMng *mapMng)

{
  int iVar1;
  CMapMng *pCVar2;
  
  if ((mapMng->field10_0xc != 0) && (mapMng->field_0x2298b != '\0')) {
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(1);
    GXSetZMode(1,3,1);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
    if ((DAT_8032ecb8 & 8) == 0) {
      pCVar2 = &MapMng;
      for (iVar1 = 0; iVar1 < mapMng->field10_0xc; iVar1 = iVar1 + 1) {
        Draw__7CMapObjFUc(pCVar2->mapObjArr,0xfe);
        pCVar2 = (CMapMng *)&pCVar2->octTreeArr[2].field51_0x3c.z;
      }
      pCVar2 = mapMng;
      for (iVar1 = 0; iVar1 < mapMng->field8_0x8; iVar1 = iVar1 + 1) {
        Draw__8COctTreeFUc(pCVar2->octTreeArr,0xff);
        pCVar2 = (CMapMng *)&pCVar2->octTreeArr[0].field_0x38;
      }
    }
  }
  return;
}

