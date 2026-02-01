// Function: pppRyjMegaBirth
// Entry: 80082894
// Size: 636 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirth(pppRyjMegaBirth *pppRyjMegaBirth,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  int iVar2;
  Vec *pVVar3;
  PARTICLE_WMAT *pPVar4;
  _PARTICLE_COLOR *p_Var5;
  VRyjMegaBirth *vRyjMegaBirth;
  
  iVar2 = param_3->m_serializedDataOffsets[1];
  vRyjMegaBirth =
       (VRyjMegaBirth *)
       ((int)(&pppRyjMegaBirth->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
  if (vRyjMegaBirth->m_particleBlock == (Vec *)0x0) {
    vRyjMegaBirth->m_numParticles = (uint)*(ushort *)(param_2->m_payload + 0xc);
    pVVar3 = (Vec *)pppMemAlloc__FUlPQ27CMemory6CStagePci
                              (vRyjMegaBirth->m_numParticles * 0x60,pppEnvStPtr->m_stagePtr,
                               s_pppRyjMegaBirth_cpp_801d9c00,0x262);
    vRyjMegaBirth->m_particleBlock = pVVar3;
    if (vRyjMegaBirth->m_particleBlock != (Vec *)0x0) {
      memset(vRyjMegaBirth->m_particleBlock,0,vRyjMegaBirth->m_numParticles * 0x60);
    }
    if ((param_2->m_payload[0xd8] == '\x01') || (param_2->m_payload[0xd8] == '\x02')) {
      pPVar4 = (PARTICLE_WMAT *)
               pppMemAlloc__FUlPQ27CMemory6CStagePci
                         (vRyjMegaBirth->m_numParticles * 0x30,pppEnvStPtr->m_stagePtr,
                          s_pppRyjMegaBirth_cpp_801d9c00,0x269);
      vRyjMegaBirth->m_worldMatrixBlock = pPVar4;
      if (vRyjMegaBirth->m_worldMatrixBlock != (PARTICLE_WMAT *)0x0) {
        memset(vRyjMegaBirth->m_worldMatrixBlock,0,vRyjMegaBirth->m_numParticles * 0x30);
      }
    }
    if (param_2->m_payload[0xd5] != '\0') {
      p_Var5 = (_PARTICLE_COLOR *)
               pppMemAlloc__FUlPQ27CMemory6CStagePci
                         (vRyjMegaBirth->m_numParticles << 5,pppEnvStPtr->m_stagePtr,
                          s_pppRyjMegaBirth_cpp_801d9c00,0x271);
      vRyjMegaBirth->m_colorBlock = p_Var5;
      if (vRyjMegaBirth->m_colorBlock != (_PARTICLE_COLOR *)0x0) {
        memset(vRyjMegaBirth->m_colorBlock,0,vRyjMegaBirth->m_numParticles << 5);
      }
    }
    (vRyjMegaBirth->m_accelerationAxis).x = *(float *)(param_2->m_payload + 0x9c);
    (vRyjMegaBirth->m_accelerationAxis).y = *(float *)(param_2->m_payload + 0xa0);
    (vRyjMegaBirth->m_accelerationAxis).z = *(float *)(param_2->m_payload + 0xa4);
    PSVECNormalize(&vRyjMegaBirth->m_accelerationAxis,&vRyjMegaBirth->m_accelerationAxis);
  }
  if (vRyjMegaBirth->m_particleBlock == (Vec *)0x0) {
    bVar1 = false;
  }
  else if (((param_2->m_payload[0xd8] == '\x01') || (param_2->m_payload[0xd8] == '\x02')) &&
          (vRyjMegaBirth->m_worldMatrixBlock == (PARTICLE_WMAT *)0x0)) {
    bVar1 = false;
  }
  else if ((param_2->m_payload[0xd5] == '\0') ||
          (vRyjMegaBirth->m_colorBlock != (_PARTICLE_COLOR *)0x0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    switch(param_2->m_payload[0x16]) {
    default:
      PSMTXCopy(&pppMngStPtr->m_matrix,(Mtx *)vRyjMegaBirth);
      break;
    case '\x01':
    case '\x03':
    case '\x05':
    case '\a':
    case '\t':
      PSMTXIdentity((Mtx *)vRyjMegaBirth);
      (vRyjMegaBirth->m_worldMatrix).value[0][0] = (pppMngStPtr->m_scale).x;
      (vRyjMegaBirth->m_worldMatrix).value[1][1] = (pppMngStPtr->m_scale).y;
      (vRyjMegaBirth->m_worldMatrix).value[2][2] = (pppMngStPtr->m_scale).z;
      (vRyjMegaBirth->m_worldMatrix).value[0][3] = (pppMngStPtr->m_position).x;
      (vRyjMegaBirth->m_worldMatrix).value[1][3] = (pppMngStPtr->m_position).y;
      (vRyjMegaBirth->m_worldMatrix).value[2][3] = (pppMngStPtr->m_position).z;
    }
    calc_particle__FP11_pppPObjectP13VRyjMegaBirthP13PRyjMegaBirthP6VColor
              (&pppRyjMegaBirth->field0_0x0,vRyjMegaBirth,(PRyjMegaBirth *)param_2,
               (VColor *)((int)(&pppRyjMegaBirth->field0_0x0 + 2) + iVar2));
  }
  return;
}

