// Function: pppFrameYmMegaBirthShpTail2
// Entry: 8008b3f4
// Size: 1072 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMegaBirthShpTail2
               (pppYmMegaBirthShpTail2 *pppYmMegaBirthShpTail2,PYmMegaBirthShpTail2 *param_2,
               int param_3)

{
  bool bVar1;
  int iVar2;
  _PARTICLE_DATA *p_Var3;
  PARTICLE_WMAT *pPVar4;
  _PARTICLE_COLOR *p_Var5;
  int iVar6;
  uint uVar7;
  VYmMegaBirthShpTail2 *vYmMegaBirthShpTail2;
  float local_88;
  float local_84;
  float local_80;
  Vec local_7c;
  Vec local_70;
  Vec local_64;
  pppFMATRIX local_58;
  
  iVar2 = *(int *)(*(int *)(param_3 + 0xc) + 4);
  vYmMegaBirthShpTail2 =
       (VYmMegaBirthShpTail2 *)
       ((int)(&pppYmMegaBirthShpTail2->field0_0x0 + 2) + *(int *)(*(int *)(param_3 + 0xc) + 8));
  if (vYmMegaBirthShpTail2->m_particles == (_PARTICLE_DATA *)0x0) {
    vYmMegaBirthShpTail2->m_maxParticles =
         (uint)*(ushort *)((int)(param_2->m_matrix).value[0] + 0xe);
    p_Var3 = (_PARTICLE_DATA *)
             pppMemAlloc__FUlPQ27CMemory6CStagePci
                       (vYmMegaBirthShpTail2->m_maxParticles * 0x1b8,pppEnvStPtr->m_stagePtr,
                        s_pppYmMegaBirthShpTail2_cpp_801d9c68,0x30e);
    vYmMegaBirthShpTail2->m_particles = p_Var3;
    if (vYmMegaBirthShpTail2->m_particles != (_PARTICLE_DATA *)0x0) {
      memset(vYmMegaBirthShpTail2->m_particles,0,vYmMegaBirthShpTail2->m_maxParticles * 0x1b8);
    }
    pPVar4 = (PARTICLE_WMAT *)
             pppMemAlloc__FUlPQ27CMemory6CStagePci
                       (vYmMegaBirthShpTail2->m_maxParticles * 0x30,pppEnvStPtr->m_stagePtr,
                        s_pppYmMegaBirthShpTail2_cpp_801d9c68,0x316);
    vYmMegaBirthShpTail2->m_wmats = pPVar4;
    if (vYmMegaBirthShpTail2->m_wmats != (PARTICLE_WMAT *)0x0) {
      memset(vYmMegaBirthShpTail2->m_wmats,0,vYmMegaBirthShpTail2->m_maxParticles * 0x30);
    }
    if (param_2->field_0x69 != '\0') {
      p_Var5 = (_PARTICLE_COLOR *)
               pppMemAlloc__FUlPQ27CMemory6CStagePci
                         (vYmMegaBirthShpTail2->m_maxParticles << 5,pppEnvStPtr->m_stagePtr,
                          s_pppYmMegaBirthShpTail2_cpp_801d9c68,0x31e);
      vYmMegaBirthShpTail2->m_colors = p_Var5;
      if (vYmMegaBirthShpTail2->m_colors != (_PARTICLE_COLOR *)0x0) {
        memset(vYmMegaBirthShpTail2->m_colors,0,vYmMegaBirthShpTail2->m_maxParticles << 5);
      }
    }
    (vYmMegaBirthShpTail2->m_tailScaleDirection).x = (param_2->m_directionTail).x;
    (vYmMegaBirthShpTail2->m_tailScaleDirection).y = (param_2->m_directionTail).y;
    (vYmMegaBirthShpTail2->m_tailScaleDirection).z = (param_2->m_directionTail).z;
    local_88 = (vYmMegaBirthShpTail2->m_tailScaleDirection).x;
    local_84 = (vYmMegaBirthShpTail2->m_tailScaleDirection).y;
    local_80 = (vYmMegaBirthShpTail2->m_tailScaleDirection).z;
    pppNormalize__FR3Vec3Vec(&vYmMegaBirthShpTail2->m_tailScaleDirection,&local_88);
  }
  if (vYmMegaBirthShpTail2->m_particles == (_PARTICLE_DATA *)0x0) {
    bVar1 = false;
  }
  else if (vYmMegaBirthShpTail2->m_wmats == (PARTICLE_WMAT *)0x0) {
    bVar1 = false;
  }
  else if ((param_2->field_0x69 == '\0') ||
          (vYmMegaBirthShpTail2->m_colors != (_PARTICLE_COLOR *)0x0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
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
      pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX((pppFMATRIX *)vYmMegaBirthShpTail2,&local_58);
      break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
      PSMTXIdentity((Mtx *)vYmMegaBirthShpTail2);
      local_64.x = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][0];
      local_64.y = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][0];
      local_64.z = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][0];
      PSVECScale((pppMngStPtr->m_scale).x,&local_64,&local_64);
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][0] = local_64.x;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][0] = local_64.y;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][0] = local_64.z;
      local_70.x = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][1];
      local_70.y = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][1];
      local_70.z = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][1];
      PSVECScale((pppMngStPtr->m_scale).x,&local_70,&local_70);
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][1] = local_70.x;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][1] = local_70.y;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][1] = local_70.z;
      local_7c.x = (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][2];
      local_7c.y = (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][2];
      local_7c.z = (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][2];
      PSVECScale((pppMngStPtr->m_scale).x,&local_7c,&local_7c);
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][2] = local_7c.x;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][2] = local_7c.y;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][2] = local_7c.z;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[0][3] = (pppMngStPtr->m_position).x;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[1][3] = (pppMngStPtr->m_position).y;
      (vYmMegaBirthShpTail2->m_emitterMatrix).value[2][3] = (pppMngStPtr->m_position).z;
    }
    iVar6 = 0;
    p_Var3 = vYmMegaBirthShpTail2->m_particles;
    pPVar4 = vYmMegaBirthShpTail2->m_wmats;
    p_Var5 = vYmMegaBirthShpTail2->m_colors;
    if ((DAT_8032ed70 == 0) && ((param_2->m_matrix).value[0][1] != 9.18341e-41)) {
      vYmMegaBirthShpTail2->m_lifeLimit = vYmMegaBirthShpTail2->m_lifeLimit + 1;
      for (uVar7 = 0; uVar7 < vYmMegaBirthShpTail2->m_maxParticles; uVar7 = uVar7 + 1) {
        if (*(short *)((int)(p_Var3->m_matrix).value[2] + 2) == 0) {
          if ((*(ushort *)((int)(param_2->m_matrix).value[1] + 2) <=
               vYmMegaBirthShpTail2->m_lifeLimit) &&
             (iVar6 < (int)(uint)*(ushort *)(param_2->m_matrix).value[1])) {
            birth__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P6VColorP14_PARTICLE_DATAP14_PARTICLE_WMATP15_PARTICLE_COLOR
                      (&pppYmMegaBirthShpTail2->field0_0x0,vYmMegaBirthShpTail2,param_2,
                       (VColor *)((int)(&pppYmMegaBirthShpTail2->field0_0x0 + 2) + iVar2),p_Var3,
                       pPVar4,p_Var5);
            iVar6 = iVar6 + 1;
          }
        }
        else {
          calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
                    (&pppYmMegaBirthShpTail2->field0_0x0,vYmMegaBirthShpTail2,param_2,
                     (VColor *)p_Var3,
                     (_PARTICLE_COLOR *)((int)(&pppYmMegaBirthShpTail2->field0_0x0 + 2) + iVar2));
        }
        if (pPVar4 != (PARTICLE_WMAT *)0x0) {
          pPVar4 = pPVar4 + 1;
        }
        if (p_Var5 != (_PARTICLE_COLOR *)0x0) {
          p_Var5 = p_Var5 + 1;
        }
        p_Var3 = (_PARTICLE_DATA *)&p_Var3[1].m_angleVelocity.z;
      }
      if (0 < iVar6) {
        vYmMegaBirthShpTail2->m_lifeLimit = 0;
      }
    }
  }
  return;
}

