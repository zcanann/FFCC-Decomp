// Function: BirthParticle__FP11_pppPObjectP9VYmBreathP9PYmBreathP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR
// Entry: 800c118c
// Size: 1580 bytes

/* WARNING: Removing unreachable block (ram,0x800c179c) */
/* WARNING: Removing unreachable block (ram,0x800c1794) */
/* WARNING: Removing unreachable block (ram,0x800c11a4) */
/* WARNING: Removing unreachable block (ram,0x800c119c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void BirthParticle__FP11_pppPObjectP9VYmBreathP9PYmBreathP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR
               (_pppPObject *pppPObject,Mtx *param_2,int param_3,VColor *vColor,Vec *param_5,
               PARTICLE_WMAT *particleWMat,_PARTICLE_COLOR *particleColor)

{
  int iVar1;
  float fVar2;
  byte bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float local_e8;
  float local_e4;
  float local_e0;
  pppIVECTOR4 local_d8;
  int local_d0;
  Vec local_c8;
  pppFMATRIX pStack_b8;
  undefined8 local_88;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  longlong local_70;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  longlong local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined8 local_48;
  
  local_88 = (double)CONCAT44(0x43300000,(uint)*(byte *)(param_3 + 0x28));
  dVar9 = (double)(float)(local_88 - DOUBLE_80330ca0);
  dVar8 = (double)(float)((double)FLOAT_80330ca8 * dVar9);
  memset(param_5,0,0x60);
  if (particleWMat != (PARTICLE_WMAT *)0x0) {
    memset(particleWMat,0,0x30);
  }
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    memset(particleColor,0,0x20);
  }
  local_c8.x = FLOAT_80330c80;
  local_c8.y = FLOAT_80330c80;
  local_c8.z = FLOAT_80330c90;
  dVar7 = (double)RandF__5CMathFv(&Math);
  local_80 = 0x43300000;
  iVar1 = (int)(dVar8 * dVar7 - dVar9);
  local_88 = (double)(longlong)iVar1;
  uStack_7c = iVar1 << 0xf ^ 0x80000000;
  local_d8._0_4_ =
       (undefined4)
       ((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80330c88) / FLOAT_80330c98);
  local_78 = (longlong)(int)local_d8._0_4_;
  dVar7 = (double)RandF__5CMathFv(&Math);
  local_68 = 0x43300000;
  iVar1 = (int)(dVar8 * dVar7 - dVar9);
  local_70 = (longlong)iVar1;
  uStack_64 = iVar1 << 0xf ^ 0x80000000;
  local_d8._4_4_ =
       (undefined4)
       ((float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330c88) / FLOAT_80330c98);
  local_60 = (longlong)(int)local_d8._4_4_;
  dVar7 = (double)RandF__5CMathFv(&Math);
  local_50 = 0x43300000;
  iVar1 = (int)(dVar8 * dVar7 - dVar9);
  local_58 = (longlong)iVar1;
  uStack_4c = iVar1 << 0xf ^ 0x80000000;
  local_d0 = (int)((float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80330c88) /
                  FLOAT_80330c98);
  local_48 = (double)(longlong)local_d0;
  pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&pStack_b8,&local_d8);
  PSMTXMultVecSR(&pStack_b8,&local_c8,param_5 + 1);
  param_5[1].x = param_5[1].x * *(float *)(param_3 + 0xb0);
  param_5[1].y = param_5[1].y * *(float *)(param_3 + 0xb4);
  param_5[1].z = param_5[1].z * *(float *)(param_3 + 0xb8);
  local_e8 = param_5[1].x;
  local_e4 = param_5[1].y;
  local_e0 = param_5[1].z;
  pppNormalize__FR3Vec3Vec(param_5 + 1,&local_e8);
  if (FLOAT_80330c80 != *(float *)(param_3 + 0xac)) {
    PSVECScale(*(float *)(param_3 + 0xac),param_5 + 1,param_5);
  }
  if (*(char *)(param_3 + 0x26) != '\0') {
    local_48 = (double)CONCAT44(0x43300000,(uint)vColor->m_alpha);
    param_5[6].y = (float)(local_48 - DOUBLE_80330ca0);
    *(undefined *)&param_5[3].x = *(undefined *)(param_3 + 0x26);
  }
  if (*(char *)(param_3 + 0x27) != '\0') {
    *(char *)((int)&param_5[3].x + 1) = *(char *)(param_3 + 0x27);
  }
  param_5[3].y = *(float *)(param_3 + 0x90);
  param_5[3].z = *(float *)(param_3 + 0x94);
  if (*(char *)(param_3 + 0xc2) != '\0') {
    dVar8 = (double)RandF__5CMathFv(&Math);
    param_5[4].x = (float)((double)*(float *)(param_3 + 0x9c) * dVar8);
    bVar3 = *(byte *)(param_3 + 0xc2);
    if (((bVar3 & 1) == 0) || ((bVar3 & 2) == 0)) {
      if ((bVar3 & 2) != 0) {
        param_5[4].x = param_5[4].x * FLOAT_80330c90;
      }
    }
    else {
      dVar8 = (double)RandF__5CMathFv(&Math);
      if (DOUBLE_80330cb0 < dVar8) {
        param_5[4].x = param_5[4].x * FLOAT_80330c90;
      }
    }
  }
  if ((*(byte *)(param_3 + 0xc2) & 4) != 0) {
    param_5[3].y = param_5[3].y + param_5[4].x;
  }
  fVar2 = FLOAT_80330c98;
  fVar4 = FLOAT_80330c94;
  if ((*(byte *)(param_3 + 0xc2) & 8) != 0) {
    param_5[3].z = param_5[3].z + param_5[4].x;
    fVar2 = FLOAT_80330c98;
    fVar4 = FLOAT_80330c94;
  }
  while (fVar6 = FLOAT_80330c9c, fVar5 = FLOAT_80330c94, fVar2 <= param_5[3].y) {
    param_5[3].y = param_5[3].y - fVar4;
  }
  while (param_5[3].y < fVar6) {
    param_5[3].y = param_5[3].y + fVar5;
  }
  param_5[4].y = *(float *)(param_3 + 0x50);
  param_5[4].z = *(float *)(param_3 + 0x54);
  param_5[5].x = *(float *)(param_3 + 0x60);
  param_5[5].y = *(float *)(param_3 + 100);
  if (*(byte *)(param_3 + 0xc1) != 0) {
    if ((*(byte *)(param_3 + 0xc1) & 0x20) == 0) {
      dVar8 = (double)RandF__5CMathFv(&Math);
      param_5[5].z = (float)((double)*(float *)(param_3 + 0x80) * dVar8);
      dVar8 = (double)RandF__5CMathFv(&Math);
      param_5[6].x = (float)((double)*(float *)(param_3 + 0x84) * dVar8);
      fVar2 = FLOAT_80330c90;
      bVar3 = *(byte *)(param_3 + 0xc1);
      if (((bVar3 & 1) == 0) || ((bVar3 & 2) == 0)) {
        if ((bVar3 & 2) != 0) {
          param_5[5].z = param_5[5].z * FLOAT_80330c90;
          param_5[6].x = param_5[6].x * fVar2;
        }
      }
      else {
        dVar8 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330cb0 < dVar8) {
          param_5[5].z = param_5[5].z * FLOAT_80330c90;
        }
        dVar8 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330cb0 < dVar8) {
          param_5[6].x = param_5[6].x * FLOAT_80330c90;
        }
      }
    }
    else {
      dVar8 = (double)RandF__5CMathFv(&Math);
      fVar2 = (float)((double)*(float *)(param_3 + 0x80) * dVar8);
      param_5[6].x = fVar2;
      param_5[5].z = fVar2;
      fVar2 = FLOAT_80330c90;
      bVar3 = *(byte *)(param_3 + 0xc1);
      if (((bVar3 & 1) == 0) || ((bVar3 & 2) == 0)) {
        if ((bVar3 & 2) != 0) {
          param_5[5].z = param_5[5].z * FLOAT_80330c90;
          param_5[6].x = param_5[6].x * fVar2;
        }
      }
      else {
        dVar8 = (double)RandF__5CMathFv(&Math);
        fVar2 = FLOAT_80330c90;
        if (DOUBLE_80330cb0 < dVar8) {
          param_5[5].z = param_5[5].z * FLOAT_80330c90;
          param_5[6].x = param_5[6].x * fVar2;
        }
      }
    }
  }
  if ((*(byte *)(param_3 + 0xc1) & 4) != 0) {
    param_5[4].y = param_5[4].y + param_5[5].z;
    param_5[4].z = param_5[4].z + param_5[6].x;
  }
  if ((*(byte *)(param_3 + 0xc1) & 8) != 0) {
    param_5[5].x = param_5[5].x + param_5[5].z;
    param_5[5].y = param_5[5].y + param_5[6].x;
  }
  fVar2 = FLOAT_80330c80;
  param_5[6].z = *(float *)(param_3 + 0x18);
  if (fVar2 != *(float *)(param_3 + 0xa8)) {
    dVar8 = (double)RandF__5CMathFv(&Math);
    param_5[6].z = param_5[6].z +
                   (float)((double)(float)((double)FLOAT_80330ca8 *
                                          (double)*(float *)(param_3 + 0xa8)) * dVar8 -
                          (double)*(float *)(param_3 + 0xa8));
  }
  if (*(short *)(param_3 + 0x24) == 0) {
    *(undefined2 *)&param_5[2].z = 0xffff;
  }
  else {
    *(short *)&param_5[2].z = *(short *)(param_3 + 0x24);
  }
  *(undefined *)&param_5[7].x = 0;
  PSMTXCopy(param_2,particleWMat);
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_colorFrameDeltas[0] = *(float *)(param_3 + 0x2c);
    particleColor->m_colorFrameDeltas[1] = *(float *)(param_3 + 0x30);
    particleColor->m_colorFrameDeltas[2] = *(float *)(param_3 + 0x34);
    particleColor->m_colorFrameDeltas[3] = *(float *)(param_3 + 0x38);
  }
  return;
}

