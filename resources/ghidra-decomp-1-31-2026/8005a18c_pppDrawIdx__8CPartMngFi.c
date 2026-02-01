// Function: pppDrawIdx__8CPartMngFi
// Entry: 8005a18c
// Size: 380 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawIdx__8CPartMngFi(CPartMng *partMng,int param_2)

{
  int iVar1;
  _pppMngSt *pppMngSt;
  double dVar2;
  Vec VStack_88;
  Vec local_7c;
  Vec VStack_70;
  Vec local_64;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  Mtx MStack_40;
  
  PSMTXInverse(&ppvCameraMatrix0,&MStack_40);
  local_64.x = MStack_40.value[0][3];
  pppMngSt = partMng->m_pppMngStArr + param_2;
  local_64.y = MStack_40.value[1][3];
  local_64.z = MStack_40.value[2][3];
  if (pppMngSt->m_endRequested != '\0') {
    return;
  }
  if (pppMngSt->m_baseTime == -0x1000) {
    return;
  }
  if (-1 < pppMngSt->m_baseTime) {
    return;
  }
  local_7c.x = (pppMngSt->m_matrix).value[0][3];
  local_7c.y = (pppMngSt->m_matrix).value[1][3];
  local_7c.z = (pppMngSt->m_matrix).value[2][3];
  pppMngStPtr = pppMngSt;
  if (DOUBLE_8032fe40 != (double)pppMngSt->m_cullRadiusSq) {
    PSVECSubtract(&local_64,&local_7c,&VStack_70);
    dVar2 = (double)PSVECSquareMag(&VStack_70);
    if ((double)pppMngSt->m_cullRadiusSq <= dVar2) {
      return;
    }
    local_44 = pppMngSt->m_cullRadius;
    local_48 = local_7c.y + pppMngSt->m_cullYOffset;
    local_58 = local_7c.x - local_44;
    local_54 = local_7c.y;
    local_4c = local_7c.x + local_44;
    local_50 = local_7c.z - local_44;
    local_44 = local_7c.z + local_44;
    iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                      ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
    if (iVar1 == 0) {
      return;
    }
  }
  PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_88);
  pppMngSt->m_sortDepth = VStack_88.z;
  pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
  pppMngStPtr = pppMngSt;
  pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
  _pppDrawPart__FP9_pppMngSt(pppMngSt);
  return;
}

