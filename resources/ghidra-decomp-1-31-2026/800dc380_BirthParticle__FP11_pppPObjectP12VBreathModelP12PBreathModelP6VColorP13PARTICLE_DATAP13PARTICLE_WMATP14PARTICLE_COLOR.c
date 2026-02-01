// Function: BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR
// Entry: 800dc380
// Size: 1568 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR
               (_pppPObject *pppPObject,Mtx *param_2,int param_3,VColor *vColor,Mtx *param_5,
               PARTICLE_WMAT *param_6,int param_7)

{
  float fVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  Vec *pVVar6;
  double dVar7;
  Vec local_a8;
  Vec local_9c;
  Mtx MStack_90;
  Mtx MStack_60;
  undefined4 local_30;
  uint uStack_2c;
  
  memset(param_5,0,0x98);
  if (param_6 != (PARTICLE_WMAT *)0x0) {
    memset(param_6,0,0x30);
  }
  if (param_7 != 0) {
    memset(param_7,0,0x20);
  }
  RandF__5CMathFv(&Math);
  RandF__5CMathFv(&Math);
  RandF__5CMathFv(&Math);
  if (*(char *)(param_3 + 0x22) != '\0') {
    uStack_2c = (uint)vColor->m_alpha;
    local_30 = 0x43300000;
    param_5[2].value[2][2] = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80330f90);
    *(undefined *)(param_5[1].value[2] + 1) = *(undefined *)(param_3 + 0x22);
  }
  if (*(char *)(param_3 + 0x23) != '\0') {
    *(char *)((int)param_5[1].value[2] + 5) = *(char *)(param_3 + 0x23);
  }
  param_5[1].value[2][2] = *(float *)(param_3 + 0x90);
  param_5[1].value[2][3] = *(float *)(param_3 + 0x94);
  if (*(char *)(param_3 + 0xc1) != '\0') {
    dVar7 = (double)RandF__5CMathFv(&Math);
    param_5[2].value[0][0] = (float)((double)*(float *)(param_3 + 0x9c) * dVar7);
    bVar2 = *(byte *)(param_3 + 0xc1);
    if (((bVar2 & 1) == 0) || ((bVar2 & 2) == 0)) {
      if ((bVar2 & 2) != 0) {
        param_5[2].value[0][0] = param_5[2].value[0][0] * FLOAT_80330f80;
      }
    }
    else {
      dVar7 = (double)RandF__5CMathFv(&Math);
      if (DOUBLE_80330f98 < dVar7) {
        param_5[2].value[0][0] = param_5[2].value[0][0] * FLOAT_80330f80;
      }
    }
  }
  if ((*(byte *)(param_3 + 0xc1) & 4) != 0) {
    param_5[1].value[2][2] = param_5[1].value[2][2] + param_5[2].value[0][0];
  }
  fVar1 = FLOAT_80330f88;
  fVar3 = FLOAT_80330f84;
  if ((*(byte *)(param_3 + 0xc1) & 8) != 0) {
    param_5[1].value[2][3] = param_5[1].value[2][3] + param_5[2].value[0][0];
    fVar1 = FLOAT_80330f88;
    fVar3 = FLOAT_80330f84;
  }
  while (fVar5 = FLOAT_80330f8c, fVar4 = FLOAT_80330f84, fVar1 <= param_5[1].value[2][2]) {
    param_5[1].value[2][2] = param_5[1].value[2][2] - fVar3;
  }
  while (param_5[1].value[2][2] < fVar5) {
    param_5[1].value[2][2] = param_5[1].value[2][2] + fVar4;
  }
  param_5[2].value[0][1] = *(float *)(param_3 + 0x50);
  param_5[2].value[0][2] = *(float *)(param_3 + 0x54);
  param_5[2].value[0][3] = *(float *)(param_3 + 0x58);
  param_5[2].value[1][0] = *(float *)(param_3 + 0x60);
  param_5[2].value[1][1] = *(float *)(param_3 + 100);
  param_5[2].value[1][2] = *(float *)(param_3 + 0x68);
  if (*(byte *)(param_3 + 0xc0) != 0) {
    if ((*(byte *)(param_3 + 0xc0) & 0x20) == 0) {
      dVar7 = (double)RandF__5CMathFv(&Math);
      param_5[2].value[1][3] = (float)((double)*(float *)(param_3 + 0x80) * dVar7);
      dVar7 = (double)RandF__5CMathFv(&Math);
      param_5[2].value[2][0] = (float)((double)*(float *)(param_3 + 0x84) * dVar7);
      dVar7 = (double)RandF__5CMathFv(&Math);
      param_5[2].value[2][1] = (float)((double)*(float *)(param_3 + 0x88) * dVar7);
      fVar1 = FLOAT_80330f80;
      bVar2 = *(byte *)(param_3 + 0xc0);
      if (((bVar2 & 1) == 0) || ((bVar2 & 2) == 0)) {
        if ((bVar2 & 2) != 0) {
          param_5[2].value[1][3] = param_5[2].value[1][3] * FLOAT_80330f80;
          param_5[2].value[2][0] = param_5[2].value[2][0] * fVar1;
          param_5[2].value[2][1] = param_5[2].value[2][1] * fVar1;
        }
      }
      else {
        dVar7 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330f98 < dVar7) {
          param_5[2].value[1][3] = param_5[2].value[1][3] * FLOAT_80330f80;
        }
        dVar7 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330f98 < dVar7) {
          param_5[2].value[2][0] = param_5[2].value[2][0] * FLOAT_80330f80;
        }
        dVar7 = (double)RandF__5CMathFv(&Math);
        if (DOUBLE_80330f98 < dVar7) {
          param_5[2].value[2][1] = param_5[2].value[2][1] * FLOAT_80330f80;
        }
      }
    }
    else {
      dVar7 = (double)RandF__5CMathFv(&Math);
      fVar1 = (float)((double)*(float *)(param_3 + 0x80) * dVar7);
      param_5[2].value[2][1] = fVar1;
      param_5[2].value[2][0] = fVar1;
      param_5[2].value[1][3] = fVar1;
      fVar1 = FLOAT_80330f80;
      bVar2 = *(byte *)(param_3 + 0xc0);
      if (((bVar2 & 1) == 0) || ((bVar2 & 2) == 0)) {
        if ((bVar2 & 2) != 0) {
          param_5[2].value[1][3] = param_5[2].value[1][3] * FLOAT_80330f80;
          param_5[2].value[2][0] = param_5[2].value[2][0] * fVar1;
          param_5[2].value[2][1] = param_5[2].value[2][1] * fVar1;
        }
      }
      else {
        dVar7 = (double)RandF__5CMathFv(&Math);
        fVar1 = FLOAT_80330f80;
        if (DOUBLE_80330f98 < dVar7) {
          param_5[2].value[1][3] = param_5[2].value[1][3] * FLOAT_80330f80;
          param_5[2].value[2][0] = param_5[2].value[2][0] * fVar1;
          param_5[2].value[2][1] = param_5[2].value[2][1] * fVar1;
        }
      }
    }
  }
  if ((*(byte *)(param_3 + 0xc0) & 4) != 0) {
    param_5[2].value[0][1] = param_5[2].value[0][1] + param_5[2].value[1][3];
    param_5[2].value[0][2] = param_5[2].value[0][2] + param_5[2].value[2][0];
    param_5[2].value[0][3] = param_5[2].value[0][3] + param_5[2].value[2][1];
  }
  if ((*(byte *)(param_3 + 0xc0) & 8) != 0) {
    param_5[2].value[1][0] = param_5[2].value[1][0] + param_5[2].value[1][3];
    param_5[2].value[1][1] = param_5[2].value[1][1] + param_5[2].value[2][0];
    param_5[2].value[1][2] = param_5[2].value[1][2] + param_5[2].value[2][1];
  }
  fVar1 = FLOAT_80330f70;
  param_5[2].value[2][3] = *(float *)(param_3 + 0x14);
  if (fVar1 != *(float *)(param_3 + 0xa8)) {
    dVar7 = (double)RandF__5CMathFv(&Math);
    param_5[2].value[2][3] =
         param_5[2].value[2][3] +
         (float)((double)(float)((double)FLOAT_80330fa0 * (double)*(float *)(param_3 + 0xa8)) *
                 dVar7 - (double)*(float *)(param_3 + 0xa8));
  }
  if (*(short *)(param_3 + 0x20) == 0) {
    *(undefined2 *)param_5[1].value[2] = 0xffff;
  }
  else {
    *(short *)param_5[1].value[2] = *(short *)(param_3 + 0x20);
  }
  *(undefined *)param_5[3].value[0] = 0;
  PSMTXCopy(param_2,param_6);
  if (param_7 != 0) {
    *(undefined4 *)(param_7 + 0x10) = *(undefined4 *)(param_3 + 0x28);
    *(undefined4 *)(param_7 + 0x14) = *(undefined4 *)(param_3 + 0x2c);
    *(undefined4 *)(param_7 + 0x18) = *(undefined4 *)(param_3 + 0x30);
    *(undefined4 *)(param_7 + 0x1c) = *(undefined4 *)(param_3 + 0x34);
  }
  PSMTXCopy(param_6,&MStack_60);
  fVar3 = FLOAT_80330f80;
  fVar1 = FLOAT_80330f70;
  pVVar6 = (Vec *)(param_5[1].value[0] + 3);
  MStack_60.value[0][3] = FLOAT_80330f70;
  MStack_60.value[1][3] = FLOAT_80330f70;
  MStack_60.value[2][3] = FLOAT_80330f70;
  param_5[1].value[0][3] = FLOAT_80330f70;
  param_5[1].value[1][0] = fVar1;
  param_5[1].value[1][1] = fVar3;
  PSMTXMultVec(&MStack_60,pVVar6,pVVar6);
  pVVar6 = (Vec *)(param_5[1].value[0] + 3);
  PSVECNormalize(pVVar6,pVVar6);
  dVar7 = (double)RandF__5CMathFf((double)*(float *)(param_3 + 0xb0),&Math);
  local_9c.x = -(float)((double)*(float *)(param_3 + 0xb0) * (double)FLOAT_80330fa4 - dVar7);
  dVar7 = (double)RandF__5CMathFf((double)*(float *)(param_3 + 0xb4),&Math);
  local_9c.y = -(float)((double)*(float *)(param_3 + 0xb4) * (double)FLOAT_80330fa4 - dVar7);
  dVar7 = (double)RandF__5CMathFf((double)*(float *)(param_3 + 0xb8),&Math);
  local_9c.z = -(float)((double)*(float *)(param_3 + 0xb8) * (double)FLOAT_80330fa4 - dVar7);
  local_a8.x = param_6->value[0][3];
  local_a8.y = param_6->value[1][3];
  local_a8.z = param_6->value[2][3];
  PSVECAdd(&local_9c,&local_a8,&local_a8);
  param_6->value[0][3] = local_a8.x;
  param_6->value[1][3] = local_a8.y;
  param_6->value[2][3] = local_a8.z;
  PSMTXConcat(param_6,&pppPObject->m_localMatrix,param_5);
  PSMTXConcat(&ppvCameraMatrix0,param_5,&MStack_90);
  fVar3 = FLOAT_80330f80;
  fVar1 = FLOAT_80330f70;
  param_5[1].value[0][3] = FLOAT_80330f70;
  param_5[1].value[1][0] = fVar1;
  param_5[1].value[1][1] = fVar3;
  return;
}

