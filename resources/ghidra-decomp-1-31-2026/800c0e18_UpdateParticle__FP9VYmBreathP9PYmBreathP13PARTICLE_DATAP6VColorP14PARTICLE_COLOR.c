// Function: UpdateParticle__FP9VYmBreathP9PYmBreathP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR
// Entry: 800c0e18
// Size: 884 bytes

void UpdateParticle__FP9VYmBreathP9PYmBreathP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR
               (undefined4 param_1,int param_2,Vec *param_3,VColor *vColor,
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
         particleColor->m_colorFrameDeltas[0] + *(float *)(param_2 + 0x3c);
    particleColor->m_colorFrameDeltas[1] =
         particleColor->m_colorFrameDeltas[1] + *(float *)(param_2 + 0x40);
    particleColor->m_colorFrameDeltas[2] =
         particleColor->m_colorFrameDeltas[2] + *(float *)(param_2 + 0x44);
    particleColor->m_colorFrameDeltas[3] =
         particleColor->m_colorFrameDeltas[3] + *(float *)(param_2 + 0x48);
    local_28 = (double)(longlong)(int)particleColor->m_color[3];
    uVar6 = (uint)vColor->m_alpha + (int)particleColor->m_color[3];
    if (0xff < (int)uVar6) {
      uVar6 = 0xff;
    }
  }
  param_3[3].y = param_3[3].y + param_3[3].z;
  if ((*(byte *)(param_2 + 0xc2) & 0x10) == 0) {
    param_3[3].z = param_3[3].z + *(float *)(param_2 + 0x98);
    fVar2 = FLOAT_80330c98;
    fVar3 = FLOAT_80330c94;
  }
  else {
    param_3[3].z = param_3[3].z + *(float *)(param_2 + 0x98) + param_3[4].x;
    fVar2 = FLOAT_80330c98;
    fVar3 = FLOAT_80330c94;
  }
  while (fVar5 = FLOAT_80330c9c, fVar4 = FLOAT_80330c94, fVar2 <= param_3[3].y) {
    param_3[3].y = param_3[3].y - fVar3;
  }
  while (param_3[3].y < fVar5) {
    param_3[3].y = param_3[3].y + fVar4;
  }
  param_3[4].y = param_3[4].y + param_3[5].x;
  param_3[4].z = param_3[4].z + param_3[5].y;
  if ((*(byte *)(param_2 + 0xc1) & 0x10) == 0) {
    param_3[5].x = param_3[5].x + *(float *)(param_2 + 0x70);
    param_3[5].y = param_3[5].y + *(float *)(param_2 + 0x74);
  }
  else {
    param_3[5].x = param_3[5].x + *(float *)(param_2 + 0x70) + param_3[5].z;
    param_3[5].y = param_3[5].y + *(float *)(param_2 + 0x74) + param_3[6].x;
  }
  param_3[6].z = param_3[6].z + *(float *)(param_2 + 0xa4);
  if (*(char *)(param_2 + 200) == '\0') {
    if ((*(float *)(param_2 + 0xa0) <= FLOAT_80330c80) ||
       (FLOAT_80330c80 <= *(float *)(param_2 + 0xa4))) {
      if ((*(float *)(param_2 + 0xa0) < FLOAT_80330c80) &&
         ((FLOAT_80330c80 < *(float *)(param_2 + 0xa4) && (FLOAT_80330c80 < param_3[6].z)))) {
        param_3[6].z = FLOAT_80330c80;
      }
    }
    else if (param_3[6].z < FLOAT_80330c80) {
      param_3[6].z = FLOAT_80330c80;
    }
  }
  PSVECScale(param_3[6].z,param_3 + 1,&VStack_38);
  PSVECAdd(&VStack_38,param_3,param_3);
  if (*(short *)(param_2 + 0x24) != 0) {
    *(short *)&param_3[2].z = *(short *)&param_3[2].z + -1;
  }
  *(char *)&param_3[7].x = *(char *)&param_3[7].x + '\x01';
  cVar1 = *(char *)&param_3[3].x;
  if ((cVar1 != '\0') && ((int)(uint)*(byte *)&param_3[7].x <= (int)cVar1)) {
    local_28 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    param_3[6].y = param_3[6].y -
                   (float)(local_28 - DOUBLE_80330c88) /
                   (float)((double)CONCAT44(0x43300000,(int)cVar1 ^ 0x80000000) - DOUBLE_80330c88);
  }
  cVar1 = *(char *)((int)&param_3[3].x + 1);
  if ((cVar1 != '\0') && ((int)*(short *)&param_3[2].z <= (int)cVar1)) {
    local_28 = (double)CONCAT44(0x43300000,(uint)*(byte *)(param_2 + 0x27));
    param_3[6].y = param_3[6].y +
                   (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DOUBLE_80330c88) /
                   (float)(local_28 - DOUBLE_80330ca0);
  }
  return;
}

