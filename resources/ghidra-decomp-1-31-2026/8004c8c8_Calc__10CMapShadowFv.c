// Function: Calc__10CMapShadowFv
// Entry: 8004c8c8
// Size: 84 bytes

void Calc__10CMapShadowFv(CMapShadow *mapShadow)

{
  float fVar1;
  
  fVar1 = FLOAT_8032fce0;
  mapShadow->field84_0x54 = mapShadow->field84_0x54 + mapShadow->field178_0xb8;
  if (fVar1 < mapShadow->field84_0x54) {
    mapShadow->field84_0x54 = mapShadow->field84_0x54 - fVar1;
  }
  fVar1 = FLOAT_8032fce0;
  mapShadow->field97_0x64 = mapShadow->field97_0x64 + *(float *)&mapShadow->field_0xbc;
  if (mapShadow->field97_0x64 <= fVar1) {
    return;
  }
  mapShadow->field97_0x64 = mapShadow->field97_0x64 - fVar1;
  return;
}

