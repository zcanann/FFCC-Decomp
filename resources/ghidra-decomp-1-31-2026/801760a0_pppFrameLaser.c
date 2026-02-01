// Function: pppFrameLaser
// Entry: 801760a0
// Size: 1468 bytes

/* WARNING: Removing unreachable block (ram,0x80176640) */
/* WARNING: Removing unreachable block (ram,0x801760b0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameLaser(pppLaser *pppLaser,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  bool bVar4;
  _pppMngSt *p_Var5;
  _pppMngSt *p_Var6;
  uint uVar7;
  uint32_t uVar8;
  float fVar9;
  float *pfVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  float *pfVar15;
  int iVar16;
  double dVar17;
  double dVar18;
  Vec local_138;
  float local_12c;
  float local_128;
  float local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  Vec local_114;
  Vec local_108;
  Vec local_fc;
  float local_f0;
  float local_ec;
  float local_e8;
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
  Mtx MStack_b0;
  Mtx MStack_80;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  if (((DAT_8032ed70 == 0) && (param_2->m_stepValue != 9.18341e-41)) &&
     (pfVar15 = (float *)((int)(&pppLaser->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]),
     FLOAT_80333448 != pfVar15[0xf])) {
    bVar2 = pfVar15[7] == 0.0;
    if (bVar2) {
      fVar9 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((uint)param_2->m_payload[0x1e] * 0xc,pppEnvStPtr->m_stagePtr,
                                s_pppLaser_cpp_801e3048,0x7d);
      pfVar15[7] = fVar9;
      memset(pfVar15[7],0,(uint)param_2->m_payload[0x1e] * 0xc);
    }
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 0x10),&pppLaser->field0_0x0,param_2->m_graphId,
               pfVar15 + 4,pfVar15 + 5,pfVar15 + 6,param_2->m_payload + 0x14,
               param_2->m_payload + 0x18);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 4),&pppLaser->field0_0x0,param_2->m_graphId,
               pfVar15 + 1,pfVar15 + 2,pfVar15 + 3,param_2->m_payload + 8,param_2->m_payload + 0xc);
    pppCalcFrameShape__FPlRsRsRss
              (**(undefined4 **)
                 (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                 (int)param_2->m_stepValue * 4),(int)pfVar15 + 0x32,pfVar15 + 0xd,pfVar15 + 0xc,
               (int)*(short *)(param_2->m_payload + 0x2c));
    dVar18 = (double)FLOAT_80333428;
    iVar16 = 0;
    for (uVar14 = 0; (int)uVar14 < (int)(param_2->m_payload[0x3a] + 1); uVar14 = uVar14 + 1) {
      iVar13 = param_2->m_payload[0x1e] - 2;
      iVar12 = iVar13 * 0xc;
      for (; (int)uVar14 <= iVar13; iVar13 = iVar13 + -1) {
        pfVar10 = (float *)((int)pfVar15[7] + iVar12);
        local_114.x = *pfVar10;
        local_114.y = pfVar10[1];
        local_114.z = pfVar10[2];
        pppCopyVector__FR3Vec3Vec((Vec *)((int)pfVar15[7] + (iVar13 + 1) * 0xc),&local_114);
        iVar12 = iVar12 + -0xc;
      }
      local_fc.x = (float)dVar18;
      local_fc.y = (float)dVar18;
      local_fc.z = *pfVar15;
      if (uVar14 == 0) {
        PSMTXConcat(&pppMngStPtr->m_matrix,&(pppLaser->field0_0x0).m_localMatrix,&MStack_80);
        pfVar15[8] = MStack_80.value[0][3];
        pfVar15[9] = MStack_80.value[1][3];
        pfVar15[10] = MStack_80.value[2][3];
        PSMTXMultVec(&MStack_80,&local_fc,(Vec *)pfVar15[7]);
LAB_8017631c:
        local_12c = pfVar15[8];
        local_128 = pfVar15[9];
        local_124 = pfVar15[10];
        puVar11 = (undefined4 *)((int)pfVar15[7] + iVar16);
        local_120 = *puVar11;
        local_11c = puVar11[1];
        local_118 = puVar11[2];
        pppSubVector__FR3Vec3Vec3Vec(&local_108,&local_120,&local_12c);
        PSVECScale(FLOAT_8033344c,&local_108,&local_108);
        local_c0 = FLOAT_80333450;
        local_c4 = FLOAT_80333450;
        local_c8 = FLOAT_80333450;
        local_b4 = FLOAT_80333454;
        local_b8 = FLOAT_80333454;
        local_bc = FLOAT_80333454;
        local_f0 = pfVar15[8];
        local_ec = pfVar15[9];
        local_e8 = pfVar15[10];
        local_d8 = local_108.x;
        local_d4 = local_108.y;
        local_d0 = local_108.z;
        local_cc = FLOAT_80333428;
        iVar13 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                           (&MapMng,&local_f0,&local_108,0xffffffff);
        p_Var6 = pppMngStPtr;
        bVar4 = false;
        if (iVar13 == 0) {
          if (uVar14 == 0) {
            if ((*(char *)(pfVar15 + 0x13) != '\0') && (pfVar15[0xf] - FLOAT_80333458 < *pfVar15)) {
              p_Var5 = pppMngStPtr + 0x5f2411;
              *pfVar15 = pfVar15[0xf] - FLOAT_80333458;
              uVar7 = (pppLaser->field0_0x0).m_graphId;
              iVar13 = (int)&p_Var5->m_scale / 0x158 + ((int)&p_Var5->m_scale >> 0x1f);
              ParticleFrameCallback__5CGameFiiiiiP3Vec
                        (&Game.game,iVar13 - (iVar13 >> 0x1f),(int)p_Var6->m_kind,
                         (int)p_Var6->m_nodeIndex,3,
                         ((int)uVar7 >> 0xc) + (uint)((int)uVar7 < 0 && (uVar7 & 0xfff) != 0));
              *(undefined *)(pfVar15 + 0x13) = 0;
            }
            if (*(char *)(pfVar15 + 0x13) != '\0') {
              *pfVar15 = *pfVar15 + pfVar15[1];
            }
          }
        }
        else {
          bVar4 = true;
          CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,(int)pfVar15[7] + iVar16);
          dVar17 = (double)PSVECDistance((Vec *)((int)pfVar15[7] + iVar16),(Vec *)(pfVar15 + 8));
          *pfVar15 = (float)dVar17;
        }
        if (uVar14 == 0) {
          local_fc.x = FLOAT_80333428;
          local_fc.y = FLOAT_80333428;
          local_fc.z = *pfVar15;
          PSMTXMultVec(&MStack_80,&local_fc,(Vec *)((int)pfVar15[7] + iVar16));
        }
        if (param_2->m_payload[0x3b] == '\0') {
          pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
                    ((double)(pppMngStPtr->m_paramD * *(float *)(param_2->m_payload + 0x24)),
                     (double)*(float *)(param_2->m_payload + 0x20),pppMngStPtr,pfVar15 + 8,
                     &local_108);
        }
        if (param_2->m_payload[0x3c] == '\0') {
          uVar8 = param_2->m_arg3;
          bVar3 = *(byte *)((int)pfVar15 + 0x2d);
          bVar1 = param_2->m_payload[0x1d] <= bVar3;
          if (bVar1) {
            *(undefined *)((int)pfVar15 + 0x2d) = 0;
          }
          else {
            *(byte *)((int)pfVar15 + 0x2d) = bVar3 + 1;
          }
          if (bVar1 && (bVar4 && uVar8 != 0xffffffff)) {
            if (pppMngStPtr->m_pppPDataVals + param_2->m_arg3 == (_pppPDataVal *)0x0) {
              iVar13 = 0;
            }
            else {
              iVar13 = pppCreatePObject__FP9_pppMngStP12_pppPDataVal
                                 (pppMngStPtr,pppMngStPtr->m_pppPDataVals + param_2->m_arg3);
              *(pppLaser **)(iVar13 + 4) = pppLaser;
            }
            puVar11 = (undefined4 *)(iVar13 + *(int *)param_2->m_payload + 0x80);
            *puVar11 = *(undefined4 *)((int)pfVar15[7] + iVar16);
            puVar11[1] = *(float *)(param_2->m_payload + 0x34) +
                         *(float *)((int)pfVar15[7] + iVar16 + 4);
            puVar11[2] = *(undefined4 *)((int)pfVar15[7] + iVar16 + 8);
          }
        }
      }
      else if (!bVar2) {
        uStack_44 = uVar14 ^ 0x80000000;
        local_50 = 0x43300000;
        uStack_4c = param_2->m_payload[0x3a] + 1 ^ 0x80000000;
        local_48 = 0x43300000;
        iVar13 = GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f
                           ((double)((FLOAT_80333448 /
                                     (float)((double)CONCAT44(0x43300000,uStack_4c) -
                                            DOUBLE_80333440)) *
                                    (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80333440
                                           )),pppMngStPtr,&MStack_b0);
        if (iVar13 != 0) {
          PSMTXConcat(&MStack_b0,&(pppLaser->field0_0x0).m_localMatrix,&MStack_b0);
          PSMTXMultVec(&MStack_b0,&local_fc,(Vec *)((int)pfVar15[7] + iVar16));
          goto LAB_8017631c;
        }
        bVar2 = true;
      }
      iVar16 = iVar16 + 0xc;
    }
    if (bVar2) {
      iVar16 = 0;
      for (iVar13 = 0; iVar13 < (int)(uint)param_2->m_payload[0x1e]; iVar13 = iVar13 + 1) {
        pfVar10 = (float *)pfVar15[7];
        local_138.x = *pfVar10;
        local_138.y = pfVar10[1];
        local_138.z = pfVar10[2];
        pppCopyVector__FR3Vec3Vec((Vec *)((int)pfVar10 + iVar16),&local_138);
        iVar16 = iVar16 + 0xc;
      }
    }
  }
  return;
}

