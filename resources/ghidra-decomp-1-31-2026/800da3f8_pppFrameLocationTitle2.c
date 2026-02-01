// Function: pppFrameLocationTitle2
// Entry: 800da3f8
// Size: 1216 bytes

/* WARNING: Removing unreachable block (ram,0x800da89c) */
/* WARNING: Removing unreachable block (ram,0x800da894) */
/* WARNING: Removing unreachable block (ram,0x800da88c) */
/* WARNING: Removing unreachable block (ram,0x800da884) */
/* WARNING: Removing unreachable block (ram,0x800da420) */
/* WARNING: Removing unreachable block (ram,0x800da418) */
/* WARNING: Removing unreachable block (ram,0x800da410) */
/* WARNING: Removing unreachable block (ram,0x800da408) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameLocationTitle2(pppLocationTitle2 *pppLocationTitle2,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  CNode *pCVar4;
  uint uVar5;
  Vec *pVVar6;
  Vec *vecB;
  Vec *pVVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  CModel *model;
  int iVar11;
  int *piVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  Vec local_1e8;
  Vec local_1dc;
  Vec VStack_1d0;
  Vec VStack_1c4;
  Mtx MStack_1b8;
  Vec local_188 [21];
  undefined4 local_88;
  uint uStack_84;
  
  if (DAT_8032ed70 == 0) {
    iVar2 = param_3->m_serializedDataOffsets[1];
    piVar12 = (int *)((int)(&pppLocationTitle2->field0_0x0 + 2) + *param_3->m_serializedDataOffsets)
    ;
    rand();
    if (param_2->m_dataValIndex != 0xffff) {
      piVar12[3] = (int)((float)piVar12[3] + (float)piVar12[4]);
      piVar12[2] = (int)((float)piVar12[2] + (float)piVar12[3]);
      if (param_2->m_graphId == (pppLocationTitle2->field0_0x0).m_graphId) {
        piVar12[2] = (int)((float)piVar12[2] + (float)param_2->m_arg3);
        piVar12[3] = (int)((float)piVar12[3] + *(float *)param_2->m_payload);
        piVar12[4] = (int)((float)piVar12[4] + *(float *)(param_2->m_payload + 4));
      }
      if (*piVar12 == 0) {
        iVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                          ((uint)*(ushort *)((int)&param_2->m_initWOrk + 2) * 0x24,
                           pppEnvStPtr->m_stagePtr,s_LocationTitle2_cpp_801db588,0x70);
        *piVar12 = iVar3;
        memset(*piVar12,0,(uint)*(ushort *)((int)&param_2->m_initWOrk + 2) * 0x24);
        iVar11 = *piVar12;
        iVar1 = *(int *)((int)(pppMngStPtr->m_velocity).y + 0xf8);
        iVar3 = 0;
        if (iVar1 != 0) {
          iVar3 = iVar1;
        }
        model = (CModel *)0x0;
        if (*(CModel **)(iVar3 + 0x168) != (CModel *)0x0) {
          model = *(CModel **)(iVar3 + 0x168);
        }
        iVar3 = SearchNode__Q26CChara6CModelFPc(model,&DAT_80330f50);
        pCVar4 = model->m_nodes;
        dVar16 = (double)FLOAT_80330f4c;
        dVar15 = DOUBLE_80330f58;
        for (uVar10 = 0; uVar10 < *(ushort *)(model->m_anim + 0x10); uVar10 = uVar10 + 1) {
          CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(pCVar4 + iVar3,model);
          uStack_84 = uVar10 ^ 0x80000000;
          local_88 = 0x43300000;
          SetFrame__Q26CChara6CModelFf
                    ((float)((double)CONCAT44(0x43300000,uStack_84) - dVar15),model);
          CalcMatrix__Q26CChara6CModelFv(model);
          PSMTXCopy((Mtx *)(pCVar4[iVar3].unk_0x8_0x43 + 0xc),&MStack_1b8);
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24) = MStack_1b8.value[0][3];
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 4) = MStack_1b8.value[1][3];
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 8) = MStack_1b8.value[2][3];
          iVar1 = (uint)*(ushort *)(piVar12 + 1) * 0x24 + 8;
          *(float *)(iVar11 + iVar1) = (float)((double)*(float *)(iVar11 + iVar1) + dVar16);
          memcpy((void *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0xc),
                 &pppLocationTitle2->field_0x88 + iVar2,4);
          *(undefined2 *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x1e) = 0;
          *(undefined2 *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x22) = 0;
          *(undefined2 *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x20) = 0;
          *(short *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x1c) = (short)uVar10;
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x10) =
               (pppLocationTitle2->field0_0x0).m_localMatrix.value[0][0];
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x14) =
               (pppLocationTitle2->field0_0x0).m_localMatrix.value[1][1];
          *(float *)(iVar11 + (uint)*(ushort *)(piVar12 + 1) * 0x24 + 0x18) =
               (pppLocationTitle2->field0_0x0).m_localMatrix.value[2][2];
          *(short *)(piVar12 + 1) = *(short *)(piVar12 + 1) + 1;
          uVar5 = (uint)*(ushort *)(piVar12 + 1);
          if ((uint)*(ushort *)((int)&param_2->m_initWOrk + 2) <= uVar5 + 1) {
            return;
          }
          if (1 < uVar5) {
            iVar8 = uVar5 - 2;
            uStack_84 = *(byte *)&param_2->m_stepValue + 1 ^ 0x80000000;
            local_88 = 0x43300000;
            iVar9 = 0;
            vecB = (Vec *)(iVar11 + iVar8 * 0x24);
            dVar13 = (double)(FLOAT_80330f4c /
                             (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80330f58));
            PSVECSubtract((Vec *)(iVar11 + (uVar5 - 1) * 0x24),vecB,&VStack_1c4);
            pVVar6 = local_188;
            pVVar7 = pVVar6;
            dVar14 = DOUBLE_80330f58;
            for (iVar1 = 0; iVar1 < (int)(uint)*(byte *)&param_2->m_stepValue; iVar1 = iVar1 + 1) {
              local_88 = 0x43300000;
              uStack_84 = iVar1 + 1U ^ 0x80000000;
              PSVECScale((float)(dVar13 * (double)(float)((double)CONCAT44(0x43300000,uStack_84) -
                                                         dVar14)),&VStack_1c4,&VStack_1d0);
              PSVECAdd(vecB,&VStack_1d0,pVVar7);
              iVar9 = iVar9 + 1;
              *(short *)(piVar12 + 1) = *(short *)(piVar12 + 1) + 1;
              if ((uint)*(ushort *)((int)&param_2->m_initWOrk + 2) <= *(ushort *)(piVar12 + 1) + 1)
              break;
              pVVar7 = pVVar7 + 1;
            }
            local_1dc.x = vecB[3].x;
            local_1dc.y = vecB[3].y;
            local_1dc.z = vecB[3].z;
            pppCopyVector__FR3Vec3Vec((Vec *)(iVar11 + (iVar8 + iVar9 + 1) * 0x24),&local_1dc);
            dVar14 = (double)FLOAT_80330f4c;
            for (iVar1 = 0; iVar1 < iVar9; iVar1 = iVar1 + 1) {
              pVVar6->z = (float)((double)pVVar6->z + dVar14);
              pVVar7 = (Vec *)(iVar11 + (iVar8 + iVar1 + 1) * 0x24);
              local_1e8.x = pVVar6->x;
              local_1e8.y = pVVar6->y;
              local_1e8.z = pVVar6->z;
              pppCopyVector__FR3Vec3Vec(pVVar7,&local_1e8);
              memcpy(pVVar7 + 1,&pppLocationTitle2->field_0x88 + iVar2,4);
              pVVar6 = pVVar6 + 1;
              *(undefined2 *)((int)&pVVar7[2].y + 2) = 0;
              *(undefined2 *)((int)&pVVar7[2].z + 2) = 0;
              *(undefined2 *)&pVVar7[2].z = 0;
              pVVar7[1].y = (pppLocationTitle2->field0_0x0).m_localMatrix.value[0][0];
              pVVar7[1].z = (pppLocationTitle2->field0_0x0).m_localMatrix.value[1][1];
              pVVar7[2].x = (pppLocationTitle2->field0_0x0).m_localMatrix.value[2][2];
              *(short *)&pVVar7[2].y = (short)uVar10;
            }
          }
        }
        SetFrame__Q26CChara6CModelFf(FLOAT_80330f48,model);
      }
    }
  }
  return;
}

