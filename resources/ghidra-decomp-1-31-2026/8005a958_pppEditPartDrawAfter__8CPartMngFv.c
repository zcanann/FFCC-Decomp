// Function: pppEditPartDrawAfter__8CPartMngFv
// Entry: 8005a958
// Size: 1320 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditPartDrawAfter__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  CPartMng *pCVar2;
  int iVar3;
  _pppMngSt *p_Var4;
  double dVar5;
  Vec VStack_178;
  Vec local_16c;
  Vec VStack_160;
  Vec VStack_154;
  Vec local_148;
  Vec VStack_13c;
  Vec VStack_130;
  Vec local_124;
  Vec VStack_118;
  Vec local_10c;
  Vec local_100;
  Vec local_f4;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  Mtx MStack_a0;
  Mtx MStack_70;
  Mtx MStack_40;
  
  if (((DAT_8032ed68 == 0) &&
      ((partMng->m_pppEnvSt).m_debugCounter = 0,
      partMng->m_pppProgOffsetReconstructionTable[0] != (long *)0x0)) &&
     ((int)partMng->m_editDrawMode < 4)) {
    PSMTXInverse(&ppvCameraMatrix0,&MStack_40);
    iVar3 = 0;
    local_f4.x = MStack_40.value[0][3];
    local_f4.y = MStack_40.value[1][3];
    local_f4.z = MStack_40.value[2][3];
    pCVar2 = partMng;
    do {
      p_Var4 = pCVar2->m_pppMngStArr;
      if ((((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
           (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
          ((pCVar2->m_pppMngStArr[0].m_drawMode == '\x05' &&
           ((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')))))) &&
         (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')) {
        local_124.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
        local_124.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
        local_124.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
        pppMngStPtr = p_Var4;
        if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005aa4c:
          PSMTXMultVec(&ppvCameraMatrix0,&local_124,&VStack_130);
          pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_130.z;
          pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
          pppMngStPtr = p_Var4;
          pppSetFpMatrix__FP9_pppMngSt(p_Var4);
          _pppDrawPart__FP9_pppMngSt(p_Var4);
        }
        else {
          PSVECSubtract(&local_f4,&local_124,&VStack_118);
          dVar5 = (double)PSVECSquareMag(&VStack_118);
          if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
            local_a4 = pCVar2->m_pppMngStArr[0].m_cullRadius;
            local_a8 = local_124.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
            local_b8 = local_124.x - local_a4;
            local_b4 = local_124.y;
            local_ac = local_124.x + local_a4;
            local_b0 = local_124.z - local_a4;
            local_a4 = local_124.z + local_a4;
            iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                              ((double)FLOAT_8032fe48,&local_b8,&local_f4,&ppvCameraMatrix0);
            if (iVar1 != 0) goto LAB_8005aa4c;
          }
        }
      }
      iVar3 = iVar3 + 1;
      pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
    } while (iVar3 < 0x180);
    PSMTXInverse(&ppvCameraMatrix0,&MStack_70);
    iVar3 = 0;
    local_100.x = MStack_70.value[0][3];
    local_100.y = MStack_70.value[1][3];
    local_100.z = MStack_70.value[2][3];
    pCVar2 = partMng;
    do {
      p_Var4 = pCVar2->m_pppMngStArr;
      if (((((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
            (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
           (pCVar2->m_pppMngStArr[0].m_drawMode == '\x06')) &&
          ((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')))) &&
         (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')) {
        local_148.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
        local_148.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
        local_148.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
        pppMngStPtr = p_Var4;
        if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005abc4:
          PSMTXMultVec(&ppvCameraMatrix0,&local_148,&VStack_154);
          pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_154.z;
          pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
          pppMngStPtr = p_Var4;
          pppSetFpMatrix__FP9_pppMngSt(p_Var4);
          _pppDrawPart__FP9_pppMngSt(p_Var4);
        }
        else {
          PSVECSubtract(&local_100,&local_148,&VStack_13c);
          dVar5 = (double)PSVECSquareMag(&VStack_13c);
          if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
            local_bc = pCVar2->m_pppMngStArr[0].m_cullRadius;
            local_c0 = local_148.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
            local_d0 = local_148.x - local_bc;
            local_cc = local_148.y;
            local_c4 = local_148.x + local_bc;
            local_c8 = local_148.z - local_bc;
            local_bc = local_148.z + local_bc;
            iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                              ((double)FLOAT_8032fe48,&local_d0,&local_100,&ppvCameraMatrix0);
            if (iVar1 != 0) goto LAB_8005abc4;
          }
        }
      }
      iVar3 = iVar3 + 1;
      pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
    } while (iVar3 < 0x180);
    PSMTXInverse(&ppvCameraMatrix0,&MStack_a0);
    iVar3 = 0;
    local_10c.x = MStack_a0.value[0][3];
    local_10c.y = MStack_a0.value[1][3];
    local_10c.z = MStack_a0.value[2][3];
    pCVar2 = partMng;
    do {
      p_Var4 = pCVar2->m_pppMngStArr;
      if (((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
          (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
         ((pCVar2->m_pppMngStArr[0].m_drawMode == '\a' &&
          (((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')) &&
           (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')))))) {
        local_16c.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
        local_16c.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
        local_16c.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
        pppMngStPtr = p_Var4;
        if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005ad3c:
          PSMTXMultVec(&ppvCameraMatrix0,&local_16c,&VStack_178);
          pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_178.z;
          pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
          pppMngStPtr = p_Var4;
          pppSetFpMatrix__FP9_pppMngSt(p_Var4);
          _pppDrawPart__FP9_pppMngSt(p_Var4);
        }
        else {
          PSVECSubtract(&local_10c,&local_16c,&VStack_160);
          dVar5 = (double)PSVECSquareMag(&VStack_160);
          if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
            local_d4 = pCVar2->m_pppMngStArr[0].m_cullRadius;
            local_d8 = local_16c.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
            local_e8 = local_16c.x - local_d4;
            local_e4 = local_16c.y;
            local_dc = local_16c.x + local_d4;
            local_e0 = local_16c.z - local_d4;
            local_d4 = local_16c.z + local_d4;
            iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                              ((double)FLOAT_8032fe48,&local_e8,&local_10c,&ppvCameraMatrix0);
            if (iVar1 != 0) goto LAB_8005ad3c;
          }
        }
      }
      iVar3 = iVar3 + 1;
      pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
    } while (iVar3 < 0x180);
  }
  DAT_801eae08 = pppHeapCheckLeak__FPQ27CMemory6CStage(pppEnvStPtr->m_stagePtr);
  if ((DAT_801eae10 == 0) || (DAT_801eae10 = DAT_801eae10 + -1, DAT_801eae0c < DAT_801eae08)) {
    DAT_801eae10 = partMng->m_heapCheckInterval << 1;
    DAT_801eae0c = DAT_801eae08;
  }
  return;
}

