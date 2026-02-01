// Function: pppFrameYmLaser
// Entry: 800d31d4
// Size: 1308 bytes

/* WARNING: Removing unreachable block (ram,0x800d36d4) */
/* WARNING: Removing unreachable block (ram,0x800d31e4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmLaser(pppYmLaser *pppYmLaser,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  bool bVar4;
  uint32_t uVar5;
  float fVar6;
  float *pfVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  float *pfVar12;
  int iVar13;
  double dVar14;
  double dVar15;
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
  
  if ((DAT_8032ed70 == 0) && (param_2->m_stepValue != 9.18341e-41)) {
    pfVar12 = (float *)((int)(&pppYmLaser->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    bVar2 = pfVar12[7] == 0.0;
    if (bVar2) {
      fVar6 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((uint)param_2->m_payload[0x1e] * 0xc,pppEnvStPtr->m_stagePtr,
                                s_pppYmLaser_cpp_801db4b0,0x5d);
      pfVar12[7] = fVar6;
      memset(pfVar12[7],0,(uint)param_2->m_payload[0x1e] * 0xc);
    }
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 0x10),&pppYmLaser->field0_0x0,param_2->m_graphId,
               pfVar12 + 4,pfVar12 + 5,pfVar12 + 6,param_2->m_payload + 0x14,
               param_2->m_payload + 0x18);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)(param_2->m_payload + 4),&pppYmLaser->field0_0x0,param_2->m_graphId,
               pfVar12 + 1,pfVar12 + 2,pfVar12 + 3,param_2->m_payload + 8,param_2->m_payload + 0xc);
    pppCalcFrameShape__FPlRsRsRss
              (**(undefined4 **)
                 (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                 (int)param_2->m_stepValue * 4),(int)pfVar12 + 0x32,pfVar12 + 0xd,pfVar12 + 0xc,
               (int)*(short *)(param_2->m_payload + 0x2c));
    dVar15 = (double)FLOAT_80330dc0;
    iVar13 = 0;
    for (uVar11 = 0; (int)uVar11 < (int)(param_2->m_payload[0x3a] + 1); uVar11 = uVar11 + 1) {
      iVar10 = param_2->m_payload[0x1e] - 2;
      iVar9 = iVar10 * 0xc;
      for (; (int)uVar11 <= iVar10; iVar10 = iVar10 + -1) {
        pfVar7 = (float *)((int)pfVar12[7] + iVar9);
        local_114.x = *pfVar7;
        local_114.y = pfVar7[1];
        local_114.z = pfVar7[2];
        pppCopyVector__FR3Vec3Vec((Vec *)((int)pfVar12[7] + (iVar10 + 1) * 0xc),&local_114);
        iVar9 = iVar9 + -0xc;
      }
      local_fc.x = (float)dVar15;
      local_fc.y = (float)dVar15;
      local_fc.z = *pfVar12;
      if (uVar11 == 0) {
        PSMTXConcat(&pppMngStPtr->m_matrix,&(pppYmLaser->field0_0x0).m_localMatrix,&MStack_80);
        pfVar12[8] = MStack_80.value[0][3];
        pfVar12[9] = MStack_80.value[1][3];
        pfVar12[10] = MStack_80.value[2][3];
        PSMTXMultVec(&MStack_80,&local_fc,(Vec *)pfVar12[7]);
LAB_800d3434:
        local_12c = pfVar12[8];
        local_128 = pfVar12[9];
        local_124 = pfVar12[10];
        puVar8 = (undefined4 *)((int)pfVar12[7] + iVar13);
        local_120 = *puVar8;
        local_11c = puVar8[1];
        local_118 = puVar8[2];
        pppSubVector__FR3Vec3Vec3Vec(&local_108,&local_120,&local_12c);
        PSVECScale(FLOAT_80330de4,&local_108,&local_108);
        local_c0 = FLOAT_80330de8;
        local_c4 = FLOAT_80330de8;
        local_c8 = FLOAT_80330de8;
        local_b4 = FLOAT_80330dec;
        local_b8 = FLOAT_80330dec;
        local_bc = FLOAT_80330dec;
        local_f0 = pfVar12[8];
        local_ec = pfVar12[9];
        local_e8 = pfVar12[10];
        local_d8 = local_108.x;
        local_d4 = local_108.y;
        local_d0 = local_108.z;
        local_cc = FLOAT_80330dc0;
        iVar10 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                           (&MapMng,&local_f0,&local_108,0xffffffff);
        bVar4 = false;
        if (iVar10 == 0) {
          if (uVar11 == 0) {
            *pfVar12 = *pfVar12 + pfVar12[1];
          }
        }
        else {
          bVar4 = true;
          CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,(int)pfVar12[7] + iVar13);
          dVar14 = (double)PSVECDistance((Vec *)((int)pfVar12[7] + iVar13),(Vec *)(pfVar12 + 8));
          *pfVar12 = (float)dVar14;
        }
        if (uVar11 == 0) {
          local_fc.x = FLOAT_80330dc0;
          local_fc.y = FLOAT_80330dc0;
          local_fc.z = *pfVar12;
          PSMTXMultVec(&MStack_80,&local_fc,(Vec *)((int)pfVar12[7] + iVar13));
        }
        if (param_2->m_payload[0x3b] == '\0') {
          pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
                    ((double)(pppMngStPtr->m_paramD * *(float *)(param_2->m_payload + 0x24)),
                     (double)*(float *)(param_2->m_payload + 0x20),pppMngStPtr,pfVar12 + 8,
                     &local_108);
        }
        if (param_2->m_payload[0x3c] == '\0') {
          uVar5 = param_2->m_arg3;
          bVar3 = *(byte *)((int)pfVar12 + 0x2d);
          bVar1 = param_2->m_payload[0x1d] <= bVar3;
          if (bVar1) {
            *(undefined *)((int)pfVar12 + 0x2d) = 0;
          }
          else {
            *(byte *)((int)pfVar12 + 0x2d) = bVar3 + 1;
          }
          if (bVar1 && (bVar4 && uVar5 != 0xffffffff)) {
            if (pppMngStPtr->m_pppPDataVals + param_2->m_arg3 == (_pppPDataVal *)0x0) {
              iVar10 = 0;
            }
            else {
              iVar10 = pppCreatePObject__FP9_pppMngStP12_pppPDataVal
                                 (pppMngStPtr,pppMngStPtr->m_pppPDataVals + param_2->m_arg3);
              *(pppYmLaser **)(iVar10 + 4) = pppYmLaser;
            }
            puVar8 = (undefined4 *)(iVar10 + *(int *)param_2->m_payload + 0x80);
            *puVar8 = *(undefined4 *)((int)pfVar12[7] + iVar13);
            puVar8[1] = *(float *)(param_2->m_payload + 0x34) +
                        *(float *)((int)pfVar12[7] + iVar13 + 4);
            puVar8[2] = *(undefined4 *)((int)pfVar12[7] + iVar13 + 8);
          }
        }
      }
      else if (!bVar2) {
        uStack_44 = uVar11 ^ 0x80000000;
        local_50 = 0x43300000;
        uStack_4c = param_2->m_payload[0x3a] + 1 ^ 0x80000000;
        local_48 = 0x43300000;
        iVar10 = GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f
                           ((double)((FLOAT_80330de0 /
                                     (float)((double)CONCAT44(0x43300000,uStack_4c) -
                                            DOUBLE_80330dd8)) *
                                    (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330dd8
                                           )),pppMngStPtr,&MStack_b0);
        if (iVar10 != 0) {
          PSMTXConcat(&MStack_b0,&(pppYmLaser->field0_0x0).m_localMatrix,&MStack_b0);
          PSMTXMultVec(&MStack_b0,&local_fc,(Vec *)((int)pfVar12[7] + iVar13));
          goto LAB_800d3434;
        }
        bVar2 = true;
      }
      iVar13 = iVar13 + 0xc;
    }
    if (bVar2) {
      iVar13 = 0;
      for (iVar10 = 0; iVar10 < (int)(uint)param_2->m_payload[0x1e]; iVar10 = iVar10 + 1) {
        pfVar7 = (float *)pfVar12[7];
        local_138.x = *pfVar7;
        local_138.y = pfVar7[1];
        local_138.z = pfVar7[2];
        pppCopyVector__FR3Vec3Vec((Vec *)((int)pfVar7 + iVar13),&local_138);
        iVar13 = iVar13 + 0xc;
      }
    }
  }
  return;
}

