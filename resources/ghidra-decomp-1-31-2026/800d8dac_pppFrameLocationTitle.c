// Function: pppFrameLocationTitle
// Entry: 800d8dac
// Size: 1228 bytes

/* WARNING: Removing unreachable block (ram,0x800d925c) */
/* WARNING: Removing unreachable block (ram,0x800d9254) */
/* WARNING: Removing unreachable block (ram,0x800d8dc4) */
/* WARNING: Removing unreachable block (ram,0x800d8dbc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameLocationTitle(pppLocationTitle *pppLocationTitle,UnkB *param_2,UnkC *param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  Vec *pVVar5;
  int iVar6;
  float *pfVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  Vec *pVVar11;
  Vec *vecB;
  double dVar12;
  double dVar13;
  Vec local_378;
  Vec local_36c;
  Vec VStack_360;
  Vec VStack_354;
  pppFMATRIX local_348;
  pppFMATRIX local_318;
  pppFMATRIX pStack_2e8;
  Vec local_2b8 [50];
  undefined4 local_60;
  uint uStack_5c;
  
  if (DAT_8032ed70 == 0) {
    iVar2 = param_3->m_serializedDataOffsets[1];
    piVar8 = (int *)((int)(&pppLocationTitle->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    rand();
    if (param_2->m_dataValIndex != 0xffff) {
      iVar9 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                        param_2->m_dataValIndex * 4);
      piVar8[3] = (int)((float)piVar8[3] + (float)piVar8[4]);
      piVar8[2] = (int)((float)piVar8[2] + (float)piVar8[3]);
      if (param_2->m_graphId == (pppLocationTitle->field0_0x0).m_graphId) {
        piVar8[2] = (int)((float)piVar8[2] + (float)param_2->m_arg3);
        piVar8[3] = (int)((float)piVar8[3] + *(float *)param_2->m_payload);
        piVar8[4] = (int)((float)piVar8[4] + *(float *)(param_2->m_payload + 4));
      }
      if (*piVar8 == 0) {
        iVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                          ((uint)*(ushort *)((int)&param_2->m_initWOrk + 2) * 0x1c,
                           pppEnvStPtr->m_stagePtr,s_pppLocationTitle_cpp_801db510,0x6d);
        *piVar8 = iVar3;
        dVar13 = (double)FLOAT_80330ee0;
        pfVar7 = (float *)*piVar8;
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)((int)&param_2->m_initWOrk + 2);
            iVar3 = iVar3 + 1) {
          *pfVar7 = (float)dVar13;
          pfVar7[1] = (float)dVar13;
          pfVar7[2] = (float)dVar13;
          memcpy(pfVar7 + 3,&pppLocationTitle->field_0x88 + iVar2,4);
          *(undefined2 *)(pfVar7 + 5) = 0;
          pfVar7[4] = (float)piVar8[2];
          iVar6 = rand();
          sVar1 = *(short *)(iVar9 + 6);
          sVar1 = (short)iVar6 - (short)(iVar6 / (int)sVar1) * sVar1;
          *(short *)(pfVar7 + 6) = sVar1;
          *(short *)((int)pfVar7 + 0x16) = sVar1;
          pfVar7 = pfVar7 + 7;
        }
      }
      iVar9 = *piVar8;
      if ((*(ushort *)(piVar8 + 1) + 1 < (uint)*(ushort *)((int)&param_2->m_initWOrk + 2)) &&
         (uVar4 = (pppLocationTitle->field0_0x0).m_graphId,
         (int)(uint)*(ushort *)(param_2->m_payload + 8) <=
         (int)(((int)uVar4 >> 0xc) + (uint)((int)uVar4 < 0 && (uVar4 & 0xfff) != 0)))) {
        local_348.value[0][0] = (pppLocationTitle->field0_0x0).m_localMatrix.value[0][0];
        local_348.value[0][1] = (pppLocationTitle->field0_0x0).m_localMatrix.value[0][1];
        local_348.value[0][2] = (pppLocationTitle->field0_0x0).m_localMatrix.value[0][2];
        local_348.value[0][3] = (pppLocationTitle->field0_0x0).m_localMatrix.value[0][3];
        local_348.value[1][0] = (pppLocationTitle->field0_0x0).m_localMatrix.value[1][0];
        local_348.value[1][1] = (pppLocationTitle->field0_0x0).m_localMatrix.value[1][1];
        local_348.value[1][2] = (pppLocationTitle->field0_0x0).m_localMatrix.value[1][2];
        local_348.value[1][3] = (pppLocationTitle->field0_0x0).m_localMatrix.value[1][3];
        local_348.value[2][0] = (pppLocationTitle->field0_0x0).m_localMatrix.value[2][0];
        local_348.value[2][1] = (pppLocationTitle->field0_0x0).m_localMatrix.value[2][1];
        local_348.value[2][2] = (pppLocationTitle->field0_0x0).m_localMatrix.value[2][2];
        local_348.value[2][3] = (pppLocationTitle->field0_0x0).m_localMatrix.value[2][3];
        local_318.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
        local_318.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
        local_318.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
        local_318.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
        local_318.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
        local_318.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
        local_318.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
        local_318.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
        local_318.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
        local_318.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
        local_318.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
        local_318.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&pStack_2e8,&local_318,&local_348);
        *(float *)(iVar9 + (uint)*(ushort *)(piVar8 + 1) * 0x1c) = pStack_2e8.value[0][3];
        *(float *)(iVar9 + (uint)*(ushort *)(piVar8 + 1) * 0x1c + 4) = pStack_2e8.value[1][3];
        *(float *)(iVar9 + (uint)*(ushort *)(piVar8 + 1) * 0x1c + 8) = pStack_2e8.value[2][3];
        uVar4 = (uint)*(ushort *)(piVar8 + 1);
        if ((int)(uVar4 - 1) < 0) {
          *(int *)(iVar9 + uVar4 * 0x1c + 0x10) = piVar8[2];
          memcpy((void *)(iVar9 + (uint)*(ushort *)(piVar8 + 1) * 0x1c + 0xc),
                 &pppLocationTitle->field_0x88 + iVar2,4);
        }
        else {
          *(int *)(iVar9 + uVar4 * 0x1c + -0xc) = piVar8[2];
          memcpy((void *)(iVar9 + (*(ushort *)(piVar8 + 1) - 1) * 0x1c + 0xc),
                 &pppLocationTitle->field_0x88 + iVar2,4);
        }
        *(short *)(piVar8 + 1) = *(short *)(piVar8 + 1) + 1;
        uVar4 = (uint)*(ushort *)(piVar8 + 1);
        if (1 < uVar4) {
          iVar3 = uVar4 - 2;
          uStack_5c = *(byte *)&param_2->m_stepValue + 1 ^ 0x80000000;
          local_60 = 0x43300000;
          iVar6 = 0;
          vecB = (Vec *)(iVar9 + iVar3 * 0x1c);
          dVar12 = (double)(FLOAT_80330ee4 /
                           (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330ee8));
          PSVECSubtract((Vec *)(iVar9 + (uVar4 - 1) * 0x1c),vecB,&VStack_354);
          pVVar11 = local_2b8;
          pVVar5 = pVVar11;
          dVar13 = DOUBLE_80330ee8;
          for (iVar10 = 0; iVar10 < (int)(uint)*(byte *)&param_2->m_stepValue; iVar10 = iVar10 + 1)
          {
            local_60 = 0x43300000;
            uStack_5c = iVar10 + 1U ^ 0x80000000;
            PSVECScale((float)(dVar12 * (double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                       dVar13)),&VStack_354,&VStack_360);
            PSVECAdd(vecB,&VStack_360,pVVar5);
            iVar6 = iVar6 + 1;
            *(short *)(piVar8 + 1) = *(short *)(piVar8 + 1) + 1;
            if ((uint)*(ushort *)((int)&param_2->m_initWOrk + 2) <= *(ushort *)(piVar8 + 1) + 1)
            break;
            pVVar5 = pVVar5 + 1;
          }
          iVar10 = iVar9 + iVar3 * 0x1c;
          local_36c.x = *(float *)(iVar10 + 0x1c);
          local_36c.y = *(float *)(iVar10 + 0x20);
          local_36c.z = *(float *)(iVar10 + 0x24);
          pppCopyVector__FR3Vec3Vec((Vec *)(iVar9 + (iVar3 + iVar6 + 1) * 0x1c),&local_36c);
          for (iVar10 = 0; iVar10 < iVar6; iVar10 = iVar10 + 1) {
            local_378.x = pVVar11->x;
            local_378.y = pVVar11->y;
            local_378.z = pVVar11->z;
            pVVar5 = (Vec *)(iVar9 + (iVar3 + iVar10 + 1) * 0x1c);
            pppCopyVector__FR3Vec3Vec(pVVar5,&local_378);
            memcpy(pVVar5 + 1,&pppLocationTitle->field_0x88 + iVar2,4);
            pVVar11 = pVVar11 + 1;
            pVVar5[1].y = (float)piVar8[2];
          }
        }
      }
    }
  }
  return;
}

