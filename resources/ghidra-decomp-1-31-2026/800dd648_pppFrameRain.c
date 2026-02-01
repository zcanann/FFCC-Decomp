// Function: pppFrameRain
// Entry: 800dd648
// Size: 1072 bytes

/* WARNING: Removing unreachable block (ram,0x800dda5c) */
/* WARNING: Removing unreachable block (ram,0x800dda54) */
/* WARNING: Removing unreachable block (ram,0x800dda4c) */
/* WARNING: Removing unreachable block (ram,0x800dd668) */
/* WARNING: Removing unreachable block (ram,0x800dd660) */
/* WARNING: Removing unreachable block (ram,0x800dd658) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameRain(pppRain *pppRain,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  float fVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  short sVar10;
  uint uVar8;
  uint uVar9;
  int *piVar11;
  float *pfVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  
  if (DAT_8032ed70 == 0) {
    piVar11 = (int *)((int)(&pppRain->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    if (*piVar11 == 0) {
      iVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        ((uint)*(ushort *)&param_2->m_dataValIndex << 5,pppEnvStPtr->m_stagePtr,
                         s_pppRain_cpp_801db610,0x7f);
      *piVar11 = iVar7;
      dVar14 = (double)FLOAT_80331020;
      pfVar12 = (float *)*piVar11;
      dVar15 = DOUBLE_80331028;
      for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)&param_2->m_dataValIndex; iVar7 = iVar7 + 1) {
        uVar8 = rand();
        uVar9 = rand();
        fVar1 = *(float *)(param_2->m_payload + 0x34);
        fVar2 = *(float *)(param_2->m_payload + 0x24);
        dVar13 = (double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,
                                                                           uVar8 ^ 0x80000000) -
                                                         dVar15));
        *pfVar12 = (float)(dVar13 * (double)(float)((double)*(float *)(param_2->m_payload + 0x2c) -
                                                   (double)*(float *)(param_2->m_payload + 0x1c)) +
                          (double)*(float *)(param_2->m_payload + 0x1c));
        pfVar12[1] = *(float *)(param_2->m_payload + 0x30);
        pfVar12[2] = (float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000
                                                                      ) - dVar15)) * (fVar1 - fVar2)
                     + *(float *)(param_2->m_payload + 0x24);
        pfVar12[3] = -(float)param_2->m_initWOrk;
        pfVar12[4] = *(float *)(param_2->m_payload + 0x10);
        pfVar12[5] = -(float)param_2->m_arg3;
        PSVECNormalize((Vec *)(pfVar12 + 3),(Vec *)(pfVar12 + 3));
        uVar9 = uVar8 >> 0x1f;
        uVar5 = uVar8 & 1 ^ uVar9;
        fVar1 = (float)(dVar13 * (double)*(float *)(param_2->m_payload + 0x44));
        pfVar12[6] = *(float *)(param_2->m_payload + 0x40);
        if (uVar5 != uVar9) {
          fVar1 = -fVar1;
        }
        pfVar12[6] = pfVar12[6] + fVar1;
        uVar3 = *(ushort *)(param_2->m_payload + 0x16);
        *(undefined2 *)(pfVar12 + 7) = *(undefined2 *)(param_2->m_payload + 0x14);
        sVar6 = (short)uVar8 - (short)((int)uVar8 / (int)(uint)uVar3) * uVar3;
        sVar10 = -sVar6;
        if (uVar5 == uVar9) {
          sVar10 = sVar6;
        }
        *(short *)(pfVar12 + 7) = *(short *)(pfVar12 + 7) + sVar10;
        pfVar12 = pfVar12 + 8;
      }
    }
    piVar11[2] = (int)((float)piVar11[2] + (float)piVar11[3]);
    piVar11[1] = (int)((float)piVar11[1] + (float)piVar11[2]);
    if (param_2->m_graphId == (pppRain->field0_0x0).m_graphId) {
      piVar11[1] = (int)((float)piVar11[1] + *(float *)(param_2->m_payload + 4));
      piVar11[2] = (int)((float)piVar11[2] + *(float *)(param_2->m_payload + 8));
      piVar11[3] = (int)((float)piVar11[3] + *(float *)(param_2->m_payload + 0xc));
    }
    pfVar12 = (float *)*piVar11;
    for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)&param_2->m_dataValIndex; iVar7 = iVar7 + 1) {
      *pfVar12 = -(pfVar12[3] * (float)piVar11[1] - *pfVar12);
      pfVar12[1] = pfVar12[1] - *(float *)(param_2->m_payload + 0x10);
      pfVar12[2] = -(pfVar12[5] * (float)piVar11[1] - pfVar12[2]);
      *(short *)(pfVar12 + 7) = *(short *)(pfVar12 + 7) + -1;
      if (*(short *)(pfVar12 + 7) < 1) {
        uVar8 = rand();
        uVar9 = rand();
        fVar4 = FLOAT_80331020;
        fVar1 = *(float *)(param_2->m_payload + 0x34);
        dVar14 = (double)(FLOAT_80331020 *
                         (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - DOUBLE_80331028))
        ;
        fVar2 = *(float *)(param_2->m_payload + 0x24);
        dVar15 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - DOUBLE_80331028;
        *pfVar12 = (float)(dVar14 * (double)(float)((double)*(float *)(param_2->m_payload + 0x2c) -
                                                   (double)*(float *)(param_2->m_payload + 0x1c)) +
                          (double)*(float *)(param_2->m_payload + 0x1c));
        pfVar12[1] = *(float *)(param_2->m_payload + 0x30);
        pfVar12[2] = fVar4 * (float)dVar15 * (fVar1 - fVar2) + *(float *)(param_2->m_payload + 0x24)
        ;
        pfVar12[3] = -(float)param_2->m_initWOrk;
        pfVar12[4] = *(float *)(param_2->m_payload + 0x10);
        pfVar12[5] = -(float)param_2->m_arg3;
        PSVECNormalize((Vec *)(pfVar12 + 3),(Vec *)(pfVar12 + 3));
        uVar9 = uVar8 >> 0x1f;
        uVar5 = uVar8 & 1 ^ uVar9;
        fVar1 = (float)(dVar14 * (double)*(float *)(param_2->m_payload + 0x44));
        pfVar12[6] = *(float *)(param_2->m_payload + 0x40);
        if (uVar5 != uVar9) {
          fVar1 = -fVar1;
        }
        pfVar12[6] = pfVar12[6] + fVar1;
        uVar3 = *(ushort *)(param_2->m_payload + 0x16);
        *(undefined2 *)(pfVar12 + 7) = *(undefined2 *)(param_2->m_payload + 0x14);
        sVar6 = (short)uVar8 - (short)((int)uVar8 / (int)(uint)uVar3) * uVar3;
        sVar10 = -sVar6;
        if (uVar5 == uVar9) {
          sVar10 = sVar6;
        }
        *(short *)(pfVar12 + 7) = *(short *)(pfVar12 + 7) + sVar10;
      }
      pfVar12 = pfVar12 + 8;
    }
    if (DAT_8032ed78 == '\0') {
      fVar1 = (float)CameraPcs._212_4_;
      fVar2 = (float)CameraPcs._216_4_;
      fVar4 = (float)CameraPcs._220_4_;
      if (Game.game.m_currentSceneId == 7) {
        fVar1 = ppvCameraMatrix0.value[0][3];
        fVar2 = ppvCameraMatrix0.value[1][3];
        fVar4 = ppvCameraMatrix0.value[2][3];
      }
      (pppMngStPtr->m_matrix).value[0][3] = fVar1;
      (pppMngStPtr->m_matrix).value[1][3] = fVar2;
      (pppMngStPtr->m_matrix).value[2][3] = fVar4;
      pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
    }
  }
  return;
}

