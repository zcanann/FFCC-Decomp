// Function: pppFrameYmMegaBirthShpTail3
// Entry: 8008d3a4
// Size: 1620 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMegaBirthShpTail3
               (pppYmMegaBirthShpTail3 *pppYmMegaBirthShpTail3,PYmMegaBirthShpTail3 *param_2,
               int param_3)

{
  bool bVar1;
  int iVar2;
  _PARTICLE_DATA *p_Var3;
  PARTICLE_WMAT *pPVar4;
  _PARTICLE_COLOR *particleColor;
  int iVar5;
  uint uVar6;
  VYmMegaBirthShpTail3 *vYmMegaBirthShpTail3;
  float local_88;
  float local_84;
  float local_80;
  Vec local_7c;
  Vec local_70;
  Vec local_64;
  pppFMATRIX local_58;
  
  iVar2 = *(int *)(*(int *)(param_3 + 0xc) + 4);
  vYmMegaBirthShpTail3 =
       (VYmMegaBirthShpTail3 *)
       ((int)(&pppYmMegaBirthShpTail3->field0_0x0 + 2) + *(int *)(*(int *)(param_3 + 0xc) + 8));
  if (vYmMegaBirthShpTail3->m_particles == (_PARTICLE_DATA *)0x0) {
    vYmMegaBirthShpTail3->m_maxParticles =
         (uint)*(ushort *)((int)(param_2->m_matrix).value[0] + 0xe);
    p_Var3 = (_PARTICLE_DATA *)
             pppMemAlloc__FUlPQ27CMemory6CStagePci
                       (vYmMegaBirthShpTail3->m_maxParticles * 0x1f8,pppEnvStPtr->m_stagePtr,
                        s_pppYmMegaBirthShpTail3_cpp_801d9c88,0x2db);
    vYmMegaBirthShpTail3->m_particles = p_Var3;
    if (vYmMegaBirthShpTail3->m_particles != (_PARTICLE_DATA *)0x0) {
      memset(vYmMegaBirthShpTail3->m_particles,0,vYmMegaBirthShpTail3->m_maxParticles * 0x1f8);
    }
    pPVar4 = (PARTICLE_WMAT *)
             pppMemAlloc__FUlPQ27CMemory6CStagePci
                       (vYmMegaBirthShpTail3->m_maxParticles * 0x30,pppEnvStPtr->m_stagePtr,
                        s_pppYmMegaBirthShpTail3_cpp_801d9c88,0x2e3);
    vYmMegaBirthShpTail3->m_wmats = pPVar4;
    if (vYmMegaBirthShpTail3->m_wmats != (PARTICLE_WMAT *)0x0) {
      memset(vYmMegaBirthShpTail3->m_wmats,0,vYmMegaBirthShpTail3->m_maxParticles * 0x30);
    }
    (vYmMegaBirthShpTail3->m_tailScaleDirection).x = (param_2->m_directionTail).x;
    (vYmMegaBirthShpTail3->m_tailScaleDirection).y = (param_2->m_directionTail).y;
    (vYmMegaBirthShpTail3->m_tailScaleDirection).z = (param_2->m_directionTail).z;
    local_88 = (vYmMegaBirthShpTail3->m_tailScaleDirection).x;
    local_84 = (vYmMegaBirthShpTail3->m_tailScaleDirection).y;
    local_80 = (vYmMegaBirthShpTail3->m_tailScaleDirection).z;
    pppNormalize__FR3Vec3Vec(&vYmMegaBirthShpTail3->m_tailScaleDirection,&local_88);
  }
  if (vYmMegaBirthShpTail3->m_particles == (_PARTICLE_DATA *)0x0) {
    bVar1 = false;
  }
  else if (vYmMegaBirthShpTail3->m_wmats == (PARTICLE_WMAT *)0x0) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] =
         *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2);
    *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] =
         *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] +
         *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1];
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 10);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2);
    *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 1) =
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 1) +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 3);
    *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 1) =
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 1) +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 1);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 6) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 6) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 0xe);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 6) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 6) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 6);
    *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] =
         *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2);
    *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) =
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) +
         *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2];
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 10);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 10) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 10) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2);
    *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 1) =
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 1) +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 3);
    *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 3) =
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 3) +
         *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 1);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 6) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 6) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 0xe);
    *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 0xe) =
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 0xe) +
         *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 6);
    if ((float)(pppYmMegaBirthShpTail3->field0_0x0).m_graphId == (param_2->m_matrix).value[0][0]) {
      *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] =
           *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] +
           *(short *)&(param_2->m_angleVelocity).z;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) +
           *(short *)((int)&(param_2->m_angleVelocity).z + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 1) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 1) +
           *(short *)&param_2->unk6;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 6) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 6) +
           *(short *)((int)&param_2->unk6 + 2);
      *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] =
           *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] +
           *(short *)&param_2->m_randomRotationRangeZ;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) +
           *(short *)((int)&param_2->m_randomRotationRangeZ + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 1) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 1) +
           *(short *)&param_2->field22_0x8c;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 6) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 6) +
           *(short *)&param_2->field_0x8e;
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 2) +
           *(short *)&(param_2->field26_0x90).x;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 10) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 10) +
           *(short *)((int)&(param_2->field26_0x90).x + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 3) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 3) +
           *(short *)&(param_2->field26_0x90).y;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 0xe) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[1] + 0xe) +
           *(short *)((int)&(param_2->field26_0x90).y + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 2) +
           *(short *)&param_2->m_randomRotationRangeX;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 10) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 10) +
           *(short *)((int)&param_2->m_randomRotationRangeX + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 3) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 3) +
           *(short *)&param_2->m_randomRotationRangeY;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 0xe) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[0] + 0xe) +
           *(short *)((int)&param_2->m_randomRotationRangeY + 2);
      *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] =
           *(short *)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] +
           *(short *)&(param_2->field26_0x90).z;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) +
           *(short *)((int)&(param_2->field26_0x90).z + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 1) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 1) +
           *(short *)&param_2->field_0x9c;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 6) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 6) +
           *(short *)&param_2->field_0x9e;
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 2) +
           *(short *)&(param_2->field31_0xa0).x;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 10) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 10) +
           *(short *)((int)&(param_2->field31_0xa0).x + 2);
      *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 3) =
           *(short *)(vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 3) +
           *(short *)&(param_2->field31_0xa0).y;
      *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 0xe) =
           *(short *)((int)vYmMegaBirthShpTail3[1].m_emitterMatrix.value[2] + 0xe) +
           *(short *)((int)&(param_2->field31_0xa0).y + 2);
    }
    switch(*(undefined *)((param_2->m_matrix).value[1] + 2)) {
    default:
      local_58.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
      local_58.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
      local_58.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
      local_58.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
      local_58.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
      local_58.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
      local_58.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
      local_58.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
      local_58.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
      local_58.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
      local_58.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
      local_58.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
      pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX((pppFMATRIX *)vYmMegaBirthShpTail3,&local_58);
      break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
      PSMTXIdentity((Mtx *)vYmMegaBirthShpTail3);
      local_64.x = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][0];
      local_64.y = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][0];
      local_64.z = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][0];
      PSVECScale((pppMngStPtr->m_scale).x,&local_64,&local_64);
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][0] = local_64.x;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][0] = local_64.y;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][0] = local_64.z;
      local_70.x = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][1];
      local_70.y = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][1];
      local_70.z = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][1];
      PSVECScale((pppMngStPtr->m_scale).x,&local_70,&local_70);
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][1] = local_70.x;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][1] = local_70.y;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][1] = local_70.z;
      local_7c.x = (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][2];
      local_7c.y = (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][2];
      local_7c.z = (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][2];
      PSVECScale((pppMngStPtr->m_scale).x,&local_7c,&local_7c);
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][2] = local_7c.x;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][2] = local_7c.y;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][2] = local_7c.z;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[0][3] = (pppMngStPtr->m_position).x;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[1][3] = (pppMngStPtr->m_position).y;
      (vYmMegaBirthShpTail3->m_emitterMatrix).value[2][3] = (pppMngStPtr->m_position).z;
    }
    iVar5 = 0;
    p_Var3 = vYmMegaBirthShpTail3->m_particles;
    pPVar4 = vYmMegaBirthShpTail3->m_wmats;
    particleColor = vYmMegaBirthShpTail3->m_colors;
    if ((DAT_8032ed70 == 0) && ((param_2->m_matrix).value[0][1] != 9.18341e-41)) {
      vYmMegaBirthShpTail3->m_lifeLimit = vYmMegaBirthShpTail3->m_lifeLimit + 1;
      for (uVar6 = 0; uVar6 < vYmMegaBirthShpTail3->m_maxParticles; uVar6 = uVar6 + 1) {
        if (*(short *)((int)(p_Var3->m_matrix).value[2] + 2) == 0) {
          if ((*(ushort *)((int)(param_2->m_matrix).value[1] + 2) <=
               vYmMegaBirthShpTail3->m_lifeLimit) &&
             (iVar5 < (int)(uint)*(ushort *)(param_2->m_matrix).value[1])) {
            birth__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
                      (&pppYmMegaBirthShpTail3->field0_0x0,vYmMegaBirthShpTail3,param_2,
                       (VColor *)((int)(&pppYmMegaBirthShpTail3->field0_0x0 + 2) + iVar2),p_Var3,
                       pPVar4,particleColor);
            iVar5 = iVar5 + 1;
          }
        }
        else {
          calc__FP11_pppPObjectP20VYmMegaBirthShpTail3P20PYmMegaBirthShpTail3P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
                    (&pppYmMegaBirthShpTail3->field0_0x0,vYmMegaBirthShpTail3,param_2,p_Var3,
                     (VColor *)((int)(&pppYmMegaBirthShpTail3->field0_0x0 + 2) + iVar2),
                     particleColor);
        }
        if (pPVar4 != (PARTICLE_WMAT *)0x0) {
          pPVar4 = pPVar4 + 1;
        }
        if (particleColor != (_PARTICLE_COLOR *)0x0) {
          particleColor = particleColor + 1;
        }
        p_Var3 = (_PARTICLE_DATA *)&p_Var3[1].m_velocityAcceleration.z;
      }
      if (0 < iVar5) {
        vYmMegaBirthShpTail3->m_lifeLimit = 0;
      }
    }
  }
  return;
}

