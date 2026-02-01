// Function: calc__FP13VRyjMegaBirthP13PRyjMegaBirthP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
// Entry: 80082cc8
// Size: 936 bytes

void calc__FP13VRyjMegaBirthP13PRyjMegaBirthP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
               (VRyjMegaBirth *vRyjMegaBirth,PRyjMegaBirth *pRyjMegaBirth,
               _PARTICLE_DATA *particleData,VColor *vColor,_PARTICLE_COLOR *particleColor)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  Vec VStack_38;
  undefined8 local_28;
  
  uVar6 = (uint)vColor->m_alpha;
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
    particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
    particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
    particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
    particleColor->m_colorFrameDeltas[0] =
         particleColor->m_colorFrameDeltas[0] + pRyjMegaBirth->m_colorDeltaAdd[0];
    particleColor->m_colorFrameDeltas[1] =
         particleColor->m_colorFrameDeltas[1] + pRyjMegaBirth->m_colorDeltaAdd[1];
    particleColor->m_colorFrameDeltas[2] =
         particleColor->m_colorFrameDeltas[2] + pRyjMegaBirth->m_colorDeltaAdd[2];
    particleColor->m_colorFrameDeltas[3] =
         particleColor->m_colorFrameDeltas[3] + pRyjMegaBirth->m_colorDeltaAdd[3];
    local_28 = (double)(longlong)(int)particleColor->m_color[3];
    uVar6 = (uint)vColor->m_alpha + (int)particleColor->m_color[3];
    if (0xff < (int)uVar6) {
      uVar6 = 0xff;
    }
  }
  (particleData->m_matrix).value[2][2] =
       (particleData->m_matrix).value[2][2] + (particleData->m_matrix).value[2][3];
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 3) & 0x10) == 0) {
    (particleData->m_matrix).value[2][3] =
         (particleData->m_matrix).value[2][3] + (pRyjMegaBirth->field26_0x90).z;
    fVar1 = FLOAT_8033045c;
    fVar2 = FLOAT_80330458;
  }
  else {
    (particleData->m_matrix).value[2][3] =
         (particleData->m_matrix).value[2][3] +
         (pRyjMegaBirth->field26_0x90).z + (particleData->m_directionTail).x;
    fVar1 = FLOAT_8033045c;
    fVar2 = FLOAT_80330458;
  }
  while (fVar4 = FLOAT_80330460, fVar3 = FLOAT_80330458,
        fVar1 <= (particleData->m_matrix).value[2][2]) {
    (particleData->m_matrix).value[2][2] = (particleData->m_matrix).value[2][2] - fVar2;
  }
  while ((particleData->m_matrix).value[2][2] < fVar4) {
    (particleData->m_matrix).value[2][2] = (particleData->m_matrix).value[2][2] + fVar3;
  }
  (particleData->m_directionTail).y =
       (particleData->m_directionTail).y + particleData->m_colorDeltaAdd[0];
  (particleData->m_directionTail).z =
       (particleData->m_directionTail).z + particleData->m_colorDeltaAdd[1];
  if ((*(byte *)((int)&(pRyjMegaBirth->m_baseDirection).x + 2) & 0x10) == 0) {
    particleData->m_colorDeltaAdd[0] =
         particleData->m_colorDeltaAdd[0] + (pRyjMegaBirth->m_angleVelocity).x;
    particleData->m_colorDeltaAdd[1] =
         particleData->m_colorDeltaAdd[1] + (pRyjMegaBirth->m_angleVelocity).y;
  }
  else {
    particleData->m_colorDeltaAdd[0] =
         particleData->m_colorDeltaAdd[0] +
         (pRyjMegaBirth->m_angleVelocity).x + particleData->m_colorDeltaAdd[2];
    particleData->m_colorDeltaAdd[1] =
         particleData->m_colorDeltaAdd[1] +
         (pRyjMegaBirth->m_angleVelocity).y + particleData->m_colorDeltaAdd[3];
  }
  particleData->m_sizeStart = particleData->m_sizeStart + pRyjMegaBirth->m_clampMaxYStep;
  if (*(char *)((int)&(pRyjMegaBirth->m_baseDirection).y + 2) == '\0') {
    if ((pRyjMegaBirth->m_clampMinY <= FLOAT_80330448) ||
       (FLOAT_80330448 <= pRyjMegaBirth->m_clampMaxYStep)) {
      if ((pRyjMegaBirth->m_clampMinY < FLOAT_80330448) &&
         ((FLOAT_80330448 < pRyjMegaBirth->m_clampMaxYStep &&
          (FLOAT_80330448 < particleData->m_sizeStart)))) {
        particleData->m_sizeStart = FLOAT_80330448;
      }
    }
    else if (particleData->m_sizeStart < FLOAT_80330448) {
      particleData->m_sizeStart = FLOAT_80330448;
    }
  }
  particleData->m_sizeVal = particleData->m_sizeVal + pRyjMegaBirth->m_accelerationZ;
  PSVECScale(particleData->m_sizeStart,(Vec *)((particleData->m_matrix).value + 1),&VStack_38);
  PSVECAdd(&VStack_38,(Vec *)particleData,(Vec *)particleData);
  PSVECScale(particleData->m_sizeVal,&vRyjMegaBirth->m_accelerationAxis,&VStack_38);
  PSVECAdd((Vec *)particleData,&VStack_38,(Vec *)particleData);
  if (*(short *)((int)(pRyjMegaBirth->m_matrix).value[2] + 6) != 0) {
    *(short *)((int)(particleData->m_matrix).value[2] + 2) =
         *(short *)((int)(particleData->m_matrix).value[2] + 2) + -1;
  }
  particleData->field_0x58 = particleData->field_0x58 + '\x01';
  uVar5 = (uint)(byte)particleData->field_0x59;
  if ((uVar5 != 0) && ((byte)particleData->field_0x58 <= uVar5)) {
    local_28 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    particleData->m_speedRandRange =
         particleData->m_speedRandRange -
         (float)(local_28 - DOUBLE_80330450) /
         (float)((double)CONCAT44(0x43300000,uVar5) - DOUBLE_80330468);
  }
  if (((byte)particleData->field_0x5a != 0) &&
     (*(ushort *)((int)(particleData->m_matrix).value[2] + 2) <=
      (ushort)(byte)particleData->field_0x5a)) {
    local_28 = (double)CONCAT44(0x43300000,
                                (uint)*(byte *)((int)(pRyjMegaBirth->m_matrix).value[2] + 9));
    particleData->m_speedRandRange =
         particleData->m_speedRandRange +
         (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DOUBLE_80330450) /
         (float)(local_28 - DOUBLE_80330468);
  }
  return;
}

