// Function: Calc__12CMaterialSetFv
// Entry: 8003c8d0
// Size: 352 bytes

void Calc__12CMaterialSetFv(CMaterialSet *materialSet)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  double dVar7;
  
  for (uVar6 = 0; uVar4 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials), uVar6 < uVar4
      ; uVar6 = uVar6 + 1) {
    iVar3 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,uVar6);
    if (iVar3 != 0) {
      iVar5 = 0;
      do {
        fVar2 = FLOAT_8032faf0;
        if (*(char *)(iVar3 + 0x4c) == '\x01') {
          *(float *)(iVar3 + 0x50) = *(float *)(iVar3 + 0x50) + *(float *)(iVar3 + 0x58);
          fVar1 = *(float *)(iVar3 + 0x50);
          if (fVar1 <= fVar2) {
            if (fVar1 < FLOAT_8032faf4) {
              *(float *)(iVar3 + 0x50) = fVar1 + fVar2;
            }
          }
          else {
            *(float *)(iVar3 + 0x50) = fVar1 - fVar2;
          }
        }
        else if (*(char *)(iVar3 + 0x4c) == '\x02') {
          dVar7 = (double)Get__12CMapKeyFrameFv(*(CMapKeyFrame **)(iVar3 + 0x58));
          *(float *)(iVar3 + 0x50) = (float)dVar7;
          Calc__12CMapKeyFrameFv(*(CMapKeyFrame **)(iVar3 + 0x58));
        }
        fVar2 = FLOAT_8032faf0;
        if (*(char *)(iVar3 + 0x4d) == '\x01') {
          *(float *)(iVar3 + 0x54) = *(float *)(iVar3 + 0x54) + *(float *)(iVar3 + 0x5c);
          fVar1 = *(float *)(iVar3 + 0x54);
          if (fVar1 <= fVar2) {
            if (fVar1 < FLOAT_8032faf4) {
              *(float *)(iVar3 + 0x54) = fVar1 + fVar2;
            }
          }
          else {
            *(float *)(iVar3 + 0x54) = fVar1 - fVar2;
          }
        }
        else if (*(char *)(iVar3 + 0x4d) == '\x02') {
          dVar7 = (double)Get__12CMapKeyFrameFv(*(CMapKeyFrame **)(iVar3 + 0x5c));
          *(float *)(iVar3 + 0x54) = (float)dVar7;
          Calc__12CMapKeyFrameFv(*(CMapKeyFrame **)(iVar3 + 0x5c));
        }
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + 0x14;
      } while (iVar5 < 4);
    }
  }
  return;
}

