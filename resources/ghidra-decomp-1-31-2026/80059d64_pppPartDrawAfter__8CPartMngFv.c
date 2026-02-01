// Function: pppPartDrawAfter__8CPartMngFv
// Entry: 80059d64
// Size: 520 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppPartDrawAfter__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  CPartMng *pCVar2;
  int iVar3;
  _pppMngSt *pppMngSt;
  double dVar4;
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
  iVar3 = 0;
  local_64.x = MStack_40.value[0][3];
  local_64.y = MStack_40.value[1][3];
  local_64.z = MStack_40.value[2][3];
  pCVar2 = partMng;
  do {
    pppMngSt = pCVar2->m_pppMngStArr;
    if (((((pCVar2->m_pppMngStArr[0].m_endRequested == '\0') &&
          (iVar1 = pCVar2->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
         (pCVar2->m_pppMngStArr[0].m_drawMode == '\x05')) &&
        ((iVar1 < 0 && (pCVar2->m_pppMngStArr[0].m_isVisible != '\0')))) &&
       (pCVar2->m_pppMngStArr[0].m_ownerVisible != '\0')) {
      local_7c.x = pCVar2->m_pppMngStArr[0].m_matrix.value[0][3];
      local_7c.y = pCVar2->m_pppMngStArr[0].m_matrix.value[1][3];
      local_7c.z = pCVar2->m_pppMngStArr[0].m_matrix.value[2][3];
      pppMngStPtr = pppMngSt;
      if (DOUBLE_8032fe40 == (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_80059e28:
        PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_88);
        pCVar2->m_pppMngStArr[0].m_sortDepth = VStack_88.z;
        pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
        pppMngStPtr = pppMngSt;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        _pppDrawPart__FP9_pppMngSt(pppMngSt);
      }
      else {
        PSVECSubtract(&local_64,&local_7c,&VStack_70);
        dVar4 = (double)PSVECSquareMag(&VStack_70);
        if (dVar4 < (double)pCVar2->m_pppMngStArr[0].m_cullRadiusSq) {
          local_44 = pCVar2->m_pppMngStArr[0].m_cullRadius;
          local_48 = local_7c.y + pCVar2->m_pppMngStArr[0].m_cullYOffset;
          local_58 = local_7c.x - local_44;
          local_54 = local_7c.y;
          local_4c = local_7c.x + local_44;
          local_50 = local_7c.z - local_44;
          local_44 = local_7c.z + local_44;
          iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                            ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
          if (iVar1 != 0) goto LAB_80059e28;
        }
      }
    }
    iVar3 = iVar3 + 1;
    pCVar2 = (CPartMng *)pCVar2->m_rgbaA;
    if (0x17f < iVar3) {
      DAT_801eae08 = pppHeapCheckLeak__FPQ27CMemory6CStage(pppEnvStPtr->m_stagePtr);
      if ((DAT_801eae10 == 0) || (DAT_801eae10 = DAT_801eae10 + -1, DAT_801eae0c < DAT_801eae08)) {
        DAT_801eae10 = partMng->m_heapCheckInterval << 1;
        DAT_801eae0c = DAT_801eae08;
      }
      return;
    }
  } while( true );
}

