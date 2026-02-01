// Function: pppSetMatrix__FP9_pppMngSt
// Entry: 80055b80
// Size: 2172 bytes

/* WARNING: Removing unreachable block (ram,0x80055bb8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetMatrix__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  uint8_t uVar5;
  float fVar4;
  int iVar6;
  Vec local_98;
  Vec local_8c;
  Vec local_80;
  Vec local_74;
  Vec local_68;
  Vec local_5c;
  Vec local_50;
  undefined auStack_40 [28];
  float local_24;
  Vec VStack_20;
  float local_14;
  
  bVar1 = pppMngSt->m_rotOrder;
  if (bVar1 == 3) {
    pppGetRotMatrixYZX__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation);
  }
  else if (bVar1 < 3) {
    if (bVar1 == 1) {
      pppGetRotMatrixXZY__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation)
      ;
    }
    else if (bVar1 == 0) {
      pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation)
      ;
    }
    else {
      pppGetRotMatrixYXZ__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation)
      ;
    }
  }
  else if (bVar1 == 5) {
    pppGetRotMatrixZYX__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation);
  }
  else if (bVar1 < 5) {
    pppGetRotMatrixZXY__FR10pppFMATRIXP11pppIVECTOR4(&pppMngStPtr->m_matrix,&pppMngSt->m_rotation);
  }
  bVar1 = pppMngSt->field38_0xe7;
  if (bVar1 == 5) {
    if ((pppMngSt->m_velocity).z == 0.0) goto LAB_800562d4;
    if (pppMngSt->m_ownerVisible == '\0') {
      pppMngSt->m_ownerVisible =
           (uint8_t)((int)((uint)*(byte *)((int)(pppMngSt->m_velocity).x + 0x9a) << 0x19) >> 0x1f);
    }
    if (pppMngSt->m_lockVisFromOwner == '\0') {
      uVar5 = '\0';
      uVar3 = *(uint *)((int)(pppMngSt->m_velocity).x + 0x60);
      if (((uVar3 & 1) != 0) && ((uVar3 & 0x400000) == 0)) {
        uVar5 = '\x01';
      }
      pppMngSt->m_isVisible = uVar5;
    }
    if (pppMngSt->m_lockScaleFromOwner == '\0') {
      fVar4 = (pppMngSt->m_velocity).x;
      bVar2 = false;
      iVar6 = *(int *)((int)fVar4 + 0xf8);
      if ((iVar6 != 0) && (*(int *)(iVar6 + 0x168) != 0)) {
        bVar2 = true;
      }
      if (bVar2) {
        fVar4 = *(float *)(*(int *)(iVar6 + 0x168) + 0x9c);
      }
      else {
        fVar4 = *(float *)((int)fVar4 + 0x4b0);
      }
      pppMngSt->m_ownerScale = fVar4;
      if (DOUBLE_8032fdf0 == (double)pppMngSt->m_ownerScale) {
        pppMngSt->m_ownerScaleMode = '\x01';
      }
      else if (DOUBLE_8032fe00 == (double)pppMngSt->m_ownerScale) {
        pppMngSt->m_ownerScaleMode = '\0';
      }
      else {
        pppMngSt->m_ownerScaleMode = '\x01';
      }
    }
    CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
              (*(CModel **)(*(int *)((int)(pppMngSt->m_velocity).x + 0xf8) + 0x168),
               (Mtx *)auStack_40,(CNode *)(pppMngSt->m_velocity).z);
LAB_80055f18:
    auStack_40._12_4_ = (float)auStack_40._12_4_ + (pppMngStPtr->m_position).x;
    local_24 = local_24 + (pppMngStPtr->m_position).y;
    local_14 = local_14 + (pppMngStPtr->m_position).z;
    PSMTXConcat((Mtx *)auStack_40,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
  }
  else {
    if (bVar1 < 5) {
      if (bVar1 == 3) {
        if ((pppMngSt->m_velocity).z == 0.0) goto LAB_800562d4;
        if (pppMngSt->m_ownerVisible == '\0') {
          pppMngSt->m_ownerVisible =
               (uint8_t)((int)((uint)*(byte *)((int)(pppMngSt->m_velocity).x + 0x9a) << 0x19) >>
                        0x1f);
        }
        if (pppMngSt->m_lockVisFromOwner == '\0') {
          uVar5 = '\0';
          uVar3 = *(uint *)((int)(pppMngSt->m_velocity).x + 0x60);
          if (((uVar3 & 1) != 0) && ((uVar3 & 0x400000) == 0)) {
            uVar5 = '\x01';
          }
          pppMngSt->m_isVisible = uVar5;
        }
        if (pppMngSt->m_lockScaleFromOwner == '\0') {
          fVar4 = (pppMngSt->m_velocity).x;
          bVar2 = false;
          iVar6 = *(int *)((int)fVar4 + 0xf8);
          if ((iVar6 != 0) && (*(int *)(iVar6 + 0x168) != 0)) {
            bVar2 = true;
          }
          if (bVar2) {
            fVar4 = *(float *)(*(int *)(iVar6 + 0x168) + 0x9c);
          }
          else {
            fVar4 = *(float *)((int)fVar4 + 0x4b0);
          }
          pppMngSt->m_ownerScale = fVar4;
          if (DOUBLE_8032fdf0 == (double)pppMngSt->m_ownerScale) {
            pppMngSt->m_ownerScaleMode = '\x01';
          }
          else if (DOUBLE_8032fe00 == (double)pppMngSt->m_ownerScale) {
            pppMngSt->m_ownerScaleMode = '\0';
          }
          else {
            pppMngSt->m_ownerScaleMode = '\x01';
          }
        }
        CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
                  (*(CModel **)(*(int *)((int)(pppMngSt->m_velocity).x + 0xf8) + 0x168),
                   (Mtx *)auStack_40,(CNode *)(pppMngSt->m_velocity).z);
      }
      else {
        if (2 < bVar1) {
          GetMapObjWMtx__7CMapMngFiPA4_f(&MapMng,(int)pppMngSt->m_mapObjIndex,auStack_40);
          goto LAB_80055f18;
        }
        if ((bVar1 < 2) || (pppMngSt->m_mapObjIndex == -1)) goto LAB_800562d4;
        GetMapObjWMtx__7CMapMngFiPA4_f(&MapMng,(int)pppMngSt->m_mapObjIndex,auStack_40);
      }
    }
    else {
      if (bVar1 == 7) {
        if ((pppMngSt->m_velocity).z == 0.0) goto LAB_800562d4;
        if (pppMngSt->m_ownerVisible == '\0') {
          pppMngSt->m_ownerVisible =
               (uint8_t)((int)((uint)*(byte *)((int)(pppMngSt->m_velocity).x + 0x9a) << 0x19) >>
                        0x1f);
        }
        if (pppMngSt->m_lockVisFromOwner == '\0') {
          uVar5 = '\0';
          uVar3 = *(uint *)((int)(pppMngSt->m_velocity).x + 0x60);
          if (((uVar3 & 1) != 0) && ((uVar3 & 0x400000) == 0)) {
            uVar5 = '\x01';
          }
          pppMngSt->m_isVisible = uVar5;
        }
        if (pppMngSt->m_lockScaleFromOwner == '\0') {
          fVar4 = (pppMngSt->m_velocity).x;
          bVar2 = false;
          iVar6 = *(int *)((int)fVar4 + 0xf8);
          if ((iVar6 != 0) && (*(int *)(iVar6 + 0x168) != 0)) {
            bVar2 = true;
          }
          if (bVar2) {
            fVar4 = *(float *)(*(int *)(iVar6 + 0x168) + 0x9c);
          }
          else {
            fVar4 = *(float *)((int)fVar4 + 0x4b0);
          }
          pppMngSt->m_ownerScale = fVar4;
          if (DOUBLE_8032fdf0 == (double)pppMngSt->m_ownerScale) {
            pppMngSt->m_ownerScaleMode = '\x01';
          }
          else if (DOUBLE_8032fe00 == (double)pppMngSt->m_ownerScale) {
            pppMngSt->m_ownerScaleMode = '\0';
          }
          else {
            pppMngSt->m_ownerScaleMode = '\x01';
          }
        }
        CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
                  (*(CModel **)(*(int *)((int)(pppMngSt->m_velocity).x + 0xf8) + 0x168),
                   (Mtx *)auStack_40,(CNode *)(pppMngSt->m_velocity).z);
        PSMTXMultVecSR((Mtx *)auStack_40,&pppMngStPtr->m_position,&local_50);
        (pppMngStPtr->m_matrix).value[0][3] = (float)auStack_40._12_4_ + local_50.x;
        (pppMngStPtr->m_matrix).value[1][3] = local_24 + local_50.y;
        (pppMngStPtr->m_matrix).value[2][3] = local_14 + local_50.z;
        goto LAB_80055cec;
      }
      if ((6 < bVar1) || ((pppMngSt->m_velocity).z == 0.0)) {
LAB_800562d4:
        local_80.x = (pppMngStPtr->m_matrix).value[0][0];
        local_80.y = (pppMngStPtr->m_matrix).value[1][0];
        local_80.z = (pppMngStPtr->m_matrix).value[2][0];
        PSVECScale((pppMngSt->m_scale).x,&local_80,&local_80);
        (pppMngStPtr->m_matrix).value[0][0] = local_80.x;
        (pppMngStPtr->m_matrix).value[1][0] = local_80.y;
        (pppMngStPtr->m_matrix).value[2][0] = local_80.z;
        local_8c.x = (pppMngStPtr->m_matrix).value[0][1];
        local_8c.y = (pppMngStPtr->m_matrix).value[1][1];
        local_8c.z = (pppMngStPtr->m_matrix).value[2][1];
        PSVECScale((pppMngSt->m_scale).y,&local_8c,&local_8c);
        (pppMngStPtr->m_matrix).value[0][1] = local_8c.x;
        (pppMngStPtr->m_matrix).value[1][1] = local_8c.y;
        (pppMngStPtr->m_matrix).value[2][1] = local_8c.z;
        local_98.x = (pppMngStPtr->m_matrix).value[0][2];
        local_98.y = (pppMngStPtr->m_matrix).value[1][2];
        local_98.z = (pppMngStPtr->m_matrix).value[2][2];
        PSVECScale((pppMngSt->m_scale).z,&local_98,&local_98);
        (pppMngStPtr->m_matrix).value[0][2] = local_98.x;
        (pppMngStPtr->m_matrix).value[1][2] = local_98.y;
        (pppMngStPtr->m_matrix).value[2][2] = local_98.z;
        (pppMngStPtr->m_matrix).value[0][3] = (pppMngSt->m_position).x;
        (pppMngStPtr->m_matrix).value[1][3] = (pppMngSt->m_position).y;
        (pppMngStPtr->m_matrix).value[2][3] = (pppMngSt->m_position).z;
        return;
      }
      if (pppMngSt->m_ownerVisible == '\0') {
        pppMngSt->m_ownerVisible =
             (uint8_t)((int)((uint)*(byte *)((int)(pppMngSt->m_velocity).x + 0x9a) << 0x19) >> 0x1f)
        ;
      }
      if (pppMngSt->m_lockVisFromOwner == '\0') {
        uVar5 = '\0';
        uVar3 = *(uint *)((int)(pppMngSt->m_velocity).x + 0x60);
        if (((uVar3 & 1) != 0) && ((uVar3 & 0x400000) == 0)) {
          uVar5 = '\x01';
        }
        pppMngSt->m_isVisible = uVar5;
      }
      if (pppMngSt->m_lockScaleFromOwner == '\0') {
        fVar4 = (pppMngSt->m_velocity).x;
        bVar2 = false;
        iVar6 = *(int *)((int)fVar4 + 0xf8);
        if ((iVar6 != 0) && (*(int *)(iVar6 + 0x168) != 0)) {
          bVar2 = true;
        }
        if (bVar2) {
          fVar4 = *(float *)(*(int *)(iVar6 + 0x168) + 0x9c);
        }
        else {
          fVar4 = *(float *)((int)fVar4 + 0x4b0);
        }
        pppMngSt->m_ownerScale = fVar4;
        if (DOUBLE_8032fdf0 == (double)pppMngSt->m_ownerScale) {
          pppMngSt->m_ownerScaleMode = '\x01';
        }
        else if (DOUBLE_8032fe00 == (double)pppMngSt->m_ownerScale) {
          pppMngSt->m_ownerScaleMode = '\0';
        }
        else {
          pppMngSt->m_ownerScaleMode = '\x01';
        }
      }
      CalcSafeNodeWorldMatrix__Q26CChara6CModelFPA4_fPQ26CChara5CNode
                (*(CModel **)(*(int *)((int)(pppMngSt->m_velocity).x + 0xf8) + 0x168),
                 (Mtx *)auStack_40,(CNode *)(pppMngSt->m_velocity).z);
      PSVECNormalize((Vec *)auStack_40,(Vec *)auStack_40);
      PSVECNormalize((Vec *)(auStack_40 + 0x10),(Vec *)(auStack_40 + 0x10));
      PSVECNormalize(&VStack_20,&VStack_20);
    }
    PSMTXMultVecSR((Mtx *)auStack_40,&pppMngStPtr->m_position,&local_50);
    auStack_40._12_4_ = (float)auStack_40._12_4_ + local_50.x;
    local_24 = local_24 + local_50.y;
    local_14 = local_14 + local_50.z;
    PSMTXConcat((Mtx *)auStack_40,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
  }
LAB_80055cec:
  fVar4 = (pppMngSt->m_scale).x;
  if (FLOAT_8032fdfc != fVar4) {
    local_5c.x = (pppMngStPtr->m_matrix).value[0][0];
    local_5c.y = (pppMngStPtr->m_matrix).value[1][0];
    local_5c.z = (pppMngStPtr->m_matrix).value[2][0];
    PSVECScale(fVar4,&local_5c,&local_5c);
    (pppMngStPtr->m_matrix).value[0][0] = local_5c.x;
    (pppMngStPtr->m_matrix).value[1][0] = local_5c.y;
    (pppMngStPtr->m_matrix).value[2][0] = local_5c.z;
  }
  fVar4 = (pppMngSt->m_scale).y;
  if (FLOAT_8032fdfc != fVar4) {
    local_68.x = (pppMngStPtr->m_matrix).value[0][1];
    local_68.y = (pppMngStPtr->m_matrix).value[1][1];
    local_68.z = (pppMngStPtr->m_matrix).value[2][1];
    PSVECScale(fVar4,&local_68,&local_68);
    (pppMngStPtr->m_matrix).value[0][1] = local_68.x;
    (pppMngStPtr->m_matrix).value[1][1] = local_68.y;
    (pppMngStPtr->m_matrix).value[2][1] = local_68.z;
  }
  fVar4 = (pppMngSt->m_scale).z;
  if (FLOAT_8032fdfc == fVar4) {
    return;
  }
  local_74.x = (pppMngStPtr->m_matrix).value[0][2];
  local_74.y = (pppMngStPtr->m_matrix).value[1][2];
  local_74.z = (pppMngStPtr->m_matrix).value[2][2];
  PSVECScale(fVar4,&local_74,&local_74);
  (pppMngStPtr->m_matrix).value[0][2] = local_74.x;
  (pppMngStPtr->m_matrix).value[1][2] = local_74.y;
  (pppMngStPtr->m_matrix).value[2][2] = local_74.z;
  return;
}

