// Function: calc__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
// Entry: 80085a38
// Size: 1432 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VRyjMegaBirthModel *vRyjMegaBirthModel,
               PRyjMegaBirthModel *pRyjMegaBirthModel,_PARTICLE_DATA *particleData,VColor *vColor,
               _PARTICLE_COLOR *particleColor)

{
  float fVar1;
  uint uVar2;
  _PARTICLE_DATA *p_Var3;
  uint uVar4;
  int iVar5;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_40;
  float local_3c;
  float local_38;
  float local_30;
  float local_2c;
  float local_28;
  undefined8 local_20;
  
  uVar4 = (uint)vColor->m_alpha;
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
    particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
    particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
    particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
    particleColor->m_colorFrameDeltas[0] =
         particleColor->m_colorFrameDeltas[0] + pRyjMegaBirthModel->m_colorDeltaAdd[0];
    particleColor->m_colorFrameDeltas[1] =
         particleColor->m_colorFrameDeltas[1] + pRyjMegaBirthModel->m_colorDeltaAdd[1];
    particleColor->m_colorFrameDeltas[2] =
         particleColor->m_colorFrameDeltas[2] + pRyjMegaBirthModel->m_colorDeltaAdd[2];
    particleColor->m_colorFrameDeltas[3] =
         particleColor->m_colorFrameDeltas[3] + pRyjMegaBirthModel->m_colorDeltaAdd[3];
    local_20 = (double)(longlong)(int)particleColor->m_color[3];
    uVar4 = (uint)vColor->m_alpha + (int)particleColor->m_color[3];
    if (0xff < (int)uVar4) {
      uVar4 = 0xff;
    }
  }
  (particleData->m_directionTail).z =
       (float)((int)(particleData->m_directionTail).z + (int)particleData->m_colorDeltaAdd[2]);
  particleData->m_colorDeltaAdd[0] =
       (float)((int)particleData->m_colorDeltaAdd[0] + (int)particleData->m_colorDeltaAdd[3]);
  particleData->m_colorDeltaAdd[1] =
       (float)((int)particleData->m_colorDeltaAdd[1] + (int)particleData->m_sizeStart);
  if ((pRyjMegaBirthModel->m_flagsVelocityB & 0x10) == 0) {
    particleData->m_colorDeltaAdd[2] =
         (float)((int)particleData->m_colorDeltaAdd[2] +
                (int)(pRyjMegaBirthModel->m_angleVelocity).x);
    particleData->m_colorDeltaAdd[3] =
         (float)((int)particleData->m_colorDeltaAdd[3] +
                (int)(pRyjMegaBirthModel->m_angleVelocity).y);
    particleData->m_sizeStart =
         (float)((int)particleData->m_sizeStart + (int)(pRyjMegaBirthModel->m_angleVelocity).z);
  }
  else {
    particleData->m_colorDeltaAdd[2] =
         (float)((int)(pRyjMegaBirthModel->m_angleVelocity).x +
                (int)particleData->m_sizeVal + (int)particleData->m_colorDeltaAdd[2]);
    particleData->m_colorDeltaAdd[3] =
         (float)((int)(pRyjMegaBirthModel->m_angleVelocity).y +
                (int)particleData->m_speedRandRange + (int)particleData->m_colorDeltaAdd[3]);
    particleData->m_sizeStart =
         (float)((int)(pRyjMegaBirthModel->m_angleVelocity).z +
                *(int *)&particleData->field_0x58 + (int)particleData->m_sizeStart);
  }
  iVar5 = 3;
  p_Var3 = particleData;
  do {
    fVar1 = (p_Var3->m_directionTail).z;
    if ((int)fVar1 < 0x8000) {
      if ((int)fVar1 < -0x8000) {
        while (0x7fff < (int)(p_Var3->m_directionTail).z) {
          (p_Var3->m_directionTail).z = (float)((int)(p_Var3->m_directionTail).z + 0x10000);
        }
      }
    }
    else {
      while (0x7fff < (int)(p_Var3->m_directionTail).z) {
        (p_Var3->m_directionTail).z = (float)((int)(p_Var3->m_directionTail).z + -0x10000);
      }
    }
    p_Var3 = (_PARTICLE_DATA *)((p_Var3->m_matrix).value[0] + 1);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  (particleData->m_speedScale).x =
       (particleData->m_speedScale).x + *(float *)&particleData->m_randType;
  (particleData->m_speedScale).y =
       (particleData->m_speedScale).y + *(float *)&particleData->m_tail2PathIndex;
  (particleData->m_speedScale).z =
       (particleData->m_speedScale).z + (particleData->m_angleVelocity).x;
  if ((pRyjMegaBirthModel->m_flagsVelocityA & 0x10) == 0) {
    *(float *)&particleData->m_randType =
         *(float *)&particleData->m_randType + (pRyjMegaBirthModel->m_velocityAcceleration).x;
    *(float *)&particleData->m_tail2PathIndex =
         *(float *)&particleData->m_tail2PathIndex + (pRyjMegaBirthModel->m_velocityAcceleration).y;
    (particleData->m_angleVelocity).x =
         (particleData->m_angleVelocity).x + (pRyjMegaBirthModel->m_velocityAcceleration).z;
  }
  else {
    *(float *)&particleData->m_randType =
         *(float *)&particleData->m_randType +
         (pRyjMegaBirthModel->m_velocityAcceleration).x + (particleData->m_angleVelocity).y;
    *(float *)&particleData->m_tail2PathIndex =
         *(float *)&particleData->m_tail2PathIndex +
         (pRyjMegaBirthModel->m_velocityAcceleration).y + (particleData->m_angleVelocity).z;
    (particleData->m_angleVelocity).x =
         (particleData->m_angleVelocity).x +
         (pRyjMegaBirthModel->m_velocityAcceleration).z + (float)particleData->unk6;
  }
  particleData->m_randomRotationRangeX =
       (int32_t)((float)particleData->m_randomRotationRangeX + pRyjMegaBirthModel->m_heightStep);
  if (pRyjMegaBirthModel->m_flagsHeight == '\0') {
    if ((pRyjMegaBirthModel->m_heightMin <= FLOAT_80330498) ||
       (FLOAT_80330498 <= pRyjMegaBirthModel->m_heightStep)) {
      if ((pRyjMegaBirthModel->m_heightMin < FLOAT_80330498) &&
         ((FLOAT_80330498 < pRyjMegaBirthModel->m_heightStep &&
          (FLOAT_80330498 < (float)particleData->m_randomRotationRangeX)))) {
        particleData->m_randomRotationRangeX = (int32_t)FLOAT_80330498;
      }
    }
    else if ((float)particleData->m_randomRotationRangeX < FLOAT_80330498) {
      particleData->m_randomRotationRangeX = (int32_t)FLOAT_80330498;
    }
  }
  particleData->m_randomRotationRangeY =
       (int32_t)((float)particleData->m_randomRotationRangeY + pRyjMegaBirthModel->m_extraOffset);
  local_5c = (particleData->m_matrix).value[0][1];
  local_58 = (particleData->m_matrix).value[1][1];
  local_54 = (particleData->m_matrix).value[2][1];
  local_30 = local_5c;
  local_2c = local_58;
  local_28 = local_54;
  pppScaleVectorXYZ__FR3Vec3Vecf((float)particleData->m_randomRotationRangeX,&local_50,&local_5c);
  local_68 = (particleData->m_matrix).value[0][3];
  local_64 = (particleData->m_matrix).value[1][3];
  local_60 = (particleData->m_matrix).value[2][3];
  local_74 = local_50;
  local_70 = local_4c;
  local_6c = local_48;
  local_40 = local_68;
  local_3c = local_64;
  local_38 = local_60;
  pppAddVector__FR3Vec3Vec3Vec(&local_40,&local_68,&local_74);
  local_80 = *(undefined4 *)vRyjMegaBirthModel;
  local_7c = *(undefined4 *)&vRyjMegaBirthModel->field_0x4;
  local_78 = *(undefined4 *)&vRyjMegaBirthModel->field_0x8;
  pppScaleVectorXYZ__FR3Vec3Vecf((float)particleData->m_randomRotationRangeY,&local_50,&local_80);
  local_98 = local_50;
  local_94 = local_4c;
  local_90 = local_48;
  local_8c = local_40;
  local_88 = local_3c;
  local_84 = local_38;
  pppAddVector__FR3Vec3Vec3Vec(&local_40,&local_8c,&local_98);
  (particleData->m_matrix).value[0][3] = local_40;
  (particleData->m_matrix).value[1][3] = local_3c;
  (particleData->m_matrix).value[2][3] = local_38;
  particleData->m_randomRotationRangeZ =
       (int32_t)((float)particleData->m_randomRotationRangeZ + (particleData->field26_0x90).x);
  *(float *)&particleData->field22_0x8c =
       *(float *)&particleData->field22_0x8c + (particleData->field26_0x90).y;
  (particleData->field26_0x90).x =
       (particleData->field26_0x90).x + (pRyjMegaBirthModel->m_directionScale).x;
  (particleData->field26_0x90).y =
       (particleData->field26_0x90).y + *(float *)&pRyjMegaBirthModel->field_0xe4;
  if (*(short *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 6) != 0) {
    *(short *)&(particleData->m_directionTail).x = *(short *)&(particleData->m_directionTail).x + -1
    ;
  }
  particleData->field_0x9c = particleData->field_0x9c + '\x01';
  uVar2 = (uint)(byte)particleData->field_0x9d;
  if ((uVar2 != 0) && ((byte)particleData->field_0x9c <= uVar2)) {
    local_20 = (double)CONCAT44(0x43300000,uVar4 ^ 0x80000000);
    (particleData->field26_0x90).z =
         (particleData->field26_0x90).z -
         (float)(local_20 - DOUBLE_803304b0) /
         (float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_803304b8);
  }
  if (((byte)particleData->field_0x9e != 0) &&
     (*(ushort *)&(particleData->m_directionTail).x <= (ushort)(byte)particleData->field_0x9e)) {
    local_20 = (double)CONCAT44(0x43300000,
                                (uint)*(byte *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 9));
    (particleData->field26_0x90).z =
         (particleData->field26_0x90).z +
         (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DOUBLE_803304b0) /
         (float)(local_20 - DOUBLE_803304b8);
  }
  return;
}

