// Function: pppDrawPrio__8CPartMngFUc
// Entry: 8005a4f4
// Size: 456 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawPrio__8CPartMngFUc(CPartMng *param_1,uint param_2)

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
  iVar2 = 0;
  local_64.x = MStack_40.value[0][3];
  local_64.y = MStack_40.value[1][3];
  local_64.z = MStack_40.value[2][3];
  do {
    pppMngSt = param_1->m_pppMngStArr;
    if ((((param_1->m_pppMngStArr[0].m_endRequested == '\0') &&
         (iVar1 = param_1->m_pppMngStArr[0].m_baseTime, iVar1 != -0x1000)) &&
        ((int)(char)param_1->m_pppMngStArr[0].m_drawMode == (param_2 & 0xff))) &&
       (((iVar1 < 0 && (param_1->m_pppMngStArr[0].m_isVisible != '\0')) &&
        (param_1->m_pppMngStArr[0].m_ownerVisible != '\0')))) {
      local_7c.x = param_1->m_pppMngStArr[0].m_matrix.value[0][3];
      local_7c.y = param_1->m_pppMngStArr[0].m_matrix.value[1][3];
      local_7c.z = param_1->m_pppMngStArr[0].m_matrix.value[2][3];
      pppMngStPtr = pppMngSt;
      if (DOUBLE_8032fe40 == (double)param_1->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005a5c8:
        PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_88);
        param_1->m_pppMngStArr[0].m_sortDepth = VStack_88.z;
        pppEnvStPtr = (_pppEnvSt *)((int)pppMngSt->m_pppResSet + 4);
        pppMngStPtr = pppMngSt;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        _pppDrawPart__FP9_pppMngSt(pppMngSt);
      }
      else {
        PSVECSubtract(&local_64,&local_7c,&VStack_70);
        dVar3 = (double)PSVECSquareMag(&VStack_70);
        if (dVar3 < (double)param_1->m_pppMngStArr[0].m_cullRadiusSq) {
          local_44 = param_1->m_pppMngStArr[0].m_cullRadius;
          local_48 = local_7c.y + param_1->m_pppMngStArr[0].m_cullYOffset;
          local_58 = local_7c.x - local_44;
          local_54 = local_7c.y;
          local_4c = local_7c.x + local_44;
          local_50 = local_7c.z - local_44;
          local_44 = local_7c.z + local_44;
          iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                            ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
          if (iVar1 != 0) goto LAB_8005a5c8;
        }
      }
    }
    iVar2 = iVar2 + 1;
    param_1 = (CPartMng *)param_1->m_rgbaA;
    if (0x17f < iVar2) {
      return;
    }
  } while( true );
}

