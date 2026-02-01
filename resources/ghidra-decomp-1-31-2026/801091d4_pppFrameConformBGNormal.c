// Function: pppFrameConformBGNormal
// Entry: 801091d4
// Size: 1552 bytes

/* WARNING: Removing unreachable block (ram,0x801097c8) */
/* WARNING: Removing unreachable block (ram,0x801097c0) */
/* WARNING: Removing unreachable block (ram,0x801097b8) */
/* WARNING: Removing unreachable block (ram,0x801091f4) */
/* WARNING: Removing unreachable block (ram,0x801091ec) */
/* WARNING: Removing unreachable block (ram,0x801091e4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameConformBGNormal(pppConformBGNormal *pppConformBGNormal,UnkB *param_2,UnkC *param_3)

{
  char cVar1;
  float fVar2;
  float fVar3;
  _pppMngSt *pppMngSt;
  int iVar4;
  float fVar5;
  Vec *inVec;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  Quat local_1ac;
  Quat local_19c;
  Quat local_18c;
  float local_17c;
  float local_178;
  float local_174;
  Vec local_170;
  Vec local_164;
  Vec local_158;
  Vec local_14c;
  Vec local_140;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
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
  Mtx MStack_b4;
  Mtx local_84;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    fVar5 = (pppMngStPtr->m_velocity).y;
    iVar4 = 0;
    fVar2 = (pppMngStPtr->m_matrix).value[0][3];
    dVar9 = (double)fVar2;
    dVar8 = (double)(pppMngStPtr->m_matrix).value[1][3];
    fVar3 = (pppMngStPtr->m_matrix).value[2][3];
    dVar7 = (double)fVar3;
    inVec = (Vec *)((int)(&pppConformBGNormal->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    if ((Game.game.m_currentSceneId != 7) || (*(char *)&param_2->m_stepValue == '\x02')) {
      cVar1 = *(char *)&param_2->m_stepValue;
      if (cVar1 == '\0') {
        if ((int)((uint)*(byte *)((int)fVar5 + 0x50) << 0x18) < 0) {
          local_164.x = *(float *)((int)fVar5 + 0x4ec);
          local_164.y = *(float *)((int)fVar5 + 0x4f0);
          local_164.z = *(float *)((int)fVar5 + 0x4f4);
        }
        else {
          local_164.x = FLOAT_80331908;
          local_164.y = FLOAT_8033190c;
          local_164.z = FLOAT_80331908;
        }
      }
      else if (cVar1 == '\x01') {
        iVar4 = 1;
        GetTargetCursor__5CGameFiR3VecR3Vec
                  (&Game.game,(pppMngStPtr->m_hitParams).m_particleIndex,&local_170,&local_164);
      }
      else if (cVar1 == '\x02') {
        local_17c = FLOAT_80331908;
        local_178 = FLOAT_80331910;
        local_174 = FLOAT_80331908;
        local_f0 = (float)(dVar8 + (double)(float)param_2->m_arg3);
        local_c4 = FLOAT_80331914;
        local_c8 = FLOAT_80331914;
        local_cc = FLOAT_80331914;
        local_b8 = FLOAT_80331918;
        local_bc = FLOAT_80331918;
        local_c0 = FLOAT_80331918;
        local_dc = FLOAT_80331908;
        local_d8 = FLOAT_80331910;
        local_d4 = FLOAT_80331908;
        local_d0 = FLOAT_80331908;
        local_f4 = fVar2;
        local_ec = fVar3;
        iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                          (&MapMng,&local_f4,&local_17c,0xffffffff);
        if (iVar4 == 0) {
          local_164.x = FLOAT_80331908;
          local_164.y = FLOAT_8033190c;
          local_164.z = FLOAT_80331908;
          local_170.x = (float)dVar9;
          local_170.y = (float)dVar8;
          local_170.z = (float)dVar7;
        }
        else {
          CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_170);
          GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&local_164);
          if (local_170.y < (float)(dVar8 - (double)FLOAT_8033191c)) {
            local_170.y = (float)dVar8;
          }
        }
      }
      if (*(char *)&inVec[1].x == '\0') {
        *(undefined *)&inVec[1].x = 1;
        inVec->x = local_164.x;
        inVec->y = local_164.y;
        inVec->z = local_164.z;
      }
      local_18c.x = inVec->x;
      local_18c.y = inVec->y;
      local_18c.z = inVec->z;
      local_18c.w = FLOAT_8033190c;
      local_19c.x = local_164.x;
      local_19c.y = local_164.y;
      local_19c.z = local_164.z;
      local_19c.w = FLOAT_8033190c;
      C_QUATSlerp((double)(float)param_2->m_initWOrk,&local_18c,&local_19c,&local_1ac);
      inVec->x = local_1ac.x;
      inVec->y = local_1ac.y;
      inVec->z = local_1ac.z;
      PSVECNormalize(inVec,&local_158);
      if ((*(char *)&param_2->m_stepValue == '\0') && (fVar5 != 0.0)) {
        dVar6 = (double)sin((double)*(float *)((int)fVar5 + 0x1a8));
        local_14c.x = (float)dVar6;
        local_14c.y = FLOAT_80331908;
        dVar6 = (double)cos((double)*(float *)((int)fVar5 + 0x1a8));
        local_14c.z = (float)dVar6;
        PSVECCrossProduct(&local_14c,&local_158,&local_140);
        PSVECNormalize(&local_140,&local_140);
        PSVECCrossProduct(&local_158,&local_140,&local_14c);
        PSVECNormalize(&local_14c,&local_14c);
      }
      else {
        local_140.y = FLOAT_80331908;
        local_140.x = FLOAT_8033190c;
        local_140.z = FLOAT_80331908;
        PSVECCrossProduct(&local_158,&local_140,&local_14c);
        PSVECNormalize(&local_14c,&local_14c);
        PSVECCrossProduct(&local_14c,&local_158,&local_140);
        PSVECNormalize(&local_140,&local_140);
      }
      PSMTXIdentity(&local_84);
      local_84.value[0][0] = local_140.x;
      local_84.value[0][1] = local_14c.x;
      local_84.value[0][2] = local_158.x;
      local_84.value[1][0] = local_140.y;
      local_84.value[1][1] = local_14c.y;
      local_84.value[1][2] = local_158.y;
      local_84.value[2][0] = local_140.z;
      local_84.value[2][1] = local_14c.z;
      local_84.value[2][2] = local_158.z;
      PSMTXCopy(&local_84,&pppMngStPtr->m_matrix);
      PSMTXScale((pppMngStPtr->m_scale).x,(pppMngStPtr->m_scale).y,(pppMngStPtr->m_scale).z,
                 &MStack_b4);
      PSMTXConcat(&MStack_b4,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
      cVar1 = *(char *)&param_2->m_stepValue;
      if (cVar1 == '\0') {
        if ((int)((uint)*(byte *)((int)fVar5 + 0x50) << 0x18) < 0) {
          (pppMngStPtr->m_matrix).value[0][3] = *(float *)((int)fVar5 + 0x15c);
          (pppMngStPtr->m_matrix).value[1][3] = *(float *)((int)fVar5 + 0x160);
          (pppMngStPtr->m_matrix).value[2][3] = *(float *)((int)fVar5 + 0x164);
        }
        else if (((*(byte *)((int)fVar5 + 0x9a) & 1) == 0) || (*(int *)((int)fVar5 + 0x18c) == 0)) {
          local_134 = *(undefined4 *)((int)fVar5 + 0x15c);
          local_130 = *(undefined4 *)((int)fVar5 + 0x160);
          local_12c = *(undefined4 *)((int)fVar5 + 0x164);
          local_1b8 = FLOAT_80331908;
          local_1b4 = FLOAT_80331910;
          local_1b0 = FLOAT_80331908;
          local_104 = FLOAT_80331914;
          local_108 = FLOAT_80331914;
          local_10c = FLOAT_80331914;
          local_f8 = FLOAT_80331918;
          local_fc = FLOAT_80331918;
          local_100 = FLOAT_80331918;
          local_11c = FLOAT_80331908;
          local_118 = FLOAT_80331910;
          local_114 = FLOAT_80331908;
          local_110 = FLOAT_80331908;
          iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                            (&MapMng,&local_134,&local_1b8,0xffffffff);
          if (iVar4 == 0) {
            fVar2 = *(float *)((int)fVar5 + 0x164);
            (pppMngStPtr->m_matrix).value[0][3] = *(float *)((int)fVar5 + 0x15c);
            (pppMngStPtr->m_matrix).value[1][3] = (float)dVar8;
            (pppMngStPtr->m_matrix).value[2][3] = fVar2;
          }
          else {
            CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_170);
            (pppMngStPtr->m_matrix).value[0][3] = local_170.x;
            (pppMngStPtr->m_matrix).value[1][3] = local_170.y;
            (pppMngStPtr->m_matrix).value[2][3] = local_170.z;
          }
        }
        else {
          fVar2 = *(float *)(*(int *)((int)fVar5 + 0x18c) + 0x160);
          fVar3 = *(float *)((int)fVar5 + 0x164);
          (pppMngStPtr->m_matrix).value[0][3] = *(float *)((int)fVar5 + 0x15c);
          (pppMngStPtr->m_matrix).value[1][3] = fVar2;
          (pppMngStPtr->m_matrix).value[2][3] = fVar3;
        }
      }
      else if (cVar1 == '\x01') {
        if (iVar4 == 0) {
          (pppMngStPtr->m_matrix).value[0][3] = (float)dVar9;
          (pppMngStPtr->m_matrix).value[1][3] = (float)dVar8;
          (pppMngStPtr->m_matrix).value[2][3] = (float)dVar7;
        }
        else {
          (pppMngStPtr->m_matrix).value[0][3] = local_170.x;
          (pppMngStPtr->m_matrix).value[1][3] = local_170.y;
          (pppMngStPtr->m_matrix).value[2][3] = local_170.z;
        }
      }
      else if (cVar1 == '\x02') {
        (pppMngStPtr->m_matrix).value[0][3] = local_170.x;
        (pppMngStPtr->m_matrix).value[1][3] = local_170.y;
        (pppMngStPtr->m_matrix).value[2][3] = local_170.z;
      }
      (pppMngStPtr->m_matrix).value[1][3] =
           (pppMngStPtr->m_matrix).value[1][3] + (float)param_2->m_dataValIndex;
      pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
  }
  return;
}

