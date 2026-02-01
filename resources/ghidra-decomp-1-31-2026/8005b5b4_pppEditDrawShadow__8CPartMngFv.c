// Function: pppEditDrawShadow__8CPartMngFv
// Entry: 8005b5b4
// Size: 488 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditDrawShadow__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  int iVar2;
  _pppMngSt *pppMngSt;
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
  
  if (DAT_8032ed68 == 0) {
    if ((partMng->m_pppProgOffsetReconstructionTable[0] != (long *)0x0) &&
       ((int)partMng->m_editDrawMode < 4)) {
      PSMTXInverse(&ppvCameraMatrix0,&MStack_40);
      iVar2 = 0;
      local_64.x = MStack_40.value[0][3];
      local_64.y = MStack_40.value[1][3];
      local_64.z = MStack_40.value[2][3];
      do {
        pppMngSt = partMng->m_pppMngStArr;
        if ((((partMng->m_pppMngStArr[0].m_endRequested == '\0') &&
             (iVar1 = partMng->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
            (partMng->m_pppMngStArr[0].m_drawMode == '\x03')) &&
           (((iVar1 < 0 && (partMng->m_pppMngStArr[0].m_isVisible != '\0')) &&
            (partMng->m_pppMngStArr[0].m_ownerVisible != '\0')))) {
          local_7c.x = partMng->m_pppMngStArr[0].m_matrix.value[0][3];
          local_7c.y = partMng->m_pppMngStArr[0].m_matrix.value[1][3];
          local_7c.z = partMng->m_pppMngStArr[0].m_matrix.value[2][3];
          pppMngStPtr = pppMngSt;
          if (DOUBLE_8032fe40 == (double)partMng->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005b694:
            PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_88);
            partMng->m_pppMngStArr[0].m_sortDepth = VStack_88.z;
            pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
            pppMngStPtr = pppMngSt;
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
            _pppDrawPart__FP9_pppMngSt(pppMngSt);
          }
          else {
            PSVECSubtract(&local_64,&local_7c,&VStack_70);
            dVar3 = (double)PSVECSquareMag(&VStack_70);
            if (dVar3 < (double)partMng->m_pppMngStArr[0].m_cullRadiusSq) {
              local_44 = partMng->m_pppMngStArr[0].m_cullRadius;
              local_48 = local_7c.y + partMng->m_pppMngStArr[0].m_cullYOffset;
              local_58 = local_7c.x - local_44;
              local_54 = local_7c.y;
              local_4c = local_7c.x + local_44;
              local_50 = local_7c.z - local_44;
              local_44 = local_7c.z + local_44;
              iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                                ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
              if (iVar1 != 0) goto LAB_8005b694;
            }
          }
        }
        iVar2 = iVar2 + 1;
        partMng = (CPartMng *)partMng->m_rgbaA;
      } while (iVar2 < 0x180);
    }
    ppvScreenMatrix.value[2][3] = FLOAT_8032ed60;
    GXSetProjection(&ppvScreenMatrix,0);
  }
  return;
}

