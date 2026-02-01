// Function: birth__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
// Entry: 8008bb28
// Size: 3700 bytes

/* WARNING: Removing unreachable block (ram,0x8008c984) */
/* WARNING: Removing unreachable block (ram,0x8008c97c) */
/* WARNING: Removing unreachable block (ram,0x8008c974) */
/* WARNING: Removing unreachable block (ram,0x8008c96c) */
/* WARNING: Removing unreachable block (ram,0x8008c964) */
/* WARNING: Removing unreachable block (ram,0x8008c95c) */
/* WARNING: Removing unreachable block (ram,0x8008c954) */
/* WARNING: Removing unreachable block (ram,0x8008bc04) */
/* WARNING: Removing unreachable block (ram,0x8008bb68) */
/* WARNING: Removing unreachable block (ram,0x8008bb60) */
/* WARNING: Removing unreachable block (ram,0x8008bb58) */
/* WARNING: Removing unreachable block (ram,0x8008bb50) */
/* WARNING: Removing unreachable block (ram,0x8008bb48) */
/* WARNING: Removing unreachable block (ram,0x8008bb40) */
/* WARNING: Removing unreachable block (ram,0x8008bb38) */
/* WARNING: Removing unreachable block (ram,0x8008c7fc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void birth__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VYmMegaBirthShpTail2 *vYmMegaBirthShpTail2,
               PYmMegaBirthShpTail2 *pYmMegaBirthShpTail2,VColor *vColor,
               _PARTICLE_DATA *particleData,PARTICLE_WMAT *particleWMat,
               _PARTICLE_COLOR *particleColor)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  short sVar4;
  float *pfVar5;
  float fVar6;
  short *psVar7;
  Vec *dest;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double in_f29;
  double in_f30;
  double in_f31;
  Vec local_1c8;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  pppIVECTOR4 local_188;
  int local_180;
  Vec local_178;
  pppFMATRIX local_168;
  pppFMATRIX local_138;
  pppFMATRIX pStack_108;
  undefined8 local_d8;
  undefined4 local_d0;
  uint uStack_cc;
  longlong local_c8;
  longlong local_c0;
  undefined4 local_b8;
  uint uStack_b4;
  longlong local_b0;
  longlong local_a8;
  double local_a0;
  undefined8 local_98;
  
  local_d8 = (double)CONCAT44(0x43300000,
                              (uint)*(byte *)((int)(pYmMegaBirthShpTail2->m_matrix).value[1] + 9));
  dVar13 = (double)(float)(local_d8 - DOUBLE_80330580);
  dVar12 = (double)(float)((double)FLOAT_80330588 * dVar13);
  memset(particleData,0,0x1b8);
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    memset(particleWMat,0,0x30);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    memset(particleColor,0,0x20);
  }
  if (*(byte *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 2) < 8) {
    local_178.x = (pYmMegaBirthShpTail2->m_matrix).value[2][0];
    local_178.y = (pYmMegaBirthShpTail2->m_matrix).value[2][1];
    local_178.z = (pYmMegaBirthShpTail2->m_matrix).value[2][2];
    dVar9 = (double)RandF__5CMathFv(&Math);
    local_d0 = 0x43300000;
    iVar8 = (int)(dVar12 * dVar9 - dVar13);
    local_d8 = (double)(longlong)iVar8;
    uStack_cc = iVar8 << 0xf ^ 0x80000000;
    local_188._0_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80330578) / FLOAT_8033058c);
    local_c8 = (longlong)(int)local_188._0_4_;
    dVar9 = (double)RandF__5CMathFv(&Math);
    local_b8 = 0x43300000;
    iVar8 = (int)(dVar12 * dVar9 - dVar13);
    local_c0 = (longlong)iVar8;
    uStack_b4 = iVar8 << 0xf ^ 0x80000000;
    local_188._4_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_b4) - DOUBLE_80330578) / FLOAT_8033058c);
    local_b0 = (longlong)(int)local_188._4_4_;
    dVar9 = (double)RandF__5CMathFv(&Math);
    iVar8 = (int)(dVar12 * dVar9 - dVar13);
    local_a8 = (longlong)iVar8;
    local_a0 = (double)(CONCAT44(0x43300000,iVar8 << 0xf) ^ 0x80000000);
    local_180 = (int)((float)(local_a0 - DOUBLE_80330578) / FLOAT_8033058c);
    local_98 = (double)(longlong)local_180;
    cVar2 = *(char *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 2);
    if ((cVar2 == '\x02') || (cVar2 == '\x03')) {
      local_188.x = 0;
      local_188.y = 0;
      local_188.z = 0;
      local_188.w = 0;
    }
    pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&pStack_108,&local_188);
    PSMTXMultVecSR(&pStack_108,&local_178,(Vec *)((particleData->m_matrix).value + 1));
    (particleData->m_matrix).value[1][0] =
         (particleData->m_matrix).value[1][0] * *(float *)&pYmMegaBirthShpTail2->field_0x58;
    (particleData->m_matrix).value[1][1] =
         (particleData->m_matrix).value[1][1] * (pYmMegaBirthShpTail2->m_speedScale).x;
    (particleData->m_matrix).value[1][2] =
         (particleData->m_matrix).value[1][2] * (pYmMegaBirthShpTail2->m_speedScale).y;
    local_1a4 = (particleData->m_matrix).value[1][0];
    local_1a0 = (particleData->m_matrix).value[1][1];
    local_19c = (particleData->m_matrix).value[1][2];
    pppNormalize__FR3Vec3Vec((particleData->m_matrix).value + 1,&local_1a4);
  }
  bVar1 = *(byte *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 2);
  if (bVar1 < 6) {
    if (3 < bVar1) {
      if (FLOAT_80330560 == pYmMegaBirthShpTail2->m_speedRandRange) goto LAB_8008c730;
      bVar1 = pYmMegaBirthShpTail2->m_randType;
      dVar12 = (double)(FLOAT_80330568 * pYmMegaBirthShpTail2->m_speedRandRange);
      if (bVar1 == 3) {
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_80330590 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange
                                                     * dVar9) * dVar13) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_80330590 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange
                                                     * dVar9) * dVar13) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_80330590 *
                      (double)(float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange
                                                     * dVar9) * dVar13) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
      }
      else if (bVar1 < 3) {
        if (bVar1 == 1) {
          RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
        }
        else if (bVar1 == 0) {
LAB_8008bfac:
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
        }
        else {
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar9 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                      dVar13);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar9 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                      dVar13);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar9 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                      dVar13);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
        }
      }
      else if (bVar1 == 5) {
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_80330568 *
                      (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_80330568 *
                      (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_80330568 *
                      (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)) -
                     (double)pYmMegaBirthShpTail2->m_speedRandRange);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
      }
      else {
        if (4 < bVar1) goto LAB_8008bfac;
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        dVar11 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             (float)(dVar11 * (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)));
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        dVar11 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             (float)(dVar11 * (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)));
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar12);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar10 = (double)RandF__5CMathFv(&Math);
        dVar11 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             (float)(dVar11 * (double)(float)(dVar10 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar9) *
                                                  dVar13)));
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar12);
      }
      (particleData->m_matrix).value[0][0] =
           (particleData->m_matrix).value[0][0] * *(float *)&pYmMegaBirthShpTail2->field_0x58;
      (particleData->m_matrix).value[0][1] =
           (particleData->m_matrix).value[0][1] * (pYmMegaBirthShpTail2->m_speedScale).x;
      (particleData->m_matrix).value[0][2] =
           (particleData->m_matrix).value[0][2] * (pYmMegaBirthShpTail2->m_speedScale).y;
      goto LAB_8008c730;
    }
  }
  else if (bVar1 < 10) {
    fVar6 = pppPObject[1].m_localMatrix.value[2][0];
    if (pYmMegaBirthShpTail2->m_tail2PathIndex < 0) goto LAB_8008c730;
    psVar7 = (short *)(*(int *)pppEnvStPtr->m_particleColors[1].m_colorRGBA +
                      pYmMegaBirthShpTail2->m_tail2PathIndex * 8);
    if (fVar6 == 0.0) {
      fVar6 = (float)pppEnvStPtr->m_mapMeshPtr[*psVar7]->field14_0x2c;
    }
    bVar1 = pYmMegaBirthShpTail2->m_randType;
    if (bVar1 == 3) {
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      dVar9 = (double)RandF__5CMathFv(&Math);
      dVar12 = (double)(float)(DOUBLE_80330598 -
                              (double)(float)(dVar9 * (double)(float)(dVar13 * dVar12)));
LAB_8008c664:
      if ((int)psVar7[1] <= (int)(uint)vYmMegaBirthShpTail2->m_pathIndex) {
        vYmMegaBirthShpTail2->m_pathIndex = 0;
      }
      if (fVar6 != 0.0) {
        local_98 = (double)(CONCAT44(0x43300000,(int)psVar7[1]) ^ 0x80000000);
        iVar8 = (int)(dVar12 * (double)(float)(local_98 - DOUBLE_80330578));
        local_a0 = (double)(longlong)iVar8;
        pfVar5 = (float *)((int)fVar6 + (uint)*(ushort *)(*(int *)(psVar7 + 2) + iVar8 * 2) * 0xc);
        in_f31 = (double)*pfVar5;
        in_f30 = (double)pfVar5[1];
        in_f29 = (double)pfVar5[2];
      }
    }
    else {
      if (2 < bVar1) {
        if (bVar1 == 5) {
          dVar12 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar9 = (double)RandF__5CMathFv(&Math);
          dVar10 = (double)RandF__5CMathFv(&Math);
          dVar11 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)(float)(DOUBLE_80330598 -
                                  (double)(float)(dVar11 * (double)(float)(dVar10 * (double)(float)(
                                                  dVar9 * (double)(float)(dVar13 * dVar12)))));
        }
        else {
          if (4 < bVar1) goto LAB_8008c4c8;
          dVar12 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar9 = (double)RandF__5CMathFv(&Math);
          dVar10 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)(float)(dVar10 * (double)(float)(dVar9 * (double)(float)(dVar13 * dVar12)
                                                           ));
        }
        goto LAB_8008c664;
      }
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        goto LAB_8008c664;
      }
      if (bVar1 != 0) {
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar9 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)(float)(dVar9 * (double)(float)(dVar13 * dVar12));
        goto LAB_8008c664;
      }
LAB_8008c4c8:
      if ((int)psVar7[1] <= (int)(uint)vYmMegaBirthShpTail2->m_pathIndex) {
        vYmMegaBirthShpTail2->m_pathIndex = 0;
      }
      if (fVar6 != 0.0) {
        uVar3 = vYmMegaBirthShpTail2->m_pathIndex;
        iVar8 = *(int *)(psVar7 + 2);
        vYmMegaBirthShpTail2->m_pathIndex = uVar3 + 1;
        pfVar5 = (float *)((int)fVar6 + (uint)*(ushort *)(iVar8 + (uint)uVar3 * 2) * 0xc);
        in_f31 = (double)*pfVar5;
        in_f30 = (double)pfVar5[1];
        in_f29 = (double)pfVar5[2];
      }
    }
    (particleData->m_matrix).value[0][0] =
         (float)(in_f31 * (double)*(float *)&pYmMegaBirthShpTail2->field_0x58);
    (particleData->m_matrix).value[0][1] =
         (float)(in_f30 * (double)(pYmMegaBirthShpTail2->m_speedScale).x);
    (particleData->m_matrix).value[0][2] =
         (float)(in_f29 * (double)(pYmMegaBirthShpTail2->m_speedScale).y);
    cVar2 = *(char *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 2);
    if ((cVar2 == '\b') || (cVar2 == '\t')) {
      local_1bc = (particleData->m_matrix).value[0][0];
      local_1b8 = (particleData->m_matrix).value[0][1];
      local_1b4 = (particleData->m_matrix).value[0][2];
      pppNormalize__FR3Vec3Vec((particleData->m_matrix).value + 1,&local_1bc);
    }
    goto LAB_8008c730;
  }
  fVar6 = pYmMegaBirthShpTail2->m_speedRandRange;
  if (FLOAT_80330560 != fVar6) {
    bVar1 = pYmMegaBirthShpTail2->m_randType;
    if (bVar1 == 3) {
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      fVar6 = -(float)((double)FLOAT_80330590 *
                       (double)(float)((double)(float)((double)pYmMegaBirthShpTail2->
                                                               m_speedRandRange * dVar13) * dVar12)
                      - (double)pYmMegaBirthShpTail2->m_speedRandRange);
    }
    else if (bVar1 < 3) {
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        fVar6 = (float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar12);
      }
      else if (bVar1 != 0) {
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        fVar6 = (float)((double)(float)((double)pYmMegaBirthShpTail2->m_speedRandRange * dVar13) *
                       dVar12);
      }
    }
    else if (bVar1 == 5) {
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      dVar9 = (double)RandF__5CMathFv(&Math);
      fVar6 = -(float)((double)FLOAT_80330568 *
                       (double)(float)(dVar9 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar13) *
                                                  dVar12)) -
                      (double)pYmMegaBirthShpTail2->m_speedRandRange);
    }
    else if (bVar1 < 5) {
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      dVar9 = (double)RandF__5CMathFv(&Math);
      dVar10 = (double)RandF__5CMathFv(&Math);
      fVar6 = (float)(dVar10 * (double)(float)(dVar9 * (double)(float)((double)(float)((double)
                                                  pYmMegaBirthShpTail2->m_speedRandRange * dVar13) *
                                                  dVar12)));
    }
    local_1b0 = (particleData->m_matrix).value[1][0];
    local_1ac = (particleData->m_matrix).value[1][1];
    local_1a8 = (particleData->m_matrix).value[1][2];
    pppScaleVectorXYZ__FR3Vec3Vecf(fVar6,particleData,&local_1b0);
  }
LAB_8008c730:
  if (*(char *)((int)(pYmMegaBirthShpTail2->m_matrix).value[1] + 6) != '\0') {
    local_98 = (double)CONCAT44(0x43300000,(uint)vColor->m_alpha);
    (particleData->m_directionTail).x = (float)(local_98 - DOUBLE_80330580);
    *(undefined *)((int)&(particleData->m_directionTail).y + 1) =
         *(undefined *)((int)(pYmMegaBirthShpTail2->m_matrix).value[1] + 6);
  }
  cVar2 = *(char *)((int)(pYmMegaBirthShpTail2->m_matrix).value[1] + 7);
  if (cVar2 != '\0') {
    *(char *)((int)&(particleData->m_directionTail).y + 2) = cVar2;
  }
  fVar6 = FLOAT_80330560;
  (particleData->m_matrix).value[2][2] = pYmMegaBirthShpTail2->m_colorDeltaAdd[1];
  (particleData->m_matrix).value[2][3] = pYmMegaBirthShpTail2->m_sizeStart;
  if (fVar6 != pYmMegaBirthShpTail2->m_colorDeltaAdd[3]) {
    dVar12 = (double)RandF__5CMathFv(&Math);
    (particleData->m_matrix).value[2][2] =
         (particleData->m_matrix).value[2][2] +
         (float)((double)(float)((double)FLOAT_80330588 *
                                (double)pYmMegaBirthShpTail2->m_colorDeltaAdd[3]) * dVar12 -
                (double)pYmMegaBirthShpTail2->m_colorDeltaAdd[3]);
  }
  sVar4 = *(short *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 1);
  if (sVar4 == 0) {
    *(undefined2 *)((int)(particleData->m_matrix).value[2] + 2) = 0xffff;
  }
  else {
    *(short *)((int)(particleData->m_matrix).value[2] + 2) = sVar4;
  }
  *(undefined *)&(particleData->m_directionTail).y = 0;
  if (pYmMegaBirthShpTail2->m_tail2MatrixMode == '\x01') {
    local_168.value[0][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][0];
    local_168.value[0][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][1];
    local_168.value[0][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][2];
    local_168.value[0][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][3];
    local_168.value[1][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][0];
    local_168.value[1][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][1];
    local_168.value[1][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][2];
    local_168.value[1][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][3];
    local_168.value[2][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][0];
    local_168.value[2][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][1];
    local_168.value[2][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][2];
    local_168.value[2][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(particleWMat,&local_168);
  }
  else if (pYmMegaBirthShpTail2->m_tail2MatrixMode == '\0') {
    local_138.value[0][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][0];
    local_138.value[0][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][1];
    local_138.value[0][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][2];
    local_138.value[0][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][3];
    local_138.value[1][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][0];
    local_138.value[1][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][1];
    local_138.value[1][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][2];
    local_138.value[1][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][3];
    local_138.value[2][0] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][0];
    local_138.value[2][1] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][1];
    local_138.value[2][2] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][2];
    local_138.value[2][3] = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(particleWMat,&local_138);
  }
  fVar6 = FLOAT_80330560;
  *(undefined2 *)((int)&(particleData->m_directionTail).z + 2) = 0;
  dest = (Vec *)(particleData->m_colorDeltaAdd + 1);
  iVar8 = 0x1e;
  *(undefined2 *)particleData->m_colorDeltaAdd = 0;
  *(undefined2 *)((int)particleData->m_colorDeltaAdd + 2) = 0;
  *(undefined *)&(particleData->m_directionTail).z = 0;
  local_190 = fVar6;
  local_194 = fVar6;
  local_198 = fVar6;
  *(undefined *)((int)&(particleData->m_directionTail).y + 3) = 0x1f;
  do {
    local_1c8.x = fVar6;
    local_1c8.y = fVar6;
    local_1c8.z = fVar6;
    pppCopyVector__FR3Vec3Vec(dest,&local_1c8);
    iVar8 = iVar8 + -1;
    dest = dest + 1;
  } while (-1 < iVar8);
  *(undefined *)&(particleData->m_directionTail).z =
       *(undefined *)((int)&(particleData->m_directionTail).y + 3);
  *(char *)&(particleData->m_directionTail).z = *(char *)&(particleData->m_directionTail).z + -1;
  return;
}

