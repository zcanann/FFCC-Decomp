// Function: calc_particle__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColor
// Entry: 80082b10
// Size: 440 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc_particle__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColor
               (_pppPObject *pppPObject,VRyjMegaBirth *vRyjMegaBirth,PRyjMegaBirth *pRyjMegaBirth,
               VColor *vColor)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  _PARTICLE_COLOR *particleColor;
  PARTICLE_WMAT *particleWMat;
  _PARTICLE_DATA *particleData;
  
  iVar6 = 0;
  particleData = (_PARTICLE_DATA *)vRyjMegaBirth->m_particleBlock;
  particleWMat = vRyjMegaBirth->m_worldMatrixBlock;
  particleColor = vRyjMegaBirth->m_colorBlock;
  iVar7 = vRyjMegaBirth->m_numParticles;
  if ((DAT_8032ed70 == 0) && ((pRyjMegaBirth->m_matrix).value[0][1] != 9.18341e-41)) {
    vRyjMegaBirth->m_emitTimer = vRyjMegaBirth->m_emitTimer + 1;
    for (iVar5 = 0; iVar5 < iVar7; iVar5 = iVar5 + 1) {
      if (*(short *)((int)(particleData->m_matrix).value[2] + 2) == 0) {
        if ((*(ushort *)((pRyjMegaBirth->m_matrix).value[2] + 1) <= vRyjMegaBirth->m_emitTimer) &&
           (iVar6 < (int)(uint)*(ushort *)((int)(pRyjMegaBirth->m_matrix).value[2] + 2))) {
          birth__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
                    (pppPObject,vRyjMegaBirth,pRyjMegaBirth,vColor,particleData,particleWMat,
                     particleColor);
          iVar6 = iVar6 + 1;
        }
      }
      else {
        calc__FP13VRyjMegaBirthP13PRyjMegaBirthP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
                  (vRyjMegaBirth,pRyjMegaBirth,particleData,vColor,particleColor);
        uVar2 = *(ushort *)((int)(particleData->m_matrix).value[1] + 0xe);
        iVar3 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                          (int)(pRyjMegaBirth->m_matrix).value[0][1] * 4);
        *(ushort *)(particleData->m_matrix).value[2] = uVar2;
        iVar4 = iVar3 + (uint)uVar2 * 8 + 0x10;
        *(short *)((particleData->m_matrix).value[1] + 3) =
             *(short *)((particleData->m_matrix).value[1] + 3) +
             SUB42((pRyjMegaBirth->m_matrix).value[0][2],0);
        uVar2 = *(ushort *)((particleData->m_matrix).value[1] + 3);
        sVar1 = *(short *)(iVar4 + 2);
        if ((int)sVar1 <= (int)(uint)uVar2) {
          *(ushort *)((particleData->m_matrix).value[1] + 3) = uVar2 - sVar1;
          *(short *)((int)(particleData->m_matrix).value[1] + 0xe) =
               *(short *)((int)(particleData->m_matrix).value[1] + 0xe) + 1;
          if ((int)*(short *)(iVar3 + 6) <=
              (int)(uint)*(ushort *)((int)(particleData->m_matrix).value[1] + 0xe)) {
            if ((*(byte *)(iVar4 + 4) & 0x80) == 0) {
              *(undefined2 *)((particleData->m_matrix).value[1] + 3) = 0;
              *(short *)((int)(particleData->m_matrix).value[1] + 0xe) =
                   *(short *)((int)(particleData->m_matrix).value[1] + 0xe) + -1;
            }
            else {
              *(undefined2 *)((int)(particleData->m_matrix).value[1] + 0xe) = 0;
              *(undefined2 *)((particleData->m_matrix).value[1] + 3) = 0;
            }
          }
        }
      }
      if (particleWMat != (PARTICLE_WMAT *)0x0) {
        particleWMat = particleWMat + 1;
      }
      if (particleColor != (_PARTICLE_COLOR *)0x0) {
        particleColor = particleColor + 1;
      }
      particleData = (_PARTICLE_DATA *)&(particleData->m_speedScale).y;
    }
    if (0 < iVar6) {
      vRyjMegaBirth->m_emitTimer = 0;
    }
  }
  return;
}

