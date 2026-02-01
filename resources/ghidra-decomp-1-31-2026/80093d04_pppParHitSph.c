// Function: pppParHitSph
// Entry: 80093d04
// Size: 372 bytes

/* WARNING: Removing unreachable block (ram,0x80093e58) */
/* WARNING: Removing unreachable block (ram,0x80093d14) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppParHitSph(_pppPObject *param_1,int param_2)

{
  _pppMngSt *p_Var1;
  double dVar2;
  undefined4 local_a8;
  undefined4 local_a4;
  Vec local_a0;
  Vec local_94;
  Vec local_88;
  Mtx MStack_78;
  Mtx local_48;
  
  p_Var1 = pppMngStPtr;
  PSVECSubtract(&pppMngStPtr->m_position,&pppMngStPtr->m_previousPosition,&local_88);
  local_94.x = (pppMngStPtr->m_matrix).value[0][3];
  local_94.y = (pppMngStPtr->m_matrix).value[1][3];
  local_94.z = (pppMngStPtr->m_matrix).value[2][3];
  dVar2 = (double)(p_Var1->m_paramD * *(float *)(param_2 + 8));
  if (((FLOAT_80330700 == local_88.x) && (FLOAT_80330700 == local_88.y)) &&
     (FLOAT_80330700 == local_88.z)) {
    pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(dVar2,p_Var1,&local_94,&local_88);
  }
  else {
    pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
              (dVar2,(double)*(float *)(param_2 + 4),p_Var1,&local_94,&local_88);
  }
  if ((CFlat._4764_4_ & 0x200000) != 0) {
    local_a4 = 0xffffffff;
    PSMTXIdentity(&MStack_78);
    PSMTXIdentity(&local_48);
    local_48.value[0][0] = (float)dVar2;
    local_48.value[1][1] = (float)dVar2;
    local_48.value[2][2] = (float)dVar2;
    PSMTXConcat(&ppvCameraMatrix0,&MStack_78,&MStack_78);
    PSMTXMultVec(&MStack_78,&local_94,&local_a0);
    local_48.value[0][3] = local_a0.x;
    local_48.value[1][3] = local_a0.y;
    local_48.value[2][3] = local_a0.z;
    local_a8 = local_a4;
    DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic,&local_48,&local_a8);
  }
  return;
}

