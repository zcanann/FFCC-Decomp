// Function: GetCharaShadow__12CMaterialManFiPP9CMaterialPPA4_fP3Vecffi
// Entry: 8003e14c
// Size: 584 bytes

int GetCharaShadow__12CMaterialManFiPP9CMaterialPPA4_fP3Vecffi
              (double param_1,double param_2,undefined4 param_3,int param_4,undefined4 *param_5,
              int param_6,Vec *param_7,int param_8)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  double dVar13;
  Vec VStack_698;
  Vec local_68c;
  float local_680;
  float local_67c;
  float local_678;
  float local_674;
  float local_670;
  float local_66c;
  Mtx MStack_668;
  int local_638 [384];
  
  piVar8 = local_638;
  iVar11 = 0;
  iVar7 = 0;
  iVar10 = 0;
  local_680 = (float)((double)param_7->x - param_1);
  local_674 = (float)((double)param_7->x + param_1);
  local_678 = (float)((double)param_7->z - param_1);
  local_66c = (float)((double)param_7->z + param_1);
  local_67c = param_7->y;
  local_670 = (float)((double)local_67c + param_2);
  puVar12 = param_5;
  for (uVar9 = 0; uVar3 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray),
      uVar9 < uVar3; uVar9 = uVar9 + 1) {
    iVar2 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar9);
    if (*(char *)(iVar2 + 0xf0) != '\0') {
      iVar6 = *(int *)(iVar2 + 0xc);
      local_68c.x = *(float *)(iVar6 + 0xc4);
      local_68c.y = *(float *)(iVar6 + 0xd4);
      local_68c.z = *(float *)(iVar6 + 0xe4);
      PSMTXScaleApply(FLOAT_8032faf8,FLOAT_8032faf8,FLOAT_8032faf0,(Mtx *)(iVar2 + 0x78),&MStack_668
                     );
      if (*(char *)(iVar2 + 7) == '\x01') {
        if (iVar11 < param_4) {
          uVar5 = __vc__22CPtrArray<P9CMaterial>FUl
                            (MapMng._136148_4_ + 8,*(undefined2 *)(iVar2 + 4));
          *puVar12 = uVar5;
          puVar12 = puVar12 + 1;
          iVar11 = iVar11 + 1;
          *(int *)(param_6 + iVar7) = iVar2 + 0x78;
          iVar7 = iVar7 + 4;
        }
      }
      else if ((param_8 != 0) ||
              ((((*(char *)(iVar2 + 9) != '\x01' || (local_68c.y <= param_7->y)) &&
                ((*(char *)(iVar2 + 9) != '\x02' || (param_7->y <= local_68c.y)))) &&
               (iVar6 = CheckFrustum__6CBoundFR3VecPA4_ff
                                  ((double)FLOAT_8032fafc,&local_680,&local_68c,&MStack_668),
               iVar6 != 0)))) {
        PSVECSubtract(&local_68c,param_7,&VStack_698);
        dVar13 = (double)PSVECSquareMag(&VStack_698);
        piVar8[1] = (int)(float)dVar13;
        iVar10 = iVar10 + 1;
        *piVar8 = iVar2;
        piVar8[2] = uVar9;
        piVar8 = piVar8 + 3;
      }
    }
  }
  iVar7 = iVar11 * 4;
  piVar4 = local_638;
  piVar8 = (int *)0x0;
  fVar1 = FLOAT_8032fb00;
  if (0 < iVar10) {
    do {
      if ((float)piVar4[1] < fVar1) {
        piVar8 = piVar4;
        fVar1 = (float)piVar4[1];
      }
      piVar4 = piVar4 + 3;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  if ((piVar8 != (int *)0x0) && (piVar8[1] = (int)FLOAT_8032fb04, iVar11 < param_4)) {
    uVar5 = __vc__22CPtrArray<P9CMaterial>FUl(MapMng._136148_4_ + 8,*(undefined2 *)(*piVar8 + 4));
    param_5[iVar11] = uVar5;
    iVar11 = iVar11 + 1;
    *(int *)(param_6 + iVar7) = *piVar8 + 0x78;
  }
  return iVar11;
}

