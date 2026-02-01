// Function: pppDraw__8CPartMngFv
// Entry: 80059f6c
// Size: 544 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDraw__8CPartMngFv(CPartMng *partMng)

{
  uint8_t uVar1;
  int iVar2;
  _pppMngSt *pppMngSt;
  int iVar3;
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
  
  (partMng->m_pppEnvSt).m_debugCounter = 0;
  PSMTXInverse(&ppvCameraMatrix0,&MStack_40);
  iVar3 = 0;
  local_64.x = MStack_40.value[0][3];
  local_64.y = MStack_40.value[1][3];
  local_64.z = MStack_40.value[2][3];
  do {
    pppMngSt = partMng->m_pppMngStArr;
    if ((((partMng->m_pppMngStArr[0].m_endRequested == '\0') &&
         (iVar2 = partMng->m_pppMngStArr[0].m_baseTime, iVar2 != -0x1000)) &&
        ((char)partMng->m_pppMngStArr[0].m_drawMode < '\x03')) &&
       (((iVar2 < 0 && (partMng->m_pppMngStArr[0].m_isVisible != '\0')) &&
        (partMng->m_pppMngStArr[0].m_ownerVisible != '\0')))) {
      local_7c.x = partMng->m_pppMngStArr[0].m_matrix.value[0][3];
      local_7c.y = partMng->m_pppMngStArr[0].m_matrix.value[1][3];
      local_7c.z = partMng->m_pppMngStArr[0].m_matrix.value[2][3];
      pppMngStPtr = pppMngSt;
      if (DOUBLE_8032fe40 == (double)partMng->m_pppMngStArr[0].m_cullRadiusSq) {
LAB_8005a03c:
        PSMTXMultVec(&ppvCameraMatrix0,&local_7c,&VStack_70);
        partMng->m_pppMngStArr[0].m_sortDepth = VStack_70.z;
        uVar1 = partMng->m_pppMngStArr[0].m_drawMode;
        if (uVar1 == '\x01') {
          AddPrimOt__10pppDrawMngFUlP9_pppMngSt(&ppvDrawMng,0x3ff,pppMngSt);
        }
        else if ((char)uVar1 < '\x01') {
          if (-1 < (char)uVar1) {
            AddPrim__10pppDrawMngFfP9_pppMngStSc
                      (VStack_70.z,&ppvDrawMng,pppMngSt,partMng->m_pppMngStArr[0].m_primTypeOrLayer)
            ;
          }
        }
        else if ((char)uVar1 < '\x03') {
          AddPrimOt__10pppDrawMngFUlP9_pppMngSt(&ppvDrawMng,0,pppMngSt);
        }
      }
      else {
        PSVECSubtract(&local_64,&local_7c,&VStack_88);
        dVar4 = (double)PSVECSquareMag(&VStack_88);
        if (dVar4 < (double)partMng->m_pppMngStArr[0].m_cullRadiusSq) {
          local_44 = partMng->m_pppMngStArr[0].m_cullRadius;
          local_48 = local_7c.y + partMng->m_pppMngStArr[0].m_cullYOffset;
          local_58 = local_7c.x - local_44;
          local_54 = local_7c.y;
          local_4c = local_7c.x + local_44;
          local_50 = local_7c.z - local_44;
          local_44 = local_7c.z + local_44;
          iVar2 = CheckFrustum__6CBoundFR3VecPA4_ff
                            ((double)FLOAT_8032fe48,&local_58,&local_64,&ppvCameraMatrix0);
          if (iVar2 != 0) goto LAB_8005a03c;
        }
      }
    }
    iVar3 = iVar3 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
    if (0x17f < iVar3) {
      DrawOt__10pppDrawMngFv(&ppvDrawMng);
      return;
    }
  } while( true );
}

