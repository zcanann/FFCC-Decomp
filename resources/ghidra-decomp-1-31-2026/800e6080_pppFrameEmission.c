// Function: pppFrameEmission
// Entry: 800e6080
// Size: 1040 bytes

/* WARNING: Removing unreachable block (ram,0x800e6474) */
/* WARNING: Removing unreachable block (ram,0x800e646c) */
/* WARNING: Removing unreachable block (ram,0x800e6464) */
/* WARNING: Removing unreachable block (ram,0x800e60a0) */
/* WARNING: Removing unreachable block (ram,0x800e6098) */
/* WARNING: Removing unreachable block (ram,0x800e6090) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameEmission(pppEmission *pppEmission,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  float fVar2;
  CCharaPcsCHandle *handle;
  int iVar3;
  short sVar5;
  int iVar4;
  short sVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  float *pfVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined4 local_68 [2];
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  
  if (DAT_8032ed70 == 0) {
    iVar7 = param_3->m_serializedDataOffsets[1];
    piVar9 = (int *)((int)(&pppEmission->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    handle = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar3 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(int **)(iVar3 + 0xe4) = piVar9;
    *(UnkB **)(iVar3 + 0xe8) = param_2;
    dVar12 = DOUBLE_803311e8;
    *(code **)(iVar3 + 0xfc) = Emission_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    fVar2 = FLOAT_803311e0;
    *(code **)(iVar3 + 0x104) = Emission_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    uStack_5c = (uint)(byte)(&pppEmission->field_0x8b)[iVar7];
    local_60 = 0x43300000;
    *(undefined *)(piVar9 + 2) = (&pppEmission->field_0x88)[iVar7];
    dVar12 = (double)((float)((double)CONCAT44(0x43300000,uStack_5c) - dVar12) / fVar2);
    *(undefined *)((int)piVar9 + 9) = (&pppEmission->field_0x89)[iVar7];
    *(undefined *)((int)piVar9 + 10) = (&pppEmission->field_0x8a)[iVar7];
    *(undefined *)((int)piVar9 + 0xb) = (&pppEmission->field_0x8b)[iVar7];
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (param_2->m_stepValue,&pppEmission->field0_0x0,param_2->m_graphId,piVar9 + 3,
               piVar9 + 4,piVar9 + 5,&param_2->m_arg3,param_2->m_payload);
    if (DAT_8032ed78 == '\0') {
      local_68[0] = 0;
      if (param_2->m_dataValIndex != 0xffff) {
        iVar3 = GetTexture__8CMapMeshFP12CMaterialSetRi
                          (pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],
                           pppEnvStPtr->m_materialSetPtr,local_68);
        piVar9[1] = iVar3;
        if (param_2->m_payload[9] != '\0') {
          if (*piVar9 == 0) {
            *(byte *)(piVar9 + 7) = param_2->m_payload[0xb] / param_2->m_payload[0xc];
            iVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                              ((uint)*(byte *)&param_2->m_initWOrk << 4,pppEnvStPtr->m_stagePtr,
                               s_pppEmission_cpp_801db7e8,0x16f);
            *piVar9 = iVar3;
            pfVar10 = (float *)*piVar9;
            dVar14 = (double)FLOAT_803311e4;
            dVar13 = DOUBLE_803311f0;
            for (uVar8 = 0; (int)uVar8 < (int)(uint)*(byte *)&param_2->m_initWOrk; uVar8 = uVar8 + 1
                ) {
              RandF__5CMathFf((double)FLOAT_803311e4,&Math);
              iVar3 = rand();
              sVar5 = (short)iVar3 -
                      (short)(iVar3 / (int)(uint)param_2->m_payload[0xd]) *
                      (ushort)param_2->m_payload[0xd];
              sVar6 = 1;
              if (0 < sVar5) {
                sVar6 = sVar5;
              }
              *(ushort *)(pfVar10 + 3) = (ushort)param_2->m_payload[0xf] + sVar6;
              sVar5 = (ushort)param_2->m_payload[0xc] + sVar6;
              *(short *)((int)pfVar10 + 10) = *(short *)(pfVar10 + 3) + sVar6 + sVar5;
              dVar11 = (double)RandF__5CMathFf((double)*(float *)(param_2->m_payload + 4),&Math);
              uStack_5c = uVar8 ^ 0x80000000;
              local_60 = 0x43300000;
              *pfVar10 = (float)((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - dVar13) *
                                 dVar11 + dVar14);
              *(undefined2 *)(pfVar10 + 1) = 0;
              *(char *)((int)pfVar10 + 0xe) =
                   (char)((int)(uint)param_2->m_payload[0xb] / (int)sVar5);
              pfVar10 = pfVar10 + 4;
            }
          }
          pfVar10 = (float *)*piVar9;
          dVar13 = DOUBLE_803311f0;
          for (iVar3 = 0; iVar3 < (int)(uint)*(byte *)&param_2->m_initWOrk; iVar3 = iVar3 + 1) {
            dVar14 = (double)RandF__5CMathFf((double)*(float *)(param_2->m_payload + 4),&Math);
            *pfVar10 = *pfVar10 + (float)((double)(float)piVar9[3] + dVar14);
            if (*(short *)(pfVar10 + 3) < 1) {
              if (*(short *)((int)pfVar10 + 10) < (short)(ushort)param_2->m_payload[0xc]) {
                *(ushort *)(pfVar10 + 1) =
                     *(short *)(pfVar10 + 1) - (ushort)*(byte *)((int)pfVar10 + 0xe);
              }
              else {
                *(ushort *)(pfVar10 + 1) = (ushort)param_2->m_payload[0xb];
              }
            }
            else {
              *(short *)(pfVar10 + 3) = *(short *)(pfVar10 + 3) + -1;
              *(ushort *)(pfVar10 + 1) =
                   *(short *)(pfVar10 + 1) +
                   (ushort)param_2->m_payload[0xb] / (ushort)param_2->m_payload[0xf];
            }
            uStack_5c = (int)*(short *)(pfVar10 + 1) ^ 0x80000000;
            local_60 = 0x43300000;
            *(short *)((int)pfVar10 + 10) = *(short *)((int)pfVar10 + 10) + -1;
            iVar1 = (int)((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - dVar13) * dVar12)
            ;
            local_58 = (longlong)iVar1;
            if (*(short *)((int)pfVar10 + 10) < 1) {
              sVar6 = 0;
              if (param_2->m_payload[0xd] != '\0') {
                iVar4 = rand();
                sVar6 = (short)iVar4 -
                        (short)(iVar4 / (int)(uint)param_2->m_payload[0xd]) *
                        (ushort)param_2->m_payload[0xd];
              }
              *(ushort *)(pfVar10 + 3) = (ushort)param_2->m_payload[0xf];
              *(ushort *)((int)pfVar10 + 10) =
                   (ushort)param_2->m_payload[0xf] +
                   (ushort)param_2->m_payload[0xe] + sVar6 + (ushort)param_2->m_payload[0xc];
              dVar14 = (double)RandF__5CMathFf((double)*(float *)(param_2->m_payload + 4),&Math);
              *pfVar10 = (float)((double)FLOAT_803311e4 + dVar14);
              *(undefined2 *)(pfVar10 + 1) = 0;
              *(byte *)((int)pfVar10 + 0xe) = param_2->m_payload[0xb] / param_2->m_payload[0xc];
            }
            *(undefined *)((int)pfVar10 + 6) = (&pppEmission->field_0x88)[iVar7];
            *(undefined *)((int)pfVar10 + 7) = (&pppEmission->field_0x89)[iVar7];
            *(undefined *)(pfVar10 + 2) = (&pppEmission->field_0x8a)[iVar7];
            *(char *)((int)pfVar10 + 9) = (char)iVar1;
            pfVar10 = pfVar10 + 4;
          }
          DCFlushRange(piVar9 + 2,4);
        }
      }
    }
  }
  return;
}

