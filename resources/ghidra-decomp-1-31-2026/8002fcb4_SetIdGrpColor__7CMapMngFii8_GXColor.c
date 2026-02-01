// Function: SetIdGrpColor__7CMapMngFii8_GXColor
// Entry: 8002fcb4
// Size: 232 bytes

void SetIdGrpColor__7CMapMngFii8_GXColor
               (CMapMng *mapMng,int mapIdGrpIndex,int param_3,undefined *param_4)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  
  if (param_3 == 2) {
    uVar1 = param_4[1];
    uVar2 = param_4[2];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xc = *param_4;
    uVar3 = param_4[3];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xd = uVar1;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xe = uVar2;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xf = uVar3;
    return;
  }
  if (1 < param_3) {
    if (3 < param_3) {
      return;
    }
    uVar1 = param_4[1];
    uVar2 = param_4[2];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x10 = *param_4;
    uVar3 = param_4[3];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x11 = uVar1;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x12 = uVar2;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x13 = uVar3;
    return;
  }
  if (param_3 == 0) {
    uVar1 = param_4[1];
    uVar2 = param_4[2];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x4 = *param_4;
    uVar3 = param_4[3];
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x5 = uVar1;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x6 = uVar2;
    mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x7 = uVar3;
    return;
  }
  if (param_3 < 0) {
    return;
  }
  uVar1 = param_4[1];
  uVar2 = param_4[2];
  mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x8 = *param_4;
  uVar3 = param_4[3];
  mapMng->mapIdGrpArr[mapIdGrpIndex].field_0x9 = uVar1;
  mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xa = uVar2;
  mapMng->mapIdGrpArr[mapIdGrpIndex].field_0xb = uVar3;
  return;
}

