// Function: birth__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
// Entry: 80085fd0
// Size: 7128 bytes

/* WARNING: Removing unreachable block (ram,0x80087b90) */
/* WARNING: Removing unreachable block (ram,0x80087b88) */
/* WARNING: Removing unreachable block (ram,0x80087b80) */
/* WARNING: Removing unreachable block (ram,0x80087b78) */
/* WARNING: Removing unreachable block (ram,0x80085ff8) */
/* WARNING: Removing unreachable block (ram,0x80085ff0) */
/* WARNING: Removing unreachable block (ram,0x80085fe8) */
/* WARNING: Removing unreachable block (ram,0x80085fe0) */
/* WARNING: Removing unreachable block (ram,0x8008609c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void birth__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VRyjMegaBirthModel *vRyjMegaBirthModel,
               PRyjMegaBirthModel *pRyjMegaBirthModel,VColor *vColor,_PARTICLE_DATA *particleData,
               PARTICLE_WMAT *particleWMat,_PARTICLE_COLOR *particleColor)

{
  byte bVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  ushort uVar6;
  short sVar7;
  float fVar8;
  float *pfVar9;
  _PARTICLE_DATA *p_Var10;
  int iVar11;
  short *psVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  float local_3d8;
  float local_3d4;
  float local_3d0;
  float local_3cc;
  float local_3c8;
  float local_3c4;
  float local_3c0;
  float local_3bc;
  float local_3b8;
  float local_3b4;
  float local_3b0;
  float local_3ac;
  float local_3a8;
  float local_3a4;
  float local_3a0;
  float local_39c;
  float local_398;
  float local_394;
  float local_390;
  float local_38c;
  float local_388;
  float local_384;
  float local_380;
  float local_37c;
  float local_378;
  float local_374;
  float local_370;
  float local_36c;
  float local_368;
  float local_364;
  float local_360;
  float local_35c;
  float local_358;
  float local_354;
  float local_350;
  float local_34c;
  float local_348;
  float local_344;
  float local_340;
  float local_33c;
  float local_338;
  float local_334;
  float local_330;
  float local_32c;
  float local_328;
  Vec local_324;
  float local_318;
  float local_314;
  float local_310;
  float local_30c;
  float local_308;
  float local_304;
  float local_300;
  float local_2fc;
  float local_2f8;
  float local_2f4;
  float local_2f0;
  float local_2ec;
  float local_2e8;
  float local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  Vec local_2ac;
  float local_2a0;
  float local_29c;
  float local_298;
  Vec local_290;
  float local_280;
  float local_27c;
  float local_278;
  float local_270;
  float local_26c;
  float local_268;
  Vec local_260;
  Vec local_250;
  Vec local_240;
  Vec local_230;
  float local_220;
  float local_21c;
  float local_218;
  float local_210;
  float local_20c;
  float local_208;
  pppFMATRIX local_200;
  pppFMATRIX local_1d0;
  pppFMATRIX local_1a0;
  pppFMATRIX local_170;
  pppFMATRIX local_140;
  pppFMATRIX local_110;
  undefined4 local_e0;
  uint uStack_dc;
  undefined8 local_d8;
  longlong local_d0;
  undefined4 local_c8;
  uint uStack_c4;
  undefined4 local_c0;
  uint uStack_bc;
  longlong local_b8;
  undefined8 local_b0;
  undefined4 local_a8;
  uint uStack_a4;
  longlong local_a0;
  undefined4 local_98;
  uint uStack_94;
  undefined8 local_90;
  undefined8 local_88;
  
  uStack_dc = (uint)*(byte *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 0xb);
  local_e0 = 0x43300000;
  dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_dc) - DOUBLE_803304b8);
  dVar17 = (double)(float)((double)FLOAT_803304c0 * dVar16);
  memset(particleData,0,0xa0);
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    memset(particleWMat,0,0x30);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    memset(particleColor,0,0x20);
  }
  pppUnitMatrix__FR10pppFMATRIX(&particleData->m_matrix);
  if (*(byte *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 10) < 8) {
    local_210 = (pRyjMegaBirthModel->m_baseDirection).x;
    local_20c = (pRyjMegaBirthModel->m_baseDirection).y;
    local_208 = (pRyjMegaBirthModel->m_baseDirection).z;
    dVar15 = (double)RandF__5CMathFv(&Math);
    local_220 = (FLOAT_803304a4 * (float)(dVar17 * dVar15 - dVar16)) / FLOAT_803304c4;
    dVar15 = (double)RandF__5CMathFv(&Math);
    local_21c = (FLOAT_803304a4 * (float)(dVar17 * dVar15 - dVar16)) / FLOAT_803304c4;
    dVar15 = (double)RandF__5CMathFv(&Math);
    cVar2 = *(char *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 10);
    local_218 = (FLOAT_803304a4 * (float)(dVar17 * dVar15 - dVar16)) / FLOAT_803304c4;
    if ((cVar2 == '\x02') || (cVar2 == '\x03')) {
      local_220 = FLOAT_80330498;
      local_21c = FLOAT_80330498;
    }
    pppUnitMatrix__FR10pppFMATRIX(&local_110);
    local_2ac.x = local_220;
    local_2ac.y = local_21c;
    local_2ac.z = local_218;
    local_170.value[0][0] = local_110.value[0][0];
    local_170.value[0][1] = local_110.value[0][1];
    local_170.value[0][2] = local_110.value[0][2];
    local_170.value[0][3] = local_110.value[0][3];
    local_170.value[1][0] = local_110.value[1][0];
    local_170.value[1][1] = local_110.value[1][1];
    local_170.value[1][2] = local_110.value[1][2];
    local_170.value[1][3] = local_110.value[1][3];
    local_170.value[2][0] = local_110.value[2][0];
    local_170.value[2][1] = local_110.value[2][1];
    local_170.value[2][2] = local_110.value[2][2];
    local_170.value[2][3] = local_110.value[2][3];
    pppRotMatrix__FR10pppFMATRIX10pppFMATRIX3Vec(&local_110,&local_170,&local_2ac);
    local_240.x = (particleData->m_matrix).value[0][1];
    local_240.y = (particleData->m_matrix).value[1][1];
    local_240.z = (particleData->m_matrix).value[2][1];
    local_2b8 = local_210;
    local_2b4 = local_20c;
    local_2b0 = local_208;
    local_1a0.value[0][0] = local_110.value[0][0];
    local_1a0.value[0][1] = local_110.value[0][1];
    local_1a0.value[0][2] = local_110.value[0][2];
    local_1a0.value[0][3] = local_110.value[0][3];
    local_1a0.value[1][0] = local_110.value[1][0];
    local_1a0.value[1][1] = local_110.value[1][1];
    local_1a0.value[1][2] = local_110.value[1][2];
    local_1a0.value[1][3] = local_110.value[1][3];
    local_1a0.value[2][0] = local_110.value[2][0];
    local_1a0.value[2][1] = local_110.value[2][1];
    local_1a0.value[2][2] = local_110.value[2][2];
    local_1a0.value[2][3] = local_110.value[2][3];
    pppApplyMatrix__FR3Vec10pppFMATRIX3Vec(&local_240,&local_1a0,&local_2b8);
    local_240.x = local_240.x * (pRyjMegaBirthModel->m_scale).x;
    local_240.y = local_240.y * (pRyjMegaBirthModel->m_scale).y;
    local_240.z = local_240.z * (pRyjMegaBirthModel->m_scale).z;
    (particleData->m_matrix).value[0][1] = local_240.x;
    (particleData->m_matrix).value[1][1] = local_240.y;
    (particleData->m_matrix).value[2][1] = local_240.z;
    pppGetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
              (&particleData->m_matrix,&local_230,&local_240,&local_250,&local_260);
    local_2c4 = local_240.x;
    local_2c0 = local_240.y;
    local_2bc = local_240.z;
    pppNormalize__FR3Vec3Vec(&local_240,&local_2c4);
    local_2dc = local_230.x;
    local_2d8 = local_230.y;
    local_2d4 = local_230.z;
    local_2d0 = local_240.x;
    local_2cc = local_240.y;
    local_2c8 = local_240.z;
    pppOuterProduct__FR3Vec3Vec3Vec(&local_250,&local_2d0,&local_2dc);
    local_2e8 = local_250.x;
    local_2e4 = local_250.y;
    local_2e0 = local_250.z;
    pppNormalize__FR3Vec3Vec(&local_250,&local_2e8);
    local_300 = local_240.x;
    local_2fc = local_240.y;
    local_2f8 = local_240.z;
    local_2f4 = local_250.x;
    local_2f0 = local_250.y;
    local_2ec = local_250.z;
    pppOuterProduct__FR3Vec3Vec3Vec(&local_230,&local_2f4,&local_300);
    local_30c = local_230.x;
    local_308 = local_230.y;
    local_304 = local_230.z;
    pppNormalize__FR3Vec3Vec(&local_230,&local_30c);
    pppSetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
              (&particleData->m_matrix,&local_230,&local_240,&local_250,&local_260);
    pppUnitMatrix__FR10pppFMATRIX(&local_140);
    local_318 = (particleData->m_matrix).value[0][1];
    local_314 = (particleData->m_matrix).value[1][1];
    local_310 = (particleData->m_matrix).value[2][1];
    dVar16 = (double)(particleData->m_matrix).value[0][3];
    dVar17 = (double)(particleData->m_matrix).value[1][3];
    dVar15 = (double)(particleData->m_matrix).value[2][3];
    local_270 = local_318;
    local_26c = local_314;
    local_268 = local_310;
    pppNormalize__FR3Vec3Vec(&local_270,&local_318);
    local_324.x = local_270;
    local_324.y = local_26c;
    local_324.z = local_268;
    pppCopyVector__FR3Vec3Vec(&local_290,&local_324);
    local_2a0 = FLOAT_80330498;
    local_29c = FLOAT_80330498;
    local_298 = FLOAT_803304c8;
    local_33c = FLOAT_80330498;
    local_338 = FLOAT_80330498;
    local_334 = FLOAT_803304c8;
    local_330 = local_290.x;
    local_32c = local_290.y;
    local_328 = local_290.z;
    pppOuterProduct__FR3Vec3Vec3Vec(&local_280,&local_330,&local_33c);
    local_348 = local_280;
    local_344 = local_27c;
    local_340 = local_278;
    pppNormalize__FR3Vec3Vec(&local_280,&local_348);
    local_360 = local_290.x;
    local_35c = local_290.y;
    local_358 = local_290.z;
    local_354 = local_280;
    local_350 = local_27c;
    local_34c = local_278;
    pppOuterProduct__FR3Vec3Vec3Vec(&local_2a0,&local_354,&local_360);
    local_36c = local_2a0;
    local_368 = local_29c;
    local_364 = local_298;
    pppNormalize__FR3Vec3Vec(&local_2a0,&local_36c);
    pppUnitMatrix__FR10pppFMATRIX(&local_140);
    local_140.value[0][0] = local_280;
    local_140.value[1][0] = local_27c;
    local_140.value[2][0] = local_278;
    local_140.value[0][1] = local_290.x;
    local_140.value[1][1] = local_290.y;
    local_140.value[2][1] = local_290.z;
    local_140.value[0][2] = local_2a0;
    local_140.value[1][2] = local_29c;
    local_140.value[2][2] = local_298;
    local_1d0.value[0][3] = (float)dVar16;
    local_1d0.value[1][3] = (float)dVar17;
    local_1d0.value[2][3] = (float)dVar15;
    local_1d0.value[0][0] = local_280;
    local_1d0.value[0][1] = local_290.x;
    local_1d0.value[0][2] = local_2a0;
    local_1d0.value[1][0] = local_27c;
    local_1d0.value[1][1] = local_290.y;
    local_1d0.value[1][2] = local_29c;
    local_1d0.value[2][0] = local_278;
    local_1d0.value[2][1] = local_290.z;
    local_1d0.value[2][2] = local_298;
    local_140.value[0][3] = local_1d0.value[0][3];
    local_140.value[1][3] = local_1d0.value[1][3];
    local_140.value[2][3] = local_1d0.value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&particleData->m_matrix,&local_1d0);
  }
  bVar1 = *(byte *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 10);
  if (bVar1 < 6) {
    if (3 < bVar1) {
      if (FLOAT_80330498 == pRyjMegaBirthModel->m_speedMag) goto LAB_8008720c;
      bVar1 = pRyjMegaBirthModel->field_0x130;
      dVar16 = (double)(FLOAT_803304d0 * pRyjMegaBirthModel->m_speedMag);
      if (bVar1 == 3) {
        local_260.x = (particleData->m_matrix).value[0][3];
        local_260.y = (particleData->m_matrix).value[1][3];
        local_260.z = (particleData->m_matrix).value[2][3];
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        local_260.x = (float)(-(double)(float)((double)FLOAT_803304cc *
                                               (double)(float)((double)(float)((double)
                                                  pRyjMegaBirthModel->m_speedMag * dVar15) * dVar17)
                                              - (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        local_260.y = (float)(-(double)(float)((double)FLOAT_803304cc *
                                               (double)(float)((double)(float)((double)
                                                  pRyjMegaBirthModel->m_speedMag * dVar15) * dVar17)
                                              - (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        local_260.z = (float)(-(double)(float)((double)FLOAT_803304cc *
                                               (double)(float)((double)(float)((double)
                                                  pRyjMegaBirthModel->m_speedMag * dVar15) * dVar17)
                                              - (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        (particleData->m_matrix).value[0][3] = local_260.x;
        (particleData->m_matrix).value[1][3] = local_260.y;
        (particleData->m_matrix).value[2][3] = local_260.z;
      }
      else if (bVar1 < 3) {
        if (bVar1 == 1) {
          RandF__5CMathFv(&Math);
          local_260.x = (particleData->m_matrix).value[0][3];
          local_260.y = (particleData->m_matrix).value[1][3];
          local_260.z = (particleData->m_matrix).value[2][3];
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.x = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.y = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.z = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          (particleData->m_matrix).value[0][3] = local_260.x;
          (particleData->m_matrix).value[1][3] = local_260.y;
          (particleData->m_matrix).value[2][3] = local_260.z;
        }
        else if (bVar1 == 0) {
LAB_80086834:
          local_260.x = (particleData->m_matrix).value[0][3];
          local_260.y = (particleData->m_matrix).value[1][3];
          local_260.z = (particleData->m_matrix).value[2][3];
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.x = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.y = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          local_260.z = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) -
                               dVar16);
          (particleData->m_matrix).value[0][3] = local_260.x;
          (particleData->m_matrix).value[1][3] = local_260.y;
          (particleData->m_matrix).value[2][3] = local_260.z;
        }
        else {
          local_260.x = (particleData->m_matrix).value[0][3];
          local_260.y = (particleData->m_matrix).value[1][3];
          local_260.z = (particleData->m_matrix).value[2][3];
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          local_260.x = (float)((double)(float)((double)(float)((double)pRyjMegaBirthModel->
                                                                        m_speedMag * dVar15) *
                                               dVar17) - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          local_260.y = (float)((double)(float)((double)(float)((double)pRyjMegaBirthModel->
                                                                        m_speedMag * dVar15) *
                                               dVar17) - dVar16);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          local_260.z = (float)((double)(float)((double)(float)((double)pRyjMegaBirthModel->
                                                                        m_speedMag * dVar15) *
                                               dVar17) - dVar16);
          (particleData->m_matrix).value[0][3] = local_260.x;
          (particleData->m_matrix).value[1][3] = local_260.y;
          (particleData->m_matrix).value[2][3] = local_260.z;
        }
      }
      else if (bVar1 == 5) {
        local_260.x = (particleData->m_matrix).value[0][3];
        local_260.y = (particleData->m_matrix).value[1][3];
        local_260.z = (particleData->m_matrix).value[2][3];
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        local_260.x = (float)(-(double)(float)((double)FLOAT_803304d0 *
                                               (double)(float)(dVar13 * (double)(float)((double)(
                                                  float)((double)pRyjMegaBirthModel->m_speedMag *
                                                        dVar15) * dVar17)) -
                                              (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        local_260.y = (float)(-(double)(float)((double)FLOAT_803304d0 *
                                               (double)(float)(dVar13 * (double)(float)((double)(
                                                  float)((double)pRyjMegaBirthModel->m_speedMag *
                                                        dVar15) * dVar17)) -
                                              (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        local_260.z = (float)(-(double)(float)((double)FLOAT_803304d0 *
                                               (double)(float)(dVar13 * (double)(float)((double)(
                                                  float)((double)pRyjMegaBirthModel->m_speedMag *
                                                        dVar15) * dVar17)) -
                                              (double)pRyjMegaBirthModel->m_speedMag) - dVar16);
        (particleData->m_matrix).value[0][3] = local_260.x;
        (particleData->m_matrix).value[1][3] = local_260.y;
        (particleData->m_matrix).value[2][3] = local_260.z;
      }
      else {
        if (4 < bVar1) goto LAB_80086834;
        local_260.x = (particleData->m_matrix).value[0][3];
        local_260.y = (particleData->m_matrix).value[1][3];
        local_260.z = (particleData->m_matrix).value[2][3];
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        local_260.x = (float)((double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)((
                                                  double)(float)((double)pRyjMegaBirthModel->
                                                                         m_speedMag * dVar15) *
                                                  dVar17))) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        local_260.y = (float)((double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)((
                                                  double)(float)((double)pRyjMegaBirthModel->
                                                                         m_speedMag * dVar15) *
                                                  dVar17))) - dVar16);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar13 = (double)RandF__5CMathFv(&Math);
        dVar14 = (double)RandF__5CMathFv(&Math);
        local_260.z = (float)((double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)((
                                                  double)(float)((double)pRyjMegaBirthModel->
                                                                         m_speedMag * dVar15) *
                                                  dVar17))) - dVar16);
        (particleData->m_matrix).value[0][3] = local_260.x;
        (particleData->m_matrix).value[1][3] = local_260.y;
        (particleData->m_matrix).value[2][3] = local_260.z;
      }
      fVar8 = (particleData->m_matrix).value[1][3];
      fVar3 = (pRyjMegaBirthModel->m_scale).y;
      fVar4 = (particleData->m_matrix).value[2][3];
      fVar5 = (pRyjMegaBirthModel->m_scale).z;
      (particleData->m_matrix).value[0][3] =
           (particleData->m_matrix).value[0][3] * (pRyjMegaBirthModel->m_scale).x;
      (particleData->m_matrix).value[1][3] = fVar8 * fVar3;
      (particleData->m_matrix).value[2][3] = fVar4 * fVar5;
      goto LAB_8008720c;
    }
  }
  else if (bVar1 < 10) {
    fVar8 = pppPObject[1].m_localMatrix.value[2][0];
    if (*(short *)&pRyjMegaBirthModel->field_0x138 < 0) goto LAB_8008720c;
    psVar12 = (short *)(*(int *)pppEnvStPtr->m_particleColors[1].m_colorRGBA +
                       *(short *)&pRyjMegaBirthModel->field_0x138 * 8);
    if (fVar8 == 0.0) {
      fVar8 = (float)pppEnvStPtr->m_mapMeshPtr[*psVar12]->field14_0x2c;
    }
    bVar1 = pRyjMegaBirthModel->field_0x130;
    if (bVar1 == 3) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar16 = (double)(float)(DOUBLE_803304d8 -
                              (double)(float)(dVar15 * (double)(float)(dVar17 * dVar16)));
LAB_80086fbc:
      if ((int)psVar12[1] <= (int)(uint)vRyjMegaBirthModel->field17_0x1e) {
        vRyjMegaBirthModel->field17_0x1e = 0;
      }
      local_e0 = 0x43300000;
      uStack_dc = (int)psVar12[1] ^ 0x80000000;
      iVar11 = (int)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,uStack_dc) -
                                             DOUBLE_803304b0));
      local_d8 = (double)(longlong)iVar11;
      pfVar9 = (float *)((int)fVar8 + (uint)*(ushort *)(*(int *)(psVar12 + 2) + iVar11 * 2) * 0xc);
      local_260.x = *pfVar9;
      local_260.y = pfVar9[1];
      local_260.z = pfVar9[2];
    }
    else {
      if (2 < bVar1) {
        if (bVar1 == 5) {
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar14 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)(float)(DOUBLE_803304d8 -
                                  (double)(float)(dVar14 * (double)(float)(dVar13 * (double)(float)(
                                                  dVar15 * (double)(float)(dVar17 * dVar16)))));
        }
        else {
          if (4 < bVar1) goto LAB_80086e28;
          dVar16 = (double)RandF__5CMathFv(&Math);
          dVar17 = (double)RandF__5CMathFv(&Math);
          dVar15 = (double)RandF__5CMathFv(&Math);
          dVar13 = (double)RandF__5CMathFv(&Math);
          dVar16 = (double)(float)(dVar13 * (double)(float)(dVar15 * (double)(float)(dVar17 * dVar16
                                                                                    )));
        }
        goto LAB_80086fbc;
      }
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        goto LAB_80086fbc;
      }
      if (bVar1 != 0) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar17 = (double)RandF__5CMathFv(&Math);
        dVar15 = (double)RandF__5CMathFv(&Math);
        dVar16 = (double)(float)(dVar15 * (double)(float)(dVar17 * dVar16));
        goto LAB_80086fbc;
      }
LAB_80086e28:
      if ((int)psVar12[1] <= (int)(uint)vRyjMegaBirthModel->field17_0x1e) {
        vRyjMegaBirthModel->field17_0x1e = 0;
      }
      uVar6 = vRyjMegaBirthModel->field17_0x1e;
      iVar11 = *(int *)(psVar12 + 2);
      vRyjMegaBirthModel->field17_0x1e = uVar6 + 1;
      pfVar9 = (float *)((int)fVar8 + (uint)*(ushort *)(iVar11 + (uint)uVar6 * 2) * 0xc);
      local_260.x = *pfVar9;
      local_260.y = pfVar9[1];
      local_260.z = pfVar9[2];
    }
    local_260.x = local_260.x * (pRyjMegaBirthModel->m_scale).x;
    local_260.y = local_260.y * (pRyjMegaBirthModel->m_scale).y;
    local_260.z = local_260.z * (pRyjMegaBirthModel->m_scale).z;
    (particleData->m_matrix).value[0][3] = local_260.x;
    (particleData->m_matrix).value[1][3] = local_260.y;
    (particleData->m_matrix).value[2][3] = local_260.z;
    cVar2 = *(char *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 10);
    if ((cVar2 == '\b') || (cVar2 == '\t')) {
      pppGetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
                (&particleData->m_matrix,&local_230,&local_240,&local_250,&local_260);
      local_384 = local_260.x;
      local_380 = local_260.y;
      local_37c = local_260.z;
      pppNormalize__FR3Vec3Vec(&local_240,&local_384);
      local_390 = local_240.x * (pRyjMegaBirthModel->m_scale).x;
      local_38c = local_240.y * (pRyjMegaBirthModel->m_scale).y;
      local_388 = local_240.z * (pRyjMegaBirthModel->m_scale).z;
      (particleData->m_matrix).value[0][1] = local_390;
      (particleData->m_matrix).value[1][1] = local_38c;
      (particleData->m_matrix).value[2][1] = local_388;
      local_240.x = local_390;
      local_240.y = local_38c;
      local_240.z = local_388;
      pppNormalize__FR3Vec3Vec(&local_240,&local_390);
      local_3a8 = local_230.x;
      local_3a4 = local_230.y;
      local_3a0 = local_230.z;
      local_39c = local_240.x;
      local_398 = local_240.y;
      local_394 = local_240.z;
      pppOuterProduct__FR3Vec3Vec3Vec(&local_250,&local_39c,&local_3a8);
      local_3b4 = local_250.x;
      local_3b0 = local_250.y;
      local_3ac = local_250.z;
      pppNormalize__FR3Vec3Vec(&local_250,&local_3b4);
      local_3cc = local_240.x;
      local_3c8 = local_240.y;
      local_3c4 = local_240.z;
      local_3c0 = local_250.x;
      local_3bc = local_250.y;
      local_3b8 = local_250.z;
      pppOuterProduct__FR3Vec3Vec3Vec(&local_230,&local_3c0,&local_3cc);
      local_3d8 = local_230.x;
      local_3d4 = local_230.y;
      local_3d0 = local_230.z;
      pppNormalize__FR3Vec3Vec(&local_230,&local_3d8);
      pppSetRowVector__FR10pppFMATRIXR3VecR3VecR3VecR3Vec
                (&particleData->m_matrix,&local_230,&local_240,&local_250,&local_260);
    }
    goto LAB_8008720c;
  }
  fVar8 = pRyjMegaBirthModel->m_speedMag;
  if (FLOAT_80330498 != fVar8) {
    bVar1 = pRyjMegaBirthModel->field_0x130;
    if (bVar1 == 3) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      fVar8 = -(float)((double)FLOAT_803304cc *
                       (double)(float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag *
                                                      dVar17) * dVar16) -
                      (double)pRyjMegaBirthModel->m_speedMag);
    }
    else if (bVar1 < 3) {
      if (bVar1 == 1) {
        RandF__5CMathFv(&Math);
        dVar16 = (double)RandF__5CMathFv(&Math);
        fVar8 = (float)((double)pRyjMegaBirthModel->m_speedMag * dVar16);
      }
      else if (bVar1 != 0) {
        dVar16 = (double)RandF__5CMathFv(&Math);
        dVar17 = (double)RandF__5CMathFv(&Math);
        fVar8 = (float)((double)(float)((double)pRyjMegaBirthModel->m_speedMag * dVar17) * dVar16);
      }
    }
    else if (bVar1 == 5) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar15 = (double)RandF__5CMathFv(&Math);
      fVar8 = -(float)((double)FLOAT_803304d0 *
                       (double)(float)(dVar15 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirthModel->m_speedMag * dVar17) * dVar16)
                                      ) - (double)pRyjMegaBirthModel->m_speedMag);
    }
    else if (bVar1 < 5) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      dVar17 = (double)RandF__5CMathFv(&Math);
      dVar15 = (double)RandF__5CMathFv(&Math);
      dVar13 = (double)RandF__5CMathFv(&Math);
      fVar8 = (float)(dVar13 * (double)(float)(dVar15 * (double)(float)((double)(float)((double)
                                                  pRyjMegaBirthModel->m_speedMag * dVar17) * dVar16)
                                              ));
    }
    local_378 = (particleData->m_matrix).value[0][1];
    local_374 = (particleData->m_matrix).value[1][1];
    local_370 = (particleData->m_matrix).value[2][1];
    local_260.x = (particleData->m_matrix).value[0][3];
    local_260.y = (particleData->m_matrix).value[1][3];
    local_260.z = (particleData->m_matrix).value[2][3];
    local_240.x = local_378;
    local_240.y = local_374;
    local_240.z = local_370;
    pppScaleVectorXYZ__FR3Vec3Vecf(fVar8,&local_260,&local_378);
    (particleData->m_matrix).value[0][3] = local_260.x;
    (particleData->m_matrix).value[1][3] = local_260.y;
    (particleData->m_matrix).value[2][3] = local_260.z;
  }
LAB_8008720c:
  bVar1 = *(byte *)&pRyjMegaBirthModel->m_sizeStart;
  RandF__5CMathFv(&Math);
  dVar16 = (double)RandF__5CMathFv(&Math);
  uStack_dc = bVar1 >> 1 ^ 0x80000000;
  local_d8 = (double)CONCAT44(0x43300000,(uint)bVar1 << 1 ^ 0x80000000);
  local_e0 = 0x43300000;
  iVar11 = (int)((double)(float)(local_d8 - DOUBLE_803304b0) * dVar16 -
                (double)(float)((double)CONCAT44(0x43300000,uStack_dc) - DOUBLE_803304b0));
  local_d0 = (longlong)iVar11;
  *(char *)((int)&(particleData->m_directionTail).x + 2) = (char)iVar11;
  bVar1 = *(byte *)((int)&pRyjMegaBirthModel->m_sizeStart + 1);
  RandF__5CMathFv(&Math);
  dVar16 = (double)RandF__5CMathFv(&Math);
  uStack_c4 = (uint)bVar1 << 1 ^ 0x80000000;
  uStack_bc = bVar1 >> 1 ^ 0x80000000;
  local_c8 = 0x43300000;
  local_c0 = 0x43300000;
  iVar11 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_c4) - DOUBLE_803304b0) * dVar16
                - (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_803304b0));
  local_b8 = (longlong)iVar11;
  *(char *)((int)&(particleData->m_directionTail).x + 3) = (char)iVar11;
  bVar1 = *(byte *)((int)&pRyjMegaBirthModel->m_sizeStart + 2);
  RandF__5CMathFv(&Math);
  dVar16 = (double)RandF__5CMathFv(&Math);
  uStack_a4 = bVar1 >> 1 ^ 0x80000000;
  local_b0 = (double)CONCAT44(0x43300000,(uint)bVar1 << 1 ^ 0x80000000);
  local_a8 = 0x43300000;
  iVar11 = (int)((double)(float)(local_b0 - DOUBLE_803304b0) * dVar16 -
                (double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_803304b0));
  local_a0 = (longlong)iVar11;
  *(char *)&(particleData->m_directionTail).y = (char)iVar11;
  bVar1 = *(byte *)((int)&pRyjMegaBirthModel->m_sizeStart + 3);
  RandF__5CMathFv(&Math);
  dVar16 = (double)RandF__5CMathFv(&Math);
  uStack_94 = (uint)bVar1 << 1 ^ 0x80000000;
  local_98 = 0x43300000;
  local_90 = (double)CONCAT44(0x43300000,bVar1 >> 1 ^ 0x80000000);
  iVar11 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_803304b0) * dVar16
                - (double)(float)(local_90 - DOUBLE_803304b0));
  local_88 = (double)(longlong)iVar11;
  *(char *)((int)&(particleData->m_directionTail).y + 1) = (char)iVar11;
  if (*(char *)((pRyjMegaBirthModel->m_matrix).value[2] + 2) != '\0') {
    local_88 = (double)CONCAT44(0x43300000,(uint)vColor->m_alpha);
    (particleData->field26_0x90).z = (float)(local_88 - DOUBLE_803304b8);
    particleData->field_0x9d = *(undefined *)((pRyjMegaBirthModel->m_matrix).value[2] + 2);
  }
  cVar2 = *(char *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 9);
  if (cVar2 != '\0') {
    particleData->field_0x9e = cVar2;
  }
  (particleData->m_directionTail).z = pRyjMegaBirthModel->m_sizeVal;
  particleData->m_colorDeltaAdd[0] = pRyjMegaBirthModel->m_speedRandRange;
  particleData->m_colorDeltaAdd[1] = *(float *)&pRyjMegaBirthModel->field_0x58;
  particleData->m_colorDeltaAdd[2] = (pRyjMegaBirthModel->m_speedScale).y;
  particleData->m_colorDeltaAdd[3] = (pRyjMegaBirthModel->m_speedScale).z;
  particleData->m_sizeStart = *(float *)&pRyjMegaBirthModel->m_randType;
  if (pRyjMegaBirthModel->m_flagsVelocityB != 0) {
    if ((pRyjMegaBirthModel->m_flagsVelocityB & 0x20) == 0) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      local_88 = (double)(CONCAT44(0x43300000,pRyjMegaBirthModel->m_randomRotationRangeX) ^
                         0x80000000);
      fVar8 = (float)(int)((double)(float)(local_88 - DOUBLE_803304b0) * dVar16);
      local_90 = (double)(longlong)(int)fVar8;
      particleData->m_sizeVal = fVar8;
      dVar16 = (double)RandF__5CMathFv(&Math);
      local_98 = 0x43300000;
      uStack_94 = pRyjMegaBirthModel->m_randomRotationRangeY ^ 0x80000000;
      fVar8 = (float)(int)((double)(float)((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_803304b0)
                          * dVar16);
      local_a0 = (longlong)(int)fVar8;
      particleData->m_speedRandRange = fVar8;
      dVar16 = (double)RandF__5CMathFv(&Math);
      local_a8 = 0x43300000;
      uStack_a4 = pRyjMegaBirthModel->m_randomRotationRangeZ ^ 0x80000000;
      iVar11 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_a4) - DOUBLE_803304b0) *
                    dVar16);
      local_b0 = (double)(longlong)iVar11;
      *(int *)&particleData->field_0x58 = iVar11;
      bVar1 = pRyjMegaBirthModel->m_flagsVelocityB;
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          particleData->m_sizeVal = (float)-(int)particleData->m_sizeVal;
          particleData->m_speedRandRange = (float)-(int)particleData->m_speedRandRange;
          *(int *)&particleData->field_0x58 = -*(int *)&particleData->field_0x58;
        }
      }
      else {
        iVar11 = 0;
        p_Var10 = particleData;
        dVar16 = DOUBLE_803304e0;
        do {
          dVar17 = (double)RandF__5CMathFv(&Math);
          if (dVar16 < dVar17) {
            p_Var10->m_sizeVal = (float)-(int)p_Var10->m_sizeVal;
          }
          iVar11 = iVar11 + 1;
          p_Var10 = (_PARTICLE_DATA *)((p_Var10->m_matrix).value[0] + 1);
        } while (iVar11 < 3);
      }
    }
    else {
      dVar16 = (double)RandF__5CMathFv(&Math);
      local_88 = (double)(CONCAT44(0x43300000,pRyjMegaBirthModel->m_randomRotationRangeX) ^
                         0x80000000);
      fVar8 = (float)(int)((double)(float)(local_88 - DOUBLE_803304b0) * dVar16);
      local_90 = (double)(longlong)(int)fVar8;
      *(float *)&particleData->field_0x58 = fVar8;
      particleData->m_speedRandRange = fVar8;
      particleData->m_sizeVal = fVar8;
      bVar1 = pRyjMegaBirthModel->m_flagsVelocityB;
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          particleData->m_sizeVal = (float)-(int)particleData->m_sizeVal;
          particleData->m_speedRandRange = (float)-(int)particleData->m_speedRandRange;
          *(int *)&particleData->field_0x58 = -*(int *)&particleData->field_0x58;
        }
      }
      else {
        dVar16 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_803304e0 < dVar16) {
          particleData->m_sizeVal = (float)-(int)particleData->m_sizeVal;
          particleData->m_speedRandRange = (float)-(int)particleData->m_speedRandRange;
          *(int *)&particleData->field_0x58 = -*(int *)&particleData->field_0x58;
        }
      }
    }
  }
  if ((pRyjMegaBirthModel->m_flagsVelocityB & 4) != 0) {
    (particleData->m_directionTail).z =
         (float)((int)(particleData->m_directionTail).z + (int)particleData->m_sizeVal);
    particleData->m_colorDeltaAdd[0] =
         (float)((int)particleData->m_colorDeltaAdd[0] + (int)particleData->m_speedRandRange);
    particleData->m_colorDeltaAdd[1] =
         (float)((int)particleData->m_colorDeltaAdd[1] + *(int *)&particleData->field_0x58);
  }
  if ((pRyjMegaBirthModel->m_flagsVelocityB & 8) != 0) {
    particleData->m_colorDeltaAdd[2] =
         (float)((int)particleData->m_colorDeltaAdd[2] + (int)particleData->m_sizeVal);
    particleData->m_colorDeltaAdd[3] =
         (float)((int)particleData->m_colorDeltaAdd[3] + (int)particleData->m_speedRandRange);
    particleData->m_sizeStart =
         (float)((int)particleData->m_sizeStart + *(int *)&particleData->field_0x58);
  }
  fVar8 = (particleData->m_directionTail).z;
  if ((0x7fff < (int)fVar8) || ((int)fVar8 < -0x8000)) {
    fVar8 = (particleData->m_directionTail).z;
    iVar11 = (int)fVar8 >> 0x1f;
    (particleData->m_directionTail).z =
         (float)((iVar11 * 0x8000 | (uint)((int)fVar8 * 0x20000 + iVar11) >> 0x11) - iVar11);
  }
  if ((0x7fff < (int)particleData->m_colorDeltaAdd[0]) ||
     ((int)particleData->m_colorDeltaAdd[0] < -0x8000)) {
    iVar11 = (int)particleData->m_colorDeltaAdd[0] >> 0x1f;
    particleData->m_colorDeltaAdd[0] =
         (float)((iVar11 * 0x8000 |
                 (uint)((int)particleData->m_colorDeltaAdd[0] * 0x20000 + iVar11) >> 0x11) - iVar11)
    ;
  }
  if ((0x7fff < (int)particleData->m_colorDeltaAdd[1]) ||
     ((int)particleData->m_colorDeltaAdd[1] < -0x8000)) {
    iVar11 = (int)particleData->m_colorDeltaAdd[1] >> 0x1f;
    particleData->m_colorDeltaAdd[1] =
         (float)((iVar11 * 0x8000 |
                 (uint)((int)particleData->m_colorDeltaAdd[1] * 0x20000 + iVar11) >> 0x11) - iVar11)
    ;
  }
  (particleData->m_speedScale).x = (pRyjMegaBirthModel->field26_0x90).x;
  (particleData->m_speedScale).y = (pRyjMegaBirthModel->field26_0x90).y;
  (particleData->m_speedScale).z = (pRyjMegaBirthModel->field26_0x90).z;
  *(float *)&particleData->m_randType = (pRyjMegaBirthModel->field31_0xa0).x;
  *(float *)&particleData->m_tail2PathIndex = (pRyjMegaBirthModel->field31_0xa0).y;
  (particleData->m_angleVelocity).x = (pRyjMegaBirthModel->field31_0xa0).z;
  if (pRyjMegaBirthModel->m_flagsVelocityA != 0) {
    if ((pRyjMegaBirthModel->m_flagsVelocityA & 0x20) == 0) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      (particleData->m_angleVelocity).y = (float)((double)pRyjMegaBirthModel->m_clampMinY * dVar16);
      dVar16 = (double)RandF__5CMathFv(&Math);
      (particleData->m_angleVelocity).z =
           (float)((double)pRyjMegaBirthModel->m_clampMaxYStep * dVar16);
      dVar16 = (double)RandF__5CMathFv(&Math);
      particleData->unk6 =
           (int32_t)(float)((double)pRyjMegaBirthModel->m_clampRandVertical * dVar16);
      fVar8 = FLOAT_803304e8;
      bVar1 = pRyjMegaBirthModel->m_flagsVelocityA;
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          (particleData->m_angleVelocity).y = (particleData->m_angleVelocity).y * FLOAT_803304e8;
          (particleData->m_angleVelocity).z = (particleData->m_angleVelocity).z * fVar8;
          particleData->unk6 = (int32_t)((float)particleData->unk6 * fVar8);
        }
      }
      else {
        dVar17 = (double)FLOAT_803304e8;
        iVar11 = 0;
        p_Var10 = particleData;
        dVar16 = DOUBLE_803304e0;
        do {
          dVar15 = (double)RandF__5CMathFv(&Math);
          if (dVar16 < dVar15) {
            (p_Var10->m_angleVelocity).y = (float)((double)(p_Var10->m_angleVelocity).y * dVar17);
          }
          iVar11 = iVar11 + 1;
          p_Var10 = (_PARTICLE_DATA *)((p_Var10->m_matrix).value[0] + 1);
        } while (iVar11 < 3);
      }
    }
    else {
      dVar16 = (double)RandF__5CMathFv(&Math);
      fVar8 = (float)((double)pRyjMegaBirthModel->m_clampMinY * dVar16);
      particleData->unk6 = (int32_t)fVar8;
      (particleData->m_angleVelocity).z = fVar8;
      (particleData->m_angleVelocity).y = fVar8;
      fVar8 = FLOAT_803304e8;
      bVar1 = pRyjMegaBirthModel->m_flagsVelocityA;
      if (((bVar1 & 1) == 0) || ((bVar1 & 2) == 0)) {
        if ((bVar1 & 2) != 0) {
          (particleData->m_angleVelocity).y = (particleData->m_angleVelocity).y * FLOAT_803304e8;
          (particleData->m_angleVelocity).z = (particleData->m_angleVelocity).z * fVar8;
          particleData->unk6 = (int32_t)((float)particleData->unk6 * fVar8);
        }
      }
      else {
        dVar16 = (double)RandF__5CMathFv(&Math);
        fVar8 = FLOAT_803304e8;
        if (DOUBLE_803304e0 < dVar16) {
          (particleData->m_angleVelocity).y = (particleData->m_angleVelocity).y * FLOAT_803304e8;
          (particleData->m_angleVelocity).z = (particleData->m_angleVelocity).z * fVar8;
          particleData->unk6 = (int32_t)((float)particleData->unk6 * fVar8);
        }
      }
    }
  }
  if ((pRyjMegaBirthModel->m_flagsVelocityA & 4) != 0) {
    (particleData->m_speedScale).x =
         (particleData->m_speedScale).x + (particleData->m_angleVelocity).y;
    (particleData->m_speedScale).y =
         (particleData->m_speedScale).y + (particleData->m_angleVelocity).z;
    (particleData->m_speedScale).z = (particleData->m_speedScale).z + (float)particleData->unk6;
  }
  if ((pRyjMegaBirthModel->m_flagsVelocityA & 8) != 0) {
    *(float *)&particleData->m_randType =
         *(float *)&particleData->m_randType + (particleData->m_angleVelocity).y;
    *(float *)&particleData->m_tail2PathIndex =
         *(float *)&particleData->m_tail2PathIndex + (particleData->m_angleVelocity).z;
    (particleData->m_angleVelocity).x =
         (particleData->m_angleVelocity).x + (float)particleData->unk6;
  }
  fVar8 = FLOAT_80330498;
  particleData->m_randomRotationRangeX = (int32_t)pRyjMegaBirthModel->m_heightMin;
  particleData->m_randomRotationRangeY = *(int32_t *)&pRyjMegaBirthModel->field_0x114;
  if (fVar8 != *(float *)&pRyjMegaBirthModel->field_0x110) {
    dVar16 = (double)RandF__5CMathFv(&Math);
    particleData->m_randomRotationRangeX =
         (int32_t)((float)particleData->m_randomRotationRangeX +
                  (float)((double)(float)((double)FLOAT_803304c0 *
                                         (double)*(float *)&pRyjMegaBirthModel->field_0x110) *
                          dVar16 - (double)*(float *)&pRyjMegaBirthModel->field_0x110));
  }
  particleData->m_randomRotationRangeZ = (int32_t)pRyjMegaBirthModel->m_accelerationZ;
  *(float *)&particleData->field22_0x8c = (pRyjMegaBirthModel->m_directionScale).y;
  (particleData->field26_0x90).x = pRyjMegaBirthModel->m_directionSpeed;
  (particleData->field26_0x90).y = (pRyjMegaBirthModel->m_directionScale).z;
  bVar1 = pRyjMegaBirthModel->m_accelerationRandomizationMode;
  if (bVar1 == 3) {
    dVar16 = (double)RandF__5CMathFv(&Math);
    particleData->m_randomRotationRangeZ =
         (int32_t)(float)((double)(float)particleData->m_randomRotationRangeZ * dVar16);
    *(float *)&particleData->field22_0x8c =
         (float)((double)*(float *)&particleData->field22_0x8c * dVar16);
  }
  else if (bVar1 < 3) {
    if (bVar1 == 1) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      particleData->m_randomRotationRangeZ =
           (int32_t)(float)((double)(float)particleData->m_randomRotationRangeZ * dVar16);
    }
    else if (bVar1 != 0) {
      dVar16 = (double)RandF__5CMathFv(&Math);
      *(float *)&particleData->field22_0x8c =
           (float)((double)*(float *)&particleData->field22_0x8c * dVar16);
    }
  }
  else if (bVar1 < 5) {
    dVar16 = (double)RandF__5CMathFv(&Math);
    particleData->m_randomRotationRangeZ =
         (int32_t)(float)((double)(float)particleData->m_randomRotationRangeZ * dVar16);
    dVar16 = (double)RandF__5CMathFv(&Math);
    *(float *)&particleData->field22_0x8c =
         (float)((double)*(float *)&particleData->field22_0x8c * dVar16);
  }
  sVar7 = *(short *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 6);
  if (sVar7 == 0) {
    *(undefined2 *)&(particleData->m_directionTail).x = 0xffff;
  }
  else {
    *(short *)&(particleData->m_directionTail).x = sVar7;
  }
  particleData->field_0x9c = 0;
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    local_200.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
    local_200.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
    local_200.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
    local_200.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
    local_200.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
    local_200.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
    local_200.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
    local_200.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
    local_200.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
    local_200.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
    local_200.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
    local_200.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(particleWMat,&local_200);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_colorFrameDeltas[0] = (pRyjMegaBirthModel->m_matrix).value[2][3];
    particleColor->m_colorFrameDeltas[1] = (pRyjMegaBirthModel->m_directionTail).x;
    particleColor->m_colorFrameDeltas[2] = (pRyjMegaBirthModel->m_directionTail).y;
    particleColor->m_colorFrameDeltas[3] = (pRyjMegaBirthModel->m_directionTail).z;
  }
  return;
}

