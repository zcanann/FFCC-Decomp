// Function: UpdatePolygonData__FP11PCharaBreakP11VCharaBreakPQ26CChara6CModel
// Entry: 801400f0
// Size: 2220 bytes

/* WARNING: Removing unreachable block (ram,0x80140980) */
/* WARNING: Removing unreachable block (ram,0x80140978) */
/* WARNING: Removing unreachable block (ram,0x80140108) */
/* WARNING: Removing unreachable block (ram,0x80140100) */

void UpdatePolygonData__FP11PCharaBreakP11VCharaBreakPQ26CChara6CModel
               (int param_1,int param_2,CModel *model)

{
  uint uVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  short sVar8;
  S16Vec *pSVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  CMesh *pCVar14;
  S16Vec *s16Vec;
  Vec *vecB;
  Vec *vecA;
  int iVar15;
  char *pcVar16;
  char *pcVar17;
  int *piVar18;
  char *pcVar19;
  int iVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  S16Vec local_1a8;
  S16Vec local_1a0;
  S16Vec local_198;
  S16Vec local_190;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  Quat QStack_170;
  Vec local_160;
  undefined auStack_154 [12];
  Vec local_148;
  Vec local_13c;
  int local_130 [3];
  S16Vec local_124;
  undefined2 local_11e;
  undefined2 local_11c;
  undefined2 local_11a;
  undefined2 local_118;
  undefined2 local_116;
  undefined2 local_114;
  Mtx MStack_110;
  Vec local_e0 [3];
  Mtx MStack_bc;
  double local_88;
  undefined8 local_80;
  uint local_78;
  
  local_78 = 0;
  local_88 = (double)(CONCAT44(0x43300000,1 << model->m_data->m_posQuant) ^ 0x80000000);
  iVar10 = 0;
  pCVar14 = model->m_meshes;
  iVar15 = (int)(*(float *)(param_2 + 4) * (*(float *)(param_2 + 0x34) - *(float *)(param_2 + 0x24))
                * (float)(local_88 - DOUBLE_80332068));
  local_80 = (double)(longlong)iVar15;
  sVar3 = (short)iVar15;
  for (; local_78 < model->m_data->m_meshCount; local_78 = local_78 + 1) {
    bVar2 = false;
    if ((pCVar14->m_data->m_skinCount == 0) && (*(char *)(param_1 + 0x42) == '\x01')) {
      bVar2 = true;
      PSMTXConcat(&model->m_localMtx,&model->m_nodes[pCVar14->m_data->m_nodeIndex].m_mtx,&MStack_bc)
      ;
    }
    iVar13 = pCVar14->m_data->m_displayListCount - 1;
    iVar15 = iVar13 * 4;
    for (; -1 < iVar13; iVar13 = iVar13 + -1) {
      iVar20 = *(int *)(iVar10 + *(int *)(param_2 + 0x1c));
      pcVar16 = *(char **)(*(int *)(iVar20 + iVar15) + 0xc);
      for (iVar12 = 0; iVar12 < (int)(uint)*(ushort *)(*(int *)(iVar20 + iVar15) + 8);
          iVar12 = iVar12 + 1) {
        if (*pcVar16 == '\0') {
          piVar18 = local_130;
          s16Vec = &local_124;
          local_130[0] = DAT_801dd684;
          iVar11 = 0;
          local_130[1] = DAT_801dd688;
          local_130[2] = DAT_801dd68c;
          pcVar17 = pcVar16;
          pcVar19 = pcVar16;
          do {
            if (bVar2) {
              pSVar9 = pCVar14->m_workPositions + *(ushort *)(pcVar19 + 0x22);
              local_190.x = pSVar9->x;
              local_190.y = pSVar9->y;
              local_190.z = pSVar9->z;
              ConvI2FVector__5CUtilFR3Vec6S16Vecl
                        ((CUtil *)&DAT_8032ec70,&local_13c,&local_190,model->m_data->m_posQuant);
              PSMTXMultVec(&MStack_bc,&local_13c,&local_13c);
              local_17c = local_13c.x;
              local_178 = local_13c.y;
              local_174 = local_13c.z;
              ConvF2IVector__5CUtilFR6S16Vec3Vecl
                        ((CUtil *)&DAT_8032ec70,s16Vec,&local_17c,model->m_data->m_posQuant);
            }
            else {
              pSVar9 = pCVar14->m_workPositions + *(ushort *)(pcVar19 + 0x22);
              s16Vec->x = pSVar9->x;
              s16Vec->y = pSVar9->y;
              s16Vec->z = pSVar9->z;
            }
            if (*(char *)(param_1 + 0x41) == '\0') {
              if (*(char *)(param_1 + 0x42) == '\x01') {
                if (s16Vec->y < sVar3) {
                  *piVar18 = 1;
                }
              }
              else if (*(short *)(pcVar17 + 0x12) < sVar3) {
                *piVar18 = 1;
              }
            }
            else if (*(char *)(param_1 + 0x41) == '\x01') {
              if (*(char *)(param_1 + 0x42) == '\x01') {
                if (sVar3 < s16Vec->y) {
                  *piVar18 = 1;
                }
              }
              else if (sVar3 < *(short *)(pcVar17 + 0x12)) {
                *piVar18 = 1;
              }
            }
            iVar11 = iVar11 + 1;
            s16Vec = s16Vec + 1;
            piVar18 = piVar18 + 1;
            pcVar17 = pcVar17 + 6;
            pcVar19 = pcVar19 + 2;
          } while (iVar11 < 3);
          if (local_130[0] == 0) {
            *pcVar16 = '\0';
          }
          else {
            *pcVar16 = '\x01';
            if (local_130[1] == 0) {
              *pcVar16 = '\0';
            }
            else {
              *pcVar16 = '\x01';
              if (local_130[2] == 0) {
                *pcVar16 = '\0';
              }
              else {
                *pcVar16 = '\x01';
              }
            }
          }
          if ((*(char *)(param_1 + 0x42) == '\x01') && (*pcVar16 != '\0')) {
            *(short *)(pcVar16 + 0x10) = local_124.x;
            *(short *)(pcVar16 + 0x12) = local_124.y;
            *(short *)(pcVar16 + 0x14) = local_124.z;
            *(undefined2 *)(pcVar16 + 0x16) = local_11e;
            *(undefined2 *)(pcVar16 + 0x18) = local_11c;
            *(undefined2 *)(pcVar16 + 0x1a) = local_11a;
            *(undefined2 *)(pcVar16 + 0x1c) = local_118;
            *(undefined2 *)(pcVar16 + 0x1e) = local_116;
            *(undefined2 *)(pcVar16 + 0x20) = local_114;
          }
        }
        if (*pcVar16 == '\0') {
          if (*(char *)(param_1 + 0x42) == '\x01') {
            *(short *)(pcVar16 + 0x10) = local_124.x;
            *(short *)(pcVar16 + 0x12) = local_124.y;
            *(short *)(pcVar16 + 0x14) = local_124.z;
            *(undefined2 *)(pcVar16 + 0x16) = local_11e;
            *(undefined2 *)(pcVar16 + 0x18) = local_11c;
            *(undefined2 *)(pcVar16 + 0x1a) = local_11a;
            *(undefined2 *)(pcVar16 + 0x1c) = local_118;
            *(undefined2 *)(pcVar16 + 0x1e) = local_116;
            *(undefined2 *)(pcVar16 + 0x20) = local_114;
          }
        }
        else {
          local_148.z = FLOAT_80332048;
          local_148.y = FLOAT_80332048;
          local_148.x = FLOAT_80332048;
          iVar11 = (int)*(short *)(pcVar16 + 0x10) +
                   (int)*(short *)(pcVar16 + 0x16) + (int)*(short *)(pcVar16 + 0x1c);
          iVar7 = (int)*(short *)(pcVar16 + 0x12) +
                  (int)*(short *)(pcVar16 + 0x18) + (int)*(short *)(pcVar16 + 0x1e);
          iVar5 = (int)*(short *)(pcVar16 + 0x14) +
                  (int)*(short *)(pcVar16 + 0x1a) + (int)*(short *)(pcVar16 + 0x20);
          sVar8 = (short)((ulonglong)((longlong)iVar11 * 0x55555556) >> 0x20) -
                  ((short)((short)(iVar11 / 0x30000) + (short)(iVar11 >> 0x1f)) >> 0xf);
          sVar6 = (short)((ulonglong)((longlong)iVar7 * 0x55555556) >> 0x20) -
                  ((short)((short)(iVar7 / 0x30000) + (short)(iVar7 >> 0x1f)) >> 0xf);
          sVar4 = (short)((ulonglong)((longlong)iVar5 * 0x55555556) >> 0x20) -
                  ((short)((short)(iVar5 / 0x30000) + (short)(iVar5 >> 0x1f)) >> 0xf);
          if ((((-0x7531 < sVar8) && (sVar8 < 0x7531)) && (-0x7531 < sVar6)) &&
             (((sVar6 < 0x7531 && (-0x7531 < sVar4)) && (sVar4 < 0x7531)))) {
            vecA = local_e0;
            iVar11 = 0;
            pcVar17 = pcVar16;
            vecB = vecA;
            do {
              local_198._0_4_ = *(undefined4 *)(pcVar17 + 0x10);
              local_198.z = *(short *)(pcVar17 + 0x14);
              ConvI2FVector__5CUtilFR3Vec6S16Vecl
                        ((CUtil *)&DAT_8032ec70,vecB,&local_198,model->m_data->m_posQuant);
              PSVECAdd(&local_148,vecB,&local_148);
              iVar11 = iVar11 + 1;
              vecB = vecB + 1;
              pcVar17 = pcVar17 + 6;
            } while (iVar11 < 3);
            PSVECScale(FLOAT_80332058,&local_148,&local_148);
            local_1a0._0_4_ = *(undefined4 *)(pcVar16 + 10);
            local_1a0.z = *(short *)(pcVar16 + 0xe);
            ConvI2FVector__5CUtilFR3Vec6S16Vecl
                      ((CUtil *)&DAT_8032ec70,auStack_154,&local_1a0,model->m_data->m_normQuant);
            local_1a8._0_4_ = *(undefined4 *)(pcVar16 + 4);
            local_1a8.z = *(short *)(pcVar16 + 8);
            ConvI2FVector__5CUtilFR3Vec6S16Vecl
                      ((CUtil *)&DAT_8032ec70,&local_160,&local_1a8,model->m_data->m_normQuant);
            dVar21 = (double)RandF__5CMathFf((double)*(float *)(param_1 + 0x3c),&Math);
            PSVECScale((float)((double)*(float *)(param_1 + 0x38) + dVar21),&local_160,&local_160);
            local_80 = (double)CONCAT44(0x43300000,(uint)(byte)pcVar16[1]);
            C_QUATRotAxisRad((double)(FLOAT_8033205c * (float)(local_80 - DOUBLE_80332070)),
                             &QStack_170,auStack_154);
            PSMTXQuat(&MStack_110,&QStack_170);
            dVar23 = (double)FLOAT_80332048;
            dVar21 = dVar23;
            if (*(char *)(param_1 + 0x40) == '\x01') {
              if (*(short *)(pcVar16 + 6) == 0) {
                iVar11 = rand();
                iVar5 = iVar11 / 10 + (iVar11 >> 0x1f);
                *(short *)(pcVar16 + 4) =
                     (short)iVar11 + ((short)iVar5 - (short)(iVar5 >> 0x1f)) * -10 +
                     *(short *)(pcVar16 + 4) + 10;
              }
              else {
                iVar11 = rand();
                iVar5 = iVar11 / 10 + (iVar11 >> 0x1f);
                *(short *)(pcVar16 + 4) =
                     *(short *)(pcVar16 + 4) -
                     ((short)iVar11 + ((short)iVar5 - (short)(iVar5 >> 0x1f)) * -10 + 10);
              }
              if (0x168 < *(short *)(pcVar16 + 4)) {
                *(short *)(pcVar16 + 4) = *(short *)(pcVar16 + 4) + -0x168;
              }
              if (*(short *)(pcVar16 + 4) < 0) {
                *(short *)(pcVar16 + 4) = *(short *)(pcVar16 + 4) + 0x168;
              }
              local_80 = (double)(CONCAT44(0x43300000,(int)*(short *)(pcVar16 + 4) << 0xf) ^
                                 0x80000000);
              uVar1 = (uint)((float)(local_80 - DOUBLE_80332068) / FLOAT_80332060);
              local_88 = (double)(longlong)(int)uVar1;
              dVar23 = (double)*(float *)((int)ppvSinTbl + (uVar1 & 0xfffc));
              dVar21 = (double)*(float *)((int)ppvSinTbl + (uVar1 + 0x4000 & 0xfffc));
            }
            iVar11 = 0;
            pcVar17 = pcVar16;
            do {
              PSVECSubtract(vecA,&local_148,vecA);
              PSMTXMultVec(&MStack_110,vecA,vecA);
              PSVECAdd(vecA,&local_148,vecA);
              if (*(char *)(param_1 + 0x40) == '\0') {
                local_80._0_4_ = 0x43300000;
                vecA->x = vecA->x + local_160.x;
                local_80 = (double)CONCAT44(local_80._0_4_,(uint)*(ushort *)(pcVar16 + 2));
                vecA->y = vecA->y + -(*(float *)(param_1 + 0x10) *
                                      (float)(local_80 - DOUBLE_80332070) - local_160.y);
                vecA->z = vecA->z + local_160.z;
              }
              else if (*(char *)(param_1 + 0x40) == '\x01') {
                dVar22 = (double)RandF__5CMathFf((double)FLOAT_80332064,&Math);
                local_80._0_4_ = 0x43300000;
                vecA->x = (float)(dVar21 * (double)(float)((double)FLOAT_8033204c + dVar22) +
                                 (double)vecA->x);
                local_80 = (double)CONCAT44(local_80._0_4_,(uint)*(ushort *)(pcVar16 + 2));
                vecA->y = vecA->y + -(*(float *)(param_1 + 0x10) *
                                      (float)(local_80 - DOUBLE_80332070) - local_160.y);
                dVar22 = (double)RandF__5CMathFf((double)FLOAT_80332064,&Math);
                vecA->z = (float)(dVar23 * (double)(float)((double)FLOAT_8033204c + dVar22) +
                                 (double)vecA->z);
              }
              vecA->x = *(float *)(param_1 + 0x18) * *(float *)(param_2 + 0x10) + vecA->x;
              vecA->y = *(float *)(param_1 + 0x1c) * *(float *)(param_2 + 0x10) + vecA->y;
              vecA->z = *(float *)(param_1 + 0x20) * *(float *)(param_2 + 0x10) + vecA->z;
              local_188 = vecA->x;
              local_184 = vecA->y;
              local_180 = vecA->z;
              ConvF2IVector__5CUtilFR6S16Vec3Vecl
                        ((CUtil *)&DAT_8032ec70,(S16Vec *)(pcVar17 + 0x10),&local_188,
                         model->m_data->m_posQuant);
              iVar11 = iVar11 + 1;
              pcVar17 = pcVar17 + 6;
              vecA = vecA + 1;
            } while (iVar11 < 3);
            *(short *)(pcVar16 + 2) = *(short *)(pcVar16 + 2) + 1;
          }
        }
        pcVar16 = pcVar16 + 0x34;
      }
      iVar15 = iVar15 + -4;
    }
    iVar10 = iVar10 + 4;
    pCVar14 = pCVar14 + 1;
  }
  return;
}

