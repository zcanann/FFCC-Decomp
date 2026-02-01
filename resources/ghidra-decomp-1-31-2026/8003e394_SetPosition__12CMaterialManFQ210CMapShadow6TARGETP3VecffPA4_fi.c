// Function: SetPosition__12CMaterialManFQ210CMapShadow6TARGETP3VecffPA4_fi
// Entry: 8003e394
// Size: 716 bytes

void SetPosition__12CMaterialManFQ210CMapShadow6TARGETP3VecffPA4_fi
               (double param_1,double param_2,undefined4 param_3,int param_4,Vec *param_5,
               undefined4 param_6,int param_7)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  double dVar9;
  undefined4 local_6c8;
  undefined4 local_6c4;
  undefined4 local_6c0;
  Vec VStack_6bc;
  Vec local_6b0;
  float local_6a4;
  float local_6a0;
  float local_69c;
  float local_698;
  float local_694;
  float local_690;
  Mtx MStack_68c;
  Mtx MStack_65c;
  int local_62c [385];
  
  local_6a4 = (float)((double)param_5->x - param_1);
  local_698 = (float)((double)param_5->x + param_1);
  local_69c = (float)((double)param_5->z - param_1);
  local_690 = (float)((double)param_5->z + param_1);
  local_6a0 = param_5->y;
  local_694 = (float)((double)local_6a0 + param_2);
  if (param_4 == 0) {
    piVar6 = local_62c;
    iVar8 = 0;
    for (uVar7 = 0; uVar3 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray),
        uVar7 < uVar3; uVar7 = uVar7 + 1) {
      iVar2 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar7);
      if (*(char *)(iVar2 + 0xf0) != '\0') {
        iVar5 = *(int *)(iVar2 + 0xc);
        local_6b0.x = *(float *)(iVar5 + 0xc4);
        local_6b0.y = *(float *)(iVar5 + 0xd4);
        local_6b0.z = *(float *)(iVar5 + 0xe4);
        PSMTXScaleApply(FLOAT_8032faf8,FLOAT_8032faf8,FLOAT_8032faf0,(Mtx *)(iVar2 + 0x78),
                        &MStack_65c);
        if (*(char *)(iVar2 + 7) == '\x01') {
          SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(param_3,iVar2,param_6,uVar7,0);
        }
        else if ((param_7 != 0) ||
                ((((*(char *)(iVar2 + 9) != '\x01' || (local_6b0.y <= param_5->y)) &&
                  ((*(char *)(iVar2 + 9) != '\x02' || (param_5->y <= local_6b0.y)))) &&
                 (iVar5 = CheckFrustum__6CBoundFR3VecPA4_ff
                                    ((double)FLOAT_8032fafc,&local_6a4,&local_6b0,&MStack_65c),
                 iVar5 != 0)))) {
          PSVECSubtract(&local_6b0,param_5,&VStack_6bc);
          dVar9 = (double)PSVECSquareMag(&VStack_6bc);
          piVar6[1] = (int)(float)dVar9;
          iVar8 = iVar8 + 1;
          *piVar6 = iVar2;
          piVar6[2] = uVar7;
          piVar6 = piVar6 + 3;
        }
      }
    }
    piVar4 = local_62c;
    piVar6 = (int *)0x0;
    fVar1 = FLOAT_8032fb00;
    if (0 < iVar8) {
      do {
        if ((float)piVar4[1] < fVar1) {
          piVar6 = piVar4;
          fVar1 = (float)piVar4[1];
        }
        piVar4 = piVar4 + 3;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    if (piVar6 != (int *)0x0) {
      piVar6[1] = (int)FLOAT_8032fb04;
      SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(param_3,*piVar6,param_6,piVar6[2],0xffffffff);
    }
  }
  else {
    for (uVar7 = 0; uVar3 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray),
        uVar7 < uVar3; uVar7 = uVar7 + 1) {
      iVar8 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar7);
      if (*(char *)(param_4 + iVar8 + 0xf0) != '\0') {
        iVar2 = *(int *)(iVar8 + 0xc);
        local_6c8 = *(undefined4 *)(iVar2 + 0xc4);
        local_6c4 = *(undefined4 *)(iVar2 + 0xd4);
        local_6c0 = *(undefined4 *)(iVar2 + 0xe4);
        PSMTXScaleApply(FLOAT_8032faf8,FLOAT_8032faf8,FLOAT_8032faf0,(Mtx *)(iVar8 + 0x78),
                        &MStack_68c);
        if ((*(char *)(iVar8 + 7) == '\x01') ||
           (iVar2 = CheckFrustum__6CBoundFR3VecPA4_ff
                              ((double)FLOAT_8032fafc,&local_6a4,&local_6c8,&MStack_68c), iVar2 != 0
           )) {
          SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(param_3,iVar8,param_6,uVar7,0);
        }
      }
    }
  }
  return;
}

