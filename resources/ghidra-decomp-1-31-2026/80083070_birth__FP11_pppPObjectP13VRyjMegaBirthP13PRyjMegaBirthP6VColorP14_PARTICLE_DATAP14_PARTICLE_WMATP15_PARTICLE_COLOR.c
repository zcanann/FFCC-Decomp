// Function: birth__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
// Entry: 80083070
// Size: 4464 bytes

/* WARNING: Removing unreachable block (ram,0x800841c8) */
/* WARNING: Removing unreachable block (ram,0x800841c0) */
/* WARNING: Removing unreachable block (ram,0x800841b8) */
/* WARNING: Removing unreachable block (ram,0x800841b0) */
/* WARNING: Removing unreachable block (ram,0x800841a8) */
/* WARNING: Removing unreachable block (ram,0x800841a0) */
/* WARNING: Removing unreachable block (ram,0x80084198) */
/* WARNING: Removing unreachable block (ram,0x8008314c) */
/* WARNING: Removing unreachable block (ram,0x800830b0) */
/* WARNING: Removing unreachable block (ram,0x800830a8) */
/* WARNING: Removing unreachable block (ram,0x800830a0) */
/* WARNING: Removing unreachable block (ram,0x80083098) */
/* WARNING: Removing unreachable block (ram,0x80083090) */
/* WARNING: Removing unreachable block (ram,0x80083088) */
/* WARNING: Removing unreachable block (ram,0x80083080) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void birth__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VRyjMegaBirth *vRyjMegaBirth,PRyjMegaBirth *pRyjMegaBirth,
               VColor *vColor,_PARTICLE_DATA *particleData,PARTICLE_WMAT *particleWMat,
               _PARTICLE_COLOR *particleColor)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  short sVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  Vec *inVec;
  float *pfVar8;
  int iVar9;
  float fVar10;
  short *psVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double in_f29;
  double in_f30;
  double in_f31;
  pppIVECTOR4 local_148;
  int local_140;
  Vec local_138;
  pppFMATRIX pStack_128;
  undefined8 local_f8;
  undefined4 local_f0;
  uint uStack_ec;
  undefined8 local_e8;
  longlong local_e0;
  undefined4 local_d8;
  uint uStack_d4;
  undefined8 local_d0;
  longlong local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  uint uStack_ac;
  undefined4 local_a8;
  uint uStack_a4;
  undefined8 local_a0;
  
  local_f8 = (double)CONCAT44(0x43300000,
                              (uint)*(byte *)((int)(pRyjMegaBirth->m_matrix).value[2] + 0xb));
  dVar16 = (double)(float)(local_f8 - DOUBLE_80330468);
  dVar15 = (double)(float)((double)FLOAT_80330470 * dVar16);
  memset(particleData,0,0x60);
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    memset(particleWMat,0,0x30);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    memset(particleColor,0,0x20);
  }
  if (*(byte *)((int)(pRyjMegaBirth->m_matrix).value[2] + 10) < 8) {
    local_138.x = (pRyjMegaBirth->field31_0xa0).x;
    local_138.y = (pRyjMegaBirth->field31_0xa0).y;
    local_138.z = (pRyjMegaBirth->field31_0xa0).z;
    dVar12 = (double)RandF__5CMathFv(&Math);
    local_f0 = 0x43300000;
    iVar9 = (int)(dVar15 * dVar12 - dVar16);
    local_f8 = (double)(longlong)iVar9;
    uStack_ec = iVar9 << 0xf ^ 0x80000000;
    local_148._0_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_ec) - DOUBLE_80330450) / FLOAT_8033045c);
    local_e8 = (double)(longlong)(int)local_148._0_4_;
    dVar12 = (double)RandF__5CMathFv(&Math);
    local_d8 = 0x43300000;
    iVar9 = (int)(dVar15 * dVar12 - dVar16);
    local_e0 = (longlong)iVar9;
    uStack_d4 = iVar9 << 0xf ^ 0x80000000;
    local_148._4_4_ =
         (undefined4)
         ((float)((double)CONCAT44(0x43300000,uStack_d4) - DOUBLE_80330450) / FLOAT_8033045c);
    local_d0 = (double)(longlong)(int)local_148._4_4_;
    dVar12 = (double)RandF__5CMathFv(&Math);
    iVar9 = (int)(dVar15 * dVar12 - dVar16);
    local_c8 = (longlong)iVar9;
    local_c0 = (double)(CONCAT44(0x43300000,iVar9 << 0xf) ^ 0x80000000);
    local_140 = (int)((float)(local_c0 - DOUBLE_80330450) / FLOAT_8033045c);
    local_b8 = (double)(longlong)local_140;
    cVar2 = *(char *)((int)(pRyjMegaBirth->m_matrix).value[2] + 10);
    if ((cVar2 == '\x02') || (cVar2 == '\x03')) {
      local_148.x = 0;
      local_148.y = 0;
      local_148.z = 0;
      local_148.w = 0;
    }
    pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&pStack_128,&local_148);
    PSMTXMultVecSR(&pStack_128,&local_138,(Vec *)((particleData->m_matrix).value + 1));
    inVec = (Vec *)((particleData->m_matrix).value + 1);
    (particleData->m_matrix).value[1][0] =
         (particleData->m_matrix).value[1][0] * (pRyjMegaBirth->m_directionScale).x;
    (particleData->m_matrix).value[1][1] =
         (particleData->m_matrix).value[1][1] * (pRyjMegaBirth->m_directionScale).y;
    (particleData->m_matrix).value[1][2] =
         (particleData->m_matrix).value[1][2] * (pRyjMegaBirth->m_directionScale).z;
    PSVECNormalize(inVec,inVec);
  }
  bVar1 = *(byte *)((int)(pRyjMegaBirth->m_matrix).value[2] + 10);
  if (bVar1 < 6) {
    if (3 < bVar1) {
      if (FLOAT_80330448 == pRyjMegaBirth->m_directionSpeed) goto LAB_80083c30;
      bVar1 = *(byte *)&(pRyjMegaBirth->m_baseDirection).x;
      dVar15 = (double)(FLOAT_80330478 * pRyjMegaBirth->m_directionSpeed);
      if (bVar1 == 3) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_80330474 *
                      (double)(float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed *
                                                     dVar12) * dVar16) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_80330474 *
                      (double)(float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed *
                                                     dVar12) * dVar16) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_80330474 *
                      (double)(float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed *
                                                     dVar12) * dVar16) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
      }
      else if (bVar1 < 3) {
        if (bVar1 == 1) {
          RandF__5CMathFv(&Math);
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
        }
        else if (bVar1 == 0) {
LAB_800834c4:
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)pRyjMegaBirth->m_directionSpeed * dVar16);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
        }
        else {
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16);
          (particleData->m_matrix).value[0][0] =
               (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16);
          (particleData->m_matrix).value[0][1] =
               (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)RandF__5CMathFv(&Math);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16);
          (particleData->m_matrix).value[0][2] =
               (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
        }
      }
      else if (bVar1 == 5) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             -(float)((double)FLOAT_80330478 *
                      (double)(float)(dVar13 * (double)(float)((double)(float)((double)pRyjMegaBirth
                                                                                       ->
                                                  m_directionSpeed * dVar12) * dVar16)) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             -(float)((double)FLOAT_80330478 *
                      (double)(float)(dVar13 * (double)(float)((double)(float)((double)pRyjMegaBirth
                                                                                       ->
                                                  m_directionSpeed * dVar12) * dVar16)) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             -(float)((double)FLOAT_80330478 *
                      (double)(float)(dVar13 * (double)(float)((double)(float)((double)pRyjMegaBirth
                                                                                       ->
                                                  m_directionSpeed * dVar12) * dVar16)) -
                     (double)pRyjMegaBirth->m_directionSpeed);
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
      }
      else {
        if (4 < bVar1) goto LAB_800834c4;
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][0] =
             (float)(dVar14 * (double)(float)(dVar13 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16
                                                  )));
        (particleData->m_matrix).value[0][0] =
             (float)((double)(particleData->m_matrix).value[0][0] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][1] =
             (float)(dVar14 * (double)(float)(dVar13 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16
                                                  )));
        (particleData->m_matrix).value[0][1] =
             (float)((double)(particleData->m_matrix).value[0][1] - dVar15);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        (particleData->m_matrix).value[0][2] =
             (float)(dVar14 * (double)(float)(dVar13 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirth->m_directionSpeed * dVar12) * dVar16
                                                  )));
        (particleData->m_matrix).value[0][2] =
             (float)((double)(particleData->m_matrix).value[0][2] - dVar15);
      }
      (particleData->m_matrix).value[0][0] =
           (particleData->m_matrix).value[0][0] * (pRyjMegaBirth->m_directionScale).x;
      (particleData->m_matrix).value[0][1] =
           (particleData->m_matrix).value[0][1] * (pRyjMegaBirth->m_directionScale).y;
      (particleData->m_matrix).value[0][2] =
           (particleData->m_matrix).value[0][2] * (pRyjMegaBirth->m_directionScale).z;
      goto LAB_80083c30;
    }
  }
  else if (bVar1 < 10) {
    sVar4 = *(short *)&(pRyjMegaBirth->m_baseDirection).z;
    fVar10 = pppPObject[1].m_localMatrix.value[2][0];
    if (sVar4 < 0) goto LAB_80083c30;
    psVar11 = (short *)(*(int *)pppEnvStPtr->m_particleColors[1].m_colorRGBA + sVar4 * 8);
    if (fVar10 == 0.0) {
      fVar10 = (float)pppEnvStPtr->m_mapMeshPtr[*psVar11]->field14_0x2c;
    }
    bVar1 = *(byte *)&(pRyjMegaBirth->m_baseDirection).x;
    if (bVar1 == 3) {
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar15 = (double)(float)(DOUBLE_80330480 -
                              (double)(float)(dVar12 * (double)(float)(dVar16 * dVar15)));
LAB_80083b7c:
      if ((int)psVar11[1] <= (int)(uint)vRyjMegaBirth->m_meshEmitIndex) {
        vRyjMegaBirth->m_meshEmitIndex = 0;
      }
      if (fVar10 != 0.0) {
        local_b8 = (double)(CONCAT44(0x43300000,(int)psVar11[1]) ^ 0x80000000);
        iVar9 = (int)(dVar15 * (double)(float)(local_b8 - DOUBLE_80330450));
        local_c0 = (double)(longlong)iVar9;
        pfVar8 = (float *)((int)fVar10 + (uint)*(ushort *)(*(int *)(psVar11 + 2) + iVar9 * 2) * 0xc)
        ;
        in_f31 = (double)*pfVar8;
        in_f30 = (double)pfVar8[1];
        in_f29 = (double)pfVar8[2];
      }
    }
    else {
      if (2 < bVar1) {
        if (bVar1 == 5) {
          dVar15 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar14 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)(float)(DOUBLE_80330480 -
                                  (double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)(
                                                  dVar12 * (double)(float)(dVar16 * dVar15)))));
        }
        else {
          if (4 < bVar1) goto LAB_800839e0;
          dVar15 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar12 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)(float)(dVar13 * (double)(float)(dVar12 * (double)(float)(dVar16 * dVar15
                                                                                    )));
        }
        goto LAB_80083b7c;
      }
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        goto LAB_80083b7c;
      }
      if (bVar1 != 0) {
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar12 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)(float)(dVar12 * (double)(float)(dVar16 * dVar15));
        goto LAB_80083b7c;
      }
LAB_800839e0:
      if ((int)psVar11[1] <= (int)(uint)vRyjMegaBirth->m_meshEmitIndex) {
        vRyjMegaBirth->m_meshEmitIndex = 0;
      }
      if (fVar10 != 0.0) {
        uVar3 = vRyjMegaBirth->m_meshEmitIndex;
        iVar9 = *(int *)(psVar11 + 2);
        vRyjMegaBirth->m_meshEmitIndex = uVar3 + 1;
        pfVar8 = (float *)((int)fVar10 + (uint)*(ushort *)(iVar9 + (uint)uVar3 * 2) * 0xc);
        in_f31 = (double)*pfVar8;
        in_f30 = (double)pfVar8[1];
        in_f29 = (double)pfVar8[2];
      }
    }
    (particleData->m_matrix).value[0][0] =
         (float)(in_f31 * (double)(pRyjMegaBirth->m_directionScale).x);
    (particleData->m_matrix).value[0][1] =
         (float)(in_f30 * (double)(pRyjMegaBirth->m_directionScale).y);
    (particleData->m_matrix).value[0][2] =
         (float)(in_f29 * (double)(pRyjMegaBirth->m_directionScale).z);
    cVar2 = *(char *)((int)(pRyjMegaBirth->m_matrix).value[2] + 10);
    if ((cVar2 == '\b') || (cVar2 == '\t')) {
      PSVECNormalize((Vec *)particleData,(Vec *)((particleData->m_matrix).value + 1));
    }
    goto LAB_80083c30;
  }
  fVar10 = pRyjMegaBirth->m_directionSpeed;
  if (FLOAT_80330448 != fVar10) {
    bVar1 = *(byte *)&(pRyjMegaBirth->m_baseDirection).x;
    if (bVar1 == 3) {
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)RandF__5CMathFv(&Math);
      fVar10 = -(float)((double)FLOAT_80330474 *
                        (double)(float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed *
                                                       dVar16) * dVar15) -
                       (double)pRyjMegaBirth->m_directionSpeed);
    }
    else if (bVar1 < 3) {
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        fVar10 = (float)((double)pRyjMegaBirth->m_directionSpeed * dVar15);
      }
      else if (bVar1 != 0) {
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        fVar10 = (float)((double)(float)((double)pRyjMegaBirth->m_directionSpeed * dVar16) * dVar15)
        ;
      }
    }
    else if (bVar1 == 5) {
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar12 = (double)RandF__5CMathFv(&Math);
      fVar10 = -(float)((double)FLOAT_80330478 *
                        (double)(float)(dVar12 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirth->m_directionSpeed * dVar16) * dVar15
                                                  )) - (double)pRyjMegaBirth->m_directionSpeed);
    }
    else if (bVar1 < 5) {
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar12 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      fVar10 = (float)(dVar13 * (double)(float)(dVar12 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirth->m_directionSpeed * dVar16) * dVar15
                                                  )));
    }
    PSVECScale(fVar10,(Vec *)((particleData->m_matrix).value + 1),(Vec *)particleData);
  }
LAB_80083c30:
  bVar1 = *(byte *)&pRyjMegaBirth->m_sizeStart;
  dVar15 = (double)RandF__5CMathFv(&Math);
  local_b8 = (double)CONCAT44(0x43300000,(uint)bVar1 << 1 ^ 0x80000000);
  local_c0 = (double)CONCAT44(0x43300000,bVar1 >> 1 ^ 0x80000000);
  iVar9 = (int)((double)(float)(local_b8 - DOUBLE_80330450) * dVar15 -
               (double)(float)(local_c0 - DOUBLE_80330450));
  local_c8 = (longlong)iVar9;
  *(char *)((particleData->m_matrix).value[2] + 1) = (char)iVar9;
  bVar1 = *(byte *)((int)&pRyjMegaBirth->m_sizeStart + 1);
  dVar15 = (double)RandF__5CMathFv(&Math);
  uStack_d4 = bVar1 >> 1 ^ 0x80000000;
  local_d0 = (double)CONCAT44(0x43300000,(uint)bVar1 << 1 ^ 0x80000000);
  local_d8 = 0x43300000;
  iVar9 = (int)((double)(float)(local_d0 - DOUBLE_80330450) * dVar15 -
               (double)(float)((double)CONCAT44(0x43300000,uStack_d4) - DOUBLE_80330450));
  local_e0 = (longlong)iVar9;
  *(char *)((int)(particleData->m_matrix).value[2] + 5) = (char)iVar9;
  bVar1 = *(byte *)((int)&pRyjMegaBirth->m_sizeStart + 2);
  dVar15 = (double)RandF__5CMathFv(&Math);
  uStack_ec = bVar1 >> 1 ^ 0x80000000;
  local_e8 = (double)CONCAT44(0x43300000,(uint)bVar1 << 1 ^ 0x80000000);
  local_f0 = 0x43300000;
  iVar9 = (int)((double)(float)(local_e8 - DOUBLE_80330450) * dVar15 -
               (double)(float)((double)CONCAT44(0x43300000,uStack_ec) - DOUBLE_80330450));
  local_f8 = (double)(longlong)iVar9;
  *(char *)((int)(particleData->m_matrix).value[2] + 6) = (char)iVar9;
  bVar1 = *(byte *)((int)&pRyjMegaBirth->m_sizeStart + 3);
  dVar15 = (double)RandF__5CMathFv(&Math);
  uStack_ac = (uint)bVar1 << 1 ^ 0x80000000;
  uStack_a4 = bVar1 >> 1 ^ 0x80000000;
  local_b0 = 0x43300000;
  local_a8 = 0x43300000;
  iVar9 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_ac) - DOUBLE_80330450) * dVar15 -
               (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_80330450));
  local_a0 = (double)(longlong)iVar9;
  *(char *)((int)(particleData->m_matrix).value[2] + 7) = (char)iVar9;
  if (*(char *)((pRyjMegaBirth->m_matrix).value[2] + 2) != '\0') {
    local_a0 = (double)CONCAT44(0x43300000,(uint)vColor->m_alpha);
    particleData->m_speedRandRange = (float)(local_a0 - DOUBLE_80330468);
    particleData->field_0x59 = *(undefined *)((pRyjMegaBirth->m_matrix).value[2] + 2);
  }
  cVar2 = *(char *)((int)(pRyjMegaBirth->m_matrix).value[2] + 9);
  if (cVar2 != '\0') {
    particleData->field_0x5a = cVar2;
  }
  (particleData->m_matrix).value[2][2] = (pRyjMegaBirth->field26_0x90).x;
  (particleData->m_matrix).value[2][3] = (pRyjMegaBirth->field26_0x90).y;
  if (*(char *)((int)&(pRyjMegaBirth->m_baseDirection).x + 3) != '\0') {
    dVar15 = (double)RandF__5CMathFv(&Math);
    (particleData->m_directionTail).x =
         (float)((double)*(float *)&pRyjMegaBirth->field_0x9c * dVar15);
    bVar1 = *(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 3);
    if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
      if ((bVar1 & 2) != 0) {
        (particleData->m_directionTail).x = (particleData->m_directionTail).x * FLOAT_80330490;
      }
    }
    else {
      dVar15 = (double)RandF__5CMathFv(&Math);
      if (DOUBLE_80330488 < dVar15) {
        (particleData->m_directionTail).x = (particleData->m_directionTail).x * FLOAT_80330490;
      }
    }
  }
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 3) & 4) != 0) {
    (particleData->m_matrix).value[2][2] =
         (particleData->m_matrix).value[2][2] + (particleData->m_directionTail).x;
  }
  fVar10 = FLOAT_8033045c;
  fVar5 = FLOAT_80330458;
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 3) & 8) != 0) {
    (particleData->m_matrix).value[2][3] =
         (particleData->m_matrix).value[2][3] + (particleData->m_directionTail).x;
    fVar10 = FLOAT_8033045c;
    fVar5 = FLOAT_80330458;
  }
  while (fVar7 = FLOAT_80330460, fVar6 = FLOAT_80330458,
        fVar10 <= (particleData->m_matrix).value[2][2]) {
    (particleData->m_matrix).value[2][2] = (particleData->m_matrix).value[2][2] - fVar5;
  }
  while ((particleData->m_matrix).value[2][2] < fVar7) {
    (particleData->m_matrix).value[2][2] = (particleData->m_matrix).value[2][2] + fVar6;
  }
  (particleData->m_directionTail).y = pRyjMegaBirth->m_sizeVal;
  (particleData->m_directionTail).z = pRyjMegaBirth->m_speedRandRange;
  particleData->m_colorDeltaAdd[0] = (pRyjMegaBirth->m_speedScale).y;
  particleData->m_colorDeltaAdd[1] = (pRyjMegaBirth->m_speedScale).z;
  bVar1 = *(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2);
  if (bVar1 != 0) {
    if ((bVar1 & 0x20) == 0) {
      dVar15 = (double)RandF__5CMathFv(&Math);
      particleData->m_colorDeltaAdd[2] =
           (float)((double)(float)pRyjMegaBirth->m_randomRotationRangeX * dVar15);
      dVar15 = (double)RandF__5CMathFv(&Math);
      particleData->m_colorDeltaAdd[3] =
           (float)((double)(float)pRyjMegaBirth->m_randomRotationRangeY * dVar15);
      fVar10 = FLOAT_80330490;
      bVar1 = *(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2);
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          particleData->m_colorDeltaAdd[2] = particleData->m_colorDeltaAdd[2] * FLOAT_80330490;
          particleData->m_colorDeltaAdd[3] = particleData->m_colorDeltaAdd[3] * fVar10;
        }
      }
      else {
        dVar15 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330488 < dVar15) {
          particleData->m_colorDeltaAdd[2] = particleData->m_colorDeltaAdd[2] * FLOAT_80330490;
        }
        dVar15 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330488 < dVar15) {
          particleData->m_colorDeltaAdd[3] = particleData->m_colorDeltaAdd[3] * FLOAT_80330490;
        }
      }
    }
    else {
      dVar15 = (double)RandF__5CMathFv(&Math);
      fVar10 = (float)((double)(float)pRyjMegaBirth->m_randomRotationRangeX * dVar15);
      particleData->m_colorDeltaAdd[3] = fVar10;
      particleData->m_colorDeltaAdd[2] = fVar10;
      fVar10 = FLOAT_80330490;
      bVar1 = *(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2);
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          particleData->m_colorDeltaAdd[2] = particleData->m_colorDeltaAdd[2] * FLOAT_80330490;
          particleData->m_colorDeltaAdd[3] = particleData->m_colorDeltaAdd[3] * fVar10;
        }
      }
      else {
        dVar15 = (double)RandF__5CMathFv(&Math);
        fVar10 = FLOAT_80330490;
        if (DOUBLE_80330488 < dVar15) {
          particleData->m_colorDeltaAdd[2] = particleData->m_colorDeltaAdd[2] * FLOAT_80330490;
          particleData->m_colorDeltaAdd[3] = particleData->m_colorDeltaAdd[3] * fVar10;
        }
      }
    }
  }
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2) & 4) != 0) {
    (particleData->m_directionTail).y =
         (particleData->m_directionTail).y + particleData->m_colorDeltaAdd[2];
    (particleData->m_directionTail).z =
         (particleData->m_directionTail).z + particleData->m_colorDeltaAdd[3];
  }
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2) & 8) != 0) {
    particleData->m_colorDeltaAdd[0] =
         particleData->m_colorDeltaAdd[0] + particleData->m_colorDeltaAdd[2];
    particleData->m_colorDeltaAdd[1] =
         particleData->m_colorDeltaAdd[1] + particleData->m_colorDeltaAdd[3];
  }
  fVar10 = FLOAT_80330448;
  particleData->m_sizeStart = pRyjMegaBirth->m_clampMinY;
  particleData->m_sizeVal = pRyjMegaBirth->m_clampYParam;
  if (fVar10 != pRyjMegaBirth->m_clampRandVertical) {
    dVar15 = (double)RandF__5CMathFv(&Math);
    particleData->m_sizeStart =
         particleData->m_sizeStart +
         (float)((double)(float)((double)FLOAT_80330470 * (double)pRyjMegaBirth->m_clampRandVertical
                                ) * dVar15 - (double)pRyjMegaBirth->m_clampRandVertical);
  }
  sVar4 = *(short *)((int)(pRyjMegaBirth->m_matrix).value[2] + 6);
  if (sVar4 == 0) {
    *(undefined2 *)((int)(particleData->m_matrix).value[2] + 2) = 0xffff;
  }
  else {
    *(short *)((int)(particleData->m_matrix).value[2] + 2) = sVar4;
  }
  particleData->field_0x58 = 0;
  bVar1 = *(byte *)&(pRyjMegaBirth->m_baseDirection).y;
  if (bVar1 == 2) {
    PSMTXCopy(&pppPObject->m_localMatrix,particleWMat);
  }
  else if ((bVar1 < 2) && (bVar1 != 0)) {
    PSMTXCopy(&vRyjMegaBirth->m_worldMatrix,particleWMat);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_colorFrameDeltas[0] = (pRyjMegaBirth->m_matrix).value[2][3];
    particleColor->m_colorFrameDeltas[1] = (pRyjMegaBirth->m_directionTail).x;
    particleColor->m_colorFrameDeltas[2] = (pRyjMegaBirth->m_directionTail).y;
    particleColor->m_colorFrameDeltas[3] = (pRyjMegaBirth->m_directionTail).z;
  }
  return;
}

