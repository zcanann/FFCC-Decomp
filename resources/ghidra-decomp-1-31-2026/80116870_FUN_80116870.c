// Function: FUN_80116870
// Entry: 80116870
// Size: 2004 bytes

/* WARNING: Removing unreachable block (ram,0x80117028) */
/* WARNING: Removing unreachable block (ram,0x80117020) */
/* WARNING: Removing unreachable block (ram,0x80117018) */
/* WARNING: Removing unreachable block (ram,0x80117010) */
/* WARNING: Removing unreachable block (ram,0x80117008) */
/* WARNING: Removing unreachable block (ram,0x801168a0) */
/* WARNING: Removing unreachable block (ram,0x80116898) */
/* WARNING: Removing unreachable block (ram,0x80116890) */
/* WARNING: Removing unreachable block (ram,0x80116888) */
/* WARNING: Removing unreachable block (ram,0x80116880) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FUN_80116870(undefined8 param_1,double param_2,int param_3,uint param_4,float *param_5,
                 undefined4 *param_6)

{
  ushort uVar1;
  float scale;
  int iVar2;
  int iVar3;
  Vec *source;
  int iVar4;
  uint uVar5;
  CGPartyObj *pCVar6;
  int iVar7;
  undefined uVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  Vec local_238;
  Vec local_22c;
  Vec local_220;
  Vec local_214;
  Vec local_208;
  Vec local_1fc;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  CVector local_1e4;
  Vec local_1d8;
  Vec local_1cc;
  CVector CStack_1c0;
  CVector local_1b4;
  CVector local_1a8;
  Vec local_19c;
  Vec VStack_190;
  Vec local_184;
  Vec local_178;
  Vec local_16c;
  Vec local_160;
  Vec local_154;
  Vec local_148;
  float local_13c;
  float local_138;
  float local_134;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  Mtx MStack_bc;
  undefined4 local_88;
  uint uStack_84;
  
  if (param_5 != (float *)0x0) {
    *param_5 = FLOAT_803319c0;
  }
  if (param_6 != (undefined4 *)0x0) {
    *param_6 = 0xffffffff;
  }
  __ct__7CVectorFv(&local_148);
  __ct__7CVectorFv(&local_154);
  __ct__7CVectorFv(&local_160);
  __ct__7CVectorFfff(*(float *)(param_3 + 0x15c),*(float *)(param_3 + 0x160),
                     *(float *)(param_3 + 0x164),&local_1a8);
  local_148.x = local_1a8.x;
  local_148.y = local_1a8.y;
  local_148.z = local_1a8.z;
  dVar9 = (double)sin(param_1);
  dVar12 = (double)(float)dVar9;
  dVar9 = (double)cos(param_1);
  __ct__7CVectorFfff((float)dVar12,FLOAT_803319d8,(float)dVar9,&local_1b4);
  local_154.x = local_1b4.x;
  local_154.y = local_1b4.y;
  local_154.z = local_1b4.z;
  __ct__7CVectorFv(&local_208);
  PSVECScale((float)param_2,&local_154,&local_208);
  local_160.x = local_208.x;
  local_160.y = local_208.y;
  local_160.z = local_208.z;
  if (*(short *)(param_3 + 0x6e4) == 0) {
    iVar3 = *(int *)(*(int *)(param_3 + 0x58) + 0x24);
  }
  else {
    iVar3 = Game.game.unkCFlatData0[1] +
            ((int)*(short *)(param_3 + 0x6e4) +
            (uint)*(ushort *)(*(int *)(*(int *)(param_3 + 0x58) + 0x24) + 0x100)) * 0x1d0 + 0x10;
  }
  if ((*(int *)(param_3 + 0x6e0) != 0) &&
     (((*(int *)(param_3 + 0x6d8) == 4 && ((*(ushort *)(iVar3 + 0x102) & 8) == 0)) ||
      ((*(int *)(param_3 + 0x6d8) != 4 && ((*(ushort *)(iVar3 + 0x102) & 4) == 0)))))) {
    iVar3 = *(int *)(*(int *)(param_3 + 0xf8) + 0x168);
    PSMTXCopy((Mtx *)(*(int *)(param_3 + 0x6e0) + 0x6c),&MStack_bc);
    local_148.x = MStack_bc.value[0][3] + *(float *)(iVar3 + 0x74);
    local_148.y = MStack_bc.value[1][3] + *(float *)(iVar3 + 0x84);
    local_148.z = MStack_bc.value[2][3] + *(float *)(iVar3 + 0x94);
    MStack_bc.value[0][3] = local_148.x;
    MStack_bc.value[1][3] = local_148.y;
    MStack_bc.value[2][3] = local_148.z;
    source = (Vec *)__ct__7CVectorFfff(FLOAT_803319c0,FLOAT_803319d8,FLOAT_803319d8,&CStack_1c0);
    PSMTXMultVecSR(&MStack_bc,source,&local_154);
    local_154.y = FLOAT_803319d8;
    Normalize__7CVectorFv((CVector *)&local_154);
    __ct__7CVectorFv(&local_214);
    PSVECScale((float)param_2,&local_154,&local_214);
    local_160.x = local_214.x;
    local_160.y = local_214.y;
    local_160.z = local_214.z;
  }
  if ((param_4 & 1) != 0) {
    local_d8 = FLOAT_80331a34 * *(float *)(param_3 + 0x144);
    dVar9 = (double)local_d8;
    local_cc = FLOAT_80331a38;
    local_d0 = FLOAT_80331a38;
    local_d4 = FLOAT_80331a38;
    local_c0 = FLOAT_80331a3c;
    local_c4 = FLOAT_80331a3c;
    local_c8 = FLOAT_80331a3c;
    local_fc = local_148.x;
    local_f8 = local_148.y;
    local_f4 = local_148.z;
    local_e4 = local_160.x;
    local_e0 = local_160.y;
    local_dc = local_160.z;
    iVar3 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_fc,&local_160,
                       (uint)*(ushort *)(*(int *)(*(int *)(param_3 + 0x58) + 0x24) + 0x1b2));
    scale = FLOAT_8032ec84;
    if (iVar3 != 0) {
      dVar12 = (double)FLOAT_8032ec84;
      if (param_5 != (float *)0x0) {
        *param_5 = FLOAT_8032ec84;
      }
      PSVECScale(scale,&local_160,&local_160);
      param_2 = (double)(float)(param_2 * dVar12);
    }
    AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
              (dVar9,(CFlatRuntime2 *)&CFlat,&local_148,&local_160,1,(char)iVar3);
  }
  if ((param_4 & 2) != 0) {
    local_88 = 0x43300000;
    uStack_84 = (uint)*(ushort *)(*(int *)(*(int *)(param_3 + 0x58) + 0x24) + 0xca);
    dVar12 = (double)FLOAT_803319d8;
    dVar9 = (double)(FLOAT_80331a34 *
                    FLOAT_80331a20 *
                    (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_803319e0));
    if (dVar12 != dVar9) {
      dVar12 = (double)tan(dVar9);
      dVar12 = (double)(FLOAT_80331a40 / (float)dVar12);
    }
    local_16c.x = local_148.x;
    local_16c.y = local_148.y;
    local_16c.z = local_148.z;
    __ct__7CVectorFv(&local_220);
    PSVECScale((float)dVar12,&local_154,&local_220);
    local_1cc.x = local_220.x;
    local_1cc.y = local_220.y;
    local_1cc.z = local_220.z;
    PSVECSubtract(&local_16c,&local_1cc,&local_16c);
    dVar13 = (double)(float)(param_2 + dVar12);
    __ct__7CVectorFv(&local_22c);
    PSVECScale((float)dVar12,&local_154,&local_22c);
    local_1d8.x = local_22c.x;
    local_1d8.y = local_22c.y;
    local_1d8.z = local_22c.z;
    PSVECAdd(&local_160,&local_1d8,&local_160);
    dVar14 = (double)(float)(dVar13 - dVar12);
    uVar8 = 0;
    iVar7 = 0;
    iVar3 = param_3;
    do {
      if (((param_4 & 4) == 0) ||
         (iVar4 = *(int *)(param_3 + 0x54c) + iVar7, uVar5 = iVar4 >> 0x1f,
         (uVar5 * 4 | iVar4 * 0x40000000 + uVar5 >> 0x1e) == uVar5)) {
        iVar4 = *(int *)(iVar3 + 0x620);
        pCVar6 = Game.game.m_partyObjArr[iVar4];
        if (((pCVar6 != (CGPartyObj *)0x0) &&
            ((((Game.game.m_gameWork.m_menuStageMode == '\0' ||
               (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
              (uVar5 = (**(code **)((int)*(void **)((int)&(pCVar6->gCharaObj).gPrgObj.object.
                                                          base_object + 0x48) + 0xc))(pCVar6),
              (uVar5 & 0x6d) != 0x6d)) ||
             ((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)))) &&
           (((((*(short *)((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0 &&
               (iVar2 = (pCVar6->gCharaObj).gPrgObj.m_lastStateId, iVar2 != 9)) && (iVar2 != 0x22))
             && (((Game.game.m_gameWork.m_menuStageMode == '\0' ||
                  (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
                 ((uVar5 = (**(code **)((int)*(void **)((int)&(pCVar6->gCharaObj).gPrgObj.object.
                                                              base_object + 0x48) + 0xc))(pCVar6),
                  (uVar5 & 0x6d) != 0x6d ||
                  ((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)))))) &&
            ((double)*(float *)(param_3 + iVar4 * 4 + 0x5d0) < dVar14)))) {
          __ct__7CVectorFfff((pCVar6->gCharaObj).gPrgObj.object.m_worldPosition.x,
                             *(float *)((int)&(pCVar6->gCharaObj).gPrgObj.object.m_worldPosition + 4
                                       ) + (pCVar6->gCharaObj).gPrgObj.object.unk_0x184,
                             *(float *)((int)&(pCVar6->gCharaObj).gPrgObj.object.m_worldPosition + 8
                                       ),&local_1e4);
          local_178.x = local_1e4.x;
          local_178.y = local_1e4.y;
          local_178.z = local_1e4.z;
          __ct__7CVectorFv(&local_238);
          PSVECSubtract(&local_178,&local_16c,&local_238);
          local_184.x = local_238.x;
          local_184.y = local_238.y;
          local_184.z = local_238.z;
          dVar10 = (double)PSVECMag(&local_184);
          if ((double)FLOAT_803319d8 < dVar10) {
            __ct__7CVectorFv(&VStack_190);
            PSVECNormalize(&local_184,&VStack_190);
            dVar11 = (double)PSVECDotProduct(&local_154,&VStack_190);
            if (((double)(float)(dVar12 - (double)*(float *)(param_3 + 0x144)) <= dVar10) &&
               (((double)FLOAT_803319d8 == dVar9 || ((double)FLOAT_803319d8 < dVar11)))) {
              dVar10 = (double)acos();
              if (((double)FLOAT_803319d8 == dVar9) || ((double)(float)dVar10 < dVar9)) {
                uVar8 = 1;
                dVar10 = (double)(FLOAT_80331a34 * *(float *)(param_3 + 0x144));
                uVar1 = *(ushort *)(*(int *)(*(int *)(param_3 + 0x58) + 0x24) + 0x1b2);
                __ct__7CVectorFv(&local_1fc);
                PSVECSubtract(&local_178,&local_148,&local_1fc);
                local_1f0 = local_1fc.x;
                local_1ec = local_1fc.y;
                local_1e8 = local_1fc.z;
                local_10c = FLOAT_80331a38;
                local_110 = FLOAT_80331a38;
                local_114 = FLOAT_80331a38;
                local_100 = FLOAT_80331a3c;
                local_104 = FLOAT_80331a3c;
                local_108 = FLOAT_80331a3c;
                local_13c = local_148.x;
                local_138 = local_148.y;
                local_134 = local_148.z;
                local_124 = local_1fc.x;
                local_120 = local_1fc.y;
                local_11c = local_1fc.z;
                local_118 = (float)dVar10;
                iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                                  (&MapMng,&local_13c,&local_1f0,(uint)uVar1);
                local_19c.x = local_184.x;
                local_19c.y = local_184.y;
                local_19c.z = local_184.z;
                if (iVar4 != 0) {
                  PSVECScale(FLOAT_8032ec84,&local_19c,&local_19c);
                }
                uVar5 = countLeadingZeros(iVar4);
                AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
                          (dVar10,(CFlatRuntime2 *)&CFlat,&local_148,&local_19c,1,(char)(uVar5 >> 5)
                          );
                if (iVar4 == 0) {
                  if (param_6 != (undefined4 *)0x0) {
                    *param_6 = (pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[0xed];
                  }
                  break;
                }
              }
            }
          }
        }
      }
      iVar7 = iVar7 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar7 < 4);
    if ((double)FLOAT_803319d8 != dVar9) {
      dVar9 = (double)tan(dVar9);
      AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii
                ((double)(float)(dVar13 * (double)(float)dVar9),(CFlatRuntime2 *)&CFlat,&local_16c,
                 &local_160,0,uVar8);
    }
  }
  return;
}

