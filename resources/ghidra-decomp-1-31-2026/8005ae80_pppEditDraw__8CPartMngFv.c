// Function: pppEditDraw__8CPartMngFv
// Entry: 8005ae80
// Size: 1844 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditDraw__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  CPartMng *pCVar2;
  int iVar3;
  _pppMngSt *p_Var4;
  double dVar5;
  Vec VStack_218;
  Vec local_20c;
  Vec VStack_200;
  Vec VStack_1f4;
  Vec local_1e8;
  Vec VStack_1dc;
  Vec VStack_1d0;
  Vec local_1c4;
  Vec VStack_1b8;
  Vec VStack_1ac;
  Vec local_1a0;
  Vec VStack_194;
  Vec local_188;
  Vec local_17c;
  Vec local_170;
  Vec local_164;
  Vec VStack_158;
  Vec local_14c;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  Mtx MStack_e0;
  Mtx MStack_b0;
  Mtx MStack_80;
  Mtx MStack_50;
  
  if (DAT_8032ed68 == 0) {
    (partMng->m_pppEnvSt).m_debugCounter = 0;
    if (partMng->m_pppProgOffsetReconstructionTable[0] != (long *)0x0) {
      if ((int)partMng->m_editDrawMode < 4) {
        PSMTXInverse(&ppvCameraMatrix0,&MStack_50);
        iVar3 = 0;
        local_164.x = MStack_50.value[0][3];
        local_164.y = MStack_50.value[1][3];
        local_164.z = MStack_50.value[2][3];
        pCVar2 = partMng;
        do {
          p_Var4 = pCVar2->m_pppMngStArr;
          if ((((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
               (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
              (pCVar2->m_pppMngStArr[0].m_drawMode == '\b')) &&
             (((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')) &&
              (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')))) {
            local_1a0.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
            local_1a0.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
            local_1a0.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
            pppMngStPtr = p_Var4;
            if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005af68:
              PSMTXMultVec(&ppvCameraMatrix0,&local_1a0,&VStack_1ac);
              pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_1ac.z;
              pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
              pppMngStPtr = p_Var4;
              pppSetFpMatrix__FP9_pppMngSt(p_Var4);
              _pppDrawPart__FP9_pppMngSt(p_Var4);
            }
            else {
              PSVECSubtract(&local_164,&local_1a0,&VStack_194);
              dVar5 = (double)PSVECSquareMag(&VStack_194);
              if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
                local_e4 = pCVar2->m_pppMngStArr[0].m_cullRadius;
                local_e8 = local_1a0.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
                local_f8 = local_1a0.x - local_e4;
                local_f4 = local_1a0.y;
                local_ec = local_1a0.x + local_e4;
                local_f0 = local_1a0.z - local_e4;
                local_e4 = local_1a0.z + local_e4;
                iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                                  ((double)FLOAT_8032fe48,&local_f8,&local_164,&ppvCameraMatrix0);
                if (iVar1 != 0) goto LAB_8005af68;
              }
            }
          }
          iVar3 = iVar3 + 1;
          pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
        } while (iVar3 < 0x180);
        PSMTXInverse(&ppvCameraMatrix0,&MStack_80);
        iVar3 = 0;
        local_170.x = MStack_80.value[0][3];
        local_170.y = MStack_80.value[1][3];
        local_170.z = MStack_80.value[2][3];
        pCVar2 = partMng;
        do {
          p_Var4 = pCVar2->m_pppMngStArr;
          if (((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
              (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
             ((pCVar2->m_pppMngStArr[0].m_drawMode == '\x04' &&
              (((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')) &&
               (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')))))) {
            local_1c4.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
            local_1c4.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
            local_1c4.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
            pppMngStPtr = p_Var4;
            if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005b0e0:
              PSMTXMultVec(&ppvCameraMatrix0,&local_1c4,&VStack_1d0);
              pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_1d0.z;
              pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
              pppMngStPtr = p_Var4;
              pppSetFpMatrix__FP9_pppMngSt(p_Var4);
              _pppDrawPart__FP9_pppMngSt(p_Var4);
            }
            else {
              PSVECSubtract(&local_170,&local_1c4,&VStack_1b8);
              dVar5 = (double)PSVECSquareMag(&VStack_1b8);
              if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
                local_fc = pCVar2->m_pppMngStArr[0].m_cullRadius;
                local_100 = local_1c4.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
                local_110 = local_1c4.x - local_fc;
                local_10c = local_1c4.y;
                local_104 = local_1c4.x + local_fc;
                local_108 = local_1c4.z - local_fc;
                local_fc = local_1c4.z + local_fc;
                iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                                  ((double)FLOAT_8032fe48,&local_110,&local_170,&ppvCameraMatrix0);
                if (iVar1 != 0) goto LAB_8005b0e0;
              }
            }
          }
          iVar3 = iVar3 + 1;
          pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
        } while (iVar3 < 0x180);
        pppDraw__8CPartMngFv(partMng);
        PSMTXInverse(&ppvCameraMatrix0,&MStack_b0);
        iVar3 = 0;
        local_17c.x = MStack_b0.value[0][3];
        local_17c.y = MStack_b0.value[1][3];
        local_17c.z = MStack_b0.value[2][3];
        pCVar2 = partMng;
        do {
          p_Var4 = pCVar2->m_pppMngStArr;
          if (((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
              (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
             (((pCVar2->m_pppMngStArr[0].m_drawMode == '\x06' &&
               ((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')))) &&
              (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')))) {
            local_1e8.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
            local_1e8.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
            local_1e8.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
            pppMngStPtr = p_Var4;
            if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005b260:
              PSMTXMultVec(&ppvCameraMatrix0,&local_1e8,&VStack_1f4);
              pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_1f4.z;
              pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
              pppMngStPtr = p_Var4;
              pppSetFpMatrix__FP9_pppMngSt(p_Var4);
              _pppDrawPart__FP9_pppMngSt(p_Var4);
            }
            else {
              PSVECSubtract(&local_17c,&local_1e8,&VStack_1dc);
              dVar5 = (double)PSVECSquareMag(&VStack_1dc);
              if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
                local_114 = pCVar2->m_pppMngStArr[0].m_cullRadius;
                local_118 = local_1e8.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
                local_128 = local_1e8.x - local_114;
                local_124 = local_1e8.y;
                local_11c = local_1e8.x + local_114;
                local_120 = local_1e8.z - local_114;
                local_114 = local_1e8.z + local_114;
                iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                                  ((double)FLOAT_8032fe48,&local_128,&local_17c,&ppvCameraMatrix0);
                if (iVar1 != 0) goto LAB_8005b260;
              }
            }
          }
          iVar3 = iVar3 + 1;
          pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
        } while (iVar3 < 0x180);
        PSMTXInverse(&ppvCameraMatrix0,&MStack_e0);
        iVar3 = 0;
        local_188.x = MStack_e0.value[0][3];
        local_188.y = MStack_e0.value[1][3];
        local_188.z = MStack_e0.value[2][3];
        pCVar2 = partMng;
        do {
          p_Var4 = pCVar2->m_pppMngStArr;
          if (((((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
                (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
               (pCVar2->m_pppMngStArr[0].m_drawMode == '\a')) &&
              ((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')))) &&
             (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')) {
            local_20c.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
            local_20c.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
            local_20c.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
            pppMngStPtr = p_Var4;
            if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005b3d8:
              PSMTXMultVec(&ppvCameraMatrix0,&local_20c,&VStack_218);
              pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_218.z;
              pppEnvStPtr = (_pppEnvSt *)((int)p_Var4->m_pppResSet + 4);
              pppMngStPtr = p_Var4;
              pppSetFpMatrix__FP9_pppMngSt(p_Var4);
              _pppDrawPart__FP9_pppMngSt(p_Var4);
            }
            else {
              PSVECSubtract(&local_188,&local_20c,&VStack_200);
              dVar5 = (double)PSVECSquareMag(&VStack_200);
              if (dVar5 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
                local_12c = pCVar2->m_pppMngStArr[0].m_cullRadius;
                local_130 = local_20c.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
                local_140 = local_20c.x - local_12c;
                local_13c = local_20c.y;
                local_134 = local_20c.x + local_12c;
                local_138 = local_20c.z - local_12c;
                local_12c = local_20c.z + local_12c;
                iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                                  ((double)FLOAT_8032fe48,&local_140,&local_188,&ppvCameraMatrix0);
                if (iVar1 != 0) goto LAB_8005b3d8;
              }
            }
          }
          iVar3 = iVar3 + 1;
          pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
        } while (iVar3 < 0x180);
      }
      else {
        pCVar2 = partMng;
        for (iVar3 = 0; iVar3 < partMng->m_editCount; iVar3 = iVar3 + 1) {
          p_Var4 = pCVar2->m_pppMngStArr;
          iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime;
          pppMngStPtr = p_Var4;
          if ((iVar1 != -0x1000) && (iVar1 < 0)) {
            local_14c.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
            local_14c.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
            local_14c.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
            PSMTXMultVec(&ppvCameraMatrix0,&local_14c,&VStack_158);
            pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_158.z;
            AddPrimOt__10pppDrawMngFUlP9_pppMngSt(&ppvDrawMng,0x3ff,p_Var4);
            if ((pCVar2->m_pppMngStArr[0].m_stopAtLifeEnd != '\0') &&
               (pCVar2->m_pppMngStArr[0].m_currentFrame == pCVar2->m_pppMngStArr[0].m_lifeEnd)) {
              DAT_801eae0c = 0;
            }
          }
          pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
        }
        DrawOt__10pppDrawMngFv(&ppvDrawMng);
      }
    }
    if (partMng->m_cursorEnable != 0) {
      drawCursor__8CPartMngFv(partMng);
      render3Dcursor__8CPartMngFv(partMng);
    }
    ppvScreenMatrix.value[2][3] = FLOAT_8032ed60;
    GXSetProjection(&ppvScreenMatrix,0);
  }
  return;
}

