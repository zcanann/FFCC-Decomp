// Function: pppFrameYmTracer
// Entry: 800934c4
// Size: 1944 bytes

/* WARNING: Removing unreachable block (ram,0x80093c40) */
/* WARNING: Removing unreachable block (ram,0x80093c38) */
/* WARNING: Removing unreachable block (ram,0x80093c30) */
/* WARNING: Removing unreachable block (ram,0x800934e4) */
/* WARNING: Removing unreachable block (ram,0x800934dc) */
/* WARNING: Removing unreachable block (ram,0x800934d4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmTracer(pppYmTracer *pppYmTracer,UnkB *param_2,UnkC *param_3)

{
  byte bVar1;
  byte bVar2;
  Vec *source;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  Vec *dest;
  float *pfVar6;
  short sVar7;
  int iVar8;
  Vec *pVVar9;
  float *pfVar10;
  float *pfVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  Vec local_1f8;
  Vec local_1ec;
  Vec local_1e0;
  Vec local_1d4;
  Vec local_1c8;
  Vec local_1bc;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  pppFMATRIX local_150;
  pppFMATRIX local_120;
  float local_f0 [12];
  float local_c0 [12];
  pppFMATRIX pStack_90;
  undefined4 local_60;
  uint uStack_5c;
  
  if (DAT_8032ed70 == 0) {
    pfVar6 = (float *)((int)(&pppYmTracer->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    source = (Vec *)pfVar6[10];
    if (source == (Vec *)0x0) {
      fVar3 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               ((uint)*(ushort *)(param_2->m_payload + 4) * 0x28,
                                pppEnvStPtr->m_stagePtr,s_pppYmTracer_cpp_801d9ce0,0xeb);
      pfVar6[10] = fVar3;
      fVar3 = FLOAT_803306e8;
      source = (Vec *)pfVar6[10];
      pVVar9 = source;
      for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(param_2->m_payload + 4); iVar5 = iVar5 + 1) {
        *(undefined2 *)&pVVar9[2].z = 0xffff;
        *(uint8_t *)((int)&pVVar9[2].y + 3) = param_2->m_payload[8];
        *(char *)((int)&pVVar9[2].z + 2) =
             (char)((ushort)param_2->m_payload[8] / *(ushort *)(param_2->m_payload + 6));
        pVVar9->z = fVar3;
        pVVar9->y = fVar3;
        pVVar9->x = fVar3;
        pVVar9[2].x = fVar3;
        pVVar9[1].z = fVar3;
        pVVar9[1].y = fVar3;
        pVVar9 = (Vec *)&pVVar9[3].y;
      }
    }
    if (param_2->m_graphId == (pppYmTracer->field0_0x0).m_graphId) {
      if (param_2->m_initWOrk == 0xffffffff) {
        puVar4 = &DAT_801eadc8;
      }
      else {
        puVar4 = (undefined4 *)
                 ((int)&pppMngStPtr->m_pppPDataVals[param_2->m_initWOrk].m_pppPObjLink[10].m_owner +
                 (int)param_2->m_stepValue);
      }
      pfVar6[8] = (float)puVar4;
      if (param_2->m_arg3 == 0xffffffff) {
        puVar4 = &DAT_801eadc8;
      }
      else {
        puVar4 = (undefined4 *)
                 ((int)&pppMngStPtr->m_pppPDataVals[param_2->m_arg3].m_pppPObjLink[10].m_owner +
                 *(int *)param_2->m_payload);
      }
      pfVar6[9] = (float)puVar4;
    }
    if (*(ushort *)(pfVar6 + 0xb) + 1 < (uint)*(ushort *)(param_2->m_payload + 4)) {
      iVar5 = *(ushort *)(param_2->m_payload + 4) - 2;
      pfVar11 = (float *)((int)source + iVar5 * 0x28);
      for (; fVar3 = FLOAT_803306e8, -1 < iVar5; iVar5 = iVar5 + -1) {
        local_1e0.x = *pfVar11;
        local_1e0.y = pfVar11[1];
        pVVar9 = (Vec *)((int)source + (iVar5 + 1) * 0x28);
        local_1e0.z = pfVar11[2];
        pppCopyVector__FR3Vec3Vec(pVVar9,&local_1e0);
        local_1d4.x = pfVar11[4];
        local_1d4.y = pfVar11[5];
        local_1d4.z = pfVar11[6];
        pppCopyVector__FR3Vec3Vec((Vec *)&pVVar9[1].y,&local_1d4);
        *(undefined2 *)(pfVar11 + 0x12) = *(undefined2 *)(pfVar11 + 8);
        *(undefined *)((int)pfVar11 + 0x4a) = *(undefined *)((int)pfVar11 + 0x22);
        *(undefined *)(pfVar11 + 0x11) = *(undefined *)(pfVar11 + 7);
        *(undefined *)((int)pfVar11 + 0x45) = *(undefined *)((int)pfVar11 + 0x1d);
        *(undefined *)((int)pfVar11 + 0x46) = *(undefined *)((int)pfVar11 + 0x1e);
        *(undefined *)((int)pfVar11 + 0x47) = *(undefined *)((int)pfVar11 + 0x1f);
        pfVar11 = pfVar11 + -10;
      }
      source = (Vec *)pfVar6[10];
      *(undefined2 *)&source[2].z = 0xffff;
      *(uint8_t *)((int)&source[2].y + 3) = param_2->m_payload[8];
      *(char *)((int)&source[2].z + 2) =
           (char)((ushort)param_2->m_payload[8] / *(ushort *)(param_2->m_payload + 6));
      source->z = fVar3;
      source->y = fVar3;
      source->x = fVar3;
      source[2].x = fVar3;
      source[1].z = fVar3;
      source[1].y = fVar3;
      fVar3 = *(float *)pfVar6[8];
      *pfVar6 = fVar3;
      source->x = fVar3;
      fVar3 = *(float *)((int)pfVar6[8] + 4);
      pfVar6[1] = fVar3;
      source->y = fVar3;
      fVar3 = *(float *)((int)pfVar6[8] + 8);
      pfVar6[2] = fVar3;
      source->z = fVar3;
      fVar3 = *(float *)pfVar6[9];
      pfVar6[4] = fVar3;
      source[1].y = fVar3;
      fVar3 = *(float *)((int)pfVar6[9] + 4);
      pfVar6[5] = fVar3;
      source[1].z = fVar3;
      fVar3 = *(float *)((int)pfVar6[9] + 8);
      pfVar6[6] = fVar3;
      source[2].x = fVar3;
      *(undefined2 *)&source[2].z = *(undefined2 *)(param_2->m_payload + 6);
      *(uint8_t *)((int)&source[2].y + 3) = param_2->m_payload[8];
      local_150.value[0][0] = (pppYmTracer->field0_0x0).m_localMatrix.value[0][0];
      local_150.value[0][1] = (pppYmTracer->field0_0x0).m_localMatrix.value[0][1];
      local_150.value[0][2] = (pppYmTracer->field0_0x0).m_localMatrix.value[0][2];
      local_150.value[0][3] = (pppYmTracer->field0_0x0).m_localMatrix.value[0][3];
      local_150.value[1][0] = (pppYmTracer->field0_0x0).m_localMatrix.value[1][0];
      local_150.value[1][1] = (pppYmTracer->field0_0x0).m_localMatrix.value[1][1];
      local_150.value[1][2] = (pppYmTracer->field0_0x0).m_localMatrix.value[1][2];
      local_150.value[1][3] = (pppYmTracer->field0_0x0).m_localMatrix.value[1][3];
      local_150.value[2][0] = (pppYmTracer->field0_0x0).m_localMatrix.value[2][0];
      local_150.value[2][1] = (pppYmTracer->field0_0x0).m_localMatrix.value[2][1];
      local_150.value[2][2] = (pppYmTracer->field0_0x0).m_localMatrix.value[2][2];
      local_150.value[2][3] = (pppYmTracer->field0_0x0).m_localMatrix.value[2][3];
      local_120.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
      local_120.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
      local_120.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
      local_120.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
      local_120.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
      local_120.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
      local_120.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
      local_120.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
      local_120.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
      local_120.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
      local_120.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
      local_120.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
      pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&pStack_90,&local_120,&local_150);
      PSMTXMultVec(&pStack_90,source,source);
      PSMTXMultVec(&pStack_90,(Vec *)&source[1].y,(Vec *)&source[1].y);
      *(short *)(pfVar6 + 0xb) = *(short *)(pfVar6 + 0xb) + 1;
      if (3 < *(ushort *)(pfVar6 + 0xb)) {
        local_60 = 0x43300000;
        sVar7 = 0;
        uStack_5c = param_2->m_payload[9] + 1 ^ 0x80000000;
        dVar12 = (double)(FLOAT_803306ec /
                         (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_803306f8));
        dVar14 = DOUBLE_803306f8;
        for (iVar5 = 0; iVar5 < (int)(uint)param_2->m_payload[9]; iVar5 = iVar5 + 1) {
          local_180 = source->x;
          local_17c = source->y;
          uStack_5c = iVar5 + 1U ^ 0x80000000;
          local_178 = source->z;
          local_60 = 0x43300000;
          local_174 = source[3].y;
          local_170 = source[3].z;
          dVar13 = (double)(float)(dVar12 * (double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                           dVar14));
          local_16c = source[4].x;
          local_168 = source[6].z;
          local_164 = source[7].x;
          local_160 = source[7].y;
          local_15c = source[10].x;
          local_158 = source[10].y;
          local_154 = source[10].z;
          GetSplinePos__5CUtilFR3Vec3Vec3Vec3Vec3Vecff
                    (dVar13,(double)FLOAT_803306ec,&DAT_8032ec70,
                     local_c0 + ((param_2->m_payload[9] - 1) - iVar5) * 3,&local_15c,&local_168,
                     &local_174,&local_180);
          local_1b0 = source[1].y;
          local_1ac = source[1].z;
          local_1a8 = source[2].x;
          local_1a4 = source[4].z;
          local_1a0 = source[5].x;
          local_19c = source[5].y;
          local_198 = source[8].x;
          local_194 = source[8].y;
          local_190 = source[8].z;
          local_18c = source[0xb].y;
          local_188 = source[0xb].z;
          local_184 = source[0xc].x;
          GetSplinePos__5CUtilFR3Vec3Vec3Vec3Vec3Vecff
                    (dVar13,(double)FLOAT_803306ec,&DAT_8032ec70,
                     local_f0 + ((param_2->m_payload[9] - 1) - iVar5) * 3,&local_18c,&local_198,
                     &local_1a4,&local_1b0);
          sVar7 = sVar7 + 1;
          *(short *)(pfVar6 + 0xb) = *(short *)(pfVar6 + 0xb) + 1;
          if ((uint)*(ushort *)(param_2->m_payload + 4) <= *(ushort *)(pfVar6 + 0xb) + 1) break;
        }
        for (iVar5 = 0; iVar5 < sVar7; iVar5 = iVar5 + 1) {
          iVar8 = *(ushort *)(param_2->m_payload + 4) - 2;
          pfVar11 = (float *)((int)source + iVar8 * 0x28);
          for (; 1 < iVar8; iVar8 = iVar8 + -1) {
            local_1f8.x = *pfVar11;
            local_1f8.y = pfVar11[1];
            pVVar9 = (Vec *)((int)source + (iVar8 + 1) * 0x28);
            local_1f8.z = pfVar11[2];
            pppCopyVector__FR3Vec3Vec(pVVar9,&local_1f8);
            local_1ec.x = pfVar11[4];
            local_1ec.y = pfVar11[5];
            local_1ec.z = pfVar11[6];
            pppCopyVector__FR3Vec3Vec((Vec *)&pVVar9[1].y,&local_1ec);
            *(undefined2 *)(pfVar11 + 0x12) = *(undefined2 *)(pfVar11 + 8);
            *(undefined *)((int)pfVar11 + 0x4a) = *(undefined *)((int)pfVar11 + 0x22);
            *(undefined *)(pfVar11 + 0x11) = *(undefined *)(pfVar11 + 7);
            *(undefined *)((int)pfVar11 + 0x45) = *(undefined *)((int)pfVar11 + 0x1d);
            *(undefined *)((int)pfVar11 + 0x46) = *(undefined *)((int)pfVar11 + 0x1e);
            *(undefined *)((int)pfVar11 + 0x47) = *(undefined *)((int)pfVar11 + 0x1f);
            pfVar11 = pfVar11 + -10;
          }
        }
        pfVar10 = local_c0;
        pfVar11 = local_f0;
        pVVar9 = source;
        for (iVar5 = 0; iVar5 < sVar7; iVar5 = iVar5 + 1) {
          dest = (Vec *)((int)source + (iVar5 + 2) * 0x28);
          *(uint8_t *)((int)&pVVar9[9].x + 3) =
               param_2->m_payload[8] - (char)(iVar5 + 2) * *(char *)((int)&pVVar9[9].y + 2);
          local_1bc.x = *pfVar10;
          local_1bc.y = pfVar10[1];
          local_1bc.z = pfVar10[2];
          pppCopyVector__FR3Vec3Vec(dest,&local_1bc);
          local_1c8.x = *pfVar11;
          local_1c8.y = pfVar11[1];
          local_1c8.z = pfVar11[2];
          pppCopyVector__FR3Vec3Vec((Vec *)&dest[1].y,&local_1c8);
          pVVar9 = (Vec *)&pVVar9[3].y;
          pfVar10 = pfVar10 + 3;
          pfVar11 = pfVar11 + 3;
        }
      }
    }
    for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(pfVar6 + 0xb); iVar5 = iVar5 + 1) {
      if (0 < *(short *)&source[2].z) {
        bVar1 = *(byte *)((int)&source[2].z + 2);
        bVar2 = *(byte *)((int)&source[2].y + 3);
        if ((int)((uint)bVar2 - (uint)bVar1) < 1) {
          *(undefined *)((int)&source[2].y + 3) = 0;
        }
        else {
          *(byte *)((int)&source[2].y + 3) = bVar2 - bVar1;
        }
        *(short *)&source[2].z = *(short *)&source[2].z + -1;
        if (*(short *)&source[2].z < 1) {
          *(short *)(pfVar6 + 0xb) = *(short *)(pfVar6 + 0xb) + -1;
          *(undefined2 *)&source[2].z = 0;
        }
      }
      source = (Vec *)&source[3].y;
    }
  }
  return;
}

