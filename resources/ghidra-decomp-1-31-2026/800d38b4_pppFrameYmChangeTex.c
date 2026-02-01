// Function: pppFrameYmChangeTex
// Entry: 800d38b4
// Size: 1264 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmChangeTex(pppYmChangeTex *pppYmChangeTex,UnkB *param_2,UnkC *param_3)

{
  CCharaPcsCHandle *pCVar1;
  int iVar2;
  float fVar3;
  CCharaPcsCHandle *handle;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined uVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  float *pfVar16;
  undefined4 *puVar17;
  int iVar18;
  int *piVar19;
  int iVar20;
  Mtx MStack_78;
  undefined4 local_48;
  uint uStack_44;
  undefined8 local_40;
  
  if (DAT_8032ed70 == 0) {
    pfVar16 = (float *)((int)(&pppYmChangeTex->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]
                       );
    pCVar1 = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1);
    pfVar16[6] = (pppMngStPtr->m_velocity).x;
    pfVar16[9] = (float)pppEnvStPtr;
    *(float **)(iVar2 + 0xe4) = pfVar16;
    *(UnkB **)(iVar2 + 0xe8) = param_2;
    *(code **)(iVar2 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    *(code **)(iVar2 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    fVar3 = (float)GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
    pfVar16[7] = fVar3;
    pCVar1 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl((CGObject *)pfVar16[6],1);
    handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl((CGObject *)pfVar16[6],2);
    if ((pCVar1 != (CCharaPcsCHandle *)0x0) &&
       (iVar4 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1), iVar4 != 0)) {
      *(float **)(iVar4 + 0xe4) = pfVar16;
      *(UnkB **)(iVar4 + 0xe8) = param_2;
      *(code **)(iVar4 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      *(code **)(iVar4 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    }
    if ((handle != (CCharaPcsCHandle *)0x0) &&
       (iVar4 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle), iVar4 != 0)) {
      *(float **)(iVar4 + 0xe4) = pfVar16;
      *(UnkB **)(iVar4 + 0xe8) = param_2;
      *(code **)(iVar4 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      *(code **)(iVar4 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    }
    if (param_2->m_payload[0] != '\0') {
      pfVar16[1] = pfVar16[1] + pfVar16[2];
      *pfVar16 = *pfVar16 + pfVar16[1];
      if (param_2->m_graphId == (pppYmChangeTex->field0_0x0).m_graphId) {
        *pfVar16 = *pfVar16 + (float)param_2->m_initWOrk;
        pfVar16[1] = pfVar16[1] + param_2->m_stepValue;
        pfVar16[2] = pfVar16[2] + (float)param_2->m_arg3;
      }
      fVar3 = (float)GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
      if (fVar3 != 0.0) {
        pfVar16[7] = fVar3;
        iVar4 = *(int *)(iVar2 + 0xac);
        if ((pfVar16[3] == 0.0) && (pfVar16[4] == 0.0)) {
          fVar3 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                                   (*(int *)(*(int *)(iVar2 + 0xa4) + 0xc) << 2,
                                    pppEnvStPtr->m_stagePtr,s_pppYmChangeTex_cpp_801db4c0,0x15d);
          pfVar16[3] = fVar3;
          fVar3 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                                   (*(int *)(*(int *)(iVar2 + 0xa4) + 0xc) << 2,
                                    pppEnvStPtr->m_stagePtr,s_pppYmChangeTex_cpp_801db4c0,0x160);
          pfVar16[4] = fVar3;
          puVar17 = (undefined4 *)pfVar16[3];
          iVar18 = 0;
          for (uVar13 = 0; uVar13 < *(uint *)(*(int *)(iVar2 + 0xa4) + 0xc); uVar13 = uVar13 + 1) {
            uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                              (*(int *)(*(int *)(iVar4 + 8) + 0x4c) << 2,pppEnvStPtr->m_stagePtr,
                               s_pppYmChangeTex_cpp_801db4c0,0x168);
            *(undefined4 *)((int)pfVar16[4] + iVar18) = uVar5;
            iVar9 = *(int *)(*(int *)(iVar4 + 8) + 0x4c) + -1;
            puVar15 = *(undefined4 **)(*(int *)(iVar4 + 8) + 0x50);
            piVar19 = (int *)(*(int *)((int)pfVar16[4] + iVar18) + iVar9 * 4);
            for (; -1 < iVar9; iVar9 = iVar9 + -1) {
              iVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (8,pppEnvStPtr->m_stagePtr,s_pppYmChangeTex_cpp_801db4c0,0x172);
              *piVar19 = iVar7;
              *(undefined4 *)(*piVar19 + 4) = *puVar15;
              uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (*puVar15,pppEnvStPtr->m_stagePtr,s_pppYmChangeTex_cpp_801db4c0,
                                 0x174);
              *(undefined4 *)*piVar19 = uVar5;
              memcpy(*(void **)*piVar19,puVar15[1],*puVar15);
              ReWriteDisplayList__5CUtilFPvUlUl
                        ((CUtil *)&DAT_8032ec70,*(undefined4 *)*piVar19,*puVar15,1);
              DCFlushRange(*(undefined4 *)*piVar19,*puVar15);
              piVar19 = piVar19 + -1;
              puVar15 = puVar15 + 3;
            }
            uVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                              (*(int *)(*(int *)(iVar4 + 8) + 0x14) << 2,pppEnvStPtr->m_stagePtr,
                               s_pppYmChangeTex_cpp_801db4c0,0x17f);
            *puVar17 = uVar5;
            memset(*puVar17,0xff,*(int *)(*(int *)(iVar4 + 8) + 0x14) << 2);
            iVar18 = iVar18 + 4;
            puVar17 = puVar17 + 1;
            iVar4 = iVar4 + 0x14;
          }
        }
        local_48 = 0x43300000;
        uStack_44 = 1 << *(int *)(*(int *)(iVar2 + 0xa4) + 0x34) ^ 0x80000000;
        iVar18 = *(int *)(iVar2 + 0xac);
        iVar4 = (int)(*pfVar16 * (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330e08));
        local_40 = (double)(longlong)iVar4;
        PSMTXCopy((Mtx *)(iVar2 + 0x68),&MStack_78);
        if ((param_2->m_payload[0] == '\x02') || (param_2->m_payload[0] == '\x01')) {
          uVar10 = 0;
          cVar11 = -1;
        }
        else {
          uVar10 = 0xff;
          cVar11 = '\0';
        }
        iVar9 = 0;
        for (uVar13 = 0; uVar13 < *(uint *)(*(int *)(iVar2 + 0xa4) + 0xc); uVar13 = uVar13 + 1) {
          iVar7 = 0;
          iVar8 = *(int *)((int)pfVar16[3] + iVar9);
          for (uVar12 = 0; uVar12 < *(uint *)(*(int *)(iVar18 + 8) + 0x14); uVar12 = uVar12 + 1) {
            uVar6 = (int)(short)iVar4 - (int)*(short *)(*(int *)(iVar18 + 0xc) + iVar7 + 2);
            if ((int)uVar6 < 0) {
              *(undefined *)(iVar8 + 3) = uVar10;
            }
            else {
              iVar14 = 0;
              iVar20 = 7;
              fVar3 = FLOAT_80330df8;
              do {
                local_40 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
                if (FLOAT_80330dfc * fVar3 < (float)(local_40 - DOUBLE_80330e08)) {
                  if (cVar11 == -1) {
                    *(char *)(iVar8 + 3) = -1 - (char)(iVar14 << 4);
                  }
                  else {
                    *(char *)(iVar8 + 3) = (char)(iVar14 << 4);
                  }
                  break;
                }
                fVar3 = fVar3 - FLOAT_80330e00;
                iVar14 = iVar14 + 1;
                iVar20 = iVar20 + -1;
              } while (iVar20 != 0);
            }
            iVar7 = iVar7 + 6;
            iVar8 = iVar8 + 4;
          }
          iVar9 = iVar9 + 4;
          iVar18 = iVar18 + 0x14;
        }
      }
    }
  }
  return;
}

