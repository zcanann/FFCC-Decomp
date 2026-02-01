// Function: SetIdGrpMask__7CMapMngFiUl
// Entry: 8002fd9c
// Size: 20 bytes

void SetIdGrpMask__7CMapMngFiUl(CMapMng *mapMng,int mapIdGrpIndex,undefined4 param_3)

{
  *(undefined4 *)(mapMng->mapIdGrpArr + mapIdGrpIndex) = param_3;
  return;
}

