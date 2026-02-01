// Function: UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR
// Entry: 800dbfd4
// Size: 940 bytes

void UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR
               (undefined4 param_1,int param_2,int param_3,VColor *vColor,
               _PARTICLE_COLOR *particleColor)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
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
         particleColor->m_colorFrameDeltas[0] + *(float *)(param_2 + 0x38);
    particleColor->m_colorFrameDeltas[1] =
         particleColor->m_colorFrameDeltas[1] + *(float *)(param_2 + 0x3c);
    particleColor->m_colorFrameDeltas[2] =
         particleColor->m_colorFrameDeltas[2] + *(float *)(param_2 + 0x40);
    particleColor->m_colorFrameDeltas[3] =
         particleColor->m_colorFrameDeltas[3] + *(float *)(param_2 + 0x44);
    local_28 = (double)(longlong)(int)particleColor->m_color[3];
    uVar6 = (uint)vColor->m_alpha + (int)particleColor->m_color[3];
    if (0xff < (int)uVar6) {
      uVar6 = 0xff;
    }
  }
  *(float *)(param_3 + 0x58) = *(float *)(param_3 + 0x58) + *(float *)(param_3 + 0x5c);
  if ((*(byte *)(param_2 + 0xc1) & 0x10) == 0) {
    *(float *)(param_3 + 0x5c) = *(float *)(param_3 + 0x5c) + *(float *)(param_2 + 0x98);
    fVar2 = FLOAT_80330f88;
    fVar3 = FLOAT_80330f84;
  }
  else {
    *(float *)(param_3 + 0x5c) =
         *(float *)(param_3 + 0x5c) + *(float *)(param_2 + 0x98) + *(float *)(param_3 + 0x60);
    fVar2 = FLOAT_80330f88;
    fVar3 = FLOAT_80330f84;
  }
  while (fVar5 = FLOAT_80330f8c, fVar4 = FLOAT_80330f84, fVar2 <= *(float *)(param_3 + 0x58)) {
    *(float *)(param_3 + 0x58) = *(float *)(param_3 + 0x58) - fVar3;
  }
  while (*(float *)(param_3 + 0x58) < fVar5) {
    *(float *)(param_3 + 0x58) = *(float *)(param_3 + 0x58) + fVar4;
  }
  *(float *)(param_3 + 100) = *(float *)(param_3 + 100) + *(float *)(param_3 + 0x70);
  *(float *)(param_3 + 0x68) = *(float *)(param_3 + 0x68) + *(float *)(param_3 + 0x74);
  *(float *)(param_3 + 0x6c) = *(float *)(param_3 + 0x6c) + *(float *)(param_3 + 0x78);
  if ((*(byte *)(param_2 + 0xc0) & 0x10) == 0) {
    *(float *)(param_3 + 0x70) = *(float *)(param_3 + 0x70) + *(float *)(param_2 + 0x70);
    *(float *)(param_3 + 0x74) = *(float *)(param_3 + 0x74) + *(float *)(param_2 + 0x74);
    *(float *)(param_3 + 0x78) = *(float *)(param_3 + 0x78) + *(float *)(param_2 + 0x78);
  }
  else {
    *(float *)(param_3 + 0x70) =
         *(float *)(param_3 + 0x70) + *(float *)(param_2 + 0x70) + *(float *)(param_3 + 0x7c);
    *(float *)(param_3 + 0x74) =
         *(float *)(param_3 + 0x74) + *(float *)(param_2 + 0x74) + *(float *)(param_3 + 0x80);
    *(float *)(param_3 + 0x78) =
         *(float *)(param_3 + 0x78) + *(float *)(param_2 + 0x78) + *(float *)(param_3 + 0x84);
  }
  *(float *)(param_3 + 0x8c) = *(float *)(param_3 + 0x8c) + *(float *)(param_2 + 0xa4);
  if (*(char *)(param_2 + 200) == '\0') {
    if ((*(float *)(param_2 + 0xa0) <= FLOAT_80330f70) ||
       (FLOAT_80330f70 <= *(float *)(param_2 + 0xa4))) {
      if ((*(float *)(param_2 + 0xa0) < FLOAT_80330f70) &&
         ((FLOAT_80330f70 < *(float *)(param_2 + 0xa4) &&
          (FLOAT_80330f70 < *(float *)(param_3 + 0x8c))))) {
        *(float *)(param_3 + 0x8c) = FLOAT_80330f70;
      }
    }
    else if (*(float *)(param_3 + 0x8c) < FLOAT_80330f70) {
      *(float *)(param_3 + 0x8c) = FLOAT_80330f70;
    }
  }
  PSVECScale(*(float *)(param_3 + 0x8c),(Vec *)(param_3 + 0x3c),&VStack_38);
  PSVECAdd(&VStack_38,(Vec *)(param_3 + 0x30),(Vec *)(param_3 + 0x30));
  if (*(short *)(param_2 + 0x20) != 0) {
    *(short *)(param_3 + 0x50) = *(short *)(param_3 + 0x50) + -1;
  }
  *(char *)(param_3 + 0x90) = *(char *)(param_3 + 0x90) + '\x01';
  cVar1 = *(char *)(param_3 + 0x54);
  if ((cVar1 != '\0') && ((int)(uint)*(byte *)(param_3 + 0x90) <= (int)cVar1)) {
    local_28 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    *(float *)(param_3 + 0x88) =
         *(float *)(param_3 + 0x88) -
         (float)(local_28 - DOUBLE_80330f78) /
         (float)((double)CONCAT44(0x43300000,(int)cVar1 ^ 0x80000000) - DOUBLE_80330f78);
  }
  if ((*(char *)(param_3 + 0x55) != '\0') &&
     ((int)*(short *)(param_3 + 0x50) <= (int)*(char *)(param_3 + 0x55))) {
    local_28 = (double)CONCAT44(0x43300000,(uint)*(byte *)(param_2 + 0x23));
    *(float *)(param_3 + 0x88) =
         *(float *)(param_3 + 0x88) +
         (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DOUBLE_80330f78) /
         (float)(local_28 - DOUBLE_80330f90);
  }
  return;
}

