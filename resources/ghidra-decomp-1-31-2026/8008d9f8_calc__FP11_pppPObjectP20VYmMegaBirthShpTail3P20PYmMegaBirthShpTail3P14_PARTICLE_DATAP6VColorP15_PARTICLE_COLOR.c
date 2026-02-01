// Function: calc__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
// Entry: 8008d9f8
// Size: 720 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VYmMegaBirthShpTail3 *vYmMegaBirthShpTail3,
               PYmMegaBirthShpTail3 *pYmMegaBirthShpTail3,_PARTICLE_DATA *particleData,
               VColor *vColor,_PARTICLE_COLOR *particleColor)

{
  float fVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined8 local_30;
  undefined4 local_28;
  uint uStack_24;
  
  uVar4 = (uint)vColor->m_alpha;
  if (particleColor != (_PARTICLE_COLOR *)0x0) {
    particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
    particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
    particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
    particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
    local_30 = (double)(longlong)(int)particleColor->m_color[3];
    uVar4 = (uint)vColor->m_alpha + (int)particleColor->m_color[3];
    if (0xff < (int)uVar4) {
      uVar4 = 0xff;
    }
  }
  (particleData->m_matrix).value[2][2] =
       (particleData->m_matrix).value[2][2] + pYmMegaBirthShpTail3->m_colorDeltaAdd[2];
  (particleData->m_matrix).value[2][3] =
       (particleData->m_matrix).value[2][3] + pYmMegaBirthShpTail3->m_sizeVal;
  local_4c = (particleData->m_matrix).value[1][0];
  local_48 = (particleData->m_matrix).value[1][1];
  local_44 = (particleData->m_matrix).value[1][2];
  pppScaleVectorXYZ__FR3Vec3Vecf((particleData->m_matrix).value[2][2],&local_40,&local_4c);
  local_64 = local_40;
  local_60 = local_3c;
  local_5c = local_38;
  local_58 = (particleData->m_matrix).value[0][0];
  local_54 = (particleData->m_matrix).value[0][1];
  local_50 = (particleData->m_matrix).value[0][2];
  pppAddVector__FR3Vec3Vec3Vec(particleData,&local_58,&local_64);
  local_70 = (vYmMegaBirthShpTail3->m_tailScaleDirection).x;
  local_6c = (vYmMegaBirthShpTail3->m_tailScaleDirection).y;
  local_68 = (vYmMegaBirthShpTail3->m_tailScaleDirection).z;
  pppScaleVectorXYZ__FR3Vec3Vecf((particleData->m_matrix).value[2][3],&local_40,&local_70);
  local_88 = local_40;
  local_84 = local_3c;
  local_80 = local_38;
  local_7c = (particleData->m_matrix).value[0][0];
  local_78 = (particleData->m_matrix).value[0][1];
  local_74 = (particleData->m_matrix).value[0][2];
  pppAddVector__FR3Vec3Vec3Vec(particleData,&local_7c,&local_88);
  if (*(short *)((pYmMegaBirthShpTail3->m_matrix).value[1] + 1) != 0) {
    *(short *)((int)(particleData->m_matrix).value[2] + 2) =
         *(short *)((int)(particleData->m_matrix).value[2] + 2) + -1;
  }
  *(char *)&(particleData->m_directionTail).y = *(char *)&(particleData->m_directionTail).y + '\x01'
  ;
  fVar1 = FLOAT_803305a4;
  uVar3 = (uint)*(byte *)((int)&(particleData->m_directionTail).y + 1);
  if ((uVar3 != 0) && (*(byte *)&(particleData->m_directionTail).y <= uVar3)) {
    local_30 = (double)CONCAT44(0x43300000,uVar4 ^ 0x80000000);
    local_28 = 0x43300000;
    (particleData->m_directionTail).x =
         (particleData->m_directionTail).x -
         (float)(local_30 - DOUBLE_803305b8) /
         (float)((double)CONCAT44(0x43300000,uVar3) - DOUBLE_803305c0);
    uStack_24 = uVar3;
    if ((particleData->m_directionTail).x < fVar1) {
      (particleData->m_directionTail).x = fVar1;
    }
  }
  fVar1 = FLOAT_803305b0;
  uVar2 = (ushort)*(byte *)((int)&(particleData->m_directionTail).y + 2);
  if ((uVar2 != 0) && (*(ushort *)((int)(particleData->m_matrix).value[2] + 2) <= uVar2)) {
    uStack_24 = uVar4 ^ 0x80000000;
    local_28 = 0x43300000;
    local_30 = (double)CONCAT44(0x43300000,
                                (uint)*(byte *)((int)(pYmMegaBirthShpTail3->m_matrix).value[1] + 7))
    ;
    (particleData->m_directionTail).x =
         (particleData->m_directionTail).x +
         (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_803305b8) /
         (float)(local_30 - DOUBLE_803305c0);
    if (fVar1 < (particleData->m_directionTail).x) {
      (particleData->m_directionTail).x = fVar1;
    }
  }
  if (*(char *)&(particleData->m_directionTail).z == '\0') {
    *(undefined *)&(particleData->m_directionTail).z =
         *(undefined *)((int)&(particleData->m_directionTail).y + 3);
  }
  *(char *)&(particleData->m_directionTail).z = *(char *)&(particleData->m_directionTail).z + -1;
  PSMTXMultVec(&pppPObject->m_localMatrix,(Vec *)particleData,
               (Vec *)(particleData->m_colorDeltaAdd +
                      (uint)*(byte *)&(particleData->m_directionTail).z * 3 + 0x11));
  return;
}

