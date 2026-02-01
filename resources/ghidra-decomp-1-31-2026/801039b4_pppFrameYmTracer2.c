// Function: pppFrameYmTracer2
// Entry: 801039b4
// Size: 1112 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmTracer2(pppYmTracer2 *pppYmTracer2,UnkB *param_2,UnkC *param_3)

{
  bool bVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  short sVar9;
  Vec *dest;
  Vec *pVVar10;
  uint uVar11;
  Vec *source;
  uint8_t *puVar12;
  Vec local_a8;
  Vec local_9c;
  Vec local_90;
  Vec local_84;
  Mtx MStack_78;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (DAT_8032ed70 == 0) {
    bVar1 = false;
    iVar4 = param_3->m_serializedDataOffsets[1];
    puVar12 = pppYmTracer2->m_serializedData + *param_3->m_serializedDataOffsets;
    if (param_2->m_initWOrk == 0xffffffff) {
      puVar7 = &DAT_801eadc8;
    }
    else {
      puVar7 = (undefined4 *)
               ((int)&pppMngStPtr->m_pppPDataVals[param_2->m_initWOrk].m_pppPObjLink[10].m_owner +
               (int)param_2->m_stepValue);
    }
    *(undefined4 **)(puVar12 + 0x20) = puVar7;
    if (param_2->m_arg3 == 0xffffffff) {
      puVar7 = &DAT_801eadc8;
    }
    else {
      puVar7 = (undefined4 *)
               ((int)&pppMngStPtr->m_pppPDataVals[param_2->m_arg3].m_pppPObjLink[10].m_owner +
               *(int *)param_2->m_payload);
    }
    *(undefined4 **)(puVar12 + 0x24) = puVar7;
    if (*(int *)(puVar12 + 0x28) == 0) {
      bVar1 = true;
      *(ushort *)(puVar12 + 0x30) =
           (ushort)param_2->m_payload[8] / *(ushort *)(param_2->m_payload + 6);
      uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        ((uint)*(ushort *)(param_2->m_payload + 4) * 0x28,pppEnvStPtr->m_stagePtr,
                         s_pppYmTracer2_cpp_801dc4b8,0xad);
      *(undefined4 *)(puVar12 + 0x28) = uVar5;
      fVar2 = FLOAT_80331840;
      pfVar6 = *(float **)(puVar12 + 0x28);
      for (iVar8 = 0; iVar8 < (int)(uint)*(ushort *)(param_2->m_payload + 4); iVar8 = iVar8 + 1) {
        *(undefined *)(pfVar6 + 8) = 0;
        *(undefined *)((int)pfVar6 + 0x1f) = 0;
        pfVar6[2] = fVar2;
        pfVar6[1] = fVar2;
        *pfVar6 = fVar2;
        pfVar6[6] = fVar2;
        pfVar6[5] = fVar2;
        pfVar6[4] = fVar2;
        pfVar6 = pfVar6 + 10;
      }
    }
    source = *(Vec **)(puVar12 + 0x28);
    *(undefined *)&source[2].z = 1;
    pVVar10 = source;
    for (uVar11 = 0; (int)uVar11 < (int)(param_2->m_payload[9] + 1); uVar11 = uVar11 + 1) {
      iVar8 = *(ushort *)(param_2->m_payload + 4) - 2;
      pfVar6 = (float *)((int)source + iVar8 * 0x28);
      for (; (int)uVar11 <= iVar8; iVar8 = iVar8 + -1) {
        *(undefined *)(pfVar6 + 0x12) = *(undefined *)(pfVar6 + 8);
        local_a8.x = *pfVar6;
        dest = (Vec *)((int)source + (iVar8 + 1) * 0x28);
        local_a8.y = pfVar6[1];
        local_a8.z = pfVar6[2];
        pppCopyVector__FR3Vec3Vec(dest,&local_a8);
        local_9c.x = pfVar6[4];
        local_9c.y = pfVar6[5];
        local_9c.z = pfVar6[6];
        pppCopyVector__FR3Vec3Vec((Vec *)&dest[1].y,&local_9c);
        *(undefined *)(pfVar6 + 0x11) = *(undefined *)(pfVar6 + 7);
        *(undefined *)((int)pfVar6 + 0x45) = *(undefined *)((int)pfVar6 + 0x1d);
        *(undefined *)((int)pfVar6 + 0x46) = *(undefined *)((int)pfVar6 + 0x1e);
        *(undefined *)((int)pfVar6 + 0x47) = *(undefined *)((int)pfVar6 + 0x1f);
        pfVar6 = pfVar6 + -10;
      }
      fVar2 = **(float **)(puVar12 + 0x20);
      *(float *)puVar12 = fVar2;
      pVVar10->x = fVar2;
      fVar2 = *(float *)(*(int *)(puVar12 + 0x20) + 4);
      *(float *)(puVar12 + 4) = fVar2;
      pVVar10->y = fVar2;
      fVar2 = *(float *)(*(int *)(puVar12 + 0x20) + 8);
      *(float *)(puVar12 + 8) = fVar2;
      pVVar10->z = fVar2;
      fVar2 = **(float **)(puVar12 + 0x24);
      *(float *)(puVar12 + 0x10) = fVar2;
      pVVar10[1].y = fVar2;
      fVar2 = *(float *)(*(int *)(puVar12 + 0x24) + 4);
      *(float *)(puVar12 + 0x14) = fVar2;
      pVVar10[1].z = fVar2;
      fVar2 = *(float *)(*(int *)(puVar12 + 0x24) + 8);
      *(float *)(puVar12 + 0x18) = fVar2;
      pVVar10[2].x = fVar2;
      *(uint8_t *)&pVVar10[2].y = pppYmTracer2->m_serializedData[iVar4 + 8];
      *(uint8_t *)((int)&pVVar10[2].y + 1) = pppYmTracer2->m_serializedData[iVar4 + 9];
      *(uint8_t *)((int)&pVVar10[2].y + 2) = pppYmTracer2->m_serializedData[iVar4 + 10];
      if (uVar11 == 0) {
        PSMTXConcat(&pppMngStPtr->m_matrix,&(pppYmTracer2->pppPObject).m_localMatrix,&MStack_78);
        PSMTXMultVec(&MStack_78,source,source);
        PSMTXMultVec(&MStack_78,(Vec *)&source[1].y,(Vec *)&source[1].y);
      }
      else if (!bVar1) {
        uStack_3c = uVar11 ^ 0x80000000;
        local_48 = 0x43300000;
        uStack_44 = param_2->m_payload[9] + 1 ^ 0x80000000;
        local_40 = 0x43300000;
        iVar8 = GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f
                          ((double)((FLOAT_80331860 /
                                    (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331858
                                           )) *
                                   (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331858)
                                   ),pppMngStPtr,&MStack_78);
        if (iVar8 == 0) {
          bVar1 = true;
        }
        else {
          PSMTXConcat(&MStack_78,&(pppYmTracer2->pppPObject).m_localMatrix,&MStack_78);
          PSMTXMultVec(&MStack_78,pVVar10,pVVar10);
          PSMTXMultVec(&MStack_78,(Vec *)&pVVar10[1].y,(Vec *)&pVVar10[1].y);
        }
      }
      pVVar10 = (Vec *)&pVVar10[3].y;
    }
    if (bVar1) {
      pVVar10 = source;
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(param_2->m_payload + 4); iVar4 = iVar4 + 1) {
        local_84.x = source->x;
        local_84.y = source->y;
        local_84.z = source->z;
        pppCopyVector__FR3Vec3Vec(pVVar10,&local_84);
        local_90.x = source[1].y;
        local_90.y = source[1].z;
        local_90.z = source[2].x;
        pppCopyVector__FR3Vec3Vec((Vec *)&pVVar10[1].y,&local_90);
        pVVar10 = (Vec *)&pVVar10[3].y;
      }
    }
    sVar9 = 0;
    for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(param_2->m_payload + 4); iVar4 = iVar4 + 1) {
      sVar3 = (ushort)param_2->m_payload[8] - (short)iVar4 * *(short *)(puVar12 + 0x30);
      if ((sVar3 < 0) || (bVar1 = *(char *)&source[2].z == '\0', bVar1)) {
        *(undefined *)((int)&source[2].y + 3) = 0;
      }
      else if (!bVar1) {
        *(char *)((int)&source[2].y + 3) = (char)sVar3;
        sVar9 = sVar9 + 1;
      }
      source = (Vec *)&source[3].y;
    }
    *(short *)(puVar12 + 0x2c) = sVar9;
  }
  return;
}

