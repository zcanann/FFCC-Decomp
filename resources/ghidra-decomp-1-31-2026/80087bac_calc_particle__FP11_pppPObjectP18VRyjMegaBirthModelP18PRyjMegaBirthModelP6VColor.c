// Function: calc_particle__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColor
// Entry: 80087bac
// Size: 316 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc_particle__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColor
               (_pppPObject *pppPObject,VRyjMegaBirthModel *vRyjMegaBirthModel,
               PRyjMegaBirthModel *pRyjMegaBirthModel,VColor *vColor)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  _PARTICLE_COLOR *particleColor;
  PARTICLE_WMAT *particleWMat;
  _PARTICLE_DATA *particleData;
  
  iVar5 = 0;
  particleData = (_PARTICLE_DATA *)vRyjMegaBirthModel->field12_0xc;
  particleWMat = vRyjMegaBirthModel->field13_0x10;
  particleColor = vRyjMegaBirthModel->field14_0x14;
  iVar6 = vRyjMegaBirthModel->field15_0x18;
  if (DAT_8032ed70 == 0) {
    fVar1 = (pppPObject->m_localMatrix).value[0][3];
    fVar2 = (pppPObject->m_localMatrix).value[1][3];
    fVar3 = (pppPObject->m_localMatrix).value[2][3];
    (vRyjMegaBirthModel->field18_0x20).x = (vRyjMegaBirthModel->field19_0x2c).x;
    (vRyjMegaBirthModel->field18_0x20).y = (vRyjMegaBirthModel->field19_0x2c).y;
    (vRyjMegaBirthModel->field18_0x20).z = (vRyjMegaBirthModel->field19_0x2c).z;
    (vRyjMegaBirthModel->field19_0x2c).x = fVar1;
    (vRyjMegaBirthModel->field19_0x2c).y = fVar2;
    (vRyjMegaBirthModel->field19_0x2c).z = fVar3;
    vRyjMegaBirthModel->field16_0x1c = vRyjMegaBirthModel->field16_0x1c + 1;
    for (iVar4 = 0; iVar4 < iVar6; iVar4 = iVar4 + 1) {
      if (*(short *)&(particleData->m_directionTail).x == 0) {
        if ((*(ushort *)((pRyjMegaBirthModel->m_matrix).value[2] + 1) <=
             vRyjMegaBirthModel->field16_0x1c) &&
           (iVar5 < (int)(uint)*(ushort *)((int)(pRyjMegaBirthModel->m_matrix).value[2] + 2))) {
          birth__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
                    (pppPObject,vRyjMegaBirthModel,pRyjMegaBirthModel,vColor,particleData,
                     particleWMat,particleColor);
          iVar5 = iVar5 + 1;
        }
      }
      else {
        calc__FP11_pppPObjectP18VRyjMegaBirthModelP18PRyjMegaBirthModelP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
                  (pppPObject,vRyjMegaBirthModel,pRyjMegaBirthModel,particleData,vColor,
                   particleColor);
      }
      if (particleWMat != (PARTICLE_WMAT *)0x0) {
        particleWMat = particleWMat + 1;
      }
      if (particleColor != (_PARTICLE_COLOR *)0x0) {
        particleColor = particleColor + 1;
      }
      particleData = (_PARTICLE_DATA *)&particleData->field31_0xa0;
    }
    if (0 < iVar5) {
      vRyjMegaBirthModel->field16_0x1c = 0;
    }
  }
  return;
}

