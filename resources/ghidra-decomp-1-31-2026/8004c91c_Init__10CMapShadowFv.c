// Function: Init__10CMapShadowFv
// Entry: 8004c91c
// Size: 236 bytes

void Init__10CMapShadowFv(CMapShadow *mapShadow)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar4 = __vc__22CPtrArray<P9CMaterial>FUl
                    (MapMng._136148_4_ + 8,*(undefined2 *)&mapShadow->field_0x4);
  dVar3 = DOUBLE_8032fcf8;
  iVar4 = *(int *)(iVar4 + 0x3c);
  uVar6 = *(undefined4 *)(iVar4 + 100);
  uVar5 = *(undefined4 *)(iVar4 + 0x68);
  mapShadow->field_0x7 = (char)*(undefined4 *)(iVar4 + 0x6c);
  fVar1 = (float)((double)CONCAT44(0x43300000,uVar6) - dVar3);
  fVar2 = (float)((double)CONCAT44(0x43300000,uVar5) - dVar3);
  if (mapShadow->field_0x6 == '\0') {
    C_MTXLightOrtho(-fVar2,fVar2,-fVar1,fVar1,
                    (float)(DOUBLE_8032fce8 * (double)*(float *)&mapShadow->field_0xa8),
                    (float)((double)FLOAT_8032fcf0 * (double)*(float *)&mapShadow->field_0xa8),
                    FLOAT_8032fcf0,FLOAT_8032fcf0,(Mtx *)&mapShadow->field_0x48);
  }
  else {
    C_MTXLightFrustum(-fVar2,fVar2,-fVar1,fVar1,*(float *)&mapShadow->field_0xac,
                      (float)(DOUBLE_8032fce8 * (double)*(float *)&mapShadow->field_0xa8),
                      (float)((double)FLOAT_8032fcf0 * (double)*(float *)&mapShadow->field_0xa8),
                      FLOAT_8032fcf0,(Mtx *)&mapShadow->field_0x48);
  }
  return;
}

