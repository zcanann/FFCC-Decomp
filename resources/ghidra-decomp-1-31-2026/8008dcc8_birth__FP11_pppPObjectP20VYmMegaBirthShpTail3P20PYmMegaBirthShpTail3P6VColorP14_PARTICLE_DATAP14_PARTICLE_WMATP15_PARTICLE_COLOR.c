// Function: birth__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
// Entry: 8008dcc8
// Size: 3700 bytes

/* WARNING: Removing unreachable block (ram,0x8008eb24) */
/* WARNING: Removing unreachable block (ram,0x8008eb1c) */
/* WARNING: Removing unreachable block (ram,0x8008eb14) */
/* WARNING: Removing unreachable block (ram,0x8008eb0c) */
/* WARNING: Removing unreachable block (ram,0x8008dd8c) */
/* WARNING: Removing unreachable block (ram,0x8008dcf0) */
/* WARNING: Removing unreachable block (ram,0x8008dce8) */
/* WARNING: Removing unreachable block (ram,0x8008dce0) */
/* WARNING: Removing unreachable block (ram,0x8008dcd8) */
/* WARNING: Removing unreachable block (ram,0x8008e974) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void birth__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VYmMegaBirthShpTail3 *vYmMegaBirthShpTail3,
               PYmMegaBirthShpTail3 *pYmMegaBirthShpTail3,VColor *vColor,
               _PARTICLE_DATA *particleData,PARTICLE_WMAT *particleWMat,
               _PARTICLE_COLOR *particleColor)

{
  byte bVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  ushort uVar5;
  short sVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  short *psVar11;
  _PARTICLE_DATA *p_Var12;
  Vec *dest;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  Vec local_198;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  pppIVECTOR4 local_158;
  int local_150;
  Vec local_148;
  pppFMATRIX local_138;
  pppFMATRIX local_108;
  pppFMATRIX pStack_d8;
  undefined8 local_a8;
  undefined4 local_a0;
  uint uStack_9c;
  longlong local_98;
  longlong local_90;
  undefined4 local_88;
  uint uStack_84;
  longlong local_80;
  longlong local_78;
  double local_70;
  undefined8 local_68;
  
  local_a8 = (double)CONCAT44(0x43300000,
                              (uint)*(byte *)((int)(pYmMegaBirthShpTail3->m_matrix).value[1] + 9));
  dVar17 = (double)(float)(local_a8 - DOUBLE_803305c0);
  dVar16 = (double)(float)((double)FLOAT_803305c8 * dVar17);
  memset(particleData,0,0x1f8);
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    memset(particleWMat,0,0x30);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    memset(particleColor,0,0x20);
  }
  if (*(byte *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 2) < 8) {
    local_148.x = (pYmMegaBirthShpTail3->m_matrix).value[2][0];
    local_148.y = (pYmMegaBirthShpTail3->m_matrix).value[2][1];
    local_148.z = (pYmMegaBirthShpTail3->m_matrix).value[2][2];
    dVar13 = (double)RandF__5CMathFv(&Math);
    local_a0 = 0x43300000;
    iVar9 = (int)(dVar16 * dVar13 - dVar17);
    local_a8 = (double)(longlong)iVar9;
    uStack_9c = iVar9 << 0xf ^ 0x80000000;
    local_158._0_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_803305b8) / FLOAT_803305cc);
    local_98 = (longlong)(int)local_158._0_4_;
    dVar13 = (double)RandF__5CMathFv(&Math);
    local_88 = 0x43300000;
    iVar9 = (int)(dVar16 * dVar13 - dVar17);
    local_90 = (longlong)iVar9;
    uStack_84 = iVar9 << 0xf ^ 0x80000000;
    local_158._4_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_803305b8) / FLOAT_803305cc);
    local_80 = (longlong)(int)local_158._4_4_;
    dVar13 = (double)RandF__5CMathFv(&Math);
    iVar9 = (int)(dVar16 * dVar13 - dVar17);
    local_78 = (longlong)iVar9;
    local_70 = (double)(CONCAT44(0x43300000,iVar9 << 0xf) ^ 0x80000000);
    local_150 = (int)((float)(local_70 - DOUBLE_803305b8) / FLOAT_803305cc);
    local_68 = (double)(longlong)local_150;
    cVar2 = *(char *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 2);
    if ((cVar2 == '\x02') || (cVar2 == '\x03')) {
      local_158.x = 0;
      local_158.y = 0;
      local_158.z = 0;
      local_158.w = 0;
    }
    pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&pStack_d8,&local_158);
    PSMTXMultVecSR(&pStack_d8,&local_148,(Vec *)((particleData->m_matrix).value + 1));
    (particleData->m_matrix).value[1][0] =
         (particleData->m_matrix).value[1][0] * *(float *)&pYmMegaBirthShpTail3->field_0x58;
    (particleData->m_matrix).value[1][1] =
         (particleData->m_matrix).value[1][1] * (pYmMegaBirthShpTail3->m_speedScale).x;
    (particleData->m_matrix).value[1][2] =
         (particleData->m_matrix).value[1][2] * (pYmMegaBirthShpTail3->m_speedScale).y;
    local_174 = (particleData->m_matrix).value[1][0];
    local_170 = (particleData->m_matrix).value[1][1];
    local_16c = (particleData->m_matrix).value[1][2];
    pppNormalize__FR3Vec3Vec((particleData->m_matrix).value + 1,&local_174);
  }
  bVar1 = *(byte *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 2);
  if (bVar1 < 6) {
    if (3 < bVar1) {
      if (FLOAT_803305a4 == pYmMegaBirthShpTail3->m_speedRandRange) goto LAB_8008e8a8;
      bVar1 = pYmMegaBirthShpTail3->m_randType;
      dVar16 = (double)(FLOAT_803305d4 * pYmMegaBirthShpTail3->m_speedRandRange);
      if (bVar1 == 3) {
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_803305d0 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange
                                                     * dVar13) * dVar17) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_803305d0 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange
                                                     * dVar13) * dVar17) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_803305d0 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange
                                                     * dVar13) * dVar17) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
      }
      else if (bVar1 < 3) {
        if (bVar1 == 1) {
          RandF__5CMathFv(&Math);
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
        }
        else if (bVar1 == 0) {
LAB_8008e134:
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
        }
        else {
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                      dVar17);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                      dVar17);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                      dVar17);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
        }
      }
      else if (bVar1 == 5) {
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_803305d4 *
                      (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_803305d4 *
                      (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_803305d4 *
                      (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)) -
                     (double)pYmMegaBirthShpTail3->m_speedRandRange);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
      }
      else {
        if (4 < bVar1) goto LAB_8008e134;
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             (float)(dVar15 * (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)));
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             (float)(dVar15 * (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)));
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             (float)(dVar15 * (double)(float)(dVar14 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar13) *
                                                  dVar17)));
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar16);
      }
      (particleData->m_matrix).value[0][0] =
           (particleData->m_matrix).value[0][0] * *(float *)&pYmMegaBirthShpTail3->field_0x58;
      (particleData->m_matrix).value[0][1] =
           (particleData->m_matrix).value[0][1] * (pYmMegaBirthShpTail3->m_speedScale).x;
      (particleData->m_matrix).value[0][2] =
           (particleData->m_matrix).value[0][2] * (pYmMegaBirthShpTail3->m_speedScale).y;
      goto LAB_8008e8a8;
    }
  }
  else if (bVar1 < 10) {
    fVar10 = pppPObject[1].m_localMatrix.value[2][0];
    if (pYmMegaBirthShpTail3->m_pathIndex < 0) goto LAB_8008e8a8;
    psVar11 = (short *)(*(int *)pppEnvStPtr->m_particleColors[1].m_colorRGBA +
                       pYmMegaBirthShpTail3->m_pathIndex * 8);
    if (fVar10 == 0.0) {
      fVar10 = (float)pppEnvStPtr->m_mapMeshPtr[*psVar11]->field14_0x2c;
    }
    bVar1 = pYmMegaBirthShpTail3->m_randType;
    if (bVar1 == 3) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)(float)(DOUBLE_803305d8 -
                              (double)(float)(dVar13 * (double)(float)(dVar17 * dVar16)));
LAB_8008e7e4:
      if ((int)psVar11[1] <= (int)(uint)vYmMegaBirthShpTail3->m_pathIndex) {
        vYmMegaBirthShpTail3->m_pathIndex = 0;
      }
      local_68 = (double)(CONCAT44(0x43300000,(int)psVar11[1]) ^ 0x80000000);
      iVar9 = (int)(dVar16 * (double)(float)(local_68 - DOUBLE_803305b8));
      local_70 = (double)(longlong)iVar9;
      pfVar7 = (float *)((int)fVar10 + (uint)*(ushort *)(*(int *)(psVar11 + 2) + iVar9 * 2) * 0xc);
      fVar10 = *pfVar7;
      fVar3 = pfVar7[1];
      fVar4 = pfVar7[2];
    }
    else {
      if (2 < bVar1) {
        if (bVar1 == 5) {
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar14 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)(float)(DOUBLE_803305d8 -
                                  (double)(float)(dVar15 * (double)(float)(dVar14 * (double)(float)(
                                                  dVar13 * (double)(float)(dVar17 * dVar16)))));
        }
        else {
          if (4 < bVar1) goto LAB_8008e650;
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar14 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)(dVar17 * dVar16
                                                                                    )));
        }
        goto LAB_8008e7e4;
      }
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        goto LAB_8008e7e4;
      }
      if (bVar1 != 0) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar16 = (double)(float)(dVar13 * (double)(float)(dVar17 * dVar16));
        goto LAB_8008e7e4;
      }
LAB_8008e650:
      if ((int)psVar11[1] <= (int)(uint)vYmMegaBirthShpTail3->m_pathIndex) {
        vYmMegaBirthShpTail3->m_pathIndex = 0;
      }
      uVar5 = vYmMegaBirthShpTail3->m_pathIndex;
      iVar9 = *(int *)(psVar11 + 2);
      vYmMegaBirthShpTail3->m_pathIndex = uVar5 + 1;
      pfVar7 = (float *)((int)fVar10 + (uint)*(ushort *)(iVar9 + (uint)uVar5 * 2) * 0xc);
      fVar10 = *pfVar7;
      fVar3 = pfVar7[1];
      fVar4 = pfVar7[2];
    }
    (particleData->m_matrix).value[0][0] = fVar10 * *(float *)&pYmMegaBirthShpTail3->field_0x58;
    (particleData->m_matrix).value[0][1] = fVar3 * (pYmMegaBirthShpTail3->m_speedScale).x;
    (particleData->m_matrix).value[0][2] = fVar4 * (pYmMegaBirthShpTail3->m_speedScale).y;
    cVar2 = *(char *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 2);
    if ((cVar2 == '\b') || (cVar2 == '\t')) {
      local_18c = (particleData->m_matrix).value[0][0];
      local_188 = (particleData->m_matrix).value[0][1];
      local_184 = (particleData->m_matrix).value[0][2];
      pppNormalize__FR3Vec3Vec((particleData->m_matrix).value + 1,&local_18c);
    }
    goto LAB_8008e8a8;
  }
  fVar10 = pYmMegaBirthShpTail3->m_speedRandRange;
  if (FLOAT_803305a4 != fVar10) {
    bVar1 = pYmMegaBirthShpTail3->m_randType;
    if (bVar1 == 3) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      fVar10 = -(float)((double)FLOAT_803305d0 *
                        (double)(float)((double)(float)((double)pYmMegaBirthShpTail3->
                                                                m_speedRandRange * dVar17) * dVar16)
                       - (double)pYmMegaBirthShpTail3->m_speedRandRange);
    }
    else if (bVar1 < 3) {
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        fVar10 = (float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar16);
      }
      else if (bVar1 != 0) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar17 = (double)RandF__5CMathFv(&Math);
        fVar10 = (float)((double)(float)((double)pYmMegaBirthShpTail3->m_speedRandRange * dVar17) *
                        dVar16);
      }
    }
    else if (bVar1 == 5) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      fVar10 = -(float)((double)FLOAT_803305d4 *
                        (double)(float)(dVar13 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar17) *
                                                  dVar16)) -
                       (double)pYmMegaBirthShpTail3->m_speedRandRange);
    }
    else if (bVar1 < 5) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      dVar14 = (double)RandF__5CMathFv(&Math);
      fVar10 = (float)(dVar14 * (double)(float)(dVar13 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail3->m_speedRandRange * dVar17) *
                                                  dVar16)));
    }
    local_180 = (particleData->m_matrix).value[1][0];
    local_17c = (particleData->m_matrix).value[1][1];
    local_178 = (particleData->m_matrix).value[1][2];
    pppScaleVectorXYZ__FR3Vec3Vecf(fVar10,particleData,&local_180);
  }
LAB_8008e8a8:
  if (*(char *)((int)(pYmMegaBirthShpTail3->m_matrix).value[1] + 6) != '\0') {
    local_68 = (double)CONCAT44(0x43300000,(uint)vColor->m_alpha);
    (particleData->m_directionTail).x = (float)(local_68 - DOUBLE_803305c0);
    *(undefined *)((int)&(particleData->m_directionTail).y + 1) =
         *(undefined *)((int)(pYmMegaBirthShpTail3->m_matrix).value[1] + 6);
  }
  cVar2 = *(char *)((int)(pYmMegaBirthShpTail3->m_matrix).value[1] + 7);
  if (cVar2 != '\0') {
    *(char *)((int)&(particleData->m_directionTail).y + 2) = cVar2;
  }
  fVar10 = FLOAT_803305a4;
  (particleData->m_matrix).value[2][2] = pYmMegaBirthShpTail3->m_colorDeltaAdd[1];
  (particleData->m_matrix).value[2][3] = pYmMegaBirthShpTail3->m_sizeStart;
  if (fVar10 != pYmMegaBirthShpTail3->m_colorDeltaAdd[3]) {
    dVar16 = (double)RandF__5CMathFv(&Math);
    (particleData->m_matrix).value[2][2] =
         (particleData->m_matrix).value[2][2] +
         (float)((double)(float)((double)FLOAT_803305c8 *
                                (double)pYmMegaBirthShpTail3->m_colorDeltaAdd[3]) * dVar16 -
                (double)pYmMegaBirthShpTail3->m_colorDeltaAdd[3]);
  }
  sVar6 = *(short *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 1);
  if (sVar6 == 0) {
    *(undefined2 *)((int)(particleData->m_matrix).value[2] + 2) = 0xffff;
  }
  else {
    *(short *)((int)(particleData->m_matrix).value[2] + 2) = sVar6;
  }
  *(undefined *)&(particleData->m_directionTail).y = 0;
  cVar2 = *(char *)((int)&(pYmMegaBirthShpTail3->m_velocityAcceleration).z + 1);
  if (cVar2 == '\x01') {
    local_138.value[0][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][0];
    local_138.value[0][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][1];
    local_138.value[0][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][2];
    local_138.value[0][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][3];
    local_138.value[1][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][0];
    local_138.value[1][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][1];
    local_138.value[1][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][2];
    local_138.value[1][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][3];
    local_138.value[2][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][0];
    local_138.value[2][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][1];
    local_138.value[2][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][2];
    local_138.value[2][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(particleWMat,&local_138);
  }
  else if (cVar2 == '\0') {
    local_108.value[0][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][0];
    local_108.value[0][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][1];
    local_108.value[0][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][2];
    local_108.value[0][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][3];
    local_108.value[1][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][0];
    local_108.value[1][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][1];
    local_108.value[1][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][2];
    local_108.value[1][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][3];
    local_108.value[2][0] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][0];
    local_108.value[2][1] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][1];
    local_108.value[2][2] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][2];
    local_108.value[2][3] = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(particleWMat,&local_108);
  }
  fVar10 = FLOAT_803305a4;
  *(undefined2 *)((int)&(particleData->m_directionTail).z + 2) = 0;
  *(undefined2 *)particleData->m_colorDeltaAdd = 0;
  dest = (Vec *)&particleData->m_randomRotationRangeX;
  iVar9 = 0;
  *(undefined2 *)((int)particleData->m_colorDeltaAdd + 2) = 0;
  *(undefined *)&(particleData->m_directionTail).z = 0;
  local_160 = fVar10;
  local_164 = fVar10;
  local_168 = fVar10;
  *(undefined *)((int)&(particleData->m_directionTail).y + 3) = 0x1f;
  p_Var12 = particleData;
  do {
    local_198.x = fVar10;
    local_198.y = fVar10;
    local_198.z = fVar10;
    pppCopyVector__FR3Vec3Vec(dest,&local_198);
    dest = dest + 1;
    iVar8 = rand();
    iVar9 = iVar9 + 1;
    *(short *)(p_Var12->m_colorDeltaAdd + 1) =
         (short)iVar8 +
         ((short)((ulonglong)((longlong)iVar8 * 0xb60b60b7) >> 0x28) -
         (short)(iVar8 / 0x168 + (iVar8 >> 0x1f) >> 0x1f)) * -0x168;
    p_Var12 = (_PARTICLE_DATA *)((int)(p_Var12->m_matrix).value[0] + 2);
  } while (iVar9 < 0x1f);
  *(undefined *)&(particleData->m_directionTail).z =
       *(undefined *)((int)&(particleData->m_directionTail).y + 3);
  *(char *)&(particleData->m_directionTail).z = *(char *)&(particleData->m_directionTail).z + -1;
  *(undefined2 *)((particleData->m_matrix).value[1] + 3) = 0;
  return;
}

