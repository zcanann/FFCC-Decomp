// Function: pppDrawPrioPdtFpno__8CPartMngFUcss
// Entry: 8005a308
// Size: 492 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawPrioPdtFpno__8CPartMngFUcss(CPartMng *partMng,uint param_2,short param_3,short param_4)

{
  int iVar1;
  _pppMngSt *pppMngSt;
  int iVar2;
  double dVar3;
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
  local_64.y = MStack_40.value[1][3];
  local_64.z = MStack_40.value[2][3];
  iVar2 = 0x180;
  while ((((pppMngSt = partMng->m_pppMngStArr, partMng->m_pppMngStArr[0].m_nodeIndex != param_4 ||
           (partMng->m_pppMngStArr[0].m_kind != param_3)) ||
          (partMng->m_pppMngStArr[0].m_endRequested != '\0')) ||
         (((iVar1 = partMng->m_pppMngStArr[0].m_baseTime, iVar1 == -0x1000 ||
           ((int)(char)partMng->m_pppMngStArr[0].m_drawMode != (param_2 & 0xff))) || (-1 < iVar1))))
        ) {
    partMng = (CPartMng *)partMng->m_rgbaA;
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return;
    }
  }
  if (partMng->m_pppMngStArr[0].m_isVisible == '\0') {
    return;
  }
  local_7c.x = partMng->m_pppMngStArr[0].m_matrix.value[0][3];
  local_7c.y = partMng->m_pppMngStArr[0].m_matrix.value[1][3];
  local_7c.z = partMng->m_pppMngStArr[0].m_matrix.value[2][3];
  pppMngStPtr = pppMngSt;
  if (DOUBLE_8032fe40 != (double)partMng->m_pppMngStArr[0].m_cullRadiusSq) {
    PSVECSubtract(&local_64,&local_7c,&VStack_70);
    dVar3 = (double)PSVECSquareMag(&VStack_70);
    if ((double)partMng->m_pppMngStArr[0].m_cullRadiusSq <= dVar3) {
      return;
    }
    local_44 = partMng->m_pppMngStArr[0].m_cullRadius;
    local_48 = local_7c.y + partMng->m_pppMngStArr[0].m_cullYOffset;
    local_58 = local_7c.x - local_44;
    local_54 = local_7c.y;
    local_4c = local_7c.x + local_44;
    local_50 = local_7c.z - local_44;
    local_44 = local_7c.z + local_44;
    iVar2 = CheckFrustum__6CBoundFR3VecPA4_ff
                      ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
    if (iVar2 == 0) {
      return;
    }
  }
  PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_88);
  partMng->m_pppMngStArr[0].m_sortDepth = VStack_88.z;
  pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
  pppMngStPtr = pppMngSt;
  pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
  _pppDrawPart__FP9_pppMngSt(pppMngSt);
  return;
}

